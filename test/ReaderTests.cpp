/*
 * ReaderTests.cpp
 *
 *  Created on: 08.10.2016
 *      Author: yael
 */


#include "gtest/gtest.h"

// "name-mangling" problem: linking c functions within c++ environment
extern "C" {
#include "reader.h"
#include "printer.h"
}


class ReaderTests: public ::testing::Test {
public:
	// use this stream/pipe to write to normal stdin (instead of creating own stream)
	// found at http://stackoverflow.com/questions/4393416/c-need-to-simulate-stdin-within-the-code-when-calling-a-function
	FILE *stdin_writer;

	// SetUp
	ReaderTests() {
		// initialize ybscheme
		initGlobals();
		initReader();

		// prepare a pipe for writing into stdin
		int p[2];
		// error return checks omitted
		pipe(p);
		dup2(p[0], STDIN_FILENO);
		stdin_writer = fdopen(p[1], "w");
	}

	// TearDown
	~ReaderTests() {
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




// #### Test Numbers ###############################################################################

TEST_F(ReaderTests, ReadIntegerMin) {

	const long i = LONG_MIN;
	writeln("%ld", i);

	OBJ o = ybRead(stdin);
	//ybPrint(o);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, ReadIntegerMax) {

	const long i = LONG_MAX;
	writeln("%ld", i);

	OBJ o = ybRead(stdin);
	//ybPrint(o);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, ReadIntegerNull) {
	const long i = 0;
	writeln("%ld", i);

	OBJ o = ybRead(stdin);
	//ybPrint(o);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, ReadIntegerPositivePlus) {

	const long i = LONG_MAX;
	writeln("+%ld", i);

	OBJ o = ybRead(stdin);
	//ybPrint(o);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

// #### Test Strings ###############################################################################

TEST_F(ReaderTests, ReadEmptyString) {

	const char *s = "";
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);
	//ybPrint(o);

	EXPECT_EQ(T_STRING, TYPE(o));
	EXPECT_STREQ(s, o->u.string.string);
}

TEST_F(ReaderTests, ReadValidString) {

	const char *s = "Valid";
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);
	//ybPrint(o);

	EXPECT_EQ(T_STRING, TYPE(o));
	EXPECT_STREQ(s, o->u.string.string);
}

TEST_F(ReaderTests, ReadLowercaseChars) {

	const char *s = "abcdefghijklmnopqrstuvwxyz";
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);
	//ybPrint(o);

	EXPECT_EQ(T_STRING, TYPE(o));
	EXPECT_STREQ(s, o->u.string.string);
}

TEST_F(ReaderTests, ReadUppercaseChars) {

	const char *s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);
	//ybPrint(o);

	EXPECT_EQ(T_STRING, TYPE(o));
	EXPECT_STREQ(s, o->u.string.string);
}

TEST_F(ReaderTests, ReadDigitChars) {

	const char *s = "0123456789";
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);
	//ybPrint(o);

	EXPECT_EQ(T_STRING, TYPE(o));
	EXPECT_STREQ(s, o->u.string.string);
}

TEST_F(ReaderTests, ReadSpecialChars) {

	const char *s = "!$&/()=?[]}+#*'~,.-:_<>|";
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);
	//ybPrint(o);

	EXPECT_EQ(T_STRING, TYPE(o));
	EXPECT_STREQ(s, o->u.string.string);
}

TEST_F(ReaderTests, ReadStringWithLeadingWhitespace) {

	char s[100];
	snprintf(s, sizeof(s), "%s", " \tabcdef");
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);
	//ybPrint(o);

	EXPECT_EQ(T_STRING, TYPE(o));
	EXPECT_STREQ(s, o->u.string.string);
}

TEST_F(ReaderTests, ReadStringWithWhitespace) {

	char s[100];
	snprintf(s, sizeof(s), "%s", "ab cd\tef");
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);
	//ybPrint(o);

	EXPECT_EQ(T_STRING, TYPE(o));
	EXPECT_STREQ(s, o->u.string.string);
}

TEST_F(ReaderTests, ReadStringWithTrailingWhitespace) {

	char s[100];
	snprintf(s, sizeof(s), "%s", "abcdef \t");
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);
	//ybPrint(o);

	EXPECT_EQ(T_STRING, TYPE(o));
	EXPECT_STREQ(s, o->u.string.string);
}

/*
//TODO: enable when strings are read dynamically
TEST_F(ReaderTests, DISABLED_ReadLongString) {

	const char *s =
"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!$&/()=?[]}+#*'~,.-:_<>|\
0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!$&/()=?[]}+#*'~,.-:_<>|\
0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!$&/()=?[]}+#*'~,.-:_<>|\
0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!$&/()=?[]}+#*'~,.-:_<>|\
0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!$&/()=?[]}+#*'~,.-:_<>|\
0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!$&/()=?[]}+#*'~,.-:_<>|\
0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!$&/()=?[]}+#*'~,.-:_<>|\
0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!$&/()=?[]}+#*'~,.-:_<>|\
0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!$&/()=?[]}+#*'~,.-:_<>|\
0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!$&/()=?[]}+#*'~,.-:_<>|";
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);
	ybPrint(o);

	EXPECT_EQ(T_STRING, TYPE(o));
	EXPECT_STREQ(s, o->u.string.string);
}
*/

// #### Test Lists #################################################################################

TEST_F(ReaderTests, ReadEmptyList) {

	writeln("()");

	OBJ o = ybRead(stdin);
	//ybPrint(o);

	EXPECT_EQ(T_NIL, TYPE(o));
}

// #### General Tests ##############################################################################

TEST_F(ReaderTests, ReadValidSyntax) {

	// 1. fill stdin with something to parse
	writeln("(+ 1 2)");

	// 2. read it
	OBJ o = ybRead(stdin);
	// debug output
	//ybPrint(obj);

	// 3. analyse the result
	EXPECT_EQ(T_CONS,   TYPE(o));
	EXPECT_EQ(T_SYMBOL, TYPE(FIRST(o)));
	EXPECT_EQ(T_CONS,   TYPE(REST(o)));
	o = REST(o);
	EXPECT_EQ(T_NUMBER, TYPE(FIRST(o)));
	EXPECT_EQ(T_CONS,   TYPE(REST(o)));
	o = REST(o);
	EXPECT_EQ(T_NUMBER, TYPE(FIRST(o)));
	EXPECT_EQ(T_NIL,    TYPE(REST(o)));
}
