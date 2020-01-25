void vilkuv_kursor(void);


//parandada ehk pole vaja
unsigned int16 ADC2voldid_v2(int16 adc_v22rtus) 
{
   //Muutujate deklareerimine
                              
   unsigned int32 voldid;
   unsigned int16 voldid_16;
   
   //Muutujasse "adc_v22rtus" l2heb ADC registi v22rtus
   //adc_v22rtus = adc_keskmine(0);
   
   //Valem, et teisendada ADC v22ruts -- > Pingeks (V)
   //100000 on ylemise ja alumise piiri vahe, antud juhul 3,4V - 1,2V = 2.2V
   voldid = (unsigned int32) (( adc_v22rtus * 220000));       
   voldid_16 = (unsigned int16) ( (voldid >> 10) / 100);
   voldid_16 += 1200; // on alumine piir, antud juhul 1.2V;    
   //Funktsiooni tagatis (v22rtus)
   //printf("\n\rvoldid_16 %Ld",voldid_16);
   return voldid_16;   
}                         



unsigned int16 ADC2voldid(int16 adc_v22rtus)      
{                                           
   //Muutujate deklareerimine
                                              
   unsigned int32 voldid;  
   unsigned int16 voldid_16;                         
   
   //Muutujasse "adc_v22rtus" l2heb ADC registi v22rtus
   //adc_v22rtus = adc_keskmine(0);
   
   //Valem, et teisendada ADC v22ruts -- > Pingeks (V)                             
   //Ylemise piir antud juhul  = 2.5V alumist aga ei ole = 0V             
   voldid = (unsigned int32) (( adc_v22rtus * 150000));       
   voldid_16 = (unsigned int16) ( (voldid >> 10)/10 );     
   //Funktsiooni tagatis (v22rtus)     
   //printf("\n\rvoldid_16 %Ld",voldid_16);  
   return voldid_16;                    
}                                                   



signed int16 Voldid2temp_conv_MCP97001A(signed int16 Pinge)     
{                            

// Muutujass "Pinge" l2heb funktsiooni
//"ADC2voldid" tagatise v22rtus                    
//Pinge = ADC2voldid(adc_keskmine(0)); 

//MCP9701A andruti pinge 0 C juures on 400mA
//Anduri temp coff on 19,5 mV C kohta.        
                                                  
Pinge -= 4000;                                              
                                            
//printf("\n\rTemperatuur %Ld",( (signed int32)(   Pinge*(signed int32)100   )  /195 ));  
return ( (signed int32)(   Pinge*(signed int32)100   )  /195 );
}
 
 
//MCP9700A vovt to temp  
signed int16 Voldid2temp_conv (signed int16 Pinge)     
{                            

// Muutujass "Pinge" l2heb funktsiooni
//"ADC2voldid" tagatise v22rtus                    
//Pinge = ADC2voldid(adc_keskmine(0)); 
                                
//MCP9700A andruti pinge 0 C juures on 500mA
//Anduri temp coff on 10 mV C kohta.        
                                                  
Pinge -= 5000;                                              
                                            
//printf("\n\rTemperatuur %Ld",( (signed int32)(   Pinge*(signed int32)100   )  /195 ));  
return ( (signed int32)(   Pinge*(signed int32)100   )  /100 );
}
                     


// Yldistatud funkts Nii KV kui ka V6 jaoks, Ei ole nii t2pne kui on 
// spetsiaalselt V6 v6i KV jaoks.                                              
signed int16 Voldid2temp_conv2(signed int16 Pinge)     
{                                    
                                     
   signed int16   Temperatuur;
                                   

   signed int16   a,                   
                  b,
                  c;

   // Muutujass "Pinge" l2heb funktsiooni
   // "ADC2voldid" tagatise v22rtus
   //Pinge = ADC2voldid(adc_keskmine(0));
   
   // Valem
   //Temperatuur = ((signed int32) (Pinge * 100000) / 754)- 16053;
   b = (signed int32) (Pinge * 100000) / 754;
   Temperatuur = b - 16053;
   

//b = = -0.00000684*F2*F2 + 0.09163*F2 + -131.8
//Pinge = 200;
//printf("\n\rPinge       %Ld",Pinge);
                                  
a =(float)Pinge*Pinge*-0.09815;
//printf("\n\ra       %Ld",a);
b =(float)( 103.6*Pinge);                      
//printf("\n\rb       %Ld",b);
c = a + b + -14300;
//printf("\n\rc       %Ld",c);            

Temperatuur = c;
//printf("\n\rTemperatuur %Ld",Temperatuur);
return Temperatuur;
}



