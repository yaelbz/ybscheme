/*
 * EvaluatorTests.cpp
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


class EvaluatorTests: public ::testing::Test, public TestHelper {
public:
	// SetUp
	EvaluatorTests() {
		// initialize ybscheme
		initGlobals();
		initReader();
		initEvaluator();
	}

	// TearDown
	~EvaluatorTests() {
	}
};




TEST_F(EvaluatorTests, EmptyList) {

	writeln("()");

	OBJ ro = ybRead(stdin);
	//ybPrint(ro);
	OBJ o  = ybEval(NULL, ro);
	//ybPrint(o);

	EXPECT_EQ(T_NIL, TYPE(o));
}

TEST_F(EvaluatorTests, massiveEvalStackUsage) {
	//todo: stucks with 10.000, to be analyzed. stream buffer size 64k?
	const int teststacksize = 20000;
	// use builtin (+) for testing the eval stack resizing
	write("(+ ");
	for (int i = 0; i < teststacksize; ++i) {
		write(" 1");
	}
	writeln(")");

	OBJ ro = ybRead(stdin);
	OBJ o  = ybEval(NULL, ro);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(teststacksize, (o->u.number.value.i));
}

TEST_F(EvaluatorTests, massiveEnvironmentUsage) {
	// works even with higher numbers but needs too much time
	const int testenvsize = 100000;
	for (int i = 0; i < testenvsize; ++i) {
		writeln("(define x%d %d)", i, i);
		OBJ ro = ybRead(stdin);
		OBJ o  = ybEval(NULL, ro);
		EXPECT_EQ(T_VOID, TYPE(o));
	}

	for (int i = 0; i < testenvsize; ++i) {
		writeln("x%d", i);
		OBJ ro = ybRead(stdin);
		OBJ o  = ybEval(NULL, ro);
		EXPECT_EQ(T_NUMBER, TYPE(o));
		EXPECT_TRUE(o->u.number.isInteger);
		EXPECT_EQ(i, (o->u.number.value.i));
	}
}
