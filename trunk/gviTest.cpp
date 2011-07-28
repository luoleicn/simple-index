/*
 * Group Variable-length Integer
 *
 * 见WSDM09-keynote.pdf第63页
 *
 * Version 0.2
 *
 */
#include <iostream>
#include <string.h>
#include <string>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#include "gvi.h"

using std::cout;
using std::endl;
using namespace luolei::hit::cir::se::gvi;


#define  NUMS  400


int main(int args, char** argv){
    //注意给bytes留下足够的缓冲，因为bytes除了要存整数数组之外，还要保存tags
    unsigned char bytes[NUMS*4+(NUMS)/4] = {0};
    unsigned int array[NUMS] = {0};
    cout << "开始随机产生数据" << endl;
    srand(time(NULL));
    for(int i=0; i<NUMS; i++){
        array[i] = rand();
        cout << array[i] << " ";
    }
    cout << endl;
    cout << "随机数生成完毕" << endl;


    int pos = 0;
    cout << "开始写入bytes流" << endl;
    for(int i=0; i<(NUMS); i+=4){
        int len = writeGVInt(&bytes[pos], &array[i]);
        pos += len;
    }

    pos = 0;
    memset(array, 0, sizeof(array));
    cout << "开始读bytes流" << endl;
    for(int i=0; i<(NUMS); i+=4){
        int len = readGVInt(&array[i], &bytes[pos]);
        pos += len;
        cout << array[i] << " " << array[i+1] << " " << array[i+2] << " " << array[i+3] << " " ;
    }


    return 0;
}


