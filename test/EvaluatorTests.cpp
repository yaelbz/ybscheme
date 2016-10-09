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




// #### Test Implementation ########################################################################

TEST_F(EvaluatorTests, EmptyList) {

	writeln("()");

	OBJ ro = ybRead(stdin);
	//ybPrint(ro);
	OBJ o  = ybEval(NULL, ro);
	//ybPrint(o);

	EXPECT_EQ(T_NIL, TYPE(o));
}
