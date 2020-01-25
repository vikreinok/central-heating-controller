
//funktsioonide prototyybid
void modulaator_T_t1(void); // puhasta kustuta
void Init(void);            
void menu_test(void);
//--------------------------------------   
                               
                             
void uuenda_taustapilt(int1 esimene_v6i_teine)                
{                                            
PUHASTA_LCD                                
                                                    
   if(esimene_v6i_teine){     
   lcd_gotoxy(1,1);      
   lcd_putc("Andmed nr. 1");                                                                                   
   lcd_gotoxy(1,2);                        
   lcd_putc("Mingid numbrid");                                                      
                                             
                            
   //printf(lcd_putc,"V6 %d KV %d aKV %d", 
   //sint16_2_sint8(v2lis6hk_temp),
   //sint16_2_sint8(reaalne_kyttevee_temp),
   //sint16_2_sint8(arvutatud_kyttevee_temp) );
   }
   else{
   lcd_gotoxy(1,1); 
   lcd_putc("Andmed nr. 2");                                               
   lcd_gotoxy(1,2);          
   lcd_putc("Mingid numbrid");               
   }                                
                                                                    
}
   
   
                                                                        
void apsoluutne_v2ljund()               
{                                      
                                      
   
   if(tick_100ms) {     
   tick_100ms = FALSE;      
   loendur_ap++;      
   }              
   
   if(uus_perioodi_tsykkel) {                        
   uus_perioodi_tsykkel = FALSE;                 
   
      if(loendur_ap <= periood) {
         if(suuna_vahetus){
            if(Pos_Neg) {
            output_bit(PIN_EDASI,1);
            }
            else {
            output_bit(PIN_TAGASI,1);
            }
         }
         else{
            if(Pos_Neg) {
            output_bit(PIN_TAGASI,1);
            }         
            else {
            output_bit(PIN_EDASI,1); 
            }
         }
         //printf("\n\r1 %Lu",periood);
      }
   } 
   else {  
      if(loendur_ap > periood) {
         //if(Pos_Neg) {
         output_bit(PIN_EDASI,0);                 
         //}
         //else {
         output_bit(PIN_TAGASI,0);
         //}
         uus_perioodi_tsykkel = TRUE;
         loendur_ap = 0;                     
         //printf("\n\r2");
      }
      else if(loendur_ap > impulls) {
         //if(Pos_Neg) {                  
         output_bit(PIN_EDASI,0);
         //}                       
         //else {
         output_bit(PIN_TAGASI,0);
         //}
         //printf("\n\r3");
      }
                              
   
   }


   
   


}
 
                                                                            
 
void TT_muundur() // T2iteteguri muundur graafikule iseloomulikuks v22rtuseks.                     
{
                    
//Parandada kohandada muuta.                                                             
                                                                      
seaduri_komponent = ( ((signed int16)((seaduri_t2itetegur - 0.5) *1000)) * 2  );
      
//printf("\n\rSeaduri_komponent %Ld",seaduri_komponent ); 
}                                            
 
        
 
