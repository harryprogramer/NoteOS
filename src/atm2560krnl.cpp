#ifndef ATM2560KRNL
#define ATM2650KRNL

#undef __AVR_ATmega2560__
#define __AVR_ATmega2560__ // only for code highlight, remove while compiling

#if defined(__AVR_ATmega2560__)

#include <Arduino.h>
#include <WString.h>
#include <WCharacter.h>
#include <stdio.h>
#include <string.h>

#include "ntskrnl.hpp"
//#include "utils.h"

#define ABOUT (cseq) "NoteOS 8-bit v1.0 , Arch: (ATMega2560), 2022"

#include "drivers/packets_manager.h"

#if SH1106_DRIVER
#include "drivers/graphic/sh1106_driver.hpp"
#endif

#if SSD1306_DRIVER
#include "drivers/graphic/ssd1306_driver.hpp"
#endif

#if SIM800L_DRIVER
#include "drivers/gsm/sim800l_driver.hpp"
#endif

#include "drivers/storage/spisdstorage.hpp"

#define MAX_DRIVER_ABOUT_NAME 64
#define IDVC_DRIVER_MAX_REGISTRY_SIZE 32
#define IDVC_DRIVER_REGISTRY_SIZE_DATA_TYPE UINT8

#define IDVCREGISTRY_OUT_OF_MEMORY          0x01
#define IDVCREGISTRY_DRIVER_REGISTRY_FULL   0x02
#define IDVCREGISTRY_NO_DRIVER              0x03

