#pragma once

#include "drivers/packets_manager.h"

#if PNTPOWER_DRIVER

#include "ntskrnl.hpp"

class PNTPowerDriver : public IDVCDriver_PowerManager {
    public:
        NTSKRNL PowerSource get_power_source();

        NTSKRNL ERR get_battery(battery*);

        NTSKRNL ERR shutdown_power();

        NTSKRNL BOOLN available();

        NTSKRNL trnsprt get_trnsprt();

        NTSKRNL void begin_device();

        NTSKRNL cseq drvr_name();

        NTSKRNL void stop_device();

        NTSKRNL ERR restart_device();
};
#endif