//Spetsiaalselt V6 piiride jaoks, et max t2psust.
signed int16 Voldid2temp_conv_V6(signed int16 Pinge) 
{

   signed int16   Temperatuur;

   signed int16   a,
                  b,
                  c;


//printf("\n\rPinge       %Ld",Pinge);

   
   a =(float)Pinge*Pinge*-0.001591;
   //printf("\n\ra       %Ld",a);
   b =(float)( 12.46*Pinge);
   //printf("\n\rb       %Ld",b);
   c = a + b + -16080;
   //printf("\n\rc       %Ld",c);

Temperatuur = c;
   
   
   

//printf("\n\rTemperatuur %Ld",Temperatuur);
return Temperatuur;
}
 
 

//Spets KV temp. piirkonna jaoks, et MAX t2psust                                                   
signed int16 Voldid2temp_conv_KV(signed int16 Pinge) 
{

   signed int16   Temperatuur;       

   signed int16   a,
                  b,
                  c;

//printf("\n\rPinge       %Ld",Pinge);
            
            
   a =(float)Pinge*Pinge*-0.0006968;
   //printf("\n\ra       %Ld",a);
   b =(float)( 9.051*Pinge);
   //printf("\n\rb       %Ld",b);
   c = a + b + -12810;
   //printf("\n\rc       %Ld",c);
   
Temperatuur = c;

//printf("\n\rTemperatuur %Ld",Temperatuur);
return Temperatuur;
}



void Voldid_temp_conv()
{
   signed int16   Temperatuur,
                  Pinge;
   int1           ADC_port;
   
   //Peatan inteeruptide t66.
   //disable_interrupts (global);
   KURSOR_V2LJAS
   PUHASTA_LCD
   printf (lcd_putc, "Andur_"); 
   lcd_gotoxy (15, 1) ;
   lcd_putc ((char)223);  
   lcd_putc ('C');   
   lcd_gotoxy (1, 2) ;
   printf (lcd_putc, "PINGE");
   lcd_gotoxy (16, 2) ;
   lcd_putc ('V');                 
                                            
   while ( !EXIT )    {
   
               if(up){
               up = FALSE;
               ADC_port = 0;
               }           
               if(down){
               down = FALSE;                                        
               ADC_port = 1; 
               }  
                                                            
            // Muutujass "Pinge" l2heb funktsiooni 
            // "ADC2voldid" tagatise v22rtus              
            Pinge = ADC2voldid (adc_keskmine(ADC_port));
            Temperatuur = Voldid2temp_conv(Pinge);  
                                                     
            // LCD kuvamis osa                            
            lcd_gotoxy (7,1); 
            printf (lcd_putc,"%u",ADC_port); 
            lcd_gotoxy (9,1);
            printf (lcd_putc,"%5.2Lw",Temperatuur);
            lcd_gotoxy (9,2);                                    
            printf (lcd_putc,"%4.4Lw",Pinge);

            }                          
   exit = FALSE;    
   //enable_interrupts (global) ;
}



float ADC2volts_float()
{               
   int16 adc_v22rtus; 
   float volts;


   adc_v22rtus = read_adc ();
   volts = (float) (adc_v22rtus * 5) / 1023.0;
      
   return volts;                               
}


                                   
int16 t2iteteguri_piir(int16 periood_min_lim, int16 impulls_min_lim)
{
//v2ljund on 1.0000 ehk 10000
// N:                   --714

int16  D_piir;
        
D_piir = ((int32)impulls_min_lim * 10000) / periood_min_lim;


//printf("\n\rD piir v22rtus on: %Lu",D_piir);
return D_piir;                   
}



int8 graafik_tegur_conv2int8(signed int16 graafiku_tegur) 
{
//-1,600
int8 v2ljund;
signed int16 v2ljund2;

v2ljund2 =((float)(graafiku_tegur)/(MAX_graafiku_tegur)*10000);
v2ljund = (int8)(v2ljund2/100);

//v2ljund = (int8)(((float)(graafiku_tegur)/((float)MAX_graafiku_tegur)) + MIN_graafiku_tegur);

//printf("\r\nGraafiku tegur conv int8 = %u",v2ljund); // kustuta hiljem   

return v2ljund;
}