void seaduri_TT_arvutus()    
{                                                                                                    
  if(arvuta_uus_TT) {          
     arvuta_uus_TT = FALSE; 
                                                                    
     if( ((count_pos > seadur_t1_min) && (count_pos < seadur_t1_max)) &&    
         ((count_nul > seadur_t0_min) && (count_nul < seadur_t0_max))     ) { 
                                           
      seadur_kinnitatud = TRUE;              
      TT_pullside_loendur_t66++; 
      
      //pulsside pikkused on suuremad seadur_min v22rtusest    
      printf("\n\rNUL %Ld",count_nul);               
      printf("\n\rPOS %Ld",count_pos);   
                                    
      
         if(TT_pullside_loendur_t66 == TT_pullside_loendur_int) {
         TT_pullside_loendur_int--;     
         TT_pullside_loendur_t66--;
                                        
         seaduri_t2itetegur = ((float)count_pos)/(count_pos + count_nul); 
                                      
         // --> Siia funkts mis arvutab graafikule iseloomulikku muuutuse. 
         TT_muundur();
         
         printf("\n\rTT %.4f !l6pp",seaduri_t2itetegur);       
         }
         else {                            
         printf("\n\rEi arvuta TT");     
         TT_pullside_loendur_int = TT_pullside_loendur_t66; //tagab, et ainul 1kord v22ra korral    
         }                       
                                           
                                        
      }                                     
      else  {                                                       
      printf("\n\rPulls ei ole piiride vahel");
      printf("\n\rNUL %Ld",count_nul);               
      printf("\n\rPOS %Ld",count_pos);     
      seadur_kinnitatud = FALSE;
                                           
         if(timer3_count > TIMER3_COUNT_MAX){
          printf("\n\rTIMER COUNT MAX");                        
         //Pane graafikut muutev seaduri komponent normi ehk nulli.
         seaduri_komponent = 0;  
         timer3_count = 0;
         count_nul = 0;              
         count_pos = 0;  
                                     
         }                    
          
                                   
      }                              
      printf("\n\rPULSID int-%u, t66-%u",TT_pullside_loendur_int,TT_pullside_loendur_t66);
  }                         


}
                                        
                                                           
                                          
   /*
     
   if(seadur_kinnitatud) { 
   
                    
      //kaitse et pulsi arvestus ei algaks valesti     
      if ((count_pos > seadur_max) && (count_nul > seadur_max))  {
                                                                    
      //count_nul = 0;              
      count_pos = 0; 
      printf("\n\rcount_pos = 0");       
      }                        
      else if( (count_nul < seadur_min) && (count_pos < seadur_min) ) {
      
      count_nul = 0;
      //count_pos = 0;                         
      printf("\n\rcount_nul = 0");
      }                                  
                                 
      if(arvuta_uus_TT) {         
      arvuta_uus_TT = FALSE;           
      //teeb pulsi T0 ja T1 t2iteteguriks 
      seaduri_t2itetegur = ((float)count_pos)/(count_pos + count_nul);
      //muundur mis teeb t2itetegurist graafiku t6usu (teguri)
                   
      }
   }
   else {    
   //printf("\n\rSeadur on kinnitamata");
   }       
                                        
}  

  */


                                         
void tagasip22s_menyyse()  //vb parandada       
{                                                   
                      
  if(nuppu_oldi_vajutatud) {
  nuppu_oldi_vajutatud = FALSE;   
  tagasip22su_loendur++;              
  LCD_taustavalgus(); // 30 sec jooksul peab korra k2ivitama. 
  //printf("\n\rT66tab ! %u",tagasip22su_loendur);
  }           
  if(tagasip22su_loendur > 5) {   // 5 ehk 2 nupu vajutust.
  tagasip22su_loendur = 0;       
  syda_v2ljap22s_flag = FALSE;   
  }                                     
                                    
                                     
}                             
                                  
                                                        

