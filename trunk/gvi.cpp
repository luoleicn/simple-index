
#include "gvi.h"
#include "exception.h"

#include <iostream>
#include <string.h>
#include <string>

using namespace luolei::hit::cir::se::exceptions;

namespace luolei { namespace hit { namespace cir { namespace se { namespace gvi {

    int readGVInt(unsigned int* data, const unsigned char* buf){
        unsigned char tags = buf[0];

        const unsigned char* p = &buf[1];

        const char* offset = GVIENTRY[tags];

        for(int i=0; i<4; i++){
            data[i] = (*((int*)p) & MASKS[(int)offset[i]]);
            p += (offset[i] + 1);
        }
        return 1 + 4 + offset[0] +offset[1] + offset[2] + offset[3];
    }

    int writeGVInt(unsigned char *buf, const unsigned int *data, int size){

        if(size > 4)
            throw GVIException("size in writeGVInt should be never larger than 4");

        int tags = 0;
        int pos = 1;//从buf[1]开始，buf[0]留给tags

        int chars = 0;//总共在buf中写了多少个char

        for(int i=0; i<size; i++){
            unsigned int tmp = data[i];
            int bits= 0;
            while( (tmp & ~0xFF) > 0){
                buf[pos++] = (tmp & 0xFF);
                chars++;
                bits++;
                tmp >>= 8;
            }
            buf[pos++] = tmp;
            chars++;
            //bits++;bits就是应该比实际的少1，tags中01表示2
            tags += (bits << (6-(i<<1)));
        }
        //对于size<4
        for(int i=0; i<(4-size); i++){
            buf[pos++] = 0;
            chars++;
        }
        buf[0] = tags;
        chars++;
        return chars;
    }
}}}}}//namespace luolei::hit::cir::se::gvi

