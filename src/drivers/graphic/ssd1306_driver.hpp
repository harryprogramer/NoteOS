#include "./drivers/packets_manager.h"

#if SSD1306_DRIVER

#ifndef OLEDSCRN_DRIVER
#define OLEDSCRN_DRIVER

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "./ntskrnl.hpp"

class OLEDIDVCHIDDriver : public IDVCHIDriver_Dsply {
    private:
        UINT8 addr;
        SIZE16 scrn_size;
        BOOLN is_connected;
        Adafruit_SSD1306 scrn;

    public:
        NTSKRNL OLEDIDVCHIDDriver(UINT8 i2c_addr, SIZE16 size);

        ERR NTSKRNL clr_scrn(VOID);

        ERR NTSKRNL get_scrn_size(SIZE16_P size);

        ERR NTSKRNL draw_pxl(SIZE16 cordinates, COLOR color);

        ERR NTSKRNL print(String msg);

        ERR NTSKRNL print(String msg, UINT16 size) = 0;

        ERR NTSKRNL set_crsr(SIZE16_P size);

        BOOLN NTSKRNL available();

        trnsprt NTSKRNL get_trnsprt();

        VOID NTSKRNL begin_device();

        cseq NTSKRNL drvr_name();

        VOID NTSKRNL stop_device(); 
};


#endif
#endif