signed int16 grafik_tegur_conv2sint16(int8 graafik_tegur_int8)
{
signed int16 v2ljund;
float v2ljund2;
                            
                                                       
//graafik_tegur_int8;
v2ljund2 = ((float)graafik_tegur_int8*MAX_graafiku_tegur)/100;
v2ljund = (signed int16)v2ljund2;
//printf("\r\nGraafiku tegur16 conv2F = %f",v2ljund2);
//printf("\r\nGraafiku tegur16 conv2L = %Ld",v2ljund);

return v2ljund; 
}                   



void graafiku_valik_kasutajaliides() 
{
int8 muudetav;      
int1 muutus = TRUE;    

PUHASTA_LCD         
                            
lcd_gotoxy(1,2); 

   if(keel) {
   printf(lcd_putc,"0-lauge 99-j\341rsk");   
   //lcd_send_byte(1,0b11100001);  // ä - täht - oct 341  
   }
   else{
   printf(lcd_putc,"0-flat  99-steep"); 
   }                 
             
graafiku_tegur_int8 = graafik_tegur_conv2int8(graafik_tegur);
                                 
muudetav = graafiku_tegur_int8;

                            
                                               
while(!select)  {   
   
   if(muutus) {
   muutus = FALSE;
   lcd_gotoxy(2,1);
   
   printf(lcd_putc,"%u ",graafiku_tegur_int8);
   
   }



   if(down) {
   down = FALSE;
   muutus = TRUE;
      if(graafiku_tegur_int8 != 99) {
      graafiku_tegur_int8++;
      }
   
   }
   if(up){
   up = FALSE;
   muutus = TRUE;
      if(graafiku_tegur_int8 != 0) {
      graafiku_tegur_int8--;
      }

   }
   if(exit) {
   break;
   }
   
   
}
   
   
   
select = FALSE;
                 
   if(!exit) {
   graafik_tegur = grafik_tegur_conv2sint16(graafiku_tegur_int8);
   write_int16_eeprom(1,graafik_tegur); 
   }
   exit = FALSE;
   
}



void graafiku_nihutamine_kasutajaliides()
{
signed int8 muudetav;
int1 muutus = TRUE;

PUHASTA_LCD

lcd_gotoxy(5,1);                  
lcd_putc ( 223) ; // oct 337
lcd_putc ( 'C') ;

lcd_gotoxy(1,2);

   if(keel){    
   printf(lcd_putc,"Graafiku nih. \»\«"); 
   }
   else{
   printf(lcd_putc,"Curve shift   \»\«");
   }   
   
muudetav =  (int8)graafik_y/100;



while(!select)  {
   
   if(muutus) {
   muutus = FALSE;
   lcd_gotoxy(2,1);
   
   printf(lcd_putc,"%d ",muudetav);
   
   }



   if(down) {
   down = FALSE;
   muutus = TRUE;
      if(muudetav!= MAX_temp_nihutamine) {
      muudetav++;
      }
   
   }
   if(up){
   up = FALSE;
   muutus = TRUE;
      if(muudetav != MIN_temp_nihutamine) {
      muudetav--;
      }

   }
if(exit) {
break;
}
   
   
}
   
   
   
select = FALSE;


if(!exit) {
graafik_y = ((signed int16)muudetav) *100;
write_int16_eeprom(3,graafik_y);
}

exit = FALSE;

    


} 
 
 

void graafiku_piiramine_max_kasutajaliides()
{
int8 muudetav;
int1 muutus = TRUE;

PUHASTA_LCD

lcd_gotoxy(5,1);
lcd_putc ((char) 223) ;
lcd_putc ('C') ;

lcd_gotoxy(1,2); 

   if(keel) {
   printf(lcd_putc,"Max KV. temp.");
   }
   else{
   printf(lcd_putc,"Max HW. temp.");  // Vb paranda s22st eesm2rk
   }

muudetav =  (int8) (graafik_max/100);




while(!select)  {
   
   if(muutus) {
   muutus = FALSE;
   lcd_gotoxy(2,1);
   
   printf(lcd_putc,"%u ",muudetav);
   
   }



   if(down) {
   down = FALSE;
   muutus = TRUE;
      if(muudetav!= MAX_temp_piiramine_max) {
      muudetav++;
      }
   }
   
   if(up){
   up = FALSE;
   muutus = TRUE;
      if((muudetav != MIN_temp_piiramine_max) && (muudetav != (int8)(graafik_min/100))) {
      muudetav--;
      }
   }
   
   if(exit) {
   break;
   }

   
}
   
   
select = FALSE;

   if(!exit) {
   graafik_max =((signed int16)muudetav) *100;
   write_int16_eeprom(5,graafik_max);

   }
exit = FALSE;
   
}



