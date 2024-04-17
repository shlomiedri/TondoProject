//
// Created by shlomiedri on 4/15/24.
//

#ifndef TONDOPROJECT_CONSTANTS_H
#define TONDOPROJECT_CONSTANTS_H
#define BAUD_RATE 9600
#define DATA_RATE 4800


#define WRONG_INPUT_ERROR "The pointer to the input array is NULL.\n"
#define WRONG_OUTPUT_ERROR "The pointer to the size of the array is NULL.\n"
#define WRONG_INPUT_SIZE_ERROR "The input array size shouldn't zero.(Should be |SIZE|>0).\n"
#define WRONG_SIZE_PROPORTION_ENCODE "The input.size and output.size should make |OUTPUT|=2*|INPUT|.\n"
#define WRONG_BIT_INPUT(i) "Wrong bit input(neither 0,1) at index %d.",i
#define WRONG_SEQUENCE_INPUT(i) "Incorrect format of bits order in array indexes: (%d,%d).", i, i+1
#define PATTERN_CHECK(i) "Should be of pattern type: %d.\n\n", i
#define WRONG_SIZE_PROPORTION_DECODE "The size of the output array doesn't fit the format |OUTPUT|*2<|INPUT|.\n"
#define ERROR_BOARD_TYPE "Board Type is not supported.\n"
#define MAXIMAL_TRANSFER 10
#define TRUE 1
#define FALSE 0
#define BIT_PERIOD_MICROS 104 //
#define TIMER_INSTANCE  NRF_TIMER1
#define SET_ARRAY_AT(array,mask,location) array[location] = (mask >> location) & 0x1;
#define SET_BIT_AT_LOCATION(bit, location) (bit ? 1 : 0) << location;
#define IDLE_ROUTINE_RATE 4
#endif //TONDOPROJECT_CONSTANTS_H
