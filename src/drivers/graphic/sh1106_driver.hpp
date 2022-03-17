#ifndef SH1306_DRIVER
#define SH1306_DRIVER

#include "./ntskrnl.hpp"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SH1106.h>

class SH1106OLEDDriver : public IDVCHIDriver_Dsply {
    private:
        UINT8 addr;
        SIZE16 scrn_size;
        BOOLN is_connected;
        Adafruit_SH1106* scrn;

    public:
        NTSKRNL SH1106OLEDDriver();

        ERR NTSKRNL clr_scrn(VOID);

        ERR NTSKRNL get_scrn_size(SIZE16_P size);

        ERR NTSKRNL draw_pxl(SIZE16 cordinates, COLOR color);

        ERR NTSKRNL print(String msg);

        ERR NTSKRNL print(String msg, UINT16 size);

        ERR NTSKRNL set_crsr(SIZE16_P size);

        BOOLN NTSKRNL available();

        trnsprt NTSKRNL get_trnsprt();

        VOID NTSKRNL begin_device();

        NTSKRNL cseq drvr_name();

        NTSKRNL VOID stop_device();

        ERR NTSKRNL write(UINT8 byte);

        ERR NTSKRNL write(UINT8 byte, BOOLN flush);

        ERR NTSKRNL render_bitmap(INT16 x, INT16 y, const UINT8 *bitmap, INT16 w,
                              INT16 h, UINT16 color);
};


#endif