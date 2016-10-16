/*
 * ReaderTests.cpp
 *
 *  Created on: 08.10.2016
 *      Author: yael
 */


#include "gtest/gtest.h"
#include "limits.h"
#include "TestHelper.h"


// "name-mangling" problem: linking c functions within c++ environment
extern "C" {
#include "reader.h"
#include "printer.h"
}


class ReaderTests: public ::testing::Test, public TestHelper {
public:
	// SetUp
	ReaderTests() {
		// initialize ybscheme
		initGlobals();
		initReader();
		flushReaderInputStream();
	}

	// TearDown
	~ReaderTests() {
		flushReaderInputStream();
	}
};



// #### Integer ####################################################################################
#include "ReaderBinaryTests.cpp"
#include "ReaderOctalTests.cpp"
#include "ReaderDecimalTests.cpp"
#include "ReaderHexadecimalTests.cpp"



// #### Test Strings ###############################################################################

TEST_F(ReaderTests, ReadEmptyString) {

	const char *s = "";
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_STRING, TYPE(o));
	EXPECT_STREQ(s, o->u.string.string);
}


TEST_F(ReaderTests, ReadValidString) {

	const char *s = "Valid";
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_STRING, TYPE(o));
	EXPECT_STREQ(s, o->u.string.string);
}

TEST_F(ReaderTests, ReadLowercaseChars) {

	const char *s = "abcdefghijklmnopqrstuvwxyz";
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_STRING, TYPE(o));
	EXPECT_STREQ(s, o->u.string.string);
}

TEST_F(ReaderTests, ReadUppercaseChars) {

	const char *s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_STRING, TYPE(o));
	EXPECT_STREQ(s, o->u.string.string);
}

TEST_F(ReaderTests, ReadDigitChars) {

	const char *s = "0123456789";
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_STRING, TYPE(o));
	EXPECT_STREQ(s, o->u.string.string);
}
/*
TEST_F(ReaderTests, ReadSpecialChars) {

	const char *s = "!$&/()=?[]}+#*'~,.-:_<>|";
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_STRING, TYPE(o));
	EXPECT_STREQ(s, o->u.string.string);
}
*/
TEST_F(ReaderTests, ReadStringWithLeadingWhitespace) {

	char s[100];
	snprintf(s, sizeof(s), "%s", " \tabcdef");
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_STRING, TYPE(o));
	EXPECT_STREQ(s, o->u.string.string);
}

TEST_F(ReaderTests, ReadStringWithWhitespace) {

	char s[100];
	snprintf(s, sizeof(s), "%s", "ab cd\tef");
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_STRING, TYPE(o));
	EXPECT_STREQ(s, o->u.string.string);
}

TEST_F(ReaderTests, ReadStringWithTrailingWhitespace) {

	char s[100];
	snprintf(s, sizeof(s), "%s", "abcdef \t");
	writeln("\"%s\"", s);

	OBJ o = ybRead(stdin);

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

	EXPECT_EQ(T_NIL, TYPE(o));
}

// #### General Tests ##############################################################################

TEST_F(ReaderTests, ReadValidSyntax) {

	writeln("(+ 1 2)");

	OBJ o = ybRead(stdin);

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


TEST_F(ReaderTests, massiveSymbolTableUsage) {
	//TODO: stucks above 11.000, to be analyzed. stream buffer size 64k?
	const int testtablesize = 11000;
	write("(");
	for (int i = 0; i < testtablesize; ++i) {
		write(" s%x", i);
	}
	writeln(")");

	OBJ o = ybRead(stdin);

	int found = 0;
	while(TYPE(o) == T_CONS) {
		EXPECT_EQ(T_SYMBOL, TYPE(FIRST(o)));
		char buf[16];
		sprintf(buf, "s%x", found);
		EXPECT_STREQ(buf, FIRST(o)->u.symbol.name);
		o = REST(o);
		found++;
	}
	EXPECT_EQ(testtablesize, found);
}


// #### Float ######################################################################################

TEST_F(ReaderTests, DISABLED_FloatPositive) {

	double d = 0.6543;
	writeln("0.6543");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_FALSE(o->u.number.isInteger);
	EXPECT_DOUBLE_EQ(d, (o->u.number.value.f));
}

TEST_F(ReaderTests, DISABLED_FloatPositiveWithPlus) {

	double d = 456.3456543;
	writeln("+456.3456543");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_FALSE(o->u.number.isInteger);
	EXPECT_DOUBLE_EQ(d, (o->u.number.value.f));
}

TEST_F(ReaderTests, DISABLED_FloatNegative) {

	double d = -12.234567;
	writeln("-12.234567");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_FALSE(o->u.number.isInteger);
	EXPECT_DOUBLE_EQ(d, (o->u.number.value.f));
}

TEST_F(ReaderTests, DISABLED_FloatNull) {

	double d = 0.0;
	writeln("0.0");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_FALSE(o->u.number.isInteger);
	EXPECT_DOUBLE_EQ(d, (o->u.number.value.f));
}

TEST_F(ReaderTests, DISABLED_FloatNullWithMinus) {

	double d = 0.0;
	writeln("-0.0");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_FALSE(o->u.number.isInteger);
	EXPECT_DOUBLE_EQ(d, (o->u.number.value.f));
}

TEST_F(ReaderTests, DISABLED_FloatNullWithPlus) {

	double d = 0.0;
	writeln("+0.0");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_FALSE(o->u.number.isInteger);
	EXPECT_DOUBLE_EQ(d, (o->u.number.value.f));
}

TEST_F(ReaderTests, DISABLED_FloatNoLeadingZero) {

	double d = 0.4321;
	writeln(".4321");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_FALSE(o->u.number.isInteger);
	EXPECT_DOUBLE_EQ(d, (o->u.number.value.f));
}

TEST_F(ReaderTests, DISABLED_FloatNoLeadingZeroWithPlus) {

	double d = 0.1234321;
	writeln("+.1234321");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_FALSE(o->u.number.isInteger);
	EXPECT_DOUBLE_EQ(d, (o->u.number.value.f));
}

TEST_F(ReaderTests, DISABLED_FloatNoLeadingZeroWithMinus) {

	double d = -0.098776;
	writeln("-.098776");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_FALSE(o->u.number.isInteger);
	EXPECT_DOUBLE_EQ(d, (o->u.number.value.f));
}
