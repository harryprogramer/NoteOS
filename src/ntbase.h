#ifndef NTBASE
#define NTBASE

typedef char* stdcseq;

typedef signed int INT8 __attribute__((__mode__(__QI__)));
typedef unsigned int UINT8 __attribute__((__mode__(__QI__)));
typedef signed int INT16 __attribute__((__mode__(__HI__)));
typedef unsigned int UINT16 __attribute__((__mode__(__HI__)));
typedef signed int INT32 __attribute__((__mode__(__SI__)));
typedef unsigned int UINT32 __attribute__((__mode__(__SI__)));

#endif