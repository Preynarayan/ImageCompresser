#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

#define MAX_ARR 5000

/*  Function: take_photo()
    Description: Simulates taking a photo as a black-and-white image represented by
                 an array of characters '1' and '0'. The photo is stored in the out[] array.

    Output: out[]   - an array of characters to store the photo data, as a string of 1 and 0 characters
    Output: rows    - an address to an integer to store the number of rows in the photo
    Output: cols    - an address to an integer to store the number of columns in the photo

    Returns: the total number of characters in the photo data OR 0 if no photo was taken
    
*/
//Forward Declarations
int take_photo(unsigned char out[], int* rows, int* cols);

unsigned char get_bit(unsigned char byte, int bit);
unsigned char set_bit(unsigned char byte, int bit);
unsigned char clear_bit(unsigned char byte, int bit);
void print_raw(unsigned char raw_string[], int rows, int cols);
int pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[]);
void print_packed(unsigned char packed[], int rows, int cols);
int encode_bits(unsigned char packed[], int packed_size, unsigned char encoded_result[]);
void print_encoded(unsigned char encoded[], int encoded_size, int rows, int cols);




//main function
int main() {
   //variables
   unsigned char rawPhoto[MAX_ARR];
   unsigned char packedImg[MAX_ARR];
   unsigned char encodedImg[MAX_ARR];
   int numRows;
   int numCols;
   int imgSize = 1;
   int raw;
   int packed;
   int encoded;


  

   // take a photo, pack it and encode it till image is ++0
    while(imgSize > 0){

    // Call take_photos()

    take_photo(rawPhoto, &numRows, &numCols);
    imgSize = strlen(rawPhoto);
    raw = imgSize;

    //if imgSize is 0 end the loop
    if(imgSize == 0){
        break;
    }

    //Print the raw photo

    printf("Raw Photo (%d bytes):\n", imgSize);
    print_raw(rawPhoto, numRows, numCols);
    printf(" \n");

    //pack the raw array and print it
    imgSize = pack_bits(rawPhoto,imgSize,packedImg);
    packed = imgSize;
    printf("Packed Photo (%d bytes):\n", imgSize);
    print_packed(packedImg, numRows, numCols);
    printf(" \n");

    //encode the packed array and print it
    imgSize = encode_bits(packedImg,imgSize, encodedImg);
    encoded = imgSize;
    printf("Encoded Photo: (%d bytes):\n", imgSize);
    print_encoded(encodedImg, imgSize, numRows, numCols);

    printf("Sizes: raw = %d bytes, packed = %d bytes, encoded = %d bytes\n", raw, packed,encoded );
    printf(" \n");

   }

}

/* Function: print_raw
---------------------------
Purpose:
Prints a raw string of 1s and 0s. The image is dependent on the value rows and columns.
A 1 is "*" and 0 is ".".


Example intput and output:
print_raw(000000011110010010010010011110000000, 6, 6);
-----> output:
......
.****.
.*..*.
.*..*.
.****.
......

Input Parameter Roles:
@param unsigned char raw_string[]   : The raw string given by take_photos()
@param int rows                     : The number of rows in the image
@param int cols                     : The number of columns in the image

Return: returns void
*/
void print_raw(unsigned char raw_string[], int rows, int cols) {


    int i = 0;
    while(raw_string[i] != '\0'){

        if(i == 0){
            if(raw_string[i] == '1'){
                printf("*");
                
            } else if ( raw_string[i] == '0'){
                printf(".");
            }
            i++;
            continue;

        }

        if((i+1) % cols != 0){
            if(raw_string[i] == '1'){ 
                printf("*");
                
            } else if ( raw_string[i] == '0'){
                printf(".");
            }
        } else {
           if(raw_string[i] == '1'){
                printf("*\n");
                
            } else if ( raw_string[i] == '0'){
                printf(".\n");
                
            }
        }


        i++;

    }


}

