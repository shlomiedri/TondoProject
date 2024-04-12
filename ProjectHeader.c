//
// Created by shlomiedri on 4/11/24.
//
#include <stdio.h>
#include "ProjectHeader.h"



// Will provide an error message in the case when we get a wrong input.
void inputErrorFactory(const uint32_t* inputArray, const uint32_t* outputArray, const int inputSize, const int outputSize,
                       int functionFlag ){
    if(inputArray == NULL){
        printf(WRONG_INPUT_ERROR);
    }
    else if(outputArray == NULL){
        printf(WRONG_OUTPUT_ERROR);
    }
    else if( inputSize == 0){
        printf(WRONG_INPUT_SIZE_ERROR);
    }
    else if(functionFlag == 0 && outputSize != 2*inputSize){
        printf(WRONG_SIZE_PROPORTION_ENCODE);
    }
    else if (functionFlag== 1 && outputSize*2<= inputSize){
        printf(WRONG_SIZE_PROPORTION_DECODE);
    }
}


// When we Encode the output array is twice as long as the regular arry.
// Therefor we cold return 0-3 which represent 00, 01, 10,11
// to remain with the same array.
void setEncodeAtLocation(uint32_t* outputArray,const  uint32_t  bit,const int index){
        outputArray[index] = bit ? 1 : 0;
        outputArray[index+1] = bit ? 0 : 1;
}
// When we decode, two bits become one, as a result the InputArray is twice as big as the output array
// Which we expected to have such conclusion as we are reserving from the code/
int setDecodeAtLocation(uint32_t* outputArray,const uint32_t bit1,const uint32_t bit2 ,const int index){
        if(bit1 == 1 ){
            if(bit2 == 1){
                return FALSE;
            }
            else{
                outputArray[index] = 1;
                return TRUE;
            }
        }
        else{
            if(bit2 == 1){
                outputArray[index] = 0;
                return TRUE;
            }
            else{
                return FALSE;
            }
        }
}

// Data bits -> Manchester Encoding
int ManchesterEncode (const uint32_t* inputArray, uint32_t* outputArray,const int inputSize,const  int outputSize){
    if(inputArray == NULL || outputArray == NULL || inputSize == 0 || outputSize < inputSize*2 ){
        inputErrorFactory(inputArray, outputArray, inputSize, outputSize, 0);
        return FALSE;
    }
    for(int i = 0; i<inputSize; i++){
        if(inputArray[i] == 0 || inputArray[i] == 1) {
            setEncodeAtLocation(outputArray, inputArray[i], i * 2);
        }
        else{
            printf(WRONG_BIT_INPUT(i));
            return FALSE;}
    }
    return TRUE;
}

int ReverseManchester(const uint32_t* inputArray,uint32_t* outputArray, const int inputSize,const  int outputSize ){
    const int remainder = inputSize%2;
    if(inputArray == NULL || outputArray == NULL || inputSize == 0  || inputSize-remainder> outputSize*2 ){
        inputErrorFactory(inputArray, outputArray, inputSize, outputSize,1);
        return FALSE;
    }
    for(int i = 0; i<inputSize-remainder; i=i+2){
        if(setDecodeAtLocation(outputArray,inputArray[i],inputArray[i+1],i/2))
        {}
        else{
            printf(WRONG_SEQUENCE_INPUT(i));
            return FALSE;
        }
    }
    return TRUE;
}