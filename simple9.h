/*
 * Simple-9压缩、解压算法
 *
 * 在<<Information Retrieval : Implementing and Evaluating Search Engine>>中第6章有介绍
 */
#ifndef _SIMPLE9_H
#define _SIMPLE9_H

namespace luolei { namespace hit { namespace cir { namespace se { namespace simple9 {

    static const int NUM_DATA_BITS = 28;
    static const int NUM_SELECTOR_BITS = 4;

    static const unsigned char NUM_1_28_BITS = 1;//1 number of 28 bits
    static const unsigned char NUM_2_14_BITS = 2;//2 number of 14 bits
    static const unsigned char NUM_3_9_9_10_BITS = 3;// 9, 9, 10
    static const unsigned char NUM_4_7_BITS = 4;// 7, 7, 7, 7
    static const unsigned char NUM_5_5_5_6_6_6_BITS = 5;// 2 of 5, 3 of 6
    static const unsigned char NUM_7_4_BITS = 6;// 7 of 4
    static const unsigned char NUM_9_3_3_3_3_3_3_3_3_4_BITS = 7; // 8 of 3 , 1 of 4
    static const unsigned char NUM_14_2_BITS = 8;//14 of 2
    static const unsigned char NUM_28_1_BITS = 9;//28 of 1

    static const int BITS_28_MASK = (1 << 28) - 1;
    static const int BITS_14_MASK = (1 << 14) - 1;
    static const int BITS_10_MASK = (1 << 10) - 1;
    static const int BITS_9_MASK = (1 << 9) - 1;
    static const int BITS_7_MASK = (1 << 7) - 1;
    static const int BITS_6_MASK = (1 << 6) - 1;
    static const int BITS_5_MASK = (1 << 5) - 1;
    static const int BITS_4_MASK = (1 << 4) - 1;
    static const int BITS_3_MASK = (1 << 3) - 1;
    static const int BITS_2_MASK = (1 << 2) - 1;
    static const int BITS_1_MASK = (1 << 1) - 1;

    /*
     * 按simple-9的方法压缩
     * 
     * 参数介绍
     *  to：压缩后整数保存地址指针
     *  from：待压缩的数组
     *  size：数组的长度，但是最终压缩结果仅仅保存在一个int32_t中，能压缩的数量可能会小于size
     *
     * 返回值：
     *  返回实际压缩的整数个数
     */
    int writeS9(unsigned int* to, unsigned int* from, int size);

    /*
     * simple-9解压
     *
     * 参数介绍：
     *  from：保存整数数组案simple-9压缩的int32_t
     *  to：保存解压整数数组的结果
     * 返回值：
     *  from中保存的整数个数
     */
    int readS9(unsigned int* from, unsigned int* val);

}}}}}//namespace luolei::hit::cir::se::simple9
#endif//_SIMPLE9_H

