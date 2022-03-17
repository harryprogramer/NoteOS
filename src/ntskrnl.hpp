#ifndef NTSKRNL
#define NTSKRNL

#include <WString.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef signed int INT8 __attribute__((__mode__(__QI__)));
typedef unsigned int UINT8 __attribute__((__mode__(__QI__)));
typedef signed int INT16 __attribute__((__mode__(__HI__)));
typedef unsigned int UINT16 __attribute__((__mode__(__HI__)));
typedef signed int INT32 __attribute__((__mode__(__SI__)));
typedef unsigned int UINT32 __attribute__((__mode__(__SI__)));

typedef UINT8 BYTE;

#define COLOR UINT8
#define ERR UINT8
#define LOG_LEVEL UINT8

#define INFO (LOG_LEVEL) 0x0A
#define WARN (LOG_LEVEL) 0x0B
#define ERROR (LOG_LEVEL) 0x0C
#define TRACE (LOG_LEVEL) 0x0D
#define DEBUG (LOG_LEVEL) 0x0E
#define CRIT (LOG_LEVEL) 0x0F
#define PANIC (LOG_LEVEL) 0xAF

#define NGL_WHITE (COLOR) 1
#define NGL_BLACK (COLOR) 0

#define idvc_id UINT16

#define IDVC_DISPLAY (idvc_id) 0x000A

#define trnsprt UINT8

#define TRNSPRT_I2C (trnsprt) 0xFF
#define TRNSPRT_UMSB (trnsprt) 0x0B
#define TRNSPRT_ETHERNET (trnsprt) 0x0C
#define TRNSPRT_DIGITAL (trnsprt) 0x0D
#define TRNSPRT_OTHER (trnsprt) 0x0E
#define TRNSPRT_UNKNOWN (trnsprt) 0x0F

/* errors */
#define NGL_ERROR_NOGRAPHICDEVICE (ERR) 0x01
#define NGL_ERROR_DEVICECOM (ERR) 0x02
#define NGL_ERROR_INCORRECT_COORD (ERR) 0x03  
#define NGL_ERROR_INCORRECT_COLOR (ERR) 0x04
#define IDVC_ERROR_NO_DEVICE (ERR) 0x04
#define IDVC_ERROR_DEVICE_NOT_RESPONDING (ERR) 0x05
#define IDVC_ERROR_DEVICE_UNREACHABLE (ERR) 0x06
#define UMSB_ERROR_DEVICE_UNREACHABLE (ERR) 0x07
#define UMSB_ERROR_DEVICE_OUT_OF_SYNC (ERR) 0x08
#define UMSB_ERROR_DEVICE_NOT_RESPONDING (ERR) 0x09

#define OPERATION_UNAVAILABLE 0x0B
#define UNDEFINED   (ERR) 0x0A
#define OK          (ERR) 0

#define VOID void /* void */

typedef String cseq; /* char sequence **/
typedef bool BOOLN;

#define PATH cseq

typedef struct umsb_device umsb_device_t;
typedef struct file file_t;
typedef UINT8 umsb_addr;

typedef struct SIZE8 {
  UINT8 x;
  UINT8 y;
}
SIZE8, * SIZE8_P;

typedef struct SIZE16 {
  UINT16 x;
  UINT16 y;
}
SIZE16, * SIZE16_P;

typedef struct SIZE32 {
  UINT32 x;
  UINT32 y;
  }
SIZE32, * SIZE32_P;

class IDVCHIDriver {
  public:

      virtual NTSKRNL BOOLN available() = 0;

      virtual NTSKRNL trnsprt get_trnsprt() = 0;

      virtual NTSKRNL VOID begin_device() = 0;

      virtual NTSKRNL cseq drvr_name() = 0;

      virtual NTSKRNL VOID stop_device() = 0;
};

class IDVCHIDriver_Dsply: virtual public IDVCHIDriver {
  public:
    
    virtual ERR NTSKRNL clr_scrn(VOID) = 0;

    virtual ERR NTSKRNL get_scrn_size(SIZE16_P size) = 0;

    virtual ERR NTSKRNL draw_pxl(SIZE16 cordinates, COLOR color) = 0;

    virtual ERR NTSKRNL print(String msg) = 0;

    virtual ERR NTSKRNL print(String msg, UINT16 size) = 0;

    virtual ERR NTSKRNL set_crsr(SIZE16_P size) = 0;

    virtual ERR NTSKRNL write(UINT8 byte) = 0;

    virtual ERR NTSKRNL write(UINT8 byte, BOOLN flush) = 0;

	virtual ERR NTSKRNL render_bitmap(INT16 x, INT16 y, const UINT8 *bitmap, INT16 w,
                              INT16 h, UINT16 color) = 0;
};

namespace NTSKernel {

  VOID NTSKRNL nt_boot_sequence(VOID);

  VOID NTSKRNL nt_srl_trnmt(cseq data);

  /**
   * @brief 
   * 
   * check if some data ready to read
   * 
   * @param s if some data is ready to read 
   *  this param will be set to size for that data to read
   * @return BOOLN is data available
   */
    
  BOOLN NTSKRNL nt_srl_vsbl(size_t* s);

  ERR NTSKRNL nt_srl_recv(BYTE* recv);

  ERR NTSKRNL nt_opn_umsb_dvc(umsb_device * device, umsb_addr addr);

  ERR NTSKRNL nt_cls_umsn_dvc(umsb_device * device);

  ERR NTSKRNL nt_get_dsply(IDVCHIDriver_Dsply** driver);

  ERR NTSKRNL nt_load_idvc_drvr(IDVCHIDriver* drvr, idvc_id id);

  ERR NTSKRNL nt_get_idvc_drvr(IDVCHIDriver** drvr, idvc_id id);

  VOID NTSKRNL nt_log(const cseq msg, LOG_LEVEL level);

  ERR NTSKRNL nt_opn_file(file* file, PATH path);

  ERR NTSKRNL nt_cls_file(file* file);

  VOID NTSKRNL nt_cls_krnl_sequence();

  UINT32 NTSKRNL nt_get_free_sram();

  VOID NTSKRNL nt_mem_free(void* ptr);

  VOID NTSKRNL nt_krnl_cycle();

  VOID NTSKRNL nt_set_logging_to_graphic(BOOLN is_loggins);

  cseq NTSKRNL nt_about();
  
};

#ifdef __cplusplus
}
#endif
#endif