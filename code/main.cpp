#include "iostream"
#include "BigInteger.h"
#include "fileReader.h"

using namespace std;




int main() {
    // ============================================================
    // First, test the simple code below
    // BigInteger A("1415921231237981273891273891279812312309");
    // A.print_dec();
    // ============================================================
    
    
    // ============================================================
    // filename = the name of txt file
    // num      = number of integers in the file 
    // ============================================================
    string filename = "bigInt.txt";
    long num = 5;
    BigInteger* A = new BigInteger[num];

    readBigInteger(A, filename, num);

    // ============================================================
    // Print integer in A
    // ============================================================
    for (int i = 0; i < num; i++) {
        A[i].print_dec();
    }   

    


    
    
}