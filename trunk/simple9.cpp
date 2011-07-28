#include "simple9.h"

#include "exception.h"

namespace luolei { namespace hit { namespace cir { namespace se { namespace simple9 {

    int writeS9(unsigned int* to, unsigned int* from, int size){
        using luolei::hit::cir::se::exceptions::S9Exception;

        if(to == NULL || from == NULL){
            throw S9Exception("Simple-9 encode : int* to or int* from is NULL");
        }

        if(size <= 0){
            throw S9Exception("Simple-9 encode : size < 0");
        }

        int inputNum;
        int minBits = 1;
        int maxVal = (1 << minBits);

        for(inputNum=1; inputNum <= size; inputNum++){
            int data = from[inputNum-1];

            int tmp = minBits;
            while(data >= maxVal){
                minBits++;
                maxVal <<= 1;
            }

            if ((tmp == 3) && (inputNum == 9) && (minBits ==4)){
                minBits = tmp;
                break;
            }
            else if((tmp == 9) && (inputNum == 3) && (minBits == 10)){
                minBits = tmp;
                break;
            }
            else if((tmp == 5) && (inputNum >= 3) && (inputNum < 5) && (minBits == 6)){
                minBits = tmp;
                continue;
            }
            else if((tmp == 5) && (inputNum == 5) && (minBits == 6)){
                minBits = tmp;
                break;
            }
            else if((inputNum * minBits) > NUM_DATA_BITS){
                    inputNum--;
                    minBits = tmp;
                    break;
                
            }
        }
        if(inputNum > size)
            inputNum--;


        while( (inputNum * (minBits +1)) <= NUM_DATA_BITS)
            minBits++;

        if( (inputNum + 1) * minBits <= NUM_DATA_BITS){
            minBits++;
            inputNum = NUM_DATA_BITS / minBits;
        }

        switch(minBits){
            case 28:
                *to = (NUM_1_28_BITS << NUM_DATA_BITS);
                *to |= from[0];
                break;
            case 14:
                *to = (NUM_2_14_BITS << NUM_DATA_BITS);
                *to |= (from[0] << 14);
                *to |= (from[1]);
                break;
            case 9:
                *to = (NUM_3_9_9_10_BITS << NUM_DATA_BITS);
                *to |= (from[0] << 19);
                *to |= (from[1] << 10);
                *to |= from[2];
                break;
            case 7:
                *to = (NUM_4_7_BITS << NUM_DATA_BITS);
                *to |= (from[0] << 21);
                *to |= (from[1] << 14);
                *to |= (from[2] << 7);
                *to |= (from[3]);
                break;
            case 5:
                *to = (NUM_5_5_5_6_6_6_BITS << NUM_DATA_BITS);
                *to |= (from[0] << 23);
                *to |= (from[1] << 18);
                *to |= (from[2] << 12);
                *to |= (from[3] << 6);
                *to |= (from[4]);
                break;
            case 4:
                *to = (NUM_7_4_BITS << NUM_DATA_BITS);
                *to |= (from[0] << 24);
                *to |= (from[1] << 20);
                *to |= (from[2] << 16);
                *to |= (from[3] << 12);
                *to |= (from[4] << 8);
                *to |= (from[5] << 4);
                *to |= (from[6]);
                break;
            case 3:
                *to = (NUM_9_3_3_3_3_3_3_3_3_4_BITS << NUM_DATA_BITS);
                *to |= (from[0] << 25);
                *to |= (from[1] << 22);
                *to |= (from[2] << 19);
                *to |= (from[3] << 16);
                *to |= (from[4] << 13);
                *to |= (from[5] << 10);
                *to |= (from[6] << 7);
                *to |= (from[7] << 4);
                *to |= (from[8]); 
                break;
            case 2:
                *to = (NUM_14_2_BITS << NUM_DATA_BITS);
                *to |= (from[0] << 26);
                *to |= (from[1] << 26);
                *to |= (from[2] << 26);
                *to |= (from[3] << 26);
                *to |= (from[4] << 26);
                *to |= (from[5] << 26);
                *to |= (from[6] << 26);
                *to |= (from[7] << 26);
                *to |= (from[8] << 26);
                *to |= (from[9] << 26);
                *to |= (from[10] << 26);
                *to |= (from[11] << 26);
                *to |= (from[12] << 26);
                *to |= (from[13] << 26);
                break;
            case 1:
                *to = (NUM_28_1_BITS << NUM_DATA_BITS);
                *to |= (from[0] << 27);
                *to |= (from[1] << 26);
                *to |= (from[2] << 25);
                *to |= (from[3] << 24);
                *to |= (from[4] << 23);
                *to |= (from[5] << 22);
                *to |= (from[6] << 21);
                *to |= (from[7] << 20);
                *to |= (from[8] << 19);
                *to |= (from[9] << 18);
                *to |= (from[10] << 17);
                *to |= (from[11] << 16);
                *to |= (from[12] << 15);
                *to |= (from[13] << 14);
                *to |= (from[14] << 13);
                *to |= (from[15] << 12);
                *to |= (from[16] << 11);
                *to |= (from[17] << 10);
                *to |= (from[18] << 9);
                *to |= (from[19] << 8);
                *to |= (from[20] << 7);
                *to |= (from[21] << 6);
                *to |= (from[22] << 5);
                *to |= (from[23] << 4);
                *to |= (from[24] << 3);
                *to |= (from[25] << 2);
                *to |= (from[26] << 1);
                *to |= (from[27]);
                break;
            default:
                throw S9Exception("Simple-9 : unknow minBits");
        }
        return inputNum;
    }


