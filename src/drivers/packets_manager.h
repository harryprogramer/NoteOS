#ifndef PACKET_MANAGER_HEADER
#define PACKET_MANAGER_HEADER
/**
 * Menadżer pakietów rozpatrujący które części systemu mają zostać skompilowane.
 * Jeśli urządzenie docelowe nie będzie używać określonego urządzenia wspieranego przez dany 
 * sterownik, można wykluczyć dany pakiet z kompilacji jądra.
 * Ten nagłowek pomaga zmiejszać rozmiar systemu.
 * 
 * Jeśli urządzenie docelowe nie będzie używac wyświetlacza OLED 1.3 do którego jest 
 * dostępny sterownik ./drivers/graphic/sh1106_driver.cpp, można ten sterownik wykluczyć ustawiająć
 * flage defincji prekompilatora na FALSE. W przypadku sterownika SSH1106 jest to
 * definicja 'SSH1106_DRIVER'. Przykład wykluczenia danego sterownika.
 * 
 * #define SH1106_DRIVER FALSE
 */
#define FALSE 0
#define TRUE 1

#define SSD1306_DRIVER          FALSE    
#define SH1106_DRIVER           TRUE
#define SIM800L_DRIVER          TRUE




#define SIM800L_RX 12
#define SIM800L_TX 11

#ifdef __AVR_ATmega2560__
#if SIM800L_RX < 11
#error "unsupported rx pin, read limitations on: https://www.arduino.cc/en/Reference/softwareSerial"
#endif

#endif 
#endif
