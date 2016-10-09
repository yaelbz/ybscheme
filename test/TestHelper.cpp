/*
 * TestHelper.cpp
 *
 *  Created on: 09.10.2016
 *      Author: martin
 */

#include "TestHelper.h"

TestHelper::TestHelper() {
	setupStdinWriter();
}

TestHelper::~TestHelper() {
	teardownStdinWriter();
}

void TestHelper::setupStdinWriter() {
	// prepare a pipe for writing into stdin
	int p[2];
	// error return checks omitted
	pipe(p);
	dup2(p[0], STDIN_FILENO);
	stdin_writer = fdopen(p[1], "w");

}

void TestHelper::teardownStdinWriter() {
	fclose(stdin_writer);
}


// wrapper for writing to stdin
void TestHelper::write(const char *format, ...) {
    va_list args;
    va_start(args, format);

	vfprintf(stdin_writer, format, args);
	fflush(stdin_writer);

	va_end(args);
}

void TestHelper::writeln(const char *format, ...) {
    va_list args;
    va_start(args, format);

	vfprintf(stdin_writer, format, args);
	fprintf(stdin_writer, "\n");
	fflush(stdin_writer);

	va_end(args);
}
