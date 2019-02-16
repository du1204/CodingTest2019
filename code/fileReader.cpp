#include "fileReader.h"
#include "string"


using namespace std;

void readFile(const string filename, string*& strArray, long num) {
    strArray = new string[num];

    ifstream openFile(filename.data());
    if(openFile.is_open()) {
        string line, temp;
        long i = 0;
        while(getline(openFile, line)){
            strArray[i] = line;
            i++;
        }
    } else {
        cout << "Error: cannot read file" << endl;
    }
}

void readBigInteger(BigInteger*& bigIntArray, const string filename, long num) {
    string* strArray;
    readFile(filename, strArray, num);

     bigIntArray = new BigInteger[num];

    for (int i = 0; i < num; i++) {
        bigIntArray[i] = BigInteger(strArray[i].c_str());
    }
}