void Kellataimeri_funktsioon() 
{
//See funkt jookseks umbes iga minut.  
// prandada : kustuta printf-id.

ds1307_read_date_time();                                
                        
                                                                    
printf("\r\n%01u/\%02u:\%02u:\%02u      %02u\\%02u\\%02u",
gca_ds1307_regs[DS1307_DAY_OF_WEEK_REG],
gca_ds1307_regs[DS1307_HOURS_REG],                            
gca_ds1307_regs[DS1307_MINUTES_REG],            
gca_ds1307_regs[DS1307_SECONDS_REG],
gca_ds1307_regs[DS1307_DATE_REG],                 
gca_ds1307_regs[DS1307_MONTH_REG],           
gca_ds1307_regs[DS1307_YEAR_REG]);                       
   
                    
KT_praegune_p2ev = gca_ds1307_regs[DS1307_DAY_OF_WEEK_REG]; // 1-7  
                     
   if(KT_praegune_p2ev != KT_eelmine_p2ev) { 
   KT_p2eva_muutus = TRUE; 
   KT_p2eva_muutus_2 = TRUE;    
   }                     
                          
KT_eelmine_p2ev = KT_praegune_p2ev; // init funktsioonis syda, eespool.
                           
   
//-------------------------------Kella prog nr1---------------------------------   

   if(KP_muudetav_v22rtus != 0){          
                                                  
      if(gca_ds1307_regs[DS1307_MINUTES_REG] >= ON_minutid) {
                                                                    
         if(gca_ds1307_regs[DS1307_HOURS_REG] >= ON_tunnid) {
               
            if( n2dalap2evad_on_off[  (gca_ds1307_regs[DS1307_DAY_OF_WEEK_REG]-1)  ] == TRUE) { 
                                                   
            KT_muutus = KP_muudetav_v22rtus;                                        
            printf("\r\nKT1_muutus ON %d",KT_muutus);
            
                 
               // KUI off aeg on suurem ja ei ole seda l6iku siis tekib probleem.  
               if(OFF_tunnid >= ON_tunnid){
               
                  if(OFF_minutid >= ON_minutid){
                  KT_p2eva_muutus = TRUE; 
                  printf("\r\n1 OFF suurem kui ON");
                  
                  }
                  
               }                                                      
                                   
            }                 
                                   
         }                               
                                      
      }                              
                                                             
                                        
      if(KT_p2eva_muutus) {          
                                
         if(gca_ds1307_regs[DS1307_MINUTES_REG] >= OFF_minutid) {
                                   
            if(gca_ds1307_regs[DS1307_HOURS_REG] >= OFF_tunnid) {                            
              
            //OFF ei s6ltu p2evast  
            KT_muutus = 0;
            KT_p2eva_muutus = FALSE; 
                                                                                                         
            printf("\r\nKT1_muutus OFF %u",KT_muutus);       
            }                    
                                                  
         }                             
                                       
      }                                                                                          
         
   }       
         
//-------------------------------Kella prog nr2---------------------------------                     
   
   
   if(KP_muudetav_v22rtus_2 != 0){
                                                  
      if(gca_ds1307_regs[DS1307_MINUTES_REG] >= ON_minutid_2) {
                                                                    
         if(gca_ds1307_regs[DS1307_HOURS_REG] >= ON_tunnid_2) { 
               
            if( n2dalap2evad_on_off_2[  (gca_ds1307_regs[DS1307_DAY_OF_WEEK_REG]-1)  ] == TRUE) { 
                                                   
            KT_muutus_2 = KP_muudetav_v22rtus_2;                                        
            printf("\r\nKT2_muutus ON %d",KT_muutus); 
            
                 
               // KUI off aeg on suurem ja ei ole seda l6iku siis tekib probleem.  
               if(OFF_tunnid_2 >= ON_tunnid_2){
               
                  if(OFF_minutid_2 >= ON_minutid_2){
                  KT_p2eva_muutus = TRUE; 
                  printf("\r\n2 OFF suurem kui ON");
                  
                  } 
                  
               }                                                      
                                   
            }                 
                                
         }                               
                                      
      }          
                                
        
      if(KT_p2eva_muutus) {          
                                   
          if(gca_ds1307_regs[DS1307_MINUTES_REG] >= OFF_minutid_2) {
                                      
              if(gca_ds1307_regs[DS1307_HOURS_REG] >= OFF_tunnid_2) {                            
                                 
              //OFF ei s6ltu p2evast  
              KT_muutus_2 = 0;              
              KT_p2eva_muutus_2 = FALSE; 
                                                                                                            
              printf("\r\nKT2_muutus OFF %u",KT_muutus);       
              }                    
                                                     
            }                             
                                          
         }                                                                                          
               
      }                           
        
                                                  
   if( (KT_muutus_2 != 0) && (KT_muutus != 0) )  {  
                                                     
   KT_graafiku_muut = ((KT_muutus + KT_muutus_2)*50);      
   printf("\n\rKT_graafiku_muut:(%d + %d)/2 = %Ld",KT_muutus,KT_muutus_2,KT_graafiku_muut); 
               
   }
   else{  
   
      if(KT_muutus != 0){
      KT_graafiku_muut = (signed int16)KT_muutus *100; 
      }
      else if(KT_muutus_2 != 0) {              
      KT_graafiku_muut = (signed int16)KT_muutus_2 *100; 
      }
      else{                      
      KT_graafiku_muut = 0;         
      }                                 
   printf("\n\rKT_graafiku_muut:%d v6i _2 %d = %Ld",KT_muutus,KT_muutus_2,KT_graafiku_muut);
   } 
                                                   
                                       
}                    
                        
                                
                               