void graafiku_piiramine_min_kasutajaliides()
{
int8 muudetav;
int1 muutus = TRUE;

PUHASTA_LCD

lcd_gotoxy(5,1);
lcd_putc ((char) 223) ;
lcd_putc ('C') ;

lcd_gotoxy(1,2);

   if(keel) {
   printf(lcd_putc,"Min KV. temp.");
   }
   else{
   printf(lcd_putc,"Min HW. temp."); 
   }  
          
//printf("\n\r%Ld ",graafik_min);
muudetav =  (int8) (graafik_min/100);



while(!select)  {               
   
   if(muutus) {
   muutus = FALSE;
   lcd_gotoxy(2,1);
   
   printf(lcd_putc,"%u ",muudetav);
   
   }



   if(down) {
   down = FALSE;
   muutus = TRUE;
      if((muudetav!= (int8)(graafik_max/100)) && (muudetav!= MAX_temp_piiramine_min)) {
      muudetav++;
      }
   }
   
   if(up){
   up = FALSE;
   muutus = TRUE;
      if(muudetav!= MIN_temp_piiramine_min) {
      muudetav--;
      }
   }
   
   if(exit) {
   break;
   }

   
}
   
   
select = FALSE;

   if(!exit) {
   graafik_min =((signed int16)muudetav) *100;
   write_int16_eeprom(13,graafik_min);

   }
exit = FALSE;
   
}
 
 

void alseadistuse_seadistamine()
{

int1 muutus = TRUE;
int1 Y_N = FALSE;

PUHASTA_LCD     
KURSOR_SEES  

lcd_gotoxy(1,1);

   if(keel){
   printf(lcd_putc,"TAASTA ALGSEADED");
   }                
   else{
   printf(lcd_putc,"RESTORE SETTINGS"); 
   } 
   
lcd_gotoxy(2,2);
printf(lcd_putc,"Y N");


while(!select) {
   
   vilkuv_kursor(); 
   
   if(muutus) {
   muutus = FALSE;
   lcd_gotoxy(9,2);
   
      if(Y_N) {
      
         if(keel){
         printf(lcd_putc,"KINNITA"); 
         }
         else{
         printf(lcd_putc,"   AGREE");  
         }
         
      }      
      else {
      
         if(keel){
         printf(lcd_putc,"T");
         lcd_send_byte(1,0b11110101);
         printf(lcd_putc,"HISTA"); 
         }
         else{       
         printf(lcd_putc,"DISAGREE");          
         }
                              
      }
                         
      if(Y_N) {              
      lcd_gotoxy(2,2);
      }
      else {
      lcd_gotoxy(4,2);
      }
                            
   }

   if(up) {
   up = FALSE;
   muutus = TRUE;
   Y_N = TRUE;
   }
   
   if(down) {
   down = FALSE;
   muutus = TRUE;
   Y_N = FALSE;
   }
   
   if(exit) {
   Y_N = FALSE;
   break;  
   }
   
   
}

PUHASTA_LCD
KURSOR_V2LJAS   

lcd_gotoxy(1,1);

   if(keel){        
   printf(lcd_putc,"Tehase seadistus\n"); 
   }
   else{
   printf(lcd_putc,"Factory setup\n");       
   } 
   
   if((Y_N == TRUE) &&  (exit == FALSE)) {  
   
      if(keel){
      printf(lcd_putc,"taastatud"); 
      }
      else{
      printf(lcd_putc,"recovered");   
      }  
      
   //--------------------------------
   // Graafiku_funktsioon   glob var
   // 2 viimast arvu on arvud peale koma
   
   //#define graafik_tegur_def -1600
   //#define graafik_null_def  -458
   //#define graafik_y_def      0
   //#define graafik_max_def    7500
   //#define graafik_min_def    2500            
   
   graafik_tegur = graafik_tegur_def ; 
   write_int16_eeprom(1,graafik_tegur_def); 
   graafik_null  = graafik_null_def;  
   
   graafik_y     = graafik_y_def;     
   write_int16_eeprom(3,graafik_y_def);
   graafik_max   = graafik_max_def;   
   write_int16_eeprom(5,graafik_max_def);
   
   graafik_min = graafik_min_def;
   write_int16_eeprom(13,graafik_min_def); // parandada 
                                         
   
   
   
   
   
   //--------------------------------
   // Kellaprogramm 1   glob var
   
   //#define KP_muudetav_v22rtus_def 0
   
   KP_muudetav_v22rtus = KP_muudetav_v22rtus_def;
   
   
   }
   else { 
      if(keel)
      {
      printf(lcd_putc,"taastamatta");
      }
      else{
      printf(lcd_putc,"not recovered");
      }
   }

delay_ms(2000);  



                  


exit = FALSE;   
KURSOR_V2LJAS
}
     

