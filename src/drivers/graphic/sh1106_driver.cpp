#include "./drivers/packets_manager.h"

#if SH1106_DRIVER

#include "sh1106_driver.hpp"

#define ABOUT "SH1106 (Adafruit) Graphic Device"

using namespace NTSKernel;

NTSKRNL SH1106OLEDDriver::SH1106OLEDDriver(){
    scrn = new Adafruit_SH1106(4);
}

ERR NTSKRNL SH1106OLEDDriver::clr_scrn(void){
    scrn -> clearDisplay();
    
    return OK;
}

ERR NTSKRNL SH1106OLEDDriver::get_scrn_size(SIZE16_P size){
    size = NULL;
    return OPERATION_UNAVAILABLE;
}

ERR NTSKRNL SH1106OLEDDriver::draw_pxl(SIZE16 cordinates, COLOR color){
    scrn -> drawPixel(cordinates.x, cordinates.y, color);
    scrn -> display();
    return OK;
}

ERR NTSKRNL SH1106OLEDDriver::print(String msg){
    scrn -> println(msg);
    scrn -> display();
    return OK;
}


ERR NTSKRNL SH1106OLEDDriver::set_crsr(SIZE16_P size){
    return OK;
}

BOOLN NTSKRNL SH1106OLEDDriver::available(){
    return TRUE;
}

trnsprt NTSKRNL SH1106OLEDDriver::get_trnsprt(){
    return TRNSPRT_I2C;
}

void NTSKRNL SH1106OLEDDriver::begin_device(){
    nt_log(F("[SH1106] Initializng SH1106 OLED Display"), INFO);
    scrn -> begin(SH1106_SWITCHCAPVCC, 0x3C);
    scrn -> display();
    scrn -> clearDisplay();
    scrn -> setTextSize(1);
    scrn -> setTextColor(WHITE);
    scrn -> setCursor(0, 0);
}

NTSKRNL cseq SH1106OLEDDriver::drvr_name(){
    return F(ABOUT);
}

NTSKRNL void SH1106OLEDDriver::stop_device(){
    String msg PROGMEM = "Stopping [" + String(ABOUT) + "] device.";
    nt_log(msg, INFO);
    delete scrn;
}

ERR SH1106OLEDDriver::print(String msg, UINT16 size){
    if(!msg.length() == 0){
        msg.trim();
        scrn -> setTextSize(size);
        scrn -> print(msg);
        scrn -> display();
    }


    return OK;
};

ERR NTSKRNL SH1106OLEDDriver::write(UINT8 byte){
    write(byte, TRUE);
    
    return OK;
}

ERR NTSKRNL SH1106OLEDDriver::write(UINT8 byte, BOOLN flush){
    scrn -> write(byte);
    if(flush) scrn -> display();

    return OK;
}

ERR NTSKRNL SH1106OLEDDriver::render_bitmap(INT16 x, INT16 y, const UINT8 *bitmap, INT16 w,
                              INT16 h, UINT16 color){
    scrn -> clearDisplay();
    scrn -> drawBitmap(x, y, bitmap, w, h, color);
    scrn -> display();

    return OK;
}

ERR NTSKRNL SH1106OLEDDriver::reverse_colors(BOOLN is_reverse){
    scrn -> invertDisplay(is_reverse);
    scrn -> display();

    return OK;
};

#endif