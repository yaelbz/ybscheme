/*
 * TestHelper.cpp
 *
 *  Created on: 09.10.2016
 *      Author: yael
 */

#include <sys/poll.h>
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
	fflush(stdin_writer);
	// if there was anything left in stdin, read it out
    struct pollfd fds;
    fds.fd = 0; /* this is STDIN */
    fds.events = POLLIN;
	while(poll(&fds, 1, 0) > 0) {
		getc(stdin);
	}
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

// from: http://www.strudel.org.uk/itoa/
/*
char* itoa(int val, int base){

	static char buf[32] = {0};

	int i = 30;

	for(; val && i ; --i, val /= base){
		buf[i] = "0123456789abcdef"[val % base];
	}

	return &buf[i+1];

}
*/
char* TestHelper::bin2str(long val) {
	static char buf[65] = {0};
	int i = 63;
	char sign = '\0';
	if(val < 0) {
		sign = '-';
		val *= -1;
	}

	for(; val && i ; --i, val>>=1){
		buf[i] = (val&1)?'1':'0';
	}

	if(sign) {
		buf[i--] = sign;
	}

	return &buf[i+1];
}
