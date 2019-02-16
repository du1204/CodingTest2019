#ifndef FILEREADER_H_
#define FILEREADER_H_

#include "fstream"
#include "string"
#include "stdint.h"
#include "iostream"	

#include "BigInteger.h"

using namespace std;

void readFile(const string filename, string*& strArray, long num);


// read file with name = filename and store the data in bigIntArray
void readBigInteger(BigInteger*& bigIntArray, const string filename, long num);



#endif