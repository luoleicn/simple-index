/*
 * 为了压缩目的, 使用变长Vbyte压缩，1bit用于说明是否还有后续，1表示有，0表示没有。后面7bit用于表示实际数值
 */
#include "vbyte.h"

namespace luolei { namespace hit { namespace cir { namespace se { namespace vbyte {
    int writeVbyte(unsigned int ui, unsigned char* buf){

        int len = 0;

        while( (ui & ~0x7F) != 0){
            buf[len++] = ((ui & 0x7F) | 0x80 );
            ui >>= 7;
        }
        buf[len++] = ui;

        return len;
    }

    int readVbyte(unsigned char * buf, unsigned int & res){

        int pos = 0;
        unsigned char b = buf[pos++];
        res = b & 0x7F;

        int shift;
        for(shift = 7; (b & 0x80) !=0; shift+=7){
            b = buf[pos++];
            res |= ((b & 0x7F) << shift);
        }

        return pos;
    }
}}}}}

