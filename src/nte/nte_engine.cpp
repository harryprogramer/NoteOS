#include "nte_engine.hpp"

using namespace NTSKernel;

struct napp {
    cseq name;
};

UINT32 get_int32(UINT8* buf){
    return (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + buf[3];
}

UINT16 get_int16(UINT8* buf){
    return (buf[0] << 8 | buf[1]);
}


String get_hex(UINT32 dec){
    String hex = String(dec, HEX);
    hex.toUpperCase();
    return "0x" + hex;
}

ERR NTEXEngine::load_app(file_t* app_file, napp_t** app){
    

    cseq filename = nt_get_filename(app_file);
    if(strcmp(filename.c_str(), "") == 0|| strlen(filename.c_str()) == 0){
        return NT_FILE_CLOSED;
    }
    
    UINT8 header[24];

    napp_t* application;
    ERR malloc_app_error = nt_malloc((void**) &application, sizeof(napp_t));
    if(malloc_app_error != OK){
        nt_log("ntenginev1: cannot create app " + filename +  " due malloc fault: " + get_hex(malloc_app_error));
        return malloc_app_error;
    }
    *app = application;

    nt_read_file(app_file, header, 24);
    UINT32 app_version = get_int32(&header[0]);
    //UINT16 nte_version = get_int16(&header[4]);
    char app_name[13];
    memcpy(app_name, &header[6], 12);
    
    for(int i = 0; i < 12; i++){
        if(!isAscii(app_name[i])){
            nt_log("kernel: app " + filename + " has invalid name at " + String(i, DEC) + " byte", ERROR);
            nt_log("kernel: aborting launch for " + filename + " app", INFO);
            return NT_INVALID_EXECUTABLE_SIGNATURE;
        }
    }
    
    app_name[12] = '\0';
    nt_log("kernel: running [" + nt_get_filename(app_file) + "] executable app: " + String(app_name) + ", version: " + String(app_version));

    return OK;
}

ERR NTEXEngine::run_app(file_t* file, napp_t* app){

}