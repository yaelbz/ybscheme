/*
 * global.h
 *
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdbool.h>

// #### object types #######################################################################################

typedef enum {
	T_ERROR = -1,			//-1
	T_NIL = 0,				//0
	T_VOID,					//1
	T_TRUE,					//2
	T_FALSE,				//3
	T_NUMBER,				//4
	T_STRING,				//5
	T_SYMBOL,				//6
	T_CONS,					//7
	T_BUILTIN_FUNCTION,		//8
	T_BUILTIN_SYNTAX,		//9
	T_USER_FUNCTION,		//10
	T_ENVIRONMENT,			//11
} objType;


// #### object definitions #######################################################################################

typedef struct ybObject *OBJ;
typedef OBJ (*ybFctPtr)(int); //Function pointer for builtin function
typedef OBJ (*ybSyntaxPtr)(OBJ, OBJ); //Function pointer for builtin syntax

struct ybAny {
	objType type;
};

struct ybError {
	objType type;
	char *message;
};

struct ybNumber {
	objType type;bool isInteger;
	union {
		long i;
		double f;
	} value;
};

struct ybSymbol {
	objType type;
	char *name;
};

struct ybString {
	objType type;
	char *string;
};

/*
 struct ybBool {
 objType type;
 bool value;
 };
 */

struct ybCons {
	objType type;
	OBJ first; //car
	OBJ rest; //cdr
};

struct ybBuiltinFunction {
	objType type;
	char *name;
	ybFctPtr impl; //implementation
};

struct ybBuiltinSyntax {
	objType type;
	char *name;
	ybSyntaxPtr impl; //implementation
};

struct ybUserFunction {
	objType type;
	OBJ env;
	int numDefs;
	char *name;
	OBJ parameterList;
	int numParameter;
	OBJ bodyList;
};

typedef struct {
	OBJ key;
	OBJ value;
} keyValuePair;

typedef struct {
	objType type;
	int size;
	int entryCount;
	OBJ parentEnv;
	keyValuePair entries[]; //array with key value pairs
} ybEnvironment;


// #### general object #######################################################################################

struct ybObject {
	union {
		struct ybAny any;
		struct ybError error;
		struct ybNumber number;
		struct ybString string;
		struct ybSymbol symbol;
		//struct ybBool		 boolean;
		struct ybCons cons;
		struct ybBuiltinFunction builtinFct;
		struct ybBuiltinSyntax builtinSyntax;
		ybEnvironment environment;
		struct ybUserFunction userFct;
	} u;
};


// #### macros #######################################################################################

#define TYPE(x)      ((x)->u.any.type)
#define FIRST(x)     ((x)->u.cons.first)
#define REST(x)      ((x)->u.cons.rest)
#define IS_TRUE(x)   ((x)->u.any.type == T_TRUE)
#define IS_FALSE(x)  ((x)->u.any.type == T_FALSE)


// #### prototypes #######################################################################################

OBJ globalNil;
OBJ globalVoid;
OBJ globalTrue;
OBJ globalFalse;
OBJ globalDefine;

void initGlobals();

OBJ newYbError(const char *, ...);
OBJ newYbIntNumber(long);
OBJ newYbFloatNumberFromInts(long, long);
OBJ newYbFloatNumber(double);
OBJ newYbString(char *);
OBJ newYbSymbol(char *);
OBJ newYbCons(OBJ, OBJ);
OBJ newYbBuiltinFunction(char *, ybFctPtr);
OBJ newYbUserDefinedFunction(char *, OBJ, OBJ, OBJ, int);
OBJ newYbBuiltinSyntax(char *, ybSyntaxPtr);
OBJ newYbEnvironment(int, OBJ);

void freeObject(OBJ);

void ybThrowError(int, const char *, ...);

#endif /* GLOBAL_H_ */
