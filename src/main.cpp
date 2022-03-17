#if 1
#include <Arduino.h>

#include "ntskrnl.hpp"

using namespace NTSKernel;

void setup() {
  nt_boot_sequence();
  IDVCHIDriver_Dsply* dsply;
  nt_get_dsply(&dsply);

  SIZE16 coords {128 / 4, 64 / 3};
  dsply -> draw_pxl(coords, NGL_BLACK);
  
}

void loop() {
  // put your main code here, to run repeatedly:
}
#endif