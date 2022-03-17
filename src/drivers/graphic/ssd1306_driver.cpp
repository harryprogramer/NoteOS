#include "./drivers/packets_manager.h"
#if SSD1306_DRIVER 

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "ssd1306_driver.hpp"

#define ABOUT "Adafruit OLED (SSD1306 Drivers) I2C"

using namespace NTSKernel;



OLEDIDVCHIDDriver::OLEDIDVCHIDDriver(UINT8 i2c_addr, SIZE16 size) {
    addr = i2c_addr;
    scrn_size = size;
    scrn = Adafruit_SSD1306(size.x, size.y, &Wire, -1);
}

VOID OLEDIDVCHIDDriver::begin_device(){
    UINT16 size = (floor(log10(scrn_size.x) + 1) + floor(log10(scrn_size.y) + 1)) + 70;
    cseq msg = (cseq) malloc(sizeof(char) * size);
    sprintf(msg, "[SSD1306] Starting OLEDSCREEN driver for size [%d x %d] on I2C.", scrn_size.x, scrn_size.y);
    msg[size] = '\0';
    nt_log(msg, INFO);
    nt_mem_free(msg);

    is_connected = !scrn.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    
    
    if(is_connected){
        nt_log(C("[SSD1306] Cannot connect to OLED, begin operation failed."), INFO);
    }else {
        scrn.clearDisplay();
        scrn.setTextSize(1);
        scrn.setTextColor(WHITE);
        scrn.setCursor(0, 10);
        scrn.println("siema");
        scrn.display();
        nt_log(C("[SSD1306] Device begin operation completed succesful."), INFO);
    }
}

ERR NTSKRNL OLEDIDVCHIDDriver::clr_scrn(VOID){
    scrn.clearDisplay();
    return UNDEFINED;
}

ERR NTSKRNL OLEDIDVCHIDDriver::get_scrn_size(SIZE16_P __size){
    *__size = scrn_size;
    return UNDEFINED;
}

ERR NTSKRNL OLEDIDVCHIDDriver::draw_pxl(SIZE16 cordinates, COLOR color){
    return UNDEFINED;
}

ERR NTSKRNL OLEDIDVCHIDDriver::print(String msg){
    scrn.println(msg);
    scrn.display(); 
    return UNDEFINED;
}

ERR NTSKRNL OLEDIDVCHIDDriver::set_crsr(SIZE16_P size){
    return UNDEFINED;
}

BOOLN NTSKRNL OLEDIDVCHIDDriver::available(){
    return is_connected;
}

trnsprt NTSKRNL OLEDIDVCHIDDriver::get_trnsprt(){
    return TRNSPRT_I2C;
}


NTSKRNL cseq OLEDIDVCHIDDriver::drvr_name(){
    return C(ABOUT);
}

NTSKRNL VOID OLEDIDVCHIDDriver::stop_device(){
    
}
#endif

 

