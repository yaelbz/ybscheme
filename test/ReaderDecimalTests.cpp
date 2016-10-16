/*
 * ReaderHexadecimalTests.cpp
 *
 *  Created on: 16.10.2016
 *      Author: yael
 */



TEST_F(ReaderTests, IntegerMin) {

	const long i = LONG_MIN;
	writeln("%ld", i);

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, IntegerMax) {

	const long i = LONG_MAX;
	writeln("%ld", i);

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, IntegerPositive) {

	const long i = 7625348;
	writeln("%ld", i);

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, IntegerNull) {
	const long i = 0;
	writeln("%ld", i);

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}

TEST_F(ReaderTests, IntegerPositiveWithPlus) {

	const long i = 987654;
	writeln("+%ld", i);

	OBJ o = ybRead(stdin);

	EXPECT_EQ(T_NUMBER, TYPE(o));
	EXPECT_TRUE(o->u.number.isInteger);
	EXPECT_EQ(i, (o->u.number.value.i));
}
