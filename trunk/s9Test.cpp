#include <iostream>
#include "exception.h"
#include "simple9.h"

using std::cout;
using std::endl;

using namespace luolei::hit::cir::se::exceptions;
using namespace luolei::hit::cir::se::simple9;

int main(int args, char** argv){

    unsigned int result;
    unsigned int encodeTest0[] ={0xf,0xf,0xf,0xf,0xf,0xf,0xf};

    int len;
    len = writeS9(&result, encodeTest0, 7);
    if(result == 0x6fffffff)
        cout << "encode successfully Len : " << len << endl;
    else
        cout << "encode error" << endl;

    unsigned int val[100] = {0};
    len = readS9(&result, val);
    for(int i=0; i<len; i++){
        cout << val[i] << " ";
    }
    cout << endl;

    unsigned int encodeTest1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    len = writeS9(&result, encodeTest1, 10);
    cout << " write Len " << len << endl;
    len = readS9(&result, val);
    for(int i=0; i<len; i++){
        cout << val[i] << " ";
    }
    cout << endl;

    return 0;
}

