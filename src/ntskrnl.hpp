#ifndef NTSKRNL
#define NTSKRNL

#include <WString.h>
#include <SD.h>
#include "ntbase.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef UINT8 BYTE;

#define C(literal) ((char*) literal)

#define COLOR UINT8
#define ERR UINT8
#define LOG_LEVEL UINT8

#define INFO (LOG_LEVEL) 0x01
#define WARN (LOG_LEVEL) 0x02
#define ERROR (LOG_LEVEL) 0x03
#define TRACE (LOG_LEVEL) 0x04
#define DEBUG (LOG_LEVEL) 0x05
#define CRIT (LOG_LEVEL) 0x06
#define PANIC (LOG_LEVEL) 0x07

#define NGL_WHITE (COLOR) 1
#define NGL_BLACK (COLOR) 0

#define idvc_id UINT8

#define trnsprt UINT8

#define TRNSPRT_I2C (trnsprt) 0x08
#define TRNSPRT_UMSB (trnsprt) 0x09
#define TRNSPRT_ETHERNET (trnsprt) 0x0A
#define TRNSPRT_DIGITAL (trnsprt) 0x0B
#define TRNSPRT_OTHER (trnsprt) 0x0C
#define TRNSPRT_SPI   (trnsprt) 0x0D
#define TRNSPRT_UNKNOWN (trnsprt) 0x0E

/* errors */
#define NGL_ERROR_NOGRAPHICDEVICE (ERR) 0x0E
#define NGL_ERROR_DEVICECOM (ERR) 0x0F
#define NGL_ERROR_INCORRECT_COORD (ERR) 0x10
#define NGL_ERROR_INCORRECT_COLOR (ERR) 0x11
#define IDVC_ERROR_NO_DEVICE (ERR) 0x12
#define IDVC_ERROR_DEVICE_NOT_RESPONDING (ERR) 0x13
#define IDVC_ERROR_DEVICE_UNREACHABLE (ERR) 0x14
#define UMSB_ERROR_DEVICE_UNREACHABLE (ERR) 0x15
#define UMSB_ERROR_DEVICE_OUT_OF_SYNC (ERR) 0x16
#define UMSB_ERROR_DEVICE_NOT_RESPONDING (ERR) 0x17

#define OPERATION_UNAVAILABLE 0x19
#define UNDEFINED   (ERR) 0x1A
#define OK          (ERR) 0x1B

#define NT_FILE_NOT_FOUND 0x1C
#define NT_FILE_CLOSED    0x1D

#define IDVC_DISPLAY (idvc_id) 0x1E
#define IDVC_STORAGE (idvc_id) 0x1F
#define IDVC_GSM     (idvc_id) 0x23
#define IDVC_POWER   (idvc_id) 0x24

#define NT_ALLOC_NOT_ENOUGH_MEMORY  0x20
#define NT_ALLOC_ALLOC_FAULT        0x21

#define NT_INVALID_EXECUTABLE_SIGNATURE 0x22

#define IO_FAULT  0x22


#define void void /* void */

typedef String cseq; /* char sequence **/
typedef bool BOOLN;

#define PATH char*

typedef struct umsb_device umsb_device_t;
typedef struct nt_storage nt_storage_t;

typedef struct file_t {
  char* filename;
  File sd_file;
} file_t;

typedef UINT8 umsb_addr;
typedef char* gsm_number;


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

      virtual NTSKRNL void begin_device() = 0;

      virtual NTSKRNL cseq drvr_name() = 0;

      virtual NTSKRNL void stop_device() = 0;

      virtual NTSKRNL ERR restart_device() = 0;
};

class IDVCHIDriver_Storage : virtual public IDVCHIDriver {
  public:
    virtual NTSKRNL ERR open_file(file_t** file, PATH filename, BOOLN open_file, BOOLN write_file) = 0;

    virtual NTSKRNL ERR read_file(file_t* file, UINT8* buf, UINT16 size) = 0;

    virtual NTSKRNL ERR flush_file(file_t* file) = 0;
    
