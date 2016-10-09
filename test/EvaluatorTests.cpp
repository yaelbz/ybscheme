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


class EvaluatorTests: public ::testing::Test {
public:
	// use this stream/pipe to write to normal stdin (instead of creating own stream)
	// found at http://stackoverflow.com/questions/4393416/c-need-to-simulate-stdin-within-the-code-when-calling-a-function
	FILE *stdin_writer;

	// SetUp
	EvaluatorTests() {
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
	~EvaluatorTests() {
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




// #### Test Implementation ########################################################################

TEST_F(EvaluatorTests, EmptyList) {

	writeln("()");

	OBJ ro = ybRead(stdin);
	//ybPrint(ro);
	OBJ o  = ybEval(NULL, ro);
	//ybPrint(o);

	EXPECT_EQ(T_NIL, TYPE(o));
}
