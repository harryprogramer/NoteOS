#ifndef NTBASE
#define NTBASE

typedef char* stdcseq;

typedef int_fast8_t INT8 __attribute__((__mode__(__QI__)));
typedef uint_fast8_t UINT8 __attribute__((__mode__(__QI__)));
typedef int_fast16_t INT16 __attribute__((__mode__(__HI__)));
typedef uint_fast16_t UINT16 __attribute__((__mode__(__HI__)));
typedef int_fast32_t INT32 __attribute__((__mode__(__SI__)));
typedef uint_fast32_t UINT32 __attribute__((__mode__(__SI__)));

#endif