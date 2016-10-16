/*
 * ReaderHexadecimalTests.cpp
 *
 *  Created on: 16.10.2016
 *      Author: yael
 */


TEST_F(ReaderTests, BinNull) {

	const long i = 0;
	writeln("#b0");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, BinNullWithPlus) {

	const long i = 0;
	writeln("#b+0");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, BinNullWithMinus) {

	const long i = 0;
	writeln("#b-0");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, BinPositive) {

	const long i = 165737460;
	writeln("#b%s", bin2str(i));

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, BinPositiveWithPlus) {

	const long i = 5652431;
	writeln("#b+%s", bin2str(i));

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, BinNegative) {

	const long i = -076365;
	writeln("#b%s", bin2str(i));

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, BinMax32bit) {

	const long i = 0x7FFFFFFF;
	writeln("#b%s", bin2str(i));

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, BinMin32bit) {

	const long i = -0x7FFFFFFF;
	writeln("#b%s", bin2str(i));

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, BinMax64bit) {

	const long i = 0x7FFFFFFFFFFFFFFF;
	writeln("#b%s", bin2str(i));

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, BinMin64bit) {

	const long i = -0x7FFFFFFFFFFFFFFF;
	writeln("#b%s", bin2str(i));

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}