const UINT8 epd_bitmap_noteos [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xc3, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xc1, 0xf1, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xc1, 0xf1, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xc0, 0xf1, 0xff, 0xff, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 
	0xff, 0xc0, 0xf1, 0xf8, 0x1f, 0x00, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 
	0xff, 0xc6, 0x71, 0xf3, 0x8f, 0x8f, 0xf3, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 
	0xff, 0xc6, 0x71, 0xe3, 0xc7, 0x8f, 0xe7, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 
	0xff, 0xc7, 0x31, 0xc7, 0xc7, 0x8f, 0xc3, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 
	0xff, 0xc7, 0x31, 0xc7, 0xe7, 0x8f, 0xc0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 
	0xff, 0xc7, 0x81, 0xc7, 0xe7, 0x8f, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 
	0xff, 0xc7, 0x81, 0xe7, 0xc7, 0x8f, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 
	0xff, 0xc7, 0xc1, 0xe3, 0xc7, 0x8f, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x0f, 0xff, 0xff, 
	0xff, 0xc7, 0xc1, 0xf1, 0x8f, 0xc7, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xff, 0xff, 
	0xff, 0xc7, 0xe3, 0xfc, 0x3f, 0xe1, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x7f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x3f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x60, 0x1f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x78, 0x1f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7c, 0x1f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7e, 0x0f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7e, 0x1f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0x1f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0x1f, 0xff, 
	0xff, 0xff, 0xff, 0xe0, 0x3f, 0xe0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0x3f, 0xff, 
	0xff, 0xff, 0xff, 0xcf, 0x9f, 0xcf, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0x3f, 0xff, 
	0xff, 0xff, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0x7f, 0xff, 
	0xff, 0xff, 0xff, 0x1f, 0xc7, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0x7f, 0xff, 
	0xff, 0xff, 0xff, 0x1f, 0xc7, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x1f, 0xc7, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x1f, 0xc3, 0xc0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x1f, 0xc3, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x1f, 0xc7, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x1f, 0xc7, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x1f, 0xc7, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x8f, 0x8f, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xc7, 0x1f, 0x9e, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf0, 0x7f, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0c, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x01, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x07, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

extern unsigned int __heap_start;
extern void *__brkval;

IDVCHIDriver_Dsply* selected_graphic = NULL;

BOOLN is_logging_to_graphic = false;

typedef struct idvc_device_t {
    idvc_id id;
    IDVCHIDriver* drvr;
} idvc_device_t;


String make_hex(UINT32 dec){
    String hex = String(dec, HEX);
    hex.toUpperCase();
    return "0x" + hex;
}


class IDVC_Registry {
    private:
        idvc_device_t *registry = NULL;
        UINT8 index = 0;

    public:
        IDVC_Registry(){
            registry = (idvc_device_t*) malloc(sizeof(idvc_device_t));
        }

        ERR add_dvc(IDVCHIDriver* drvr, idvc_id id){

            registry = (idvc_device_t*) realloc(registry, ++index * sizeof(idvc_device_t));
            if(registry == NULL){
                NTSKernel::nt_log(F("idvc_bus: Driver registry is out of memory. Operation cancelled."), CRIT);
                return IDVCREGISTRY_OUT_OF_MEMORY;
            }
            registry[index - 1] = (idvc_device_t){id, drvr};

            UINT16 drvr_name = strlen(drvr -> drvr_name().c_str());
            if(drvr_name > MAX_DRIVER_ABOUT_NAME){
                drvr_name = MAX_DRIVER_ABOUT_NAME;
            }

            cseq msg = "idvc_bus: Driver [" + drvr -> drvr_name() + "] has been added to registry.";
            NTSKernel::nt_log(msg, INFO);

            return OK;
        }

        ERR get_dvc(idvc_id id, IDVCHIDriver** source_drvr){
            for(int i = 0; i < index; i++){
                idvc_device_t drvr = registry[i];
                if(drvr.id == id){
                    *source_drvr = drvr.drvr;
                    return OK;
                }
            }
            
            *source_drvr = NULL;
            return IDVCREGISTRY_NO_DRIVER;
        }

        ERR get_dvcs(idvc_device_t** driver, IDVC_DRIVER_REGISTRY_SIZE_DATA_TYPE *__size){
            if(registry == NULL){
                NTSKernel::nt_log(F("idvc_bus: Driver register is empty or not allocated yet."), WARN);
                return IDVCREGISTRY_NO_DRIVER;
                *driver = NULL;
            }
            *driver = registry;
            if(__size != NULL) *__size = get_drivers_count();
            return OK;
        }

        ERR delete_dvc(idvc_id type){
            //idvc_device_t* new_registry;
            //ERR err = NTSKernel::nt_malloc((void**) &new_registry, get_drivers_count() - 1 * sizeof(idvc_device));
            //if(err != OK){
            //   NTSKernel::nt_log("idvc_bus: cannot rebuild registry, malloc fault: " + make_hex(err), INFO);
            //    return err;
            //}

            // TODO

            return OK;

        }

        ERR stop_dvcs(BOOLN __clear_registry){
            idvc_device_t* devices;
            get_dvcs(&devices, NULL);
            for(IDVC_DRIVER_REGISTRY_SIZE_DATA_TYPE i = 0; i < get_drivers_count(); i++){
                NTSKernel::nt_log("idvc_bus: Stopping device " + String(devices[i].drvr -> drvr_name()), INFO);
                devices[i].drvr -> stop_device();
            }

            if(__clear_registry) {
                NTSKernel::nt_log(F("idvc_bus: Uninstalling all drivers."), INFO);
                NTSKernel::nt_mem_free(registry);
            }

            return OK;
        }
        
        size_t get_used_space(){
            return sizeof(idvc_device_t) * index;
        }

        IDVC_DRIVER_REGISTRY_SIZE_DATA_TYPE get_drivers_count(){
            return index;
        }
};


IDVC_Registry *idvc_registry = NULL;

struct umsb_device {

};


void init_drivers(){
    NTSKernel::nt_log(F("kernel: Initializing drivers."), INFO);

#if SH1106_DRIVER
    SH1106OLEDDriver* scrn_drvr = new SH1106OLEDDriver;
    NTSKernel::nt_load_idvc_drvr(scrn_drvr, IDVC_DISPLAY);
#endif

#if SSD1306_DRIVER 
    OLEDIDVCHIDDriver* scrn_drvr = new OLEDIDVCHIDDriver;
    NTSKernel::nt_load_idvc_drvr(scrn_drvr, IDVC_DISPLAY);
#endif

#if SIM800L_DRIVER
    SIM800L_Driver* gsm_drvr = new SIM800L_Driver;
    NTSKernel::nt_load_idvc_drvr(gsm_drvr, IDVC_GSM);
#endif

    SPISDStorage* storage_drvr = new SPISDStorage;
    NTSKernel::nt_load_idvc_drvr(storage_drvr, IDVC_STORAGE);
}


void start_drivers(){
    NTSKernel::nt_log("kernel: Starting all devices", INFO);

    idvc_device_t* drivers;
    IDVC_DRIVER_REGISTRY_SIZE_DATA_TYPE size;

    ERR err = idvc_registry -> get_dvcs(&drivers, &size);
    if(err == OK){
        for(IDVC_DRIVER_REGISTRY_SIZE_DATA_TYPE i = 0; i < size; i++){
            idvc_device_t device = drivers[i];
            IDVCHIDriver* driver = device.drvr;
            cseq device_hex = make_hex(device.id);
            cseq msg = "idvc_bus: Starting [" + device_hex + "] device with [" + String(driver -> drvr_name()) + "] driver.";
            cseq msg2 = "idvc_bus: Device [" + device_hex + "] use transport [" + make_hex(driver -> get_trnsprt()) + "]";
            NTSKernel::nt_log(msg, INFO);
            NTSKernel::nt_log(msg2, INFO);

            driver -> begin_device();
            if(!driver -> available()){
                String msg3 = "idvc_bus: At the moment device [" + device_hex + "] is unavailable";
                NTSKernel::nt_log((msg3.c_str()), INFO);
            }
        }
    }else {
        String msg = "idvc_bus: Cannot fetch drivers for start sequence due error: [" + make_hex(err)  + "]";
        NTSKernel::nt_log((msg.c_str()), ERROR);
    }
}

void init_graphic(){    
    IDVCHIDriver* drvr;
    IDVCHIDriver_Dsply* display;
    if(NTSKernel::nt_get_idvc_drvr(&drvr, IDVC_DISPLAY) != OK){
        NTSKernel::nt_log(F("kernel: Graphic not found in current environment."), INFO);
        return;
    }
    
    display = reinterpret_cast<IDVCHIDriver_Dsply*>(drvr);
    
    if(display -> available()){
        display -> clr_scrn();
        selected_graphic = display;
        String msg = "kernel: Graphics device [" + String(display -> drvr_name()) + "] is selected as primary monitor.";
        NTSKernel::nt_log(msg, INFO);
        display -> render_bitmap(0, 0, epd_bitmap_noteos, 128, 64, WHITE);
        
    }else {
        NTSKernel::nt_log(F("kernel: Graphics is found but display device is unreachable at the moment."), INFO);
    }
}

BOOLN is_booted = false;

cseq translate_loglevel(LOG_LEVEL level){
    if(level == INFO){
        return "INFO";
    }else if(level == WARN){
        return "WARN";
    }else if(level == ERROR){
        return "ERROR";    
    }else if(level ==  CRIT){
        return "CRIT";
    }else if(level == TRACE){
        return "TRACE";
    }else if(level == DEBUG){
        return "DEBUG";
    }else if(level == CRIT){
        return "CRIT";
    }else if(level == PANIC){
        return "PANIC";
    }else {
        return "nolevel";
    }
}

void NTSKRNL NTSKernel::nt_log(const cseq msg, LOG_LEVEL level = INFO){
    cseq level_str = translate_loglevel(level);
    if(strcmp(level_str.c_str(), "nolevel") != 0){
        Serial.print("[");
        Serial.print(String(millis() / 1000.0, 4));
        Serial.print("] [");
        Serial.print(level_str);
        Serial.print("]: ");
        Serial.print(msg);
        Serial.print("\n");
        Serial.flush();  
    }

    if(selected_graphic != NULL && is_logging_to_graphic){
        selected_graphic -> print(String(msg));
    }

}

void NTSKRNL NTSKernel::nt_boot_sequence(void) {
    if(is_booted){
        nt_log(F("Boot sequence request while system running."), WARN);    
    }

    delay(2000);
    Serial.begin(9600);

    String msg PROGMEM = "Booting: " + ABOUT;
    nt_log(msg, INFO);


    init_drivers();

    start_drivers();

    nt_log(F("kernel: Loading graphics."), INFO);
    init_graphic();

    is_booted = true;
}

void NTSKRNL NTSKernel::nt_srl_trnmt(const cseq data){

}


ERR NTSKRNL NTSKernel::nt_load_idvc_drvr(IDVCHIDriver* drvr, idvc_id id)
{
    if(idvc_registry == NULL){
        idvc_registry = new IDVC_Registry;
    }

    idvc_registry -> add_dvc(drvr, id);
    return OK;
}

void NTSKRNL NTSKernel::nt_cls_krnl_sequence(){
    if(is_booted){
        nt_log(F("kernel: Shutting down kernel."), INFO);

        delete idvc_registry;
    }else {
        nt_log(F("kernel: Requested kernel close operation but system is not already booted."), ERROR);
    }
}

UINT32 NTSKRNL NTSKernel::nt_get_free_sram(){
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void NTSKRNL NTSKernel::nt_mem_free(void* ptr){
    if(ptr != NULL){
        free(ptr);
        ptr = 0;
    }else {
        char buf[128];
        sprintf(buf, "kernel: Pointer at %p cannot be released because address is already 0.", &ptr);
        nt_log(buf, ERROR);
    }
}

cseq NTSKRNL NTSKernel::nt_about(){
    return ABOUT;
}

ERR NTSKRNL NTSKernel::nt_get_dsply(IDVCHIDriver_Dsply** driver){
    *driver = selected_graphic;
    return OK;
}

ERR NTSKRNL NTSKernel::nt_get_idvc_drvr(IDVCHIDriver** drvr, idvc_id id){
    ERR err = idvc_registry->get_dvc(id, drvr);
    if(err != OK){
        nt_log("kernel: Driver [" + make_hex(id) + "] is cannot be get from registry due: [" + make_hex(err) + "]", WARN);
        *drvr = NULL;
        return err;
    }

    return OK;
}

void NTSKRNL nt_set_logging_to_graphic(BOOLN is_logging){
    is_logging_to_graphic = is_logging;
}

ERR NTSKRNL NTSKernel::nt_open_file(file_t** file, PATH path, BOOLN create_file, BOOLN write_file){
    IDVCHIDriver* driver;
    ERR err = nt_get_idvc_drvr(&driver, IDVC_STORAGE);
    
    if(err != OK){
        if(err == IDVC_ERROR_NO_DEVICE){
            nt_log(F("kernel: no storage device found, cannot open file, nt_open_file();"), WARN);
            return err;
        }else {
            nt_log("kernel: cannot get storage device, error: " + make_hex(err) + ", aborting: nt_open_file();", ERROR);
            return err;
        }
    }

    nt_log("kernel: opening file " + String(path) + " from storage " + String(driver -> drvr_name()), INFO);
    IDVCHIDriver_Storage* storage = reinterpret_cast<IDVCHIDriver_Storage*>(driver);
    return storage -> open_file(file, path, create_file, write_file);
}

ERR NTSKRNL NTSKernel::nt_close_file(file_t* file){
    IDVCHIDriver* driver = NULL;
    ERR err = nt_get_idvc_drvr(&driver, IDVC_STORAGE);

    if(err != OK){
        if(err == IDVC_ERROR_NO_DEVICE){
            nt_log(F("kernel: no storage device found, cannot open file, nt_close_file();"), WARN);
            return err;
        }else {
            nt_log("kernel: cannot get storage device, error: " + make_hex(err) + ", aborting: nt_close_file();", ERROR);
            return err;
        }
    }
 
    IDVCHIDriver_Storage* storage = reinterpret_cast<IDVCHIDriver_Storage*>(driver);
    String filename = storage -> get_filename(file);
    nt_log("kernel: closing file " + filename + " from storage " + String(driver -> drvr_name()), INFO);


    return storage -> close_file(file);
}

ERR NTSKRNL NTSKernel::nt_flush_file(file_t* file){
    IDVCHIDriver* driver = NULL;
    ERR err = nt_get_idvc_drvr(&driver, IDVC_STORAGE);

    if(err != OK){
        if(err == IDVC_ERROR_NO_DEVICE){
            nt_log(F("kernel: no storage device found, cannot open file, nt_flush_file();"), WARN);
            return err;
        }else {
            nt_log("kernel: cannot get storage device, error: " + make_hex(err) + ", aborting: nt_flush_file();", ERROR);
            return err;
        }
    }

    IDVCHIDriver_Storage* storage = reinterpret_cast<IDVCHIDriver_Storage*>(driver);
    return storage -> flush_file(file);
}

ERR NTSKRNL NTSKernel::nt_delete_file(file_t* file_t){
    return OPERATION_UNAVAILABLE;
}

ERR NTSKRNL NTSKernel::nt_read_file(file_t* file, UINT8* buf, UINT16 size){
    IDVCHIDriver* driver = NULL;
    ERR err = nt_get_idvc_drvr(&driver, IDVC_STORAGE);

    if(err != OK){
        if(err == IDVC_ERROR_NO_DEVICE){
            nt_log(F("kernel: no storage device found, cannot open file, nt_write_file();"), WARN);
            return err;
        }else {
            nt_log("kernel: cannot get storage device, error: " + make_hex(err) + ", aborting: nt_read_file();", ERROR);
            return err;
        }
    }

    IDVCHIDriver_Storage* storage = reinterpret_cast<IDVCHIDriver_Storage*>(driver);
    return storage -> read_file(file, buf, size);
}


ERR NTSKRNL NTSKernel::nt_malloc(void** __mem, size_t size){
    if(size > nt_get_free_sram()){
        nt_log("kernel: cannot malloc memory for size " + cseq(size) + ", not enough memory, size > nt_get_free_sram();", CRIT);
        return NT_ALLOC_NOT_ENOUGH_MEMORY;
    }
    *__mem = malloc(size);
    
    if(*__mem == NULL){
        nt_log("kernel: cannot malloc memory for size " + cseq(size ) + ", malloc() == NULL", PANIC);
        nt_reboot(C("malloc()"), C("allocation fault"), true);
        return NT_ALLOC_ALLOC_FAULT;
    }

    return OK;
}

ERR NTSKRNL NTSKernel::nt_calloc(void** __mem, size_t size){
    return OPERATION_UNAVAILABLE;
}

void NTSKRNL NTSKernel::nt_reboot(char* source, char* reason, BOOLN force){
    nt_log("kernel: src: " + String(source) + ", reason: " + String(reason) + ", reboot requested.", INFO);
    if(!force){
        idvc_registry -> stop_dvcs(true);
    }
    nt_log(F("kernel: restart confirmed, calling reboot, goodbye!"), INFO);
    ((void(*)(void))0)();
}

ERR NTSKRNL NTSKernel::nt_write_file(file_t* file, UINT8* buf, UINT16 size){
    IDVCHIDriver* driver = NULL;
    ERR err = nt_get_idvc_drvr(&driver, IDVC_STORAGE);

    
    if(err != OK){
        if(err == IDVC_ERROR_NO_DEVICE){
            nt_log(F("kernel: no storage device found, cannot open file, nt_write_file();"), WARN);
            return err;
        }else {
            nt_log("kernel: cannot get storage device, error: " + make_hex(err) + ", aborting: nt_write_file();", ERROR);
            return err;
        }
    }

    IDVCHIDriver_Storage* storage = reinterpret_cast<IDVCHIDriver_Storage*>(driver);
    return storage -> write_to_file(file, buf, size);
}

BOOLN NTSKRNL NTSKernel::nt_is_file_open(file_t* file){
    IDVCHIDriver* driver = NULL;
    ERR err = nt_get_idvc_drvr(&driver, IDVC_STORAGE);

    
    if(err != OK){
        if(err == IDVC_ERROR_NO_DEVICE){
            nt_log(F("kernel: no storage device found, cannot open file, nt_is_file_open();"), WARN);
            return err;
        }else {
            nt_log("kernel: cannot get storage device, error: " + make_hex(err) + ", aborting: nt_is_file_open();", ERROR);
            return err;
        }
    }

    IDVCHIDriver_Storage* storage = reinterpret_cast<IDVCHIDriver_Storage*>(driver);
    return storage -> is_open(file);
}

UINT32 get_int32(UINT8* buf){
    return (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + buf[3];
}

UINT16 get_int16(UINT8* buf){
    return (buf[0] << 8 | buf[1]);
}

void get_cstr(UINT8* buf, char* _src, UINT16 size){
    
}

ERR NTSKRNL NTSKernel::nt_run_app(file_t* file){
    UINT8 header[24];
    if(file == NULL){
        return NT_FILE_CLOSED;
    }
    cseq filename = nt_get_filename(file);

    nt_log("kernel: opening executable file " + nt_get_filename(file));

    nt_read_file(file, header, 24);
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
    nt_log("kernel: running [" + nt_get_filename(file) + "] executable app: " + String(app_name) + ", version: " + String(app_version) + "");

    return OK;
}

cseq NTSKRNL NTSKernel::nt_get_filename(file_t* file){
    IDVCHIDriver* driver = NULL;
    ERR err = nt_get_idvc_drvr(&driver, IDVC_STORAGE);

    
    if(err != OK){
        if(err == IDVC_ERROR_NO_DEVICE){
            nt_log(F("kernel: no storage device found, cannot open file, nt_get_filename();"), WARN);
            return "";
        }else {
            nt_log("kernel: cannot get storage device, error: " + make_hex(err) + ", aborting: nt_get_filename();", ERROR);
            return "";
        }
    }
    IDVCHIDriver_Storage* storage = reinterpret_cast<IDVCHIDriver_Storage*>(driver);
    return storage -> get_filename(file);
}

#endif

#endif