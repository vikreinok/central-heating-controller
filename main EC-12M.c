//#include "C:\Documents and Settings\Viktor\Application Data\PICC\Projects\EC-12M\main EC-12M.h"  
#include "main EC-12M.h"
                                                                         
#OPT 9 // Programmis optimiseerimist kirjeldav & m6jutav tegur                                     
#priority ext,rtcc,rb  //katkestuste prioriteet      
                                                                                                  
               

//Macro -d  
//----------------------------------------------------------
#define PUHASTA_LCD  lcd_send_byte(0,0x01);  //Puhastab LCD
#define KURSOR_SEES  lcd_send_byte(0,0x0E); //kursor sees
#define KURSOR_V2LJAS  lcd_send_byte(0,0x0C); //kursor v2ljas  
//----------------------------------------------------------
                                                            
                                   
//GLOBAL VARIABLES + DEFINES          
//---------------------------------------------------------- 
int1 global_reset = TRUE; // kellaprogrammi funktsioonis         
int1 global_M_v6i_T = TRUE; // Menu = TRUE, t66funkts = FALSE                                                          
                       
#define LCD_LED  PIN_E0   //taustavlagustuse funktsioonis
#define LCD_LED_loendur  340 // T3 loendab
                                  
                                            
                                                  

//--------------------------------
//PIDi konstandid muuta hiljem.                                         
#define K_P     1.00   
#define K_I     0.01
#define K_D     0.10   


//--------------------------------
//T2iteteguri modulaator 
                           
#define MIN_PERIOOD 2800  //2.8   
#define MIN_IMPULLS  200  //0.2    
                         
                         
//--------------------------------                                  
//Kellataimeri funktsiooni  defainid 
                                                                  
#define  KELLATAIMERI_MINUT 600 //600*100ms                                                                     
 

                                                           
//--------------------------------         
// MENU global varaibles    
#byte portb = 0xf81     //pordi B address     
int1 do_debounce = FALSE, select = FALSE, down = FALSE, up = FALSE,
     exit = FALSE;
int1 initial_delay = TRUE;
int8 pointer_line = 1, menu_window_start = 1;
int8 *control;        
int8 temp, repeat_delay_count = 0;     
                                           
   const char menu_EST[][*] = {
//   "ADC v\341\341rtus",//0 vb ei ole vaja  
//   "Change language", //1
//   "Graafiku valik",  //2
//   "Graafiku nihe",   //3
//   "Piiramine max*",  //4    
//   "Piiramine min*",  //5     
//   "Nr. MUUTMINE Kp", //6
//   "Nr. MUUTMINE Ki", //7
//   "Nr. MUUTMINE Kd", //8          
//   "N\341ita kuup. aeg", //9             
//   "Seadista aeg",    //10                                
//   "Seadista koop.",  //11              
//   "Seadista suund",  //12  ei ole vaja            
//   "Kellaprogramm 1", //13                      
//   "Kellaprogramm 2", //14                          
  "Taasta algseade"  //15                 
   };                                                
   
   const char menu_ENG[][*] = {     
   "AD conv. value",  //0  vb ei ole vaja 
   "Vaheta Keel",     //1            
   "Curve slope",     //2
   "Curve shift",     //3 
   "Curve lim. max",  //4    
   "Curve lim. min",  //5
   "Set value: Kp.",  //6      
   "Set value: Ki.",  //7         
   "Set value: Kd.",  //8        
   "Show date& time", //9 
   "Set Time",        //10
   "Set Date",        //11              
   "Set direction",   //12   ei ole vaja 
   "Prog. timer nr1", //13
   "Prog. timer nr2", //14                          
   "Reset settings"   //15                    
   };                         
                                  
  
//--------------------------------
// PID global varaibles        
                           
int1  tick_100ms; 
int1  tick_100ms_v2;
signed int16 error;
signed int16 PID_sum; 
signed int16 setpoint;  
float  P, I, D, value;           
int16 lugeja = 0;               
                     
//--------------------------------
// Numbri muutmine global varaibles      
int1 Y;
int1 timer0_tick;           
char string[8];                    
                                 

                                     
//--------------------------------        
// Seadur glob vars  //* 1 tick 0.0873 s T3 prescaler 1:8  
int1 L2H_flag,    
     seadur_kinnitatud,  
     arvuta_uus_TT = FALSE;    

unsigned int16 timer3_count,       
               count_pos,         
               count_nul; 
               
unsigned int8  TT_pullside_loendur_int = 0,
               TT_pullside_loendur_t66 = 0;
               
               
float          seaduri_t2itetegur;
//Seaduri komponent m6jutab graafiku nihet ylesse ja alla, see on v22rtusega 
//mis on vee temperatuurile proportionaalne +5 ka -5 toa temp kraadi. Norm = 0;
signed int16   seaduri_komponent = 0;   
            
