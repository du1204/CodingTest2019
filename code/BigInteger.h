#ifndef BigInteger_H_
#define BigInteger_H_

#include "string"
#include "stdint.h"
using namespace std;

class BigInteger {
    /*
    This class structure is just an example you may need.
    Feel free to redefine any functions
    */
public:
    uint64_t* data;
    int n; 
	int	n_max;

    BigInteger() {};

    // define BigInt from given string        
    BigInteger(const char* str);

    // print data as an decimal number
    void print_dec() const;
    
    // add given BigInteger to this
    void add(const BigInteger& given);


};

/*
    TODO : This is the funciton for the main task
        Input : two arrays of BigInt A, B of length N
        output : array of BigInt C of length N such that C[i] = A[i] + B[i]
*/
void parallelAddition(const BigInteger*& A, BigInteger& B, long N);


#endif