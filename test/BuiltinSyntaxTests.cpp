/*
 * ReaderTests.cpp
 *
 * Use the reader for generating test input data for the evaluator.
 * Not really clean, but easy
 *
 *  Created on: 08.10.2016
 *      Author: yael
 */


#include "gtest/gtest.h"

// "name-mangling" problem: linking c functions within c++ environment
extern "C" {
#include "reader.h"
#include "evaluator.h"
#include "printer.h"
}


class BuiltinSyntaxTests: public ::testing::Test {
public:
	// use this stream/pipe to write to normal stdin (instead of creating own stream)
	// found at http://stackoverflow.com/questions/4393416/c-need-to-simulate-stdin-within-the-code-when-calling-a-function
	FILE *stdin_writer;

	// SetUp
	BuiltinSyntaxTests() {
		// initialize ybscheme
		initGlobals();
		initReader();
		initEvaluator();

		// prepare a pipe for writing into stdin
		int p[2];
		// error return checks omitted
		pipe(p);
		dup2(p[0], STDIN_FILENO);
		stdin_writer = fdopen(p[1], "w");
	}

	// TearDown
	~BuiltinSyntaxTests() {
		fclose(stdin_writer);
	}

	// wrapper for writing to stdin
	void write(const char *format, ...) {
	    va_list args;
	    va_start(args, format);

		vfprintf(stdin_writer, format, args);
		fflush(stdin_writer);

		va_end(args);
	}
	void writeln(const char *format, ...) {
	    va_list args;
	    va_start(args, format);

		vfprintf(stdin_writer, format, args);
		fprintf(stdin_writer, "\n");
		fflush(stdin_writer);

		va_end(args);
	}
};

// #### if #######################################################################################


TEST_F(BuiltinSyntaxTests, If_WorksWith3ArgsTrue) {

	writeln("(if #t 1 2)");

	OBJ ro = ybRead(stdin);
	//ybPrint(ro);
	OBJ o  = ybEval(NULL, ro);
	//ybPrint(o);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(1, (o->u.number.value.i));
}

TEST_F(BuiltinSyntaxTests, If_WorksWith3ArgsFalse) {

	writeln("(if #f 1 2)");

	OBJ ro = ybRead(stdin);
	//ybPrint(ro);
	OBJ o  = ybEval(NULL, ro);
	//ybPrint(o);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(2, (o->u.number.value.i));
}

TEST_F(BuiltinSyntaxTests, If_WorksWith2ArgsTrue) {

	writeln("(if #t 1)");

	OBJ ro = ybRead(stdin);
	//ybPrint(ro);
	OBJ o  = ybEval(NULL, ro);
	//ybPrint(o);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(1, (o->u.number.value.i));
}

TEST_F(BuiltinSyntaxTests, If_WorksWith2ArgsFalse) {

	writeln("(if #f 1)");

	OBJ ro = ybRead(stdin);
	//ybPrint(ro);
	OBJ o  = ybEval(NULL, ro);
	//ybPrint(o);

	EXPECT_EQ(T_NIL, TYPE(o));
}

TEST_F(BuiltinSyntaxTests, If_eqOp2Numbers) {

	writeln("(if (= 3 3) 1)");

	OBJ ro = ybRead(stdin);
	//ybPrint(ro);
	OBJ o  = ybEval(NULL, ro);
	//ybPrint(o);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(1, (o->u.number.value.i));
}

// #### lambda #######################################################################################

// > ((lambda (x) x) 10)
// 10
TEST_F(BuiltinSyntaxTests, lambda_returnParameter) {

	writeln("((lambda (x) x) 10)");

	OBJ ro = ybRead(stdin);
	//ybPrint(ro);
	OBJ o  = ybEval(NULL, ro);
	//ybPrint(o);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(10, (o->u.number.value.i));
}

// > ((lambda (x y) (* x y)) 10 2)
// 20
TEST_F(BuiltinSyntaxTests, lambda_2paramsReturnMult) {

	writeln("((lambda (x y) (* x y)) 10 2)");

	OBJ ro = ybRead(stdin);
	//ybPrint(ro);
	OBJ o  = ybEval(NULL, ro);
	//ybPrint(o);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(20, (o->u.number.value.i));
}

// > ((lambda (x y) (list y x)) 1 2)
// '(2 1)


// > ((lambda (x [y 5]) (list y x)) 1 2)
// '(2 1)

/*
> (let ([f (lambda (x #:arg y) (list y x))])
   (list (f 1 #:arg 2)
         (f #:arg 2 1)))

'((2 1) (2 1))
*/