#define seadur_t1_min 10  // * 1 tick 0.0873 s T3 prescaler 1:8   
#define seadur_t0_min 20                   
                                                        
#define seadur_t1_max 100                                      
#define seadur_t0_max 200                                                  

#define seadur_max 1                
#define seadur_min 2         

#define TIMER3_COUNT_MAX 300   
                                  

//--------------------------------
// T66_funktsioon      glob var 
                                       
signed int16 v2lis6hk_temp;                  
signed int16 reaalne_kyttevee_temp;
signed int16 arvutatud_kyttevee_temp;     
int16 ADC_v22rtus_glob;

//--------------------------------
// Graafiku_funktsioon   glob var
// 2 viimast arvu on arvud peale koma
#define graafik_tegur_def -1600
#define graafik_null_def  -458
#define graafik_y_def      0
#define graafik_max_def    7500
#define graafik_min_def    2500

signed int16 graafik_tegur = -1600; // M6jutab graafiku nurka
signed int16 graafik_null = -458;  // Tegur mis m6jutab v2ikest temp. t6usu 0 c kraadi juures
signed int16 graafik_y = 0;     // Graafiku asend y skaalal 20c v2lis6hu temp juures. Norm on 20 (nagu v2lis6hk-ki)
signed int16 graafik_max = 7500;   // Graafiku max v22rtus. Graafiku v2ljund ei saa kuidagi olla suurem kui see v22rtus.
signed int16 graafik_min = 2500;   // Graafiku min v22rtus. Graafiku v2ljund ei saa kuidagi olla v2iksem kui see v22rtus.

//--------------------------------   
// Kellaprogramm 1   glob var


#define MAX_graafiku_nihe_pos 15
#define MAX_graafiku_nihe_neg -15
 
#define KP_muudetav_v22rtus_def 0
signed int8 KP_muudetav_v22rtus = -10;  

#define n2dalap2evad_on_off_def_0 1 
#define n2dalap2evad_on_off_def_1 1 
#define n2dalap2evad_on_off_def_2 1  
#define n2dalap2evad_on_off_def_3 1  
#define n2dalap2evad_on_off_def_4 1  
#define n2dalap2evad_on_off_def_5 0 
#define n2dalap2evad_on_off_def_6 0    
int1 n2dalap2evad_on_off[7] = 1,1,1,1,1,0,0;

#define ON_tunnid_def 22
int8 ON_tunnid = 00;        

#define ON_minutid_def 00
int8 ON_minutid = 02;

#define OFF_tunnid_def 06             
int8 OFF_tunnid = 00;       

#define OFF_minutid_def 00 
int8 OFF_minutid = 01;

 
//--------------------------------
// Kellaprogramm 2  glob var

int1 kellaprog_nr;
 
#define KP_muudetav_v22rtus_2_def 00  
signed int8 KP_muudetav_v22rtus_2 = 0;   
 
#define n2dalap2evad_on_off_2_def_0 0 
#define n2dalap2evad_on_off_2_def_1 0 
#define n2dalap2evad_on_off_2_def_2 0  
#define n2dalap2evad_on_off_2_def_3 0  
#define n2dalap2evad_on_off_2_def_4 0  
#define n2dalap2evad_on_off_2_def_5 1 
#define n2dalap2evad_on_off_2_def_6 1                        
int1 n2dalap2evad_on_off_2[7] = 0,0,0,0,0,1,1; 

#define ON_tunnid_2_def 17  
int8 ON_tunnid_2 = 17;

#define ON_minutid_2_def 30 
int8 ON_minutid_2 = 30; 

#define OFF_tunnid_2_def 21 
int8 OFF_tunnid_2 = 21;
                               
#define OFF_minutid_2_def 30                
int8 OFF_minutid_2 = 30;      


//--------------------------------
// Grafiku tegur muutmine  glob var

//#define MIN_graafiku_tegur  -200
#define MAX_graafiku_tegur  -3000//-3,0 (signed int16)
int8 graafiku_tegur_int8;
                                     
//--------------------------------
// Grafiku nihutamine kasutajaliides  glob var

#define MAX_temp_nihutamine  20
#define MIN_temp_nihutamine  -20


//--------------------------------
// Grafiku nihutamine max kasutajaliides  glob var

#define MAX_temp_piiramine_max  95 //kraadi
#define MIN_temp_piiramine_max  20


//--------------------------------
// Grafiku nihutamine min kasutajaliides  glob var

#define MAX_temp_piiramine_min  55 //kraadi
#define MIN_temp_piiramine_min  15


//--------------------------------
// t66funktsiooni taganemise mehhanism  glob var 

int1 nuppu_on_vajutatud = FALSE; 
int16 t66funkts_taastamine_loendur;
                        
//--------------------------------
// Taustavalgustuse funktsioon  glob var  
                             
