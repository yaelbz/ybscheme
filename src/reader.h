/*
 * reader.h
 *
 */

#ifndef READER_H_
#define READER_H_

#include "global.h"

void initReader();
void flushReaderInputStream();
OBJ ybRead(FILE*);

#endif /* READER_H_ */
