//
// Created by shlomiedri on 4/11/24.
//
#include <stdio.h>
#include <bits/stdint-uintn.h>
#include "ProjectHeader.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Additional function which are handler for cases and design patterns to keep our code dynamic.////////////////////////

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

void setEncodeAtLocation(uint32_t* outputArray,const  uint32_t  bit,const int index){
    outputArray[index] = bit ? 1 : 0;
    outputArray[index+1] = bit ? 0 : 1;
}

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
/**
 *For a specific platform the function will return the current time capture of this specific function.
 */
unsigned long PlatformDigitalTimer(const Platform boardType) {
    uint32_t timerValue;
    switch (boardType) {
        case Arduino:
            return micros();
        case NRF52840:
            timerValue= 0;
            nrfx_timer_capture(&timer, NRF_TIMER_CC_CHANNEL0, &timer_value);
            return timer_value;
        default:
            printf(ERROR_BOARD_TYPE);
            return 0;
    }
}
/**
 * Like above just return the digitalRead which mean we will return the input in RAM[i]
*/
int PlatformDigitalReader(const Platform boardType, const int receivePin) {
    switch (boardType) {
        case Arduino:
            return digitalRead(receivePin);
        case NRF52840:
            return nrf_gpio_pin_read(receivePin);
    }
}
/**
 * Specific function to set time for specific NRF system.
 */
void timeSetupNRF(){
    // Configure timer with default settings
    nrfx_timer_config_t timer_cfg = NRFX_TIMER_DEFAULT_CONFIG;
    // Initialize timer
    ret_code_t err_code = nrfx_timer_init(&TIMER_INSTANCE, &timer_cfg, NULL);
    APP_ERROR_CHECK(err_code);
    // Configure timer with 1MHz frequency (1us resolution)
    nrfx_timer_frequency_set(&TIMER_INSTANCE, NRF_TIMER_FREQ_1MHz);
    // Configure timer for 9600 baud rate (104us per bit)
    nrfx_timer_extended_compare(&TIMER_INSTANCE,
                                NRF_TIMER_CC_CHANNEL0,
                                nrfx_timer_us_to_ticks(&TIMER_INSTANCE, BIT_PERIOD_MICROS),
                                NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,
                                TRUE);

    // Start timer
    nrfx_timer_enable(&TIMER_INSTANCE);
}
/**
 * Setting the timer for each of the Platform/
 */
void PlatformTimeSetUp(const Platform boardType){
    switch(boardType){
        case Arduino:
            return;
        case NRF52840:
            timeSetupNRF();
            return;
        default:
            printf(ERROR_BOARD_TYPE);
            return;
    }
}
/***************************************************************************************
 * Each of this function handle a different case of our transmitted bits over the GPIO *
 ***************************************************************************************/
States IdleStateHandler(uint32_t* transmittedBits, const int currentBit,const int lastBit) {
    if(lastBit == currentBit){
        return IdleState;
    }
    else{
        *transmittedBits = SET_BIT_AT_LOCATION(currentBit, 1);
        return DataBits;
    }
}


States DataBitsHandler(uint32_t *transmittedBit, int *receivedBits, int *stoppingConditionCounter, const int currentBit,
                       const int initialBit){
    if(*receivedBits == MAXIMAL_TRANSFER ){
        return MaximalBits;
    }
    if(currentBit == initialBit){
        (*stoppingConditionCounter)++;
        if(*stoppingConditionCounter == IDLE_ROUTINE_RATE){
            return StopConditions;
        }
    }
    else{(*stoppingConditionCounter) = 0;}
    (*transmittedBit) += SET_BIT_AT_LOCATION(currentBit,*receivedBits);
    (*receivedBits)++;
    return DataBits;
}


void createArray(const uint32_t transmittedStream, const int receivedBits , uint32_t * outputArray) {
    // Mask the shifted bits to get the 10 bits
    uint16_t maskedBits = transmittedStream & 0x3FF;  // 0x3FF is binary 1111111111
    // Store the masked bits into the output array
    // Our initial bit is the LSB(in transmittedBits , therefore it will need to be at index 0.
    for (int i = 0; i < receivedBits; i++) {
        SET_ARRAY_AT(outputArray, maskedBits, i);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BootStrap(const Platform platform, const int receivePin){
    if(receivePin < 0 || receivePin > 31){
        printf(ERROR_INCORRECT_PIN);
    }
    switch (platform) {
        case Arduino:
            pinMode(receivePin, INPUT);
            break;
        case NRF52840:
            nrf_gpio_cfg_input(receivePin, NRF_GPIO_PIN_NOPULL);
            nrf_gpiote_init();
            break;
        default:
            printf(ERROR_BOARD_TYPE);
            break;
    }
}

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

int ManchesterTransmitting(const Platform platform, const int receivePin, uint32_t* outputData){

    const int initialBit = PlatformDigitalReader(platform, receivePin);  // State of the GPIO when the system starts
    int lastBit = initialBit;  // Initialize last bit to initialBitint isStartBit = FALSE;  // Flag to indicate start bit
    States state = IdleState;
    uint32_t transmittedBits = 0; // The bits which were transmitted from the GPIO.
    int receivedBits = 0;  // The size of the inputted data received from the designated pin.
    int stoppingConditionCounter = 0;  // Count for consecutive initial bits
    PlatformTimeSetUp(platform); // Setting the timer for each Platform.
    unsigned long  timingFactor = PlatformDigitalTimer(platform); // Taking the first lap of the wath.
    int isStoppingCondition = FALSE; // If we have reach stopping condition.
    int outputSize = 0;
    while(!isStoppingCondition){
        while (PlatformDigitalTimer(platform) - timingFactor < BIT_PERIOD_MICROS / 2);
        // Making sure we are getting a new bit.
        int currentBit = PlatformDigitalReader(platform, receivePin);

        switch(state){
            case IdleState:
                state = IdleStateHandler(&transmittedBits ,currentBit, lastBit);
                // Handle Idle case situatio
                break;
            case DataBits:
                state = DataBitsHandler(&transmittedBits, &receivedBits, &stoppingConditionCounter ,
                                        currentBit, initialBit);
                // Checking the bit, raising the counter condition if the case is closing to stop condition/
                if(state == StopConditions || state == MaximalBits){
                }else{break;}
            case StopConditions:
                receivedBits = receivedBits-4; // For stopping condition/
                outputSize = receivedBits/2;
                isStoppingCondition = !isStoppingCondition;
                break;
            case MaximalBits:
                outputSize = receivedBits/2;
                isStoppingCondition = !isStoppingCondition;
                break;
            // If we want to make the function to work constantly, we will create another case of ReturnData
            // and we will set createArray and ReserveManchester there, and we will everything just
            // reset our state and transmitted line.
        }
        lastBit = currentBit;
        timingFactor = PlatformDigitalTimer(platform);
    }
    uint32_t inputData[10];
    createArray(transmittedBits, receivedBits, inputData);
    ReverseManchester(inputData,outputData,receivedBits, outputSize);
    return outputSize;
}




