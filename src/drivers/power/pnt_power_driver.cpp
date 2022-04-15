#include "drivers/packets_manager.h"

#if PNTPOWER_DRIVER

#include "ntskrnl.hpp"
#include "pnt_power_driver.hpp"

#define NAME "PNT Power Manager"

NTSKRNL PNTPowerDriver::PowerSource PNTPowerDriver::get_power_source(){}

NTSKRNL ERR PNTPowerDriver::get_battery(battery*){}

NTSKRNL ERR PNTPowerDriver::shutdown_power(){}

NTSKRNL BOOLN PNTPowerDriver::available(){}

NTSKRNL trnsprt PNTPowerDriver::get_trnsprt(){}

NTSKRNL void PNTPowerDriver::begin_device(){
    
}

NTSKRNL cseq PNTPowerDriver::drvr_name(){
    return NAME;
}

NTSKRNL void PNTPowerDriver::stop_device(){}

NTSKRNL ERR PNTPowerDriver::restart_device(){}

#endif