void pysim2lu_stardis()  
{                        

/*//////////////////////////////////

Mida Kirjutan EEPROM-i m2llu ?

On vaja Teada addressit ja nende 
addresite peal asuvat muutujat.

Kyttegraafiku parameetrid:

- "Graafiku valik" 
muutuja: sint16 graafik_tegur; 

- "Graafik nihe"
muutuja: sint16 graafik_y;

- "Piiramine"
muutuja: sint16 graafik_max; 


Programmkella nr1 parameetrid:

-"Kellaprogrammi nr1 uudetav v22rtus"    
muutuja: sint8 KP_muudetav_v22rtus 

-"N2dalap2evad on ja off"  
muutujad: int1 array n2dalap2evad_on_off[7] = 1,1,1,1,1,0,0;  

-"ON ja OFF aeg"  
muutujad: int8 ON_tunnid;
          int8 ON_minutid;
          int8 OFF_tunnid;
          int8 OFF_minutid;
          
- Programmkell 2 sama moodi.
*///////////////////////////////////


// Esimene k2ivitamise kord kirjutab eepromi def v22rtused
if (read_eeprom(0) != 'V') {
//printf("\n\r Esimene k2ivitamine !!!!!!!!");


//- "Graafiku valik" 
//muutuja: sint16 graafik_tegur; 
write_int16_eeprom(1,graafik_tegur_def); 

//- "Graafik nihe"
//muutuja: sint16 graafik_y;
write_int16_eeprom(3,graafik_y_def);

//- "Piiramine max"
//muutuja: sint16 graafik_max; 
write_int16_eeprom(5,graafik_max_def);

//- "Piiramine min"
//muutuja: sint16 graafik_min; 
write_int16_eeprom(13,graafik_min_def);

//printf("\n\r %Ld",read_int16_eeprom(4));

//-"Kellaprogrammi nr1 uudetav v22rtus"  
//muutuja: sint8 KP_muudetav_v22rtus 
write_eeprom(7,KP_muudetav_v22rtus_def);  

//-"N2dalap2evad on ja off"  
//muutujad: int1 array n2dalap2evad_on_off[7] = 1,1,1,1,1,0,0;  
write_int1_eeprom(8,0,n2dalap2evad_on_off_def_0);
write_int1_eeprom(8,1,n2dalap2evad_on_off_def_1);
write_int1_eeprom(8,2,n2dalap2evad_on_off_def_2);
write_int1_eeprom(8,3,n2dalap2evad_on_off_def_3);
write_int1_eeprom(8,4,n2dalap2evad_on_off_def_4);
write_int1_eeprom(8,5,n2dalap2evad_on_off_def_5);
write_int1_eeprom(8,6,n2dalap2evad_on_off_def_6); 
                            
//-"ON ja OFF aeg"  
//muutujad: int8 ON_tunnid;
//          int8 ON_minutid;
//          int8 OFF_tunnid;
//          int8 OFF_minutid;
write_eeprom(9,ON_tunnid_def);
write_eeprom(10,ON_minutid_def);
write_eeprom(11,OFF_tunnid_def); 
write_eeprom(12,OFF_tunnid_def); 


// Kellaprogramm nr2

write_eeprom(13,KP_muudetav_v22rtus_2_def);  

write_int1_eeprom(14,0,n2dalap2evad_on_off_2_def_0); 
write_int1_eeprom(14,1,n2dalap2evad_on_off_2_def_1);
write_int1_eeprom(14,2,n2dalap2evad_on_off_2_def_2);
write_int1_eeprom(14,3,n2dalap2evad_on_off_2_def_3);
write_int1_eeprom(14,4,n2dalap2evad_on_off_2_def_4);
write_int1_eeprom(14,5,n2dalap2evad_on_off_2_def_5);
write_int1_eeprom(14,6,n2dalap2evad_on_off_2_def_6); 

write_eeprom(15,ON_tunnid_2_def);
write_eeprom(16,ON_minutid_2_def);        
write_eeprom(17,OFF_tunnid_2_def); 
write_eeprom(18,OFF_tunnid_2_def); 
                    



//read_int1_eeprom(8,4)  
write_eeprom(0,'V');
}                                 
else {
//printf("\n\r Ei ole esimene k2ivitamine !!!!!!!!");

//- "Graafiku valik" 
//muutuja: sint16 graafik_tegur; 
graafik_tegur = read_int16_eeprom(1);

//- "Graafik nihe"
//muutuja: sint16 graafik_y;
graafik_y = read_int16_eeprom(3);
                            
//printf("\n\r %Lu",read_int16_eeprom(5));
//- "Piiramine max"
//muutuja: sint16 graafik_max; 
graafik_max = read_int16_eeprom(5);

//- "Piiramine min"
//muutuja: sint16 graafik_min; 
graafik_min = read_int16_eeprom(13);

//-"Kellaprogrammi nr1 uudetav v22rtus"  
//muutuja: sint8 KP_muudetav_v22rtus 
KP_muudetav_v22rtus = read_eeprom(7); 
                                     
//-"N2dalap2evad on ja off"  
//muutujad: int1 array n2dalap2evad_on_off[7] = 1,1,1,1,1,0,0;  
n2dalap2evad_on_off[0] = read_int1_eeprom(8,0);
n2dalap2evad_on_off[1] = read_int1_eeprom(8,1);
n2dalap2evad_on_off[2] = read_int1_eeprom(8,2);
n2dalap2evad_on_off[3] = read_int1_eeprom(8,3);
n2dalap2evad_on_off[4] = read_int1_eeprom(8,4);
n2dalap2evad_on_off[5] = read_int1_eeprom(8,5);
n2dalap2evad_on_off[6] = read_int1_eeprom(8,6);
                                      
                            
//-"ON ja OFF aeg"                       
//muutujad: int8 ON_tunnid;
//          int8 ON_minutid;
//          int8 OFF_tunnid;
//          int8 OFF_minutid;
ON_tunnid = read_eeprom(9);
ON_minutid = read_eeprom(10);
OFF_tunnid = read_eeprom(11);
OFF_minutid = read_eeprom(12);
                                

//Kellaprogramam nr2
KP_muudetav_v22rtus_2 = read_eeprom(13); 

n2dalap2evad_on_off_2[0] = read_int1_eeprom(14,0);
n2dalap2evad_on_off_2[1] = read_int1_eeprom(14,1);
n2dalap2evad_on_off_2[2] = read_int1_eeprom(14,2);
n2dalap2evad_on_off_2[3] = read_int1_eeprom(14,3);
n2dalap2evad_on_off_2[4] = read_int1_eeprom(14,4);
n2dalap2evad_on_off_2[5] = read_int1_eeprom(14,5); 
n2dalap2evad_on_off_2[6] = read_int1_eeprom(14,6); 
         
ON_tunnid_2 = read_eeprom(15);               
ON_minutid_2 = read_eeprom(16);
OFF_tunnid_2 = read_eeprom(17); 
OFF_minutid_2 = read_eeprom(18);


//Suuna vahetus
suuna_vahetus = read_int1_eeprom(8,7); 

                              
//keele valik
keel = read_int1_eeprom(14,7);  
}




}


signed int8 sint16_2_sint8(signed int16 sisend) // Sis nr. N: 2342 v6i -2134
{

signed int8 a;
int8 b;

//printf("\n\rALGUS sint16  %ld",sisend);

b = sisend % 10;

sisend = sisend /10;

   if(b >= 5) {
   sisend++;
   }
   
b = sisend % 10;

a = sisend /10;

   if(b >= 5) {
   a++;
   }
   

//printf("\n\rL6PP sint8    %u",a);


return  a;

}


void LCD_taustavalgus()
{

//printf("\n\r taustavalgustuse loendur %Lu",taustavalgustuse_loendur);
//Mida tihedamini kontrollida seda t2sem on see define ~30 sec.


if(nuppu_vajutati) {
nuppu_vajutati = FALSE;
taustavalgustuse_loendur = 0;
}
if(taustavalgustuse_loendur > LCD_LED_loendur) { //LCD_LED_loendus ~340 ~ 30 sec
output_bit(LCD_LED,0);
taustavalgustuse_loendur = LCD_LED_loendur + 10;

}
else {             
output_bit(LCD_LED,1);          
}                                


}                                     



