//////////////////////////////////////////////////////
//               G.E Thomas style                 ////
//          0 is coded as 01 (low-high)           ////
//          1 is coded as 10 ( high-low)          ////
//          Decoding 01-> 0 , 10- > 1            /////
//////////////////////////////////////////////////////



#ifndef TONDOPROJECT_PROJECTHEADER_H
#define TONDOPROJECT_PROJECTHEADER_H
#include <stdint.h>
#include <stddef.h>

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

typedef enum { FALSE=0, TRUE=1 } Bool; // Define a boolean type

typedef enum {Arduino, NRF52840} BoardType;

/***
 * A function which receives an array which contains data bits and outputArray
 * which will return as the Manchester Encoding of the provided data bits
 * @param inputArray - An array which contains data bits
 * @param outputArray - ManchesterEncoding of inputArray
 * @param arraySize - The size of inputArray and Outputarray.
 * @return 1 if the operation perform successfully, 0 otherwise.
 */
int ManchesterEncode (const uint32_t* inputArray, uint32_t* outputArray,const int arraySize,const int outputSize);




/***
 * The function receives an inputArray which contains a ManchesterEncoding sequence of bits.
 * The function write the data bits accordingly to the agree sequence in Output array which means
 * any squence of 01=0, 10=1 and it will be return in Outputarray
 * @param inputArray - A sequence of bits coded in ManchesterEncoding
 * @param outputArray - An array to write the coded bits in the correct format.
 * @param inputSize - The size of the input array.
 * @param outputSize - The size of the output array.
 * @return true in the case we translated correctly, false otherwise.
 */
int ReverseManchester(const uint32_t* inputArray,uint32_t* outputArray,const int inputSize,const  int outputSize );





#endif //TONDOPROJECT_PROJECTHEADER_H
