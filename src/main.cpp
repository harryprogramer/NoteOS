#if 1
#include <Arduino.h>

#include "ntskrnl.hpp"

using namespace NTSKernel;

void setup() {
  nt_boot_sequence();

  IDVCHIDriver_Dsply* dsply;
  nt_get_dsply(&dsply);

  dsply -> reverse_colors(true);

  
  file_t* app_file;
  if(nt_open_file(&app_file, C("app.nte"), false, false) != OK){
    nt_log("can't open file", WARN);
  }else {
    nt_run_app(app_file);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
}
#endif

#if 0
#include "drivers/packets_manager.h"
#include <SoftwareSerial.h>
#include <Arduino.h>
SoftwareSerial gsm2(SIM800L_RX, SIM800L_TX);

void setup() {
  Serial.begin(9600);
  Serial.println("hello");
  gsm2.begin(9600);
}

void loop() {
  while (Serial.available()) {
      delay(1);
      gsm2.write(Serial.read());
  }
  while (gsm2.available()) {
       Serial.write(gsm2.read());
  }
  
}

#endif