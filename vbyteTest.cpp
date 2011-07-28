#include <stdio.h>
#include "vbyte.h"

using namespace luolei::hit::cir::se::vbyte;

int main(int args, char** argv){

    unsigned int a = 1624u;

    unsigned char buf[100] = {0};

    int len = writeVbyte(a, buf);

    int i=0;
    while(buf[i] != 0){
        printf("%d\n", buf[i++]);
    }
    printf("len = %d\n", len);

    unsigned int res;
    len = readVbyte(buf, res);
    printf("%u %d\n", res, len);

    return 0;
}
