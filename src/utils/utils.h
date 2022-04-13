#ifndef NTUTILS
#define NTUTILS

#ifdef __cplusplus
extern "C"
{
#endif

#include "ntbase.h"

// make hex from 4 bytes unsigned number
stdcseq make_hex32(UINT32);

// make hex from 2 bytes unsigned number
stdcseq make_hex16(UINT16);

// make hex from 1 byte unsigned number
stdcseq make_hex8(UINT8);

// support only ascii
void to_upper_case_ascii(char* __src, UINT32 __size);

#ifdef __cplusplus
}
#endif


#endif