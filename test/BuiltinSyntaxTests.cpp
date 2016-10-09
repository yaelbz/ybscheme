/*
 * BuiltinSyntaxTests.cpp
 *
 * Use the reader for generating test input data for the evaluator.
 * Not really clean, but easy
 *
 *  Created on: 08.10.2016
 *      Author: yael
 */


#include "gtest/gtest.h"
#include "TestHelper.h"

// "name-mangling" problem: linking c functions within c++ environment
extern "C" {
#include "reader.h"
#include "evaluator.h"
#include "printer.h"
}


class BuiltinSyntaxTests: public ::testing::Test, public TestHelper {
public:
	// SetUp
	BuiltinSyntaxTests() {
		// initialize ybscheme
		initGlobals();
		initReader();
		initEvaluator();
	}

	// TearDown
	~BuiltinSyntaxTests() {
	}
};



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
