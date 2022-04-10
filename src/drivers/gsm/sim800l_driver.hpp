#include "drivers/packets_manager.h"

#if SIM800L_DRIVER

#include "ntskrnl.hpp"

class SIM800L_Driver : public IDVCDriver_GSM {
    public:
        SIM800L_Driver(){}

        ~SIM800L_Driver(){}

        gsm_number NTSKRNL incoming_status();

        uint8_t NTSKRNL signal_strength();

        BOOLN is_sim_inserted();
         
        NTSKRNL BOOLN available();

        NTSKRNL trnsprt get_trnsprt();

        NTSKRNL void begin_device();

        NTSKRNL cseq drvr_name();

        NTSKRNL void stop_device();

        NTSKRNL ERR restart_device();
};

#endif