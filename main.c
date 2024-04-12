 #include <stdio.h>
#include "ProjectHeader.h"
#include <assert.h>


 typedef struct unit32_t unit32_t;

 void DisplayArray(const uint32_t* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


void TestEncodingDecoding(){
    // Test data
    const uint32_t input1[] = {1, 0, 1, 0, 0, 1};  // Input data bits
    const int dataSize1 = sizeof(input1) / sizeof(input1[0]);
    const int encodedSize1 = dataSize1 * 2;  // Each data bit is encoded as 2 bits in Manchester encoding
    uint32_t encoded1[encodedSize1];  // Array to store encoded bits
    uint32_t decoded1[dataSize1];     // Array to store decoded bits

    // Encode the input data
    assert(ManchesterEncode(input1, encoded1, dataSize1, encodedSize1) == TRUE);

    // Decode the encoded data
    assert(ReverseManchester(encoded1, decoded1, encodedSize1, dataSize1) == TRUE);

    // Assert that the decoded data matches the original input
    for (int i = 0; i < dataSize1; i++) {
        assert(input1[i] == decoded1[i]);
    }

    // Test data 2
    const uint32_t input2[] = {0, 1, 1, 0, 1};
    const int dataSize2 = sizeof(input2) / sizeof(input2[0]);
    const int encodedSize2 = dataSize2 * 2;
    uint32_t encoded2[encodedSize2];
    uint32_t decoded2[dataSize2];

    assert(ManchesterEncode(input2, encoded2, dataSize2, encodedSize2) == 1);
    assert(ReverseManchester(encoded2, decoded2, encodedSize2, dataSize2) == 1);
    for (int i = 0; i < dataSize2; i++) {
        assert(input2[i] == decoded2[i]);
    }

    // Test data 3
    const uint32_t input3[] = {1, 1, 1, 1, 1};
    const int dataSize3 = sizeof(input3) / sizeof(input3[0]);
    const int encodedSize3 = dataSize3 * 2;
    uint32_t encoded3[encodedSize3];
    uint32_t decoded3[dataSize3];

    assert(ManchesterEncode(input3, encoded3, dataSize3, encodedSize3) == 1);
    assert(ReverseManchester(encoded3, decoded3, encodedSize3, dataSize3) == 1);
    for (int i = 0; i < dataSize3; i++) {
        assert(input3[i] == decoded3[i]);
    }

    // Test data 4
    const uint32_t input4[] = {0, 0, 0, 0, 0};
    const int dataSize4 = sizeof(input4) / sizeof(input4[0]);
    const int encodedSize4 = dataSize4 * 2;
    uint32_t encoded4[encodedSize4];
    uint32_t decoded4[dataSize4];

    assert(ManchesterEncode(input4, encoded4, dataSize4, encodedSize4) == 1);
    assert(ReverseManchester(encoded4, decoded4, encodedSize4, dataSize4) == 1);
    for (int i = 0; i < dataSize4; i++) {
        assert(input4[i] == decoded4[i]);
    }

    // Test data 5
    const uint32_t input5[] = {1, 0, 1, 1, 0, 0, 1, 1};
    const int dataSize5 = sizeof(input5) / sizeof(input5[0]);
    const int encodedSize5 = dataSize5 * 2;
    uint32_t encoded5[encodedSize5];
    uint32_t decoded5[dataSize5];

    assert(ManchesterEncode(input5, encoded5, dataSize5, encodedSize5) == 1);
    assert(ReverseManchester(encoded5, decoded5, encodedSize5, dataSize5) == 1);
    for (int i = 0; i < dataSize5; i++) {
        assert(input5[i] == decoded5[i]);
    }
}

void TestReverseManchester(){
    // Test cases 1: Checking parameters
    uint32_t output1[1];
    assert(ReverseManchester(NULL, output1, 3, 1) == FALSE);

    uint32_t input2[] = {1, 0, 1};
    assert(ReverseManchester(input2, NULL, 3, 1) == FALSE);

    uint32_t input3[] = {};
    uint32_t output3[1];
    assert(ReverseManchester(input3, output3, 0, 1) == FALSE);

    uint32_t input4[] = {1, 0, 1};
    uint32_t output4[1];
    assert(ReverseManchester(input4, output4, 3, 0) == FALSE);

    // Test case 2: Valid input and output
    uint32_t input5[] = {1, 0, 1};
    uint32_t output5[1];
    assert(ReverseManchester(input5, output5, 3, 1) == TRUE);
    printf("Output array for test case 5: ");
    DisplayArray(output5, 1);
    const int pattern5 = 1;
    printf(PATTERN_CHECK(pattern5));
    // Additional test cases
    // Test case 6: Input size not equal to half the output size
    uint32_t input6[] = {1, 0, 0, 1}; // Size is not half of output size
    uint32_t output6[2];
    assert(ReverseManchester(input6, output6, 4, 2) == TRUE);
    printf("Output array for test case 6: ");
    DisplayArray(output6, 2);
    const int pattern6 = 10;
    printf(PATTERN_CHECK(pattern6));

    uint32_t input7[] = {1, 0, 1,0,1,};
    uint32_t output7[1]; // Output size is too small to hold the decoded data
    assert(ReverseManchester(input7, output7, 5, 1) == FALSE);

    uint32_t input8[] = {1, 0, 1, 0, 1, 0}; // Alternating bits in Manchester encoding
    uint32_t output8[3];
    assert(ReverseManchester(input8, output8, 6, 3) == TRUE);
    printf("Output array for test case 8: ");
    DisplayArray(output8, 3);
    const int pattern8 = 111;
    printf(PATTERN_CHECK(pattern8));
}

void TestManchesterEncoding(){
    // Test case 1: Basics input checks
    uint32_t output1[6];
    assert(ManchesterEncode(NULL, output1, 3, 6) == FALSE);

    uint32_t input2[] = {1, 0, 1};
    assert(ManchesterEncode(input2, NULL, 3, 6) == FALSE);

    uint32_t input3[] = {};
    uint32_t output3[6];
    assert(ManchesterEncode(input3, output3, 0, 6) == FALSE);

    uint32_t input4[] = {1, 0, 1};
    uint32_t output4[6];
    assert(ManchesterEncode(input4, output4, 3, 0) == FALSE);

    uint32_t input5[] = {1, 0, 1};
    uint32_t output5[6];
    assert(ManchesterEncode(input5, output5, 3, 6) == TRUE);
    printf("Output array for test case 1.5: \n" );
    DisplayArray(output5, 6);
    const int pattern5 = 100110;
    printf(PATTERN_CHECK(pattern5));

    // Test cases 2: Valid input, but arrays doesn't much format or bits.
    uint32_t input6[] = {1, 0, 1};
    uint32_t output6[2];
    assert(ManchesterEncode(input6, output6, 3, 2) == FALSE);
    // wrongly output array size.


    uint32_t input7[] = {1, 0, 2}; // Contains non-binary value (2)
    uint32_t output7[6];
    assert(ManchesterEncode(input7, output7, 3, 6) == FALSE);


    // Test cases 3: Different types of inputs.
    const int largeSize = 10000;
    uint32_t input8[largeSize];
    uint32_t output8[largeSize * 2];
    for (int i = 0; i < largeSize; i++) {
        input8[i] = i % 2; // Alternating 0's and 1's
    }
    assert(ManchesterEncode(input8, output8, largeSize, largeSize * 2) == TRUE);
    printf("Output array for test case 3.1: \n");
    DisplayArray(output8, largeSize * 2);
    const int pattern8 = 0110;
    printf(PATTERN_CHECK(pattern8));


    uint32_t input9[] = {0, 0, 0};
    uint32_t output9[6];
    assert(ManchesterEncode(input9, output9, 3, 6) == TRUE);
    printf("Output array for test case 3.2: \n");
    DisplayArray(output9, 6);
    const int pattern9 = 010101;
    printf(PATTERN_CHECK(pattern9));

    uint32_t input10[] = {1, 1, 1};
    uint32_t output10[6];
    assert(ManchesterEncode(input10, output10, 3, 6) == TRUE);
    printf("Output array for test case 3.3: \n");
    DisplayArray(output10, 6);
    const int pattern10 = 101010;
    printf(PATTERN_CHECK(pattern10));

    uint32_t input11[] = {0, 1, 0, 1, 0, 1};
    uint32_t output11[12];
    assert(ManchesterEncode(input11, output11, 6, 12) == TRUE);
    printf("Output array for test case 3.4: \n");
    DisplayArray(output11, 12);
    const int pattern12 = 011001100110;
    printf(PATTERN_CHECK(pattern12));

    // Test case 13: Odd input size
    uint32_t input13[] = {1, 0, 1, 0, 1};
    uint32_t output13[10];
    assert(ManchesterEncode(input13, output13, 5, 10) == TRUE);
    printf("Output array for test case 3.5: \n");
    DisplayArray(output13, 10);
    const int pattern13 = 1001100110;
    printf(PATTERN_CHECK(pattern13));
}
int main() {
    TestManchesterEncoding();
    TestReverseManchester();
    TestEncodingDecoding();
    return 0;
}


