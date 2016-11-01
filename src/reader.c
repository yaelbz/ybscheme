/*
 * reader.c
 * repl --> reader
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "global.h"
#include "reader.h"
#include "symbolTable.h"

#define CHARSTACK_SIZE   2
#define STRING_INITIAL_LENGTH 64
static int charStackPtr = -1;
static int charStack[CHARSTACK_SIZE];
static bool readingString = false;

// #### init ##########################################################################################

void initReader() {
	flushReaderInputStream();
}

void flushReaderInputStream() {
	charStackPtr = -1;
}

// #### helper functions ##########################################################################################

bool isBinaryDigit(int ch) {
	return (ch >= '0' && ch <= '1');
}

bool isOctalDigit(int ch) {
	return (ch >= '0' && ch <= '7');
}

bool isDecimalDigit(int ch) {
	return (ch >= '0' && ch <= '9');
}

bool isHexadecimalDigit(int ch) {
	return ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f')
			|| (ch >= 'A' && ch <= 'F'));
}

int convertHexDigit(int ch) {
	int chval = -1;
	if (ch >= '0' && ch <= '9') {
		chval = (ch - '0');
	} else if (ch >= 'a' && ch <= 'f') {
		chval = (ch - 'a' + 10);
	} else if (ch >= 'A' && ch <= 'F') {
		chval = (ch - 'A' + 10);
	}
	return chval;
}

bool isLetter(int ch) {
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

bool isWhitespace(int ch) {
	return (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r');
}

//------------------------
// from: http://www.scheme.com/tspl2d/grammar.html --> identifier
// <letter> | ! | $ | % | & | * | / | : | < | = | > | ? | ~ | _ | ^
// + | - | . --> special forms
//------------------------
bool isSymbolInitialChar(int ch) {
	return (ch == '!' || ch == '$' || ch == '%' || ch == '&' || ch == '*'
			|| ch == '/' || ch == ':' || ch == '<' || ch == '=' || ch == '>'
			|| ch == '?' || ch == '~' || ch == '^' || ch == '_' || ch == '.'
			|| ch == '+' || ch == '-' || isLetter(ch));
}

//------------------------
// from: http://www.scheme.com/tspl2d/grammar.html --> identifier
// <initial> | <digit>
//------------------------
bool isSymbolSubsequentChar(int ch) {
	return (isSymbolInitialChar(ch) || isDecimalDigit(ch));
}

// #### get/push char ##########################################################################################

void pushCharBack(int ch) {
	if (charStackPtr >= CHARSTACK_SIZE) {
		ybThrowError(-1, "reader: charStack overflow");
	} else {
		charStack[++charStackPtr] = ch;
	}
}

int getNextRelevantChar(FILE* inputStream) {
	int ch;

	if (charStackPtr >= 0) {
		ch = charStack[charStackPtr--];
	} else {
		ch = getc(inputStream);
	}
	//ignore comments
	if (!readingString && ch == ';') {
		while (ch != '\n') {
			ch = getc(inputStream);
		}
		//read next relevant char
		ch = getc(inputStream);
	}

	return ch;
}

int getNextRelevantCharWithoutWhitespaces(FILE* inputStream) {
	int ch;
	//ignore whitespace
	do {
		ch = getNextRelevantChar(inputStream);
	} while (isWhitespace(ch));
	return ch;
}

// #### read functions ##########################################################################################

//------------------------
// read list
//------------------------
OBJ ybReadList(FILE* inputStream) {
	int ch = getNextRelevantCharWithoutWhitespaces(inputStream);
	if (ch == ')') {
		return globalNil;
	}

	pushCharBack(ch);

	OBJ first = ybRead(inputStream);
	OBJ rest = ybReadList(inputStream);

	return newYbCons(first, rest);
}

typedef bool (*isDigitPtr)(int);

//------------------------
// read number sign
//------------------------
int ybReadNumberSign(int *ch, FILE* inputStream, isDigitPtr isDigitFct) {
	int sign = 1;

	if (*ch == '-') {
		sign = -1;
		*ch = getNextRelevantChar(inputStream);
		//this is not a number, maybe a symbol
		if (!isDigitFct(*ch)) {
			pushCharBack(*ch);
			pushCharBack('-');
			return 0;
		}
	} else if (*ch == '+') {
		*ch = getNextRelevantChar(inputStream);
		//this is not a number, maybe a symbol
		if (!isDigitFct(*ch)) {
			pushCharBack(*ch);
			pushCharBack('+');
			return 0;
		}
	}

	// this is not a number, maybe a symbol
	if (!isDigitFct(*ch)) {
		pushCharBack(*ch);
		return 0;
	}

	return sign;
}

//------------------------
// read binary num
//------------------------
OBJ ybReadNumberBinary(FILE* inputStream) {
	int ch = getNextRelevantChar(inputStream);
	int sign = ybReadNumberSign(&ch, inputStream, &isBinaryDigit);
	if (!sign) {
		//not a number
		return globalNil;
	}

	long value = ch - '0';
	while (isBinaryDigit(ch = getNextRelevantChar(inputStream))) {
		//assuming compiler will optimize *2 by shift operation
		value = value * 2 + (ch - '0');
	};

	//read one too much
	pushCharBack(ch);
	return newYbIntNumber(value * sign);
}

//------------------------
// read octal num
//------------------------
OBJ ybReadNumberOctal(FILE* inputStream) {
	int ch = getNextRelevantChar(inputStream);
	int sign = ybReadNumberSign(&ch, inputStream, &isOctalDigit);
	if (!sign) {
		//not a number
		return globalNil;
	}

	long value = ch - '0';
	while (isOctalDigit(ch = getNextRelevantChar(inputStream))) {
		//assuming compiler will optimize *8 by shift operation
		value = value * 8 + (ch - '0');
	};

	//read one too much
	pushCharBack(ch);
	return newYbIntNumber(value * sign);
}

//------------------------
// read decimal num
//------------------------
OBJ ybReadNumberDecimal(FILE* inputStream) {
	int ch = getNextRelevantChar(inputStream);
	int sign = ybReadNumberSign(&ch, inputStream, &isDecimalDigit);
	if (!sign) {
		//not a number
		return globalNil;
	}

	long value = ch - '0';
	while (isDecimalDigit(ch = getNextRelevantChar(inputStream))) {
		value = value * 10 + (ch - '0');
	};

	//read one too much
	pushCharBack(ch);
	return newYbIntNumber(value * sign);
}

//------------------------
// read hex num
//------------------------
OBJ ybReadNumberHexadecimal(FILE* inputStream) {
	int ch = getNextRelevantChar(inputStream);
	int sign = ybReadNumberSign(&ch, inputStream, &isHexadecimalDigit);
	if (!sign) {
		//not a number
		return globalNil;
	}

	long value = convertHexDigit(ch);
	while (isHexadecimalDigit(ch = getNextRelevantChar(inputStream))) {
		//assuming compiler will optimize *16 by shift operation
		value = value * 16 + convertHexDigit(ch);
	}

	//read one too much
	pushCharBack(ch);
	return newYbIntNumber(value * sign);
}

//------------------------
// read string
//------------------------
OBJ ybReadString(FILE* inputStream) {
	readingString = true;
	OBJ obj;
	char *val = (char*) malloc(STRING_INITIAL_LENGTH * sizeof(char));
	int valLength = STRING_INITIAL_LENGTH;
	int countChars = 0;
	int ch = getNextRelevantChar(inputStream);
	while (ch != '"') {
		if (countChars >= valLength - 1) {
			valLength += STRING_INITIAL_LENGTH;
			val = (char*) realloc(val, valLength * sizeof(char));
		}
		val[countChars] = ch;
		countChars++;
		ch = getNextRelevantChar(inputStream);
	}
	val[countChars] = '\0'; //end of string
	obj = newYbString(val);
	free(val);
	readingString = false;
	return obj;
}

//------------------------
// read symbol
//------------------------
OBJ ybReadSymbol(FILE* inputStream) {
	//check first char
	int ch = getNextRelevantCharWithoutWhitespaces(inputStream);
	if (!isSymbolInitialChar(ch)) {
		return newYbError("syntax error: not a valid symbol, starting with: %c",
				ch);
	}

	OBJ obj;

	char *val = (char*) malloc(STRING_INITIAL_LENGTH * sizeof(char));
	int valLength = STRING_INITIAL_LENGTH;
	val[0] = ch;
	int countChars = 1;

	//check the following chars
	ch = getNextRelevantChar(inputStream);
	while (isSymbolSubsequentChar(ch)) {
		if (countChars >= valLength - 1) {
			valLength += STRING_INITIAL_LENGTH;
			val = (char*) realloc(val, valLength * sizeof(char));
		}
		val[countChars] = ch;
		countChars++;
		ch = getNextRelevantChar(inputStream);
	}
	val[countChars] = '\0'; //end of string
	pushCharBack(ch);

	if ((val[0] == '+' || val[0] == '-') && val[1] != '\0') {
		return newYbError("syntax error: not a valid symbol: %s", val);
	}
	if (strcmp(val, "nil") == 0) {
		free(val);
		return globalNil;
	}

	obj = addToSymbolTable(val);
	free(val);
	return obj;
}

// #### read ##########################################################################################

//------------------------
// main read
// called from repl
//------------------------
OBJ ybRead(FILE* inputStream) {
	int ch = getNextRelevantCharWithoutWhitespaces(inputStream);

	//quote
	if (ch == '\'') {
		return newYbCons(addToSymbolTable("quote"),
				newYbCons(ybRead(inputStream), globalNil));
	}

	//list
	if (ch == '(') {
		return ybReadList(inputStream);
	}

	//string
	if (ch == '"') {
		return ybReadString(inputStream);
	}

	//simple syntax error
	if (ch == ')') {
		return newYbError("syntax error: one ) too much");
	}

	//get number system
	if (ch == '#') {
		ch = getNextRelevantChar(inputStream);
		switch (ch) {
		case 'b':
			return ybReadNumberBinary(inputStream);
		case 'o':
			return ybReadNumberOctal(inputStream);
		case 'd':
			return ybReadNumberDecimal(inputStream);
		case 'x':
			return ybReadNumberHexadecimal(inputStream);
		case 't':
			return globalTrue;
		case 'f':
			return globalFalse;
		default:
			//no symbol/other type may start with a #
			return newYbError("syntax error: invalid token: #%c", ch);
		}
	}
	pushCharBack(ch);

	//default number system is decimal
	OBJ obj = ybReadNumberDecimal(inputStream);
	//if not a number, this must be a symbol
	if (obj == globalNil) {
		return ybReadSymbol(inputStream);
	}
	return obj;
}
