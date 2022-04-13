#ifndef NTE_ENGINE
#define NTE_ENGINE

#include "ntskrnl.hpp"

typedef struct napp napp_t; 

namespace NTEXEngine {

    ERR load_app(file_t*, napp_t**);

    ERR run_app(file_t*, napp_t*);

}

#endif