void p2evad()                        
{
output_bit(PIN_EDASI,1);
output_bit(PIN_TAGASI,0);           
delay_ms(120000); // 120 sec 
output_bit(PIN_EDASI,0);
output_bit(PIN_TAGASI,1);               
delay_ms(120000); // 120 sec
}                   



void keele_valik()                      
{             
keel++;
lcd_gotoxy(1,1);   
LCD_putc("Keel vahetatud  ");               
lcd_gotoxy(1,2); 
LCD_putc("LANGUAGE CHANGED");
write_int1_eeprom(14,7,keel);
delay_ms(1500); 
 

}
                                        
                                                        
                                                                      
void suuna_valik() 
{                                                
int1 v2ljap22s = TRUE; 
int1 eelmine_suuna_vahetus = suuna_vahetus;
int1 muutus    = TRUE;
   
PUHASTA_LCD                
KURSOR_SEES

lcd_gotoxy(1,1); 


printf(lcd_putc,"\» \«");

   do {       
   vilkuv_kursor();                           
                     

      if(up){
      up = FALSE;            
      muutus = TRUE; 
      suuna_vahetus = TRUE;     
      }                                               
      
      if(down){                                                  
      down = FALSE;     
      muutus = TRUE;   
      suuna_vahetus = FALSE;                          
      }                                               
                                                                                   
      
      if(muutus) {                                                           
      muutus = FALSE;
      
          
      
         if(suuna_vahetus){   
         lcd_gotoxy(1,2); 
            if(keel) {        
            printf(lcd_putc,"P\341rip\341eva");                   
            }               
            else{
            printf(lcd_putc,"clockwise     ");
            }
         lcd_gotoxy(3,1); 
            
         }
         else{         
         lcd_gotoxy(1,2);
            if(keel) {
            printf(lcd_putc,"Vastup\341eva");
            }
            else{              
            printf(lcd_putc,"anti clockwise");
            }
         lcd_gotoxy(1,1);   
         }                   
      }                         
       
      // parandada kui v2line lyl tuleb siis.
      //synkida v2lise nupuga   
      
   if(exit){                
   exit = FALSE;
   suuna_vahetus = eelmine_suuna_vahetus;
   v2ljap22s = FALSE;                                
   }                         
                       
   if(select) {              
   select = FALSE;    
   v2ljap22s = FALSE;           
                                   
   write_int1_eeprom(8,7,suuna_vahetus); 
   }
    
                                     
   } while(v2ljap22s);  
   
   
                    
KURSOR_V2LJAS                 

}

          

