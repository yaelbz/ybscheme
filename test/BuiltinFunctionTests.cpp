/*
 * BuiltinFunctionTests.cpp
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


class BuiltinFunctionTests: public ::testing::Test, public TestHelper {
public:

	// SetUp
	BuiltinFunctionTests() {
		// initialize ybscheme
		initGlobals();
		initReader();
		initEvaluator();
	}

	// TearDown
	~BuiltinFunctionTests() {
	}
};



// #### Plus #######################################################################################

TEST_F(BuiltinFunctionTests, Plus_2Integers) {

	writeln("(+ 1 2)");

	OBJ ro = ybRead(stdin);
	//ybPrint(ro);
	OBJ o  = ybEval(NULL, ro);
	//ybPrint(o);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(3, (o->u.number.value.i));
}

TEST_F(BuiltinFunctionTests, Plus_20Integers) {

	writeln("(+ 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20)");

	OBJ ro = ybRead(stdin);
	//ybPrint(ro);
	OBJ o  = ybEval(NULL, ro);
	//ybPrint(o);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(210, (o->u.number.value.i));
}

// #### equal #######################################################################################

//-- eq? --//

TEST_F(BuiltinFunctionTests, eqQ_emptyLists) {
	writeln("(eq? () ())");

	OBJ ro = ybRead(stdin);
	OBJ o = ybEval(NULL, ro);

	EXPECT_EQ(globalTrue, o);
}

TEST_F(BuiltinFunctionTests, eqQ_sameValuesAreNotSameObjects) {
	writeln("(eq? 1 1)");

	OBJ ro = ybRead(stdin);
	OBJ o = ybEval(NULL, ro);

	EXPECT_EQ(globalFalse, o);
}

TEST_F(BuiltinFunctionTests, eqQ_1ArgReturnsError) {
	writeln("(eq? 5)");

	OBJ ro = ybRead(stdin);
	OBJ o = ybEval(NULL, ro);

	EXPECT_EQ(T_ERROR, TYPE(o));
}

TEST_F(BuiltinFunctionTests, eqQ_3ArgsReturnError) {
	writeln("(eq? 6 7 8)");

	OBJ ro = ybRead(stdin);
	OBJ o = ybEval(NULL, ro);

	EXPECT_EQ(T_ERROR, TYPE(o));
}

//-- = --//

TEST_F(BuiltinFunctionTests, eqOpQ_sameValues) {
	writeln("(= 1 1)");

	OBJ ro = ybRead(stdin);
	OBJ o = ybEval(NULL, ro);

	EXPECT_EQ(globalTrue, o);
}

TEST_F(BuiltinFunctionTests, eqOpQ_diffValues) {
	writeln("(= 67 45)");

	OBJ ro = ybRead(stdin);
	OBJ o = ybEval(NULL, ro);

	EXPECT_EQ(globalFalse, o);
}

TEST_F(BuiltinFunctionTests, eqOpQ_sameStringsReturnsError) {
	//= works only for numbers
	writeln("(= \"string1\" \"string1\")");

	OBJ ro = ybRead(stdin);
	OBJ o = ybEval(NULL, ro);

	EXPECT_EQ(T_ERROR, TYPE(o));
}

TEST_F(BuiltinFunctionTests, eqOpQ_1ArgReturnsError) {
	writeln("(= 5)");

	OBJ ro = ybRead(stdin);
	OBJ o = ybEval(NULL, ro);

	EXPECT_EQ(T_ERROR, TYPE(o));
}

TEST_F(BuiltinFunctionTests, eqOpQ_3ArgsReturnError) {
	writeln("(= 6 7 8)");

	OBJ ro = ybRead(stdin);
	OBJ o = ybEval(NULL, ro);

	EXPECT_EQ(T_ERROR, TYPE(o));
}
