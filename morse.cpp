#include<stdio.h>
#include<iostream>
#include"morse.h"

using namespace std;

alphabet::alphabet(char* filename){
    FILE* file= NULL;
    file=fopen(filename,"r"); //open reference file
    if (file==NULL)
        return;
    char buf[64];
    while (!feof(file)){
        fgets(buf,64,file);
        array[buf[0]]=ditdah(buf+1,length+buf[0]); //initilize reference array with translation of character data
    }
    fclose(file); // close the file
    return;
}
/*
outputs morse code character encoded as an int. 
decimalplace represents where the representation is being appended in the int
if a dit (.) is read, a value of 0b1 is bitshifted by current number of decimal places, ORed onto the output, and then the decimal place is advanced by 2
this effectively appends a 0b01 to the right side of the output int
if a dah (_) is read, a value of 0b111 (three timeunits) is bitshifted by the current number of decimal places, and ORed onto the output, and the decimal place is advanced by 4
this effectivly appends a 0b0111 to the right side of the output int
EXAMPLE: ._.. would be encoded as 0b0101110101. (sub-divided as 0b_01_0111_01_01)
*/
int alphabet::ditdah(char* input,int* length){ 
    int retval=0,i,decimalplace=0;
    for (i=0; input[i]!='\0' ; i++){ //while input character in string is not null character
        switch (input[i]){
            case '.':
                retval = retval|(1<<decimalplace);
                decimalplace+=2;
                break;
            case '-':
                retval = retval|(7<<decimalplace);
                decimalplace+=4;
                break;
        }
    }   
    *length=decimalplace-1; //stores length of morse code binnary value indirectly in length value passed in. This is put in the length array by alphabet().
    return retval;
}

int alphabet::translate(char input){
    return array[input];
}

int alphabet::getLength(char input){
    return length[input];
}