void syda()             
{                                                                       
int1 muutus = TRUE;                       
unsigned int8 LCD_loendur = 0; 
int1 LCD_loendur_flag = FALSE;
unsigned int8 USB_loendur = 0; 
int1 USB_loendur_flag = FALSE; 
unsigned int16 Kellataimeri_loendur = KELLATAIMERI_MINUT; //k2ivitub kui t66 funktsi sisenetakse   
int1 Kellataimeri_flag = FALSE;                                

                             
global_M_v6i_T = FALSE;       
       
//setup_wdt(WDT_OFF);                                                               






//KT kellatiameri funkts init
//-------------------------------------- 
ds1307_read_date_time();  //Uuendab DS1307 glob registrid  
// vb oleks parem panna timer0 initi ette 

KT_eelmine_p2ev = gca_ds1307_regs[DS1307_DAY_OF_WEEK_REG]; // 1-7                              
//--------------------------------------             
                                                                                                         
                            
//Timer0_init                 
//--------------------------------------
setup_timer_0(RTCC_internal | RTCC_DIV_16);
//setup_timer_0(RTCC_OFF);               //kommenteeri, et timer v2lja lylitada    
set_timer0(28036);  // 10Hz @ 24 Mhz   
enable_interrupts(INT_TIMER0);                        
enable_interrupts(GLOBAL);                 
//--------------------------------------



   
   
//USB_init                     
//--------------------------------------
usb_cdc_init();   // Start cdc 
//usb_init();       // Start USB
usb_init_cs();   // vb parem varian kui ylemine

//--------------------------------------
                                                          
           

                                                                        
   while(syda_v2ljap22s_flag) {       
                                
   seaduri_TT_arvutus();   

                          
// LCD n2itamise osa.
//--------------------------------------
   
      if (tick_100ms_v2) {           
      tick_100ms_v2 = FALSE;                                   
      LCD_loendur++;                                    
      USB_loendur++;
      Kellataimeri_loendur++;  // ka kellataimeri osa.
      }                                                            
      
      if(LCD_loendur > 15) {  //15*100ms = 1,5 sec 
      LCD_loendur = 0;                                                                      
      LCD_loendur_flag++;  //toimub ylejooks
      muutus = TRUE;                     
      }
      
      if(USB_loendur > 10) {  //10*100ms = 1 sec      
      USB_loendur = 0;                     
      USB_loendur_flag = TRUE;  
      }
                                                     
      //T66funkts taustapildi asi         
      if(muutus) {                                      
      muutus = FALSE;     
      uuenda_taustapilt(LCD_loendur_flag);        
      }                                  
                                                         
//---------------------------------------  

     
//Kellataimeri osa 
//---------------------------------------
      if(Kellataimeri_loendur >= KELLATAIMERI_MINUT) {  //600 + 1*100ms = 1 min.
      Kellataimeri_loendur = 0;  
      Kellataimeri_flag = TRUE;                        
      }                    
      
      if(Kellataimeri_flag) {  
      Kellataimeri_flag = FALSE; 
      Kellataimeri_funktsioon();                           
      }                         
//---------------------------------------
  
                                   
//Uuendab kytte graafiku glob v22rtusi   
//--------------------------------------------------------------------------
                                                            
   //ADC_v22rtus_glob = adc_keskmine(0);                                                                                                     
                                           
   v2lis6hk_temp = Voldid2temp_conv( ADC2voldid(adc_keskmine(0) ));  
   //v2lis6hk_temp = Voldid2temp_conv_V6(ADC2voldid(adc_keskmine(0)));
   //printf("\n\rv2lis6hk_temp           %Ld",v2lis6hk_temp);              
                       
   reaalne_kyttevee_temp = Voldid2temp_conv( ADC2voldid(adc_keskmine(1)));  
   //reaalne_kyttevee_temp = Voldid2temp_conv_KV(ADC2voldid(adc_keskmine(1)));
   //printf("\n\rreaalne_kyttevee_temp   %Ld",reaalne_kyttevee_temp);
                                                                         
   arvutatud_kyttevee_temp = graafiku_funktsioon(v2lis6hk_temp); //11 jan. muuta tagasi 
   //printf("\n\rarvutatud_kyttevee_temp %Ld",arvutatud_kyttevee_temp);
                          
//--------------------------------------------------------------------------
                             
                                                                       
   tagasip22s_menyyse();             
   //LCD_taustavalgus(); // 30 sec jooksul peab korra k2ivitama.
                         
                            
   
   modulaator_T_t1 (); 
   apsoluutne_v2ljund();
                                                                
                    
   
                              
                                 
   //d = 'V';                  
   //write_ext_eeprom(a, d);                                                                     
   //d = read_ext_eeprom(a);       
   //a++;    
      
       
      
   } 
   
syda_v2ljap22s_flag = TRUE; 
       
setup_timer_0(RTCC_OFF);       
set_timer0(0);                              
                
   
                                   

}