/* Function: pack_bits
---------------------------
Purpose:
To pack the the 0s and 1s from an unpacked string and return an array of where each character 
now contains 8 pixels worth of information instead of only 1. returns the size of the packed string.
Example intput and output:
pack_bits(00000001 11100100 10010010 01111000 0000, 36, packed_result)
-----> returns:
packed_result = [0b00000001, 0b11100100 ,0b10010010, 0b01111000, 0b00000000]
returns 4.

Parameter roles:
@param unsigned char unpacked_string[]  : An unpacked photo
@param int num_chars                    : size of unpacked_string
@param unsigned char packed_result[]    : a place to store the packed results

Return:
the size of packed_result
 
*/
int pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[]){

    unsigned char currCharUP;
    unsigned char currPackedByte;
    unsigned char currBit   = 0b00000000;

    

    //Loop over each Character in an array
    int i = 0;
    int packSize = 0;
    // While loop to look at every charcter in the string unpacked string
    while(  unpacked_string[i] != '\0'){
        currCharUP = unpacked_string[i];
        

        if(currCharUP == '1'){
            currBit = currBit << 1;
            currBit = set_bit(currBit,0);
            

            currPackedByte = currBit;
            
            // if after setting it i+1 is  multiple of 8 then 
            // add currpackedbyte to packed_resuly
            if((i+1) % 8 ==0){
                
                packed_result[packSize] = currPackedByte;

                packSize++;
                

            } 
            
        } else {
            currBit = currBit << 1;
            currBit = clear_bit(currBit,0);

            
            

            currPackedByte = currBit;
            // if after setting it i+1 is  multiple of 8 then 
            // add currpackedbyte to packed_resuly
            if((i+1) % 8 ==0){
                packed_result[packSize] = currPackedByte;

                packSize++;
                
                

            } 
            
        }
        
        i++;
        
    }

    return packSize;
}

/* Function: print_packed
---------------------------
Purpose:
To print the packed array. 0s are "." and 1s are "*"


Example intput and output:
print_packed([0b00000001, 0b11100100 ,0b10010010, 0b01111000, 0b00000000], 6, 6)
-----> output:
......
.****.
.*..*.
.*..*.
.****.
......

Parameter roles:
@param unsigned char packed[]   : A packed image
@param int rows                 : The number of rows in the image
@param int cols                 : The number of columns in the image

Return:
void


*/
void print_packed(unsigned char packed[], int rows, int cols){
    int i =0;
    int colsCntr = 0;
    //look at every byte in packed
    while((i < ((rows*cols)/8))){



        for(int j = 7; j >= 0; j--){
            if ((colsCntr+1) == cols){
                if(get_bit(packed[i], j) == 0b00000001){
                        printf("*\n");
                } else{
                    printf(".\n");
                }
                colsCntr = 0;
                continue;
            }
            colsCntr++;
            if(get_bit(packed[i], j) == 0b00000001){
                    printf("*");
            } else{
                    printf(".");
            }
            

            }
        

  

        i++;
    }
}

/* Function: encode_bits
---------------------------
Purpose:
Encode a packed string so that a char is how many 1s then how many 0s then 1s and then 0s. 
Add the number of consecutive bits to encoded_results


Example intput and output:
encode_bits([0b00000001, 0b11100100 ,0b10010010, 0b01111000, 0b00000000], 5, encoded_result)

encoded_results = [0d7,0d4,0d2,0d1,0d2,0d1,0d2,0d1,0d2,0d1,0d2,0d4,0d11]
returns 13

Parameter roles:
@param unsigned char packed[]           : A packed array ready to be encoded
@param int packed_size                  : The size of the packed array
@param unsigned char encoded_result[]   : A place to store the encoded results

Return:
the size of the encoded string
*/
int encode_bits(unsigned char packed[], int packed_size, unsigned char encoded_result[]){

    int i = 0;
    int j = 7;
    int encodedSize = 0;
    unsigned char currBit;
    unsigned char cmpto = 0b00000001;
    unsigned char consecCounter = 0b00000001;

    // go through packed
    
    while(i < packed_size ){
        if(i==0 && j==7){
            if(get_bit(packed[0],7) != 0b00000001){
                encoded_result[encodedSize] = 0b00000000;
                encodedSize++;
                cmpto = get_bit(packed[0],7);
            }
            j--;

            continue;

        } 

        if(consecCounter == 0b11111111){
            encoded_result[encodedSize] = consecCounter;
            encodedSize++;
            cmpto =  currBit;
            consecCounter = 0b00000001;
        }

        currBit = get_bit(packed[i], j);

        if(currBit == cmpto){            
            consecCounter++;

        } else{
            cmpto =  currBit;
            encoded_result[encodedSize] = consecCounter;
            consecCounter = 0b00000001;
            encodedSize++;
            
        }
        if(i == packed_size-1 && j ==0){
            encoded_result[encodedSize] = consecCounter;
            encodedSize++;

        }

        j--;
        if(j == -1){
            j = 7;
            i++;
        }

    }
    return encodedSize;

}



