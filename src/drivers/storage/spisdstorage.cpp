#include <SPI.h>
#include <SD.h>

#include "spisdstorage.hpp"

using namespace NTSKernel;


ERR check_file(file_t* file){
    if(file == NULL){
        return UNDEFINED;
    }

    if(!file -> sd_file){
        return NT_FILE_CLOSED;
    }

    return OK;
}

ERR SPISDStorage::open_file(file_t** file, PATH filename, BOOLN create_file, BOOLN write_file){
    UINT8 permissions = (write_file ? O_READ | O_WRITE : O_READ) | (create_file ? O_CREAT : 0);
    nt_log("sd_card: opening file: " + cseq(filename) + " with permissions: 0x" + String(permissions, HEX), INFO);

    File sd_file = SD.open(filename, FILE_WRITE);

    if(!sd_file){
        nt_log("sd_card: file " + String(filename) + " not found or cannot be open", WARN);
        *file = NULL;
        return NT_FILE_NOT_FOUND;
    };

    file_t* new_file = (file_t*) malloc(sizeof(file_t));
    new_file -> filename = filename;
    new_file -> sd_file = sd_file;
    *file = new_file;
    return OK;
}

ERR SPISDStorage::read_file(file_t* file, UINT8* buf, UINT16 size){
    UINT16 i;

    ERR err = check_file(file);
    if(err != OK){
        return err;
    }

    while(file -> sd_file.available()){
        buf[i] = file -> sd_file.read();

        if(++i > size){
            break;
        }
    }

    return OK;
}

ERR SPISDStorage::flush_file(file_t* file){
    nt_log("sd_card: flushing file " + String(file -> filename), INFO);
    file -> sd_file.flush();
    return OK;
}
    
ERR SPISDStorage::write_to_file(file_t* file, UINT8* buf, UINT16 size){
    if(buf == NULL){
        return NT_FILE_NOT_FOUND;
    }

    ERR err = check_file(file);
    if(err != OK){
        return err;
    }
    
    for(UINT16 i = 0; i < size; i++){
        File sd = file -> sd_file;
        
        if(sd.write(buf[i]) == (size_t) -1){
            nt_log("sd_card: write_to_file() io fault, filename: " + String(file -> filename), ERROR);
            return IO_FAULT;
        }
    
    }

    return OK;
}

ERR SPISDStorage::delete_file(file_t* file_t){
    return OK;
}

ERR SPISDStorage::close_file(file_t* file){
    ERR err = check_file(file);
    if(err != OK){
        return err;
    }

    nt_log("sd_card: Closing file " + String(get_filename(file)), INFO);
    File sd_file = file -> sd_file;
    sd_file.close();
    free(file);
    return OK;  
}

BOOLN SPISDStorage::available(){
    return true;
}

trnsprt SPISDStorage::get_trnsprt(){
    return TRNSPRT_SPI;
}

void SPISDStorage::begin_device(){
    if(!SD.begin(53)){
        is_available = false;
        nt_log(F("sd_card: Cannot enable sd storage device."), INFO);
    }else {
        is_available = true;
        nt_log(F("sd_card: Device initialized succesful."), INFO);
    }
}

NTSKRNL String SPISDStorage::get_filename(file_t* file){
    ERR err = check_file(file);
    if(err != OK){
        return "";
    }

    return file -> filename;
}

cseq SPISDStorage::drvr_name(){
    return F("SD Card (SPI)");
}

void SPISDStorage::stop_device(){

}