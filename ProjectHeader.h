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
#include "Constants.h"
#include "nrg_gpio.h"
#include "nrfx_timer.h"
#include <Arduino.h>

typedef enum{IdleState, DataBits, StopConditions, MaximalBits} States;

typedef enum {Arduino, NRF52840} Platform;

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

/**
 * Setup the platform and pin needed to INPUT mode so we would be able to listen.
 * @param platform - The type of Platform we will work over
 * @param receivePin - The pin which we would like to connect to.
 */
void BootStrap(const Platform platform, const int receivePin);

/***
 * This function listens to a speicifc GPIO of one of the supported Platform(Must be bootstrap before)
 * and retruns the decoded ManchesterEncode of that specific pin.
 * The user must provide outputData of size 5 (which is constant) the function return the last
 * index of the decoded message.
 * @param platform - The type of platform our user would use.(Should be
 * @param receivePin - The pin which we would like to listen to.
 * @param outputData - An array of uint32_t* of our output data.
 * @return The effective size of output date which we use.
 */

int ManchesterTransmitting(const Platform platform, const int receivePin, uint32_t* outputData);
#endif //TONDOPROJECT_PROJECTHEADER_H
