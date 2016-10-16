/*
 * ReaderOctadecimalTests.cpp
 *
 *  Created on: 16.10.2016
 *      Author: yael
 */



TEST_F(ReaderTests, OctNull) {

	const long i = 0;
	writeln("#o0");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, OctNullWithPlus) {

	const long i = 0;
	writeln("#o+0");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, OctNullWithMinus) {

	const long i = 0;
	writeln("#o-0");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, OctPositive) {

	const long i = 00165737460;
	writeln("#o%lo", i);
	//writeln("#o0165737460");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, OctPositiveWithPlus) {

	const long i = 05652431;
	writeln("#o+%lo", i);
	//writeln("#o+5652431");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, OctNegative) {

	const long i = -076365;
	writeln("#o-076365");

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, OctMax32bit) {

	const long i = 0x7FFFFFFF;
	writeln("#o%lo", i);

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, OctMin32bit) {

	const long i = -0x7FFFFFFF;
	writeln("#o%lo", i);

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, OctMax64bit) {

	const long i = 0x7FFFFFFFFFFFFFFF;
	writeln("#o%lo", i);

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, OctMin64bit) {

	const long i = -0x7FFFFFFFFFFFFFFF;
	writeln("#o%lo", i);

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}