/* Function: print_encoded
---------------------------
Purpose:
Prints the encoded bits with the first value being how many 1 therefore "*" and 
the next number being how many 0s therefore "."

Example intput and output:
print_encoded([0d7,0d4,0d2,0d1,0d2,0d1,0d2,0d1,0d2,0d1,0d2,0d4,0d11], 13, 6, 6);
-------> outputs:
......
.****.
.*..*.
.*..*.
.****.
......


Parameter roles:
@param unsigned char encoded[]  : an already encoded string.
@param int encoded_size         : size of encoded string
@param int rows                 : The number of rows in the image
@param int cols                 : The number of columns in the image

Return:
void
*/
void print_encoded(unsigned char encoded[], int encoded_size, int rows, int cols){
    int i = 0;
    int colsCntr = 0;
    unsigned char cmpto = 0b00000001;
    unsigned char curbit;


    
    while(i < encoded_size){
        curbit = encoded[i];

        if(encoded[i] == 0 && cmpto == 0b00000001){
            i++;
            cmpto = 0b00000000;
            continue;
        }
        while(curbit != 0b00000000){
            

            if(cmpto == 0b00000001){
                curbit--;

                if((colsCntr+1) == cols ){
                    printf("*\n");
                    colsCntr = 0;

                } else{
                    printf("*");
                    colsCntr++;

                }

                if(curbit == 0b00000000){
                    cmpto = 0b00000000;
                    continue;

                }
                
                


            }
            if(cmpto == 0b00000000){
                curbit--;
 

                if((colsCntr+1) == cols ){
                    printf(".\n");
                    colsCntr = 0;

                } else{
                    printf(".");
                

                
                    colsCntr++;
                }
                if(curbit == 0b00000000){
                    cmpto = 0b00000001;
                    continue;

                }

            }


        }
        i++;
        
    }
}


/* Function: get_bit
---------------------------
Purpose:
To get the bit at a position "bit" in a byte. returns the byte as a char. 


Example intput and output:
get_bit(0b00001000, 3)
returns ---> a char = 0b00000001

Parameter roles:
@param unsigned char byte   : the byte we want to look in
@param int bit              : position of the bit


Return:
A char of the byte, either 0b00000000 or 0b00000001
*/
unsigned char get_bit(unsigned char byte, int bit) {
    return (byte >> bit) & 1;
}


/* Function: set_bit
---------------------------
Purpose:
To set the bit at a position "bit" in a byte to 1. returns the byte as a char of the byte set with the bit

Example intput and output:
set_bit(0b10111111, 6)
returns ---> a char = 0b11111111

Parameter roles:
@param unsigned char byte   : the byte we want to look in
@param int bit              : position of the bit

Return:
A char of the byte with the bit you want set to 1
*/
unsigned char set_bit(unsigned char byte, int bit) {
   
   
    return byte | (1 << bit);
}

/* Function: clear_bit
---------------------------
Purpose:
To clear the bit at a position "bit" in a byte to 0. returns the byte as a char of the byte set with the bit

Example intput and output:
set_bit(0b11111111, 5)
returns --- a char = 0b11011111

Parameter roles:
@param unsigned char byte   : the byte we want to look in
@param int bit              : position of the bit

Return:
A char of the byte with the bit you want set to 0
*/
unsigned char clear_bit(unsigned char byte, int bit) {
    return byte & ~(1 << bit);
}