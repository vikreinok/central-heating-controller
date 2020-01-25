


void pilt_nr1_vilgub() 
{
int8 loendur = 0;


while(!select ) {
                                             
//printf("\n\rLoendur:%u",loendur); 

   if(timer0_tick)  {
   timer0_tick = FALSE;
   loendur++;
                                              
      lcd_gotoxy(11,1);
      printf(lcd_putc,"   ");
                                    

      if(loendur < 5) {
      lcd_gotoxy(11,1);
         if(kellaprog_nr) {              
            if(KP_muudetav_v22rtus == 0) {
            printf(lcd_putc,"OFF" );
            }
            else{
            printf(lcd_putc,"%d",KP_muudetav_v22rtus);
            }
         }
         else {
            if(KP_muudetav_v22rtus_2 == 0) {
            printf(lcd_putc,"OFF" ); 
            }
            else{
            printf(lcd_putc,"%d",KP_muudetav_v22rtus_2);
            }
         }
               }
      else if(loendur > 10) {
      loendur = 0;
      }

   }
   
   if(up) {
   up = FALSE;
   loendur = 0;
      if(kellaprog_nr) {
         if(KP_muudetav_v22rtus > MAX_graafiku_nihe_neg) {
         KP_muudetav_v22rtus --;
         }
      }
      else {
         if(KP_muudetav_v22rtus_2 > MAX_graafiku_nihe_neg) {
         KP_muudetav_v22rtus_2 --;
         }
      }
   }
   if(down) {
   down = FALSE;
   loendur = 0;
      if(kellaprog_nr) {
         if(KP_muudetav_v22rtus < MAX_graafiku_nihe_pos) {
         KP_muudetav_v22rtus ++;
         }
         }
      else {
         if(KP_muudetav_v22rtus_2 < MAX_graafiku_nihe_pos) {
         KP_muudetav_v22rtus_2 ++;
         }
      }
      

   }
   
}
select = FALSE;
lcd_gotoxy(11,1);         
   if(kellaprog_nr) {
   printf(lcd_putc,"%d",KP_muudetav_v22rtus); 
   write_eeprom(7,KP_muudetav_v22rtus); 
   }
   else {
   printf(lcd_putc,"%d",KP_muudetav_v22rtus_2); 
   write_eeprom(13,KP_muudetav_v22rtus_2); 
   }
     
                        


}

void pilt_nr2_vilgub()
{

int1 exit_flag = TRUE;
int1 edasi_flag = FALSE;
int8 asukoht = 1;
int8 a,b;              

lcd_gotoxy(2,1);                                       

   if(keel){
   printf(lcd_putc,"E T K N R L P"); 
   }                                     
   else{                            
   printf(lcd_putc,"M T W T F S S"); // vb paranda  
   }                                

for(a=0;a<7;a++) {       

lcd_gotoxy(b=(a*2)+2,2);
//printf("\n\ra = %u",b );



   if(kellaprog_nr) {   
      if (n2dalap2evad_on_off[a] == 1) {  //hiljem parandada.
      lcd_putc('!');
      }
      else {
      lcd_putc('?');
      }
   }
   else {
      if (n2dalap2evad_on_off_2[a] == 1) {
      lcd_putc('!');
      }
      else {
      lcd_putc('?');
      }
   
   }
}


KURSOR_SEES
 

while(exit_flag) {

switch(asukoht) {

  case 1: lcd_gotoxy(2,2);
         break;
  case 2: lcd_gotoxy(4,2);
         break;
  case 3: lcd_gotoxy(6,2);
         break;
  case 4: lcd_gotoxy(8,2);
         break;
  case 5: lcd_gotoxy(10,2);
         break;
  case 6: lcd_gotoxy(12,2);
         break;
  case 7: lcd_gotoxy(14,2);
         break;
  case 8: exit_flag = FALSE;
          edasi_flag = TRUE;
         break;
}

   if(select) {
   select = FALSE;
      if (asukoht != 8) {
      asukoht++;
      }
   }
   
   if(up){
   up = FALSE;
   lcd_putc('?');  
   //lcd_gotoxy(b = asukoht * 2,2);
      if(kellaprog_nr) {
      n2dalap2evad_on_off[asukoht] = FALSE;
      }
      else {
      n2dalap2evad_on_off_2[asukoht] = FALSE;
      }
   
   }
   
   if(down) {
   down = FALSE;
   lcd_putc('!');
   //lcd_gotoxy(b = asukoht * 2,2);
      if(kellaprog_nr) { 
      n2dalap2evad_on_off[asukoht] = TRUE;
      }
      else {
      n2dalap2evad_on_off_2[asukoht] = TRUE;
      }
   
   }
   

   if(exit) {
   exit = FALSE;
   edasi_flag = FALSE;
   exit_flag = FALSE;
   }
   


}
   KURSOR_V2LJAS
   
   if(edasi_flag) {
   up = TRUE;
   
   }
   
   if(kellaprog_nr) {    
   write_int1_eeprom(8,0,n2dalap2evad_on_off[0]);
   write_int1_eeprom(8,1,n2dalap2evad_on_off[1]);
   write_int1_eeprom(8,2,n2dalap2evad_on_off[2]);
   write_int1_eeprom(8,3,n2dalap2evad_on_off[3]);
   write_int1_eeprom(8,4,n2dalap2evad_on_off[4]);
   write_int1_eeprom(8,5,n2dalap2evad_on_off[5]);
   write_int1_eeprom(8,6,n2dalap2evad_on_off[6]); 
   }
   else {
   write_int1_eeprom(14,0,n2dalap2evad_on_off_2[0]);
   write_int1_eeprom(14,1,n2dalap2evad_on_off_2[1]);
   write_int1_eeprom(14,2,n2dalap2evad_on_off_2[2]);           
   write_int1_eeprom(14,3,n2dalap2evad_on_off_2[3]);
   write_int1_eeprom(14,4,n2dalap2evad_on_off_2[4]);
   write_int1_eeprom(14,5,n2dalap2evad_on_off_2[5]);
   write_int1_eeprom(14,6,n2dalap2evad_on_off_2[6]); 
   }

   


}

