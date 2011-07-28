/*
 * 为了压缩目的, 使用变长Vbyte压缩，1bit用于说明是否还有后续，1表示有，0表示没有。后面7bit用于表示实际数值
 */

#include <iostream>


#ifndef _VBYTE_H
#define _VBYTE_H
namespace luolei { namespace hit { namespace cir { namespace se { namespace vbyte {
    int writeVbyte(unsigned int ui, unsigned char* buf);
    int readVbyte(unsigned char * buf, unsigned int & res);

}}}}}

#endif

