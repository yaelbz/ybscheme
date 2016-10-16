/*
 * TestHelper.h
 *
 *  Created on: 09.10.2016
 *      Author: martin
 *
 */

#ifndef TESTHELPER_H_
#define TESTHELPER_H_

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

class TestHelper {
private:
	// use this stream/pipe to write to normal stdin (instead of creating own stream)
	// found at http://stackoverflow.com/questions/4393416/c-need-to-simulate-stdin-within-the-code-when-calling-a-function
	FILE *stdin_writer;
public:
	TestHelper();
	~TestHelper();

	void setupStdinWriter();
	void teardownStdinWriter();

	void write(const char *, ...);
	void writeln(const char *, ...);
	char* bin2str(long);
};

#endif /* TESTHELPER_H_ */