void pilt_nr3_vilgub()                           
{
int8 loendur;
int1 tick = FALSE;
int8 valik = 1;

while(valik != 5) {

   if(timer0_tick)  {
   timer0_tick = FALSE;
   loendur++;
      if(loendur > 3) {
      loendur =0;
         if (tick) {
         tick = FALSE;
         }
         else {
         tick = TRUE;
         }
      }
   }
   //printf("\n\rtick %u",tick);
    if(select) {
    tick = TRUE;
    }
   
   
   if(up) {
   up = FALSE;
   tick = TRUE;
      switch (valik) {
      case 1: if(kellaprog_nr) {
                 if(ON_tunnid != 23) {
                 ON_tunnid++;
                 }      
              }
              else {
                 if(ON_tunnid_2 != 23) {
                 ON_tunnid_2++;
                 } 
              }
             break;
      case 2: if(kellaprog_nr) {
                 if(ON_minutid != 59) {
                 ON_minutid++;
                 }     
              }
              else {
                 if(ON_minutid_2 != 59) {
                 ON_minutid_2++;
                 }
              }
                 
              break;
      case 3: if(kellaprog_nr) {
                 if(OFF_tunnid != 23) {
                 OFF_tunnid++;
                 }      
              }
              else {
                 if(OFF_tunnid_2 != 23) {
                 OFF_tunnid_2++;
                 }
              }   
              break;
      case 4: if(kellaprog_nr) {
                 if(OFF_minutid != 59) {
                 OFF_minutid++;
                 }      
              }
              else {
                 if(OFF_minutid_2 != 59) {
                 OFF_minutid_2++;
                 }
              }
                 
              break;
      }
      
      
   
   }
   
   if(down) {
   down = FALSE;
   tick = TRUE;
      switch (valik) {
      case 1: if(kellaprog_nr) {
                 if(ON_tunnid != 0) {
                 ON_tunnid--;
                 }      
              }
              else {
                 if(ON_tunnid_2 != 0) {
                 ON_tunnid_2--;
                 } 
              }
             break;
      case 2: if(kellaprog_nr) {
                 if(ON_minutid != 0) {
                 ON_minutid--;
                 }     
              }
              else {
                 if(ON_minutid_2 != 0) {
                 ON_minutid_2--;
                 }
              }
                 
              break;
      case 3: if(kellaprog_nr) {
                 if(OFF_tunnid != 0) {
                 OFF_tunnid--;
                 }      
              }
              else {
                 if(OFF_tunnid_2 != 0) {
                 OFF_tunnid_2--;
                 }
              }   
              break;
      case 4: if(kellaprog_nr) {
                 if(OFF_minutid != 0) {
                 OFF_minutid--;
                 }      
              }
              else {
                 if(OFF_minutid_2 != 0) {
                 OFF_minutid_2--;
                 }
              }
                 
              break;
      }
   }
   
   
   
   
   switch (valik) {
   case 1: if (tick) {
           lcd_gotoxy(7,1);
              if (kellaprog_nr) {
              printf(lcd_putc,"%02u:",ON_tunnid );
              }
              else {
              printf(lcd_putc,"%02u:",ON_tunnid_2 );
              }
              if(select) {
              select = FALSE;
              valik++;
              //tick = TRUE;
              }
           }
           else {
           lcd_gotoxy(7,1);
           printf(lcd_putc,"  :");          
           }
   
          break;
   case 2: if (tick) {
           lcd_gotoxy(10,1);
           
              if (kellaprog_nr) {
              printf(lcd_putc,"%02u",ON_minutid );
              }
              else {
              printf(lcd_putc,"%02u",ON_minutid_2 );
              }
              if(select) {
              select = FALSE; 
              valik++;
              //tick = TRUE;
              }
           }
           else {
           lcd_gotoxy(10,1);
           printf(lcd_putc,"  ");          
           }
          break;
   case 3: if (tick) {
           lcd_gotoxy(7,2);
           
              if (kellaprog_nr) {
              printf(lcd_putc,"%02u",OFF_tunnid);
              }
              else {
              printf(lcd_putc,"%02u",OFF_tunnid_2);
              }              
              if(select) {
              select = FALSE;
              valik++;
              //tick = TRUE;
              }
           }
           else {
           lcd_gotoxy(7,2);
           printf(lcd_putc,"  ");          
           }
          break;
   case 4: if (tick) {
           lcd_gotoxy(10,2);
           
              if (kellaprog_nr) {
              printf(lcd_putc,"%02u",OFF_minutid );
              }
              else {
              printf(lcd_putc,"%02u",OFF_minutid_2 );
              }        
              if(select) {
              select = FALSE; 
              valik++;
              //tick = TRUE;
              }
           }
           else {
           lcd_gotoxy(10,2);
           printf(lcd_putc,"  ");          
           }
          break;
   }
   
   
   
   if(exit) {
   exit = FALSE;
   break;
   }
   
   
                 
}
   if(kellaprog_nr) { 
   write_eeprom(9,ON_tunnid);
   write_eeprom(10,ON_minutid);
   write_eeprom(11,OFF_tunnid);
   write_eeprom(12,OFF_tunnid); 
   }
   else {
   write_eeprom(15,ON_tunnid_2);  
   write_eeprom(16,ON_minutid_2);
   write_eeprom(17,OFF_tunnid_2);
   write_eeprom(18,OFF_tunnid_2); 
   }   
   

}




