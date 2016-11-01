/*
 * environment.h
 *
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "global.h"

void initEnv();
void envAdd(OBJ, OBJ, OBJ);
OBJ envGet(OBJ, OBJ);

#endif /* ENVIRONMENT_H_ */