    int readS9(unsigned int* from, unsigned int* val){
        using luolei::hit::cir::se::exceptions::S9Exception;


        unsigned char selector = ((*from) >> NUM_DATA_BITS);

        switch(selector){
            case NUM_1_28_BITS:
                val[0] = ((*from)&BITS_28_MASK);
                return 1;
            case NUM_2_14_BITS:
                val[0] = (((*from) >> 14) & BITS_14_MASK);
                val[1] = ((*from) & BITS_14_MASK);
                return 2;
            case NUM_3_9_9_10_BITS:
                val[0] = (((*from) >> 19) & BITS_9_MASK);
                val[1] = (((*from) >> 10) & BITS_9_MASK);
                val[2] = ((*from) & BITS_10_MASK);
                return 3;
            case NUM_4_7_BITS:
                val[0] = (((*from) >> 21) & BITS_7_MASK);
                val[1] = (((*from) >> 14) & BITS_7_MASK);
                val[2] = (((*from) >> 7)  & BITS_7_MASK);
                val[3] = ((*from) & BITS_7_MASK);
                return 4;
            case NUM_5_5_5_6_6_6_BITS:
                val[0] = (((*from) >> 23) & BITS_5_MASK);
                val[1] = (((*from) >> 18) & BITS_5_MASK);
                val[2] = (((*from) >> 12) & BITS_6_MASK);
                val[3] = (((*from) >> 6) & BITS_6_MASK);
                val[4] = ((*from) & BITS_6_MASK);
                return 5;
            case NUM_7_4_BITS:
                val[0] = (((*from) >> 24) & BITS_4_MASK);
                val[1] = (((*from) >> 20) & BITS_4_MASK);
                val[2] = (((*from) >> 16) & BITS_4_MASK);
                val[3] = (((*from) >> 12) & BITS_4_MASK);
                val[4] = (((*from) >> 8) & BITS_4_MASK);
                val[5] = (((*from) >> 4) & BITS_4_MASK);
                val[6] = (((*from)) & BITS_4_MASK);
                return 7;
            case NUM_9_3_3_3_3_3_3_3_3_4_BITS:
                val[0] = (((*from) >> 25) & BITS_3_MASK);
                val[1] = (((*from) >> 22) & BITS_3_MASK);
                val[2] = (((*from) >> 19) & BITS_3_MASK);
                val[3] = (((*from) >> 16) & BITS_3_MASK);
                val[4] = (((*from) >> 13) & BITS_3_MASK);
                val[5] = (((*from) >> 10) & BITS_3_MASK);
                val[6] = (((*from) >> 7) & BITS_3_MASK);
                val[7] = (((*from) >> 4) & BITS_3_MASK);
                val[8] = (((*from)) & BITS_4_MASK);
                return 9;
            case NUM_14_2_BITS:
                val[0] = (((*from) >> 26) & BITS_2_MASK);
                val[1] = (((*from) >> 24) & BITS_2_MASK);
                val[2] = (((*from) >> 22) & BITS_2_MASK);
                val[3] = (((*from) >> 20) & BITS_2_MASK);
                val[4] = (((*from) >> 18) & BITS_2_MASK);
                val[5] = (((*from) >> 16) & BITS_2_MASK);
                val[6] = (((*from) >> 14) & BITS_2_MASK);
                val[7] = (((*from) >> 12) & BITS_2_MASK);
                val[8] = (((*from) >> 10) & BITS_2_MASK);
                val[9] = (((*from) >> 8) & BITS_2_MASK);
                val[10] = (((*from) >> 6) & BITS_2_MASK);
                val[11] = (((*from) >> 4) & BITS_2_MASK);
                val[12] = (((*from) >> 2) & BITS_2_MASK);
                val[13] = (((*from)) & BITS_2_MASK);
                return 14;
            case NUM_28_1_BITS:
                val[0] = (((*from) >> 27) & BITS_1_MASK);
                val[1] = (((*from) >> 26) & BITS_1_MASK);
                val[2] = (((*from) >> 25) & BITS_1_MASK);
                val[3] = (((*from) >> 24) & BITS_1_MASK);
                val[4] = (((*from) >> 23) & BITS_1_MASK);
                val[5] = (((*from) >> 22) & BITS_1_MASK);
                val[6] = (((*from) >> 21) & BITS_1_MASK);
                val[7] = (((*from) >> 20) & BITS_1_MASK);
                val[8] = (((*from) >> 19) & BITS_1_MASK);
                val[9] = (((*from) >> 18) & BITS_1_MASK);
                val[10] = (((*from) >> 17) & BITS_1_MASK);
                val[11] = (((*from) >> 16) & BITS_1_MASK);
                val[12] = (((*from) >> 15) & BITS_1_MASK);
                val[13] = (((*from) >> 14) & BITS_1_MASK);
                val[14] = (((*from) >> 13) & BITS_1_MASK);
                val[15] = (((*from) >> 12) & BITS_1_MASK);
                val[16] = (((*from) >> 11) & BITS_1_MASK);
                val[17] = (((*from) >> 10) & BITS_1_MASK);
                val[18] = (((*from) >> 9) & BITS_1_MASK);
                val[19] = (((*from) >> 8) & BITS_1_MASK);
                val[20] = (((*from) >> 7) & BITS_1_MASK);
                val[21] = (((*from) >> 6) & BITS_1_MASK);
                val[22] = (((*from) >> 5) & BITS_1_MASK);
                val[23] = (((*from) >> 4) & BITS_1_MASK);
                val[24] = (((*from) >> 3) & BITS_1_MASK);
                val[25] = (((*from) >> 2) & BITS_1_MASK);
                val[26] = (((*from) >> 1) & BITS_1_MASK);
                val[27] = (((*from)) & BITS_1_MASK);
                return 28;
            default:
                throw S9Exception("unknow simple-9 selector");
        }

    }
}}}}}//namespace luolei::hit::cir::se::simple9

