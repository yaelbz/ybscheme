/*
 * AllTests.cpp
 *
 * Test framework:
 * https://github.com/google/googletest
 *
 * Setup guide (slightly different)
 * http://stackoverflow.com/questions/3951808/using-googletest-in-eclipse-how
 *
 *  Created on: 08.10.2016
 *      Author: yael
 */


#include "gtest/gtest.h"

// include directly the cpp files for easy use
#include "ReaderTests.cpp"
#include "EvaluatorTests.cpp"
#include "BuiltinFunctionTests.cpp"
#include "BuiltinSyntaxTests.cpp"





GTEST_API_ int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
