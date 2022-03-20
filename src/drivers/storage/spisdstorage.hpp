#ifndef SPISDSTORAGE
#define SPISDSTORAGE

#include "./ntskrnl.hpp"

class SPISDStorage : public IDVCHIDriver_Storage {
    private:
        bool is_available;

    public: 
        SPISDStorage(){
        }

        ~SPISDStorage(){

        }

        NTSKRNL ERR open_file(file_t** file, PATH filename, BOOLN open_file, BOOLN write_file);

        NTSKRNL String get_filename(file_t* file);

        NTSKRNL ERR read_file(file_t* file, UINT8* buf, UINT16 size);

        NTSKRNL ERR flush_file(file_t* file);
        
        NTSKRNL ERR write_to_file(file_t* file, UINT8* buf, UINT16 size);

        NTSKRNL ERR delete_file(file_t* file);

        NTSKRNL ERR close_file(file_t* file);

        NTSKRNL BOOLN available();

        NTSKRNL trnsprt get_trnsprt();

        NTSKRNL void begin_device();

        NTSKRNL cseq drvr_name();

        NTSKRNL void stop_device();
};

#endif