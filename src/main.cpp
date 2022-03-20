#if 1
#include <Arduino.h>

#include "ntskrnl.hpp"

using namespace NTSKernel;

void setup() {
  nt_boot_sequence();
  Serial.println("boot end");
  IDVCHIDriver_Dsply* dsply;
  nt_get_dsply(&dsply);

  dsply -> reverse_colors(true);
  nt_log("Free MEM: " + cseq(nt_get_free_sram()), INFO);
  file_t* file;
  Serial.println("nt_open_file: " + String(nt_open_file(&file, C("test.txt"), true, true), HEX));
  UINT8 data[]{'s', 'i', 'e', 'm', 'a'};
  Serial.println("nt_write_file: " + String(nt_write_file(file, data, 4), HEX));
  //nt_flush_file(file);
  Serial.println("nt_close_file: " + String(nt_close_file(file), HEX));
  
}

void loop() {
  // put your main code here, to run repeatedly:
}
#endif