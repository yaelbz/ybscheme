/*
 * ReaderHexadecimalTests.cpp
 *
 *  Created on: 16.10.2016
 *      Author: yael
 */



TEST_F(ReaderTests, HexNull) {

	const long i = 0;
	writeln("#x0");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, HexNullWithPlus) {

	const long i = 0;
	writeln("#x+0");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, HexNullWithMinus) {

	const long i = 0;
	writeln("#x-0");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, HexLowercase) {

	const long i = 0xC0FFEE;
	writeln("#xc0ffee");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, HexPositive) {

	const long i = 0x1ABCDEF0;
	writeln("#x1ABCDEF0");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, HexPositiveWithPlus) {

	const long i = 0xAFFE;
	writeln("#x+AFFE");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, HexNegative) {

	const long i = -0xCAFE;
	writeln("#x-CAFE");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, HexMax32bit) {

	const long i = 0x7FFFFFFF;
	writeln("#x7FFFFFFF");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, HexMin32bit) {

	const long i = -0x7FFFFFFF;
	writeln("#x-7FFFFFFF");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, HexMax64bit) {

	const long i = 0x7FFFFFFFFFFFFFFF;
	writeln("#x7FFFFFFFFFFFFFFF");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, HexMin64bit) {

	const long i = -0x7FFFFFFFFFFFFFFF;
	writeln("#x-7FFFFFFFFFFFFFFF");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}