    virtual NTSKRNL ERR write_to_file(file_t* file, UINT8* buf, UINT16 size) = 0;

    virtual NTSKRNL ERR delete_file(file_t* file) = 0;

    virtual NTSKRNL ERR close_file(file_t* file) = 0;

    virtual NTSKRNL String get_filename(file_t* file) = 0;

    virtual NTSKRNL BOOLN is_open(file_t* file) = 0;

};

class IDVCHIDriver_Dsply : virtual public IDVCHIDriver {
  public:
    
    virtual ERR NTSKRNL clr_scrn() = 0;

    virtual ERR NTSKRNL get_scrn_size(SIZE16_P size) = 0;

    virtual ERR NTSKRNL draw_pxl(SIZE16 cordinates, COLOR color) = 0;

    virtual ERR NTSKRNL print(String msg) = 0;

    virtual ERR NTSKRNL print(String msg, UINT16 size) = 0;

    virtual ERR NTSKRNL set_crsr(SIZE16_P size) = 0;

    virtual ERR NTSKRNL write(UINT8 byte) = 0;

    virtual ERR NTSKRNL write(UINT8 byte, BOOLN flush) = 0;

	  virtual ERR NTSKRNL render_bitmap(INT16 x, INT16 y, const UINT8 *bitmap, INT16 w,
                              INT16 h, UINT16 color) = 0;

    virtual ERR NTSKRNL reverse_colors(BOOLN is_reverse) = 0;
};

class IDVCDriver_GSM : virtual public IDVCHIDriver {
  public:
    // return null if there is no call to answer
    // else return current phone number of the person who's calling
    virtual gsm_number NTSKRNL incoming_status() = 0;

    virtual uint8_t NTSKRNL signal_strength() = 0;

    virtual BOOLN NTSKRNL is_sim_inserted() = 0;
};

class IDVCDriver_PowerManager : virtual public IDVCHIDriver {
  public:
    enum PowerSource {
      BATTERY = 0x0A,
      EXTERNAL_POWER = 0x0B
    };

    typedef struct battery {
      UINT8 percent;
      UINT8 voltage;
      UINT16 capacity;
    } battery, *battery_p;

    virtual NTSKRNL PowerSource get_power_source() = 0;

    virtual NTSKRNL ERR get_battery(battery*) = 0;

    virtual NTSKRNL ERR shutdown_power() = 0;

};

namespace NTSKernel {

  void NTSKRNL nt_boot_sequence();

  void NTSKRNL nt_srl_trnmt(cseq);

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

  void NTSKRNL nt_log(const cseq msg, LOG_LEVEL level = INFO, const char* caller = __builtin_FUNCTION());

  void NTSKRNL nt_cls_krnl_sequence();

  UINT32 NTSKRNL nt_get_free_sram();

  void NTSKRNL nt_mem_free(void* ptr);

  ERR NTSKRNL nt_malloc(void** __mem, size_t size);

  ERR NTSKRNL nt_calloc(void** __mem, size_t size);

  void NTSKRNL nt_krnl_cycle();

  void NTSKRNL nt_set_logging_to_graphic(BOOLN is_loggins);

  cseq NTSKRNL nt_about();

  ERR NTSKRNL nt_open_file(file_t** file_t, PATH path, BOOLN create_file, BOOLN write_file);

  ERR NTSKRNL nt_close_file(file_t* file_t);

  ERR NTSKRNL nt_flush_file(file_t* file_t);

  ERR NTSKRNL nt_delete_file(file_t* file_t);

  ERR NTSKRNL nt_read_file(file_t* file, UINT8* buf, UINT16 size);

  cseq NTSKRNL nt_get_filename(file_t* file);

  ERR NTSKRNL nt_write_file(file_t* file, UINT8* buf, UINT16 size);

  BOOLN NTSKRNL nt_is_file_open(file_t* file);

  void NTSKRNL nt_reboot(char* source, char* reason, BOOLN force);

  ERR NTSKRNL nt_run_app(file_t* file);
};

#ifdef __cplusplus
}
#endif
#endif