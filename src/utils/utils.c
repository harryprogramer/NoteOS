#include <string.h>
#include <stdio.h>
#include "utils.h"


char hex_buf32[11];
char hex_buf16[7];
char hex_buf8[5];

void to_upper_case_ascii(char* __src, UINT32 __size){
    for(UINT32 i = 0; i < __size; i++){
        char character = __src[i];
        if((character - 0x60) * (character - 0x7b) >= 0){ // up case
            continue;
        }else if((character - 0x40) * (character - 0x5b) >= 0){ // low case
            __src[i] = character - 32;
        }else {
            i++;
        }
    }
}

stdcseq make_hex32(UINT32 dec){
    memset(hex_buf32, 0, 11);
    sprintf(hex_buf32, "0x%08lx", dec);
    hex_buf32[10] = '\0'; 
    to_upper_case_ascii(&hex_buf32[2], 11);
    return hex_buf32;
}

stdcseq make_hex16(UINT16 dec){
    memset(hex_buf16, 0, 7);
    sprintf(hex_buf16, "0x%04x", dec);
    hex_buf16[10] = '\0'; 
    to_upper_case_ascii(&hex_buf16[2], 11);
    return hex_buf16;
}

stdcseq make_hex8(UINT8 dec){
    memset(hex_buf8, 0, 5);
    sprintf(hex_buf8, "0x%02x", dec);
    hex_buf8[10] = '\0'; 
    to_upper_case_ascii(&hex_buf8[2], 11);
    return hex_buf8;
}