int1 nuppu_vajutati = FALSE;     
int16 taustavalgustuse_loendur;  

//--------------------------------
// tagasip22s_menyyse funktsiooni  glob var     

int1 nuppu_oldi_vajutatud = FALSE;
int1 syda_v2ljap22s_flag = TRUE;
int8 tagasip22su_loendur = 0; 
                     
                              
//--------------------------------
// T_t1_modulaator T2iteteguri glob var
                               
#define MIN_PID_sum 44   //Tagab selle et max periood oleks ~45 sec 45000 arvuna
int1  Pos_Neg;                   
int16 t2iteteguri_piirv22rtus;            
signed int16 t2iteteguri_piirv22rtus_neg;
int16 periood;
int16 impulls;                             
                                                
                                   
//--------------------------------
// Apsoluutne v2ljund funkts glob var 

#define PIN_EDASI    PIN_E1
#define PIN_TAGASI   PIN_E2   
                             
int1 suuna_vahetus = TRUE;   
int1 uus_perioodi_tsykkel = TRUE;  
int16 loendur_ap = 0;               
                                     
                                                       
//-------------------------------- 
// Kellataimeri_funktsioon glob var. KT - kellataimer                      

signed int8 KT_muutus = 0;
signed int8 KT_muutus_2 = 0;
int1 KT_p2eva_muutus = FALSE;
int1 KT_p2eva_muutus_2 = FALSE;
int8 KT_praegune_p2ev = 0;
int8 KT_eelmine_p2ev = 0; 

signed int16 KT_graafiku_muut = 0;  
                             


//-------------------------------- 
// Keele glob muutujad 

int1 keel = FALSE;  // TRUE  - EST                                
                    // FALSE - ENG




//-------------------------------- 
// USB glob muutujad     

#define USB_CON_SENSE_PIN PIN_B2 
                                
#define USB_OPT_FOR_ROM 1       
                  
                      

//--------------------------------                                                         
// INCLUDE
#include <pid IAR.h>    
#include <pid IAR.c>   
#include <flex_lcd.c>   
#include <stdlib.h>
#include <DS1307.c>     
#include <internal_eeprom.c>
#include <2464.c>                         //eeprom
//#include <USB_minu.c> 
//#include <usb_cdc.h> 
#include <graafiku_funktsioon.c>    
#include <ADCfunktsioonid.c>
#include <muutmine.c>            
#include <T66 funktsioon.c>                    
#include <kellaprogramm.c>
#include <aeg_paika.c>
#include <interruptid_include.c>
//#include <numbri_muutmine_include.c>
//#include <numbri_muutmine.c>        
//#include <numbri_muutmine_int16.c>                 
#include <menu_include.c>
#include <menu.c>
#include <PID.c>                  

                  

//-----------------------------------------------------------------------
// FUNCTION PROTOTYPES
                            
                           
 
//=============================================
//PROGRAMM            
    


//=============================================
//MAIN
void main()
{
   output_high(LCD_LED); 
   
   

   init_ext_eeprom();
   
   //pysim2lu_stardis();
   
   //Hiljem parandada.
   //Esmasp2ev on 1 mitte 0 kui Pp on 7;                                            
   gca_ds1307_regs[DS1307_DAY_OF_WEEK_REG]= 1;         
   ds1307_set_date_time();  
 

   t2iteteguri_piirv22rtus = t2iteteguri_piir(MIN_PERIOOD,MIN_IMPULLS);
   t2iteteguri_piirv22rtus_neg = -t2iteteguri_piirv22rtus;
   
                
   //Ext int init      
   L2H_flag = TRUE;         
   ext_int_edge(L_TO_H);  //Katkesus k2ivitub, impulsi t6usul                        
   enable_interrupts(INT_EXT); 
   //-----------------------------------------------------
          
   //Timer3 intit ----------------------------------------
   setup_timer_3(T3_INTERNAL | T3_DIV_BY_8); 
   set_timer3(0);   //Period = 0,0873813 s  T3 prescaler 1:8  @24Mhz
   enable_interrupts(INT_TIMER3);         
   //-----------------------------------------------------    
                                
   //Change on port B katkestus                 
   enable_interrupts(INT_RB);             
   //-------------------------------------     
   
   //ADC init                                        
   SETUP_ADC_PORTS (AN0_TO_AN1| VREF_VREF);
   //setup_adc( ADC_CLOCK_INTERNAL ); 
   setup_adc( ADC_CLOCK_DIV_16 );
   read_adc(ADC_START_ONLY);                
   //------------------------------------- 
   
                                         
   //Init LCD                                      
   lcd_init(); 
   
   //Init PID
   Init_PID();    
                              
   while(TRUE)
   { 
        

      //yleslaadimine(100);
      
                                                         
      menu_test(); // K6ike siduv funktsioon
      
   


   }                 
}          
       

                     
                                    
