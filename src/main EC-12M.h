#include <18F4550.h>
#device adc=10
  
                                                                                                                   
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
//#FUSES INTRC_IO               //Internal RC Osc, no CLKOUT
#FUSES XTPLL  
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOBROWNOUT               //No brownout reset
//#FUSES BORV20                   //Brownout reset at 2.0V  doe new compiler error
#FUSES PUT                      //Power Up Timer
#FUSES NOCPD                    //No EE protection
#FUSES STVREN                   //Stack full/underflow will cause reset
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOWRT                    //Program memory not write protected
#FUSES NOWRTD                   //Data EEPROM not write protected
#FUSES NOIESO                   //**Internal External Switch Over mode enabled
#FUSES NOFCMEN                  //**Fail-safe clock monitor enabled
#FUSES NOPBADEN                 //**PORTB pins are configured as analog input channels on RESET
#FUSES NOWRTC                   //configuration not registers write protected
#FUSES NOWRTB                   //Boot block not write protected
#FUSES NOEBTR                   //Memory not protected from table reads
#FUSES NOEBTRB                  //Boot block not protected from table reads
#FUSES NOCPB                    //No Boot Block code protection
#FUSES MCLR                     //Master Clear pin enabled
#FUSES LPT1OSC                  //Timer1 configured for low-power operation
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES PLL1                     //Divide By 12(48MHz oscillator input)
#FUSES CPUDIV3                  //System Clock by 4   // 3 = 4   96 / 4 = 24 Mhz 
#FUSES USBDIV                   //USB clock source comes from PLL divide by 2
#FUSES VREGEN                   //USB voltage regulator enabled
#FUSES HS 
//#FUSES NOICPRT                  //**ICPRT enabled     
                                        
              
//-------------------------------
//#define RTCC_PRELOAD (256 -  39)   
#define RTC_SDA  PIN_C1
#define RTC_SCL  PIN_C0 

 
                                                          
//------------------------------
#use I2C(MULTI_MASTER,sda=RTC_SDA, scl=RTC_SCL)
//#use delay(clock=4M)
#use delay(clock=24MHz, crystal=4MHz, USB_LOW)

#use rs232(uart1, baud=9600 ,XMIT=PIN_C6, RCV=PIN_C7 )
//------------------------------

