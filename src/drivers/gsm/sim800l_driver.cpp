#include "drivers/packets_manager.h"

#if SIM800L_DRIVER

#include <SoftwareSerial.h>
#include <string.h>
#include "sim800l_driver.hpp"

#define NAME "SIM800L GSM TTL"

SoftwareSerial gsm(SIM800L_RX, SIM800L_TX);

BOOLN is_available = false;

using namespace NTSKernel;

#define RESPONSE_BUFFER_SIZE    256
#define RESPONSE_TIMEOUT_TIME   6000.0

#define RESPONSE_TIMEOUT (ERR) 0x0A


typedef struct gsm_response {
    String msg;
    ERR error = OK;
} gsm_response;

int get_absolute_size(char* msg){
    int size = 0;
    if(msg == NULL)
        return 0;

    for(int i = 0; i < strlen(msg); i++){
        char character = msg[i];
        if(character == 0x0A || character == 0x0D){
            continue;
        }

        size++;
    }

    return size;
}

gsm_response send_command(char* command){
    gsm.println(command);

    uint64_t millis_start = millis();
    gsm_response response;

    uint16_t index = 0;
    
    while(1){
        if((millis() - millis_start) >= RESPONSE_TIMEOUT_TIME){
            nt_log("[SIM800L] Response timeout.", INFO);
            response.error = RESPONSE_TIMEOUT; 
            return response;
        }

        int gsm_available = gsm.available();
        if(gsm_available){
            uint8_t buf[RESPONSE_BUFFER_SIZE];
            int buf_index = 0;
            while(gsm_available){
                if(buf_index == RESPONSE_BUFFER_SIZE){
                    break;
                }
                buf[buf_index++] = gsm.read();
                gsm_available = gsm.available();
            }

            
            uint8_t msg[RESPONSE_BUFFER_SIZE];
            int msg_index = 0;
            int command_size = get_absolute_size(command);
            for(int i = 0; i < RESPONSE_BUFFER_SIZE; i++){
                uint8_t character = buf[i];
                if(character == 0x0A || character == 0x0D || i - 1 < command_size){
                    continue;
                }

                msg[msg_index++] = character;
            }
            String finalmsg = String((const char*) msg);

            response.msg = finalmsg;
            nt_log("[SIM800L] Response received, read " + String(finalmsg.length(), DEC) + " bytes in " 
                    + String((millis() - millis_start) / 1000.0, DEC) + "s.", INFO);
            response.error = OK;
            return response;
        }
    }
}

gsm_number NTSKRNL SIM800L_Driver::incoming_status(){

}

uint8_t NTSKRNL SIM800L_Driver::signal_strength(){

}

BOOLN SIM800L_Driver::is_sim_inserted(){

}
         
NTSKRNL BOOLN SIM800L_Driver::available(){
    return is_available;
}

NTSKRNL trnsprt SIM800L_Driver::get_trnsprt(){

}

NTSKRNL void SIM800L_Driver::begin_device(){
    nt_log("[SIM800L] Starting device...", INFO);
    gsm.begin(9600);
    gsm_response response = send_command("AT");
    if(response.error == RESPONSE_TIMEOUT){
        nt_log("[SIM800L] Device is not reachable. Response timeout.", ERROR);
        is_available = false;
    }else {
        if(response.msg.equalsIgnoreCase("OK")){
            nt_log("[SIM800L] Device OK. Fetching details.", INFO);
            
        }else {
            nt_log("[SIM800L] Unexecpted device response. Device failure.", ERROR);
            nt_log("[SIM800L] Failure response on AT command: " + response.msg, INFO);
        }
    }
}

NTSKRNL cseq SIM800L_Driver::drvr_name(){
    return C(NAME);
}

NTSKRNL void SIM800L_Driver::stop_device(){

}

NTSKRNL ERR SIM800L_Driver::restart_device(){
    
}

#endif