void n2dalap2evad_vilkuma()
{
int8 loendur;
int8 a,b;
//printf("\n\rLoendur:%u",loendur);

   if(timer0_tick) {
   timer0_tick = FALSE;
   loendur++;
   
      if(loendur <= 5) {
      lcd_gotoxy(2,1); 
                     
         if(keel){                     
         printf(lcd_putc,"E T K N R L P"); 
         }              //2 4 6 8 101214                       
         else{                            
         printf(lcd_putc,"M T W T F S S"); // vb paranda  
         }   
            
      }
      else {
                        
      lcd_gotoxy(2,1);
      
         for(a=0;a<7;a++) {
         
         lcd_gotoxy(b=(a*2)+2,1);
         //printf("\n\ra = %u",b );
            if(kellaprog_nr) {
               if (n2dalap2evad_on_off[a] == 1) {
               lcd_putc('!');
               }
               else {
               lcd_putc('?');
               }
            }
            else {
               if (n2dalap2evad_on_off_2[a] == 1) {
               lcd_putc('!');
               }
               else {
               lcd_putc('?');
               }
            }
         }
         
      }
      if(loendur >= 10) {
      loendur = 0;
      }
      
   }
   


}




void kellaprogramm_main() 
{
int1 muutus = TRUE;
int1 KP_main_flag = TRUE;
int1 midagi_vilgub = FALSE;
int1 N2dalap2evad_vilguvad = FALSE;

int8 pilt_nr = 0;
pilt_nr = 0;
PUHASTA_LCD
KURSOR_V2LJAS


//if(global_reset) { //Hiljem koristada
//KP_muudetav_v22rtus = KP_muudetav_v22rtus_def; 
//}

   while(KP_main_flag) {
   
      if(muutus) {
      muutus = FALSE;
      
         if(pilt_nr == 0) {
         lcd_send_byte(0,0x01);  // PUHASTAB LCD
         lcd_gotoxy(16,1);
         lcd_putc('>');
         lcd_gotoxy(16,2);
         lcd_putc('>');
         lcd_gotoxy(1,1);
         
            if(keel){
            printf(lcd_putc,"KV muutus");
            }
            else{                           
            printf(lcd_putc,"HW CHANGE"); // Vb parandada. 
            }            
                              
         lcd_gotoxy(14,1);
         lcd_putc ((char)223);
         lcd_putc ('C');
         lcd_gotoxy(11,1);
            if(kellaprog_nr) {
               if(KP_muudetav_v22rtus == 0) {
               printf(lcd_putc,"OFF" );
               }
               else{
               printf(lcd_putc,"%d",KP_muudetav_v22rtus);
               }
            }                       
            else {
               if(KP_muudetav_v22rtus_2 == 0) {
               printf(lcd_putc,"OFF" );
               }                    
               else{
               printf(lcd_putc,"%d",KP_muudetav_v22rtus_2);
               }
                
            }      
         
         
                      

         lcd_gotoxy(1,2);
         
            if(keel){
            printf(lcd_putc,"Graafik nih. \»\«" );
            }
            else{      
            printf(lcd_putc,"Curve shift  \»\«" );      
            }
         
         n2dalap2evad_vilguvad = FALSE;
         }
         else if(pilt_nr == 1) {
         PUHASTA_LCD
         lcd_gotoxy(16,1);
         lcd_putc('>');
         lcd_gotoxy(16,2);
         lcd_putc('>');
         lcd_gotoxy(1,1);
         lcd_putc('<');
         lcd_gotoxy(1,2);
         lcd_putc('<');
         
         n2dalap2evad_vilguvad = TRUE;
         
         //printf(lcd_putc,"");
         
         
         }
         else {
         PUHASTA_LCD
         lcd_gotoxy(1,1);
         lcd_putc('<');
         lcd_gotoxy(1,2);
         lcd_putc('<');
         //printf("\n\rLoendur:3  ");
         lcd_gotoxy(3,1);
         printf(lcd_putc,"ON" );
         lcd_gotoxy(3,2);
         printf(lcd_putc,"OFF" );
         lcd_gotoxy(7,1);
            if(kellaprog_nr) {
            printf(lcd_putc,"%02u:",ON_tunnid );
            printf(lcd_putc,"%02u",ON_minutid );
            }
            else {
            printf(lcd_putc,"%02u:",ON_tunnid_2 );
            printf(lcd_putc,"%02u",ON_minutid_2 );
            }
            
         lcd_gotoxy(7,2);
            if(kellaprog_nr) {
            printf(lcd_putc,"%02u:",OFF_tunnid);
            printf(lcd_putc,"%02u",OFF_minutid );
            }
            else {
            printf(lcd_putc,"%02u:",OFF_tunnid_2);
            printf(lcd_putc,"%02u",OFF_minutid_2 );
            }
            
         n2dalap2evad_vilguvad = FALSE;
         }
      }
      //selgitus_abi_nr1();
      
      if(midagi_vilgub) {
      
      }
      if(n2dalap2evad_vilguvad) {
      //n2dalap2evad_vilguvad = FALSE;
      n2dalap2evad_vilkuma();
      }
      
      if(select) {
      select = FALSE;
         if(pilt_nr == 0) {
         pilt_nr1_vilgub();
         midagi_vilgub = TRUE;
         }
         else if(pilt_nr == 1) {
         muutus = TRUE;
         pilt_nr2_vilgub();
         
         }
         else if(pilt_nr == 2) {
         
         pilt_nr3_vilgub();
         }
         exit = FALSE;
         
      }
      
      if(up) {
      up = FALSE;
      
         if(pilt_nr != 3) {
         pilt_nr++;
         muutus = TRUE;
         }
      }
      
      if(down) {
      down = FALSE;
      
         if(pilt_nr != 0) {
         pilt_nr--;
         muutus = TRUE;
         }
      }
      if(exit) {
      exit = FALSE;
      KP_main_flag = FALSE;
      }
   
   
   }
      
   



}                               
