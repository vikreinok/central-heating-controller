//1 rida all: prototyyp funktsioon
char n2dalap2ev_nr_2_char(int8);


void Aeg()
{                                         
int8 a;                                  
                                         
                                          
KURSOR_V2LJAS    
PUHASTA_LCD


   for(a=0;(a<20) && (!EXIT);a++){
                                
   delay_ms(300);  

   ds1307_read_date_time();      
   
   
   //sec   = gca_ds1307_regs[DS1307_SECONDS_REG];
   //min   = gca_ds1307_regs[DS1307_MINUTES_REG];
   //hrs   = gca_ds1307_regs[DS1307_HOURS_REG];
   //day   = gca_ds1307_regs[DS1307_DAY_OF_WEEK_REG];
   //date  = gca_ds1307_regs[DS1307_DATE_REG];
   //month = gca_ds1307_regs[DS1307_MONTH_REG];
   //yr    = gca_ds1307_regs[DS1307_YEAR_REG];


                                  
    lcd_gotoxy(1,1);                      
    printf(lcd_putc, "\%02u/\%02u/\%02u",gca_ds1307_regs[DS1307_DATE_REG],
                                        gca_ds1307_regs[DS1307_MONTH_REG],
                                        gca_ds1307_regs[DS1307_YEAR_REG]);
    lcd_gotoxy(1,2);
    printf(lcd_putc, "%01c/\%02u:\%02u:\%02u",
                   (char)n2dalap2ev_nr_2_char(gca_ds1307_regs[DS1307_DAY_OF_WEEK_REG]),
                                              gca_ds1307_regs[DS1307_HOURS_REG],
                                              gca_ds1307_regs[DS1307_MINUTES_REG],
                                              gca_ds1307_regs[DS1307_SECONDS_REG]);
                                               
   }                                            
   exit = FALSE;         
}                                   


void vilkuv_kursor() //programm v6ib kursori kaotada kui l6peb vales kohas
{
int8 loendur;                             

if(timer0_tick) {                    
   timer0_tick = FALSE;
   loendur++;
   //printf("\n\rLoendus: %u",loendur);
      if(loendur <= 5) {           
      KURSOR_SEES                       
      }                             
      else {
      KURSOR_V2LJAS
      }
      if(loendur >= 10) {
      loendur = 0;
      }           
}
}


char n2dalap2ev_nr_2_char(int8 nr)
{
char a;
   if(keel){
   
      switch(nr) {            //Kui muutuja asendadada erinevate returinidega <ROM
            case 0:  a = 'E'; // VB tuleb parandada 
                     break;
            case 1:  a = 'E'; 
                     break;
            case 2:  a = 'T'; 
                     break;
            case 3:  a = 'K'; 
                     break;
            case 4:  a = 'N'; 
                     break;
            case 5:  a = 'R'; 
                     break;
            case 6:  a = 'L';
                     break;
            case 7:  a = 'P'; 
                     break;
          }
   }
   else{
   
      switch(nr) {            //Kui muutuja asendadada erinevate returinidega <ROM
            case 0:  a = 'M'; // VB tuleb parandada 
                     break;
            case 1:  a = 'M'; 
                     break;
            case 2:  a = 'T'; 
                     break;
            case 3:  a = 'W'; 
                     break;
            case 4:  a = 'T'; 
                     break;
            case 5:  a = 'F'; 
                     break;
            case 6:  a = 'S';
                     break;
            case 7:  a = 'S'; 
                     break;
          }   
   
   }
return a;

}


void print_function(int8 a) 
{
//printf(lcd_putc,"%02u",a); // saved 6 bytes of ROM

int b;
b = a/10;
lcd_putc(b+48); // by divide 10 you can get Example: 9 from 97 
b = a%10;
lcd_putc(b+48); // by modulo 10 you can get Example: 7 from 97
                 // by using modulo 80 byes saved  80 vs 6
}


int8 aeg_muutmine(int8 a,int8 b,int8 c,int8 koht,int1 A_D)//The problem function
{
int8 loendur, d; //d to replase 3X returns 2 byte saved
//printf("\n\ra%u  b%u  c%u",a,b,c);



while((!select) && (!exit)) {
//printf("\n\rkoht %u",koht);

   if(timer0_tick) {
   timer0_tick = FALSE;
   loendur++;
   }
   
   if(loendur < 5) {
   
      if(A_D){
         if(koht == 1) {
         lcd_gotoxy(1,1);
         }
         else if(koht == 2){
         lcd_gotoxy(3,1);
         lcd_putc(' ');
         }
         else{
         lcd_gotoxy(6,1);
         lcd_putc(' ');
         }
      }
      else{
         if(koht == 1) {
         lcd_gotoxy(1,1);
         }
         else if(koht == 2){
         lcd_gotoxy(4,1);
         }
         else{
         lcd_gotoxy(7,1);
         }
         lcd_putc(' ');   
      }
      lcd_putc(' ');     
   }
   else if(loendur > 10){
   loendur = 0;

   }
   else{
      if(A_D){
         if(koht == 1){
         lcd_gotoxy(1,1);
         lcd_putc((char)n2dalap2ev_nr_2_char(a));
         }
         else if(koht == 2){
         lcd_gotoxy(3,1);
         print_function(b);
         }                      
         else{
         lcd_gotoxy(6,1);
         print_function(c);
         }
      }
      else{
         if(koht == 1){
         lcd_gotoxy(1,1);
         print_function(a);
         }
         else if(koht == 2){
         lcd_gotoxy(4,1);
         print_function(b);
         }
         else{
         lcd_gotoxy(7,1);
         print_function(c);
         }         
      }
   }
//printf("\n\ra%u  b%u  c%u",a,b,c);

   if(down) {              
   down = FALSE;
   loendur = 5;
      if(A_D){
         if(koht == 1){
            if(a != 7 ) {
            a++;
            }
         }
         else if(koht == 2){
            if(b != 23 ) {
            b++;
            }
         }
         else{
            if(c != 59 ) {
            c++;
            }
         }
      }
      else{
         if(koht == 1){
            if(a != 31 ) {
            a++;
            }
         }
         else if(koht == 2){
            if(b != 12 ) {
            b++;
            }
         }
         else{
            if(c != 99 ) {
            c++;
            }
         }
      }
      
   }
   
   if(up) {
   up = FALSE;
   loendur = 5;
      if(A_D){
         if(koht == 1){
            if(a >= 2 ) {
            a--;
            }
         }
         else if(koht == 2){
            if(b !=0 ) {
            b--;
            }
         }                     
         else{
            if(c !=0 ) {
            c--;
            }
         }
      }
      else{
         if(koht == 1){
            if(a !=0 ) {
            a--;             
            }
         }              
         else if(koht == 2){
            if(b !=0 ) {
            b--;
            }
         }
         else{
            if(c !=0 ) {
            c--;
            }
         }                        
      }
      
   }
   
   
}

   if(koht == 1){
      d = a;
   }
   else if(koht == 2){
      d = b;
   }
   else{
      d = c;         
   }
                                
   return d;
}


void Aeg_kuup2ev_main(int1 A_D)  // A_D == TRUE v6rdub day, tund, min
{
   int1 lcd_uuendus = TRUE;
   int1 ei_v2lju = TRUE;
   int8 a, b, c;
   int8 koht = 0;
   
   ds1307_read_date_time();
   
      if(A_D) {
      a = gca_ds1307_regs[DS1307_DAY_OF_WEEK_REG];
      b = gca_ds1307_regs[DS1307_HOURS_REG];
      c = gca_ds1307_regs[DS1307_MINUTES_REG];
      }
      else{
      a = gca_ds1307_regs[DS1307_DATE_REG];
      b = gca_ds1307_regs[DS1307_MONTH_REG];
      c = gca_ds1307_regs[DS1307_YEAR_REG];
      }
      
   //printf("\r\n%02u  %02u  %02u",a,b,c);
   
   //printf("\r\n%01u  %02u  %02u",n2dalap2ev,tunnid,minutid);
   
   PUHASTA_LCD     
   

   while(ei_v2lju) {
      
      
      if(lcd_uuendus) {
      lcd_uuendus = FALSE;
      
      lcd_gotoxy(1,1);
         if(A_D){
         printf(lcd_putc,"%c/%02u:%02u",(char)n2dalap2ev_nr_2_char(a),b,c);
         }
         else{
         printf(lcd_putc,"%02u/%02u/%02u",a,b,c);
         }
      }
      
      
      if(select) {
      select = FALSE;
      koht++;
      
      
      }
      lcd_gotoxy(1,2);
         if(koht != 0) { 
            if(keel){
            printf(lcd_putc,"Sis. ");
            }
            else{
            printf(lcd_putc,"Enter "); 
            }  
         }
      switch(koht) {
            case 0:  lcd_gotoxy(1,2);
            
                        if(keel) {
                        printf(lcd_putc,"OK, et muuta");//enter weekday
                        }
                        else{
                        printf(lcd_putc,"OK, TO CHANGE");//enter weekday
                        }
                        
                     break;                 
                     
            case 1:  if(A_D) {  
            
                        if(keel) {
                        printf(lcd_putc,"n\341dalap\341ev"); 
                        }
                        else{
                        printf(lcd_putc,"week-day"); 
                        }                                       
                        
                     a = aeg_muutmine(a,b,c,koht,A_D);
                     }
                     else{
                     
                        if(keel){
                        printf(lcd_putc,"kuup\341v");
                        }
                        else{                    
                        printf(lcd_putc,"date   ");     
                        }                            
                        
                     a = aeg_muutmine(a,b,c,koht,A_D);
                     }
                     lcd_uuendus = TRUE;
                     break;
                     
            case 2:  if(A_D) { 
            
                        if(keel){
                        printf(lcd_putc,"tunnid    ");
                        }
                        else{                  
                        printf(lcd_putc,"hours   ");
                        }
                        
                     b = aeg_muutmine(a,b,c,koht,A_D);
                     }
                     else{
                     
                        if(keel){
                        printf(lcd_putc,"kuu    ");
                        }
                        else{
                        printf(lcd_putc,"month");
                        }    
                     
                     b = aeg_muutmine(a,b,c,koht,A_D);
                     }
                     lcd_uuendus = TRUE;
                     break;
                     
            case 3:  if(A_D) {
            
                        if(keel){
                        printf(lcd_putc,"minutid");
                        }
                        else{
                        printf(lcd_putc,"minutes");
                        }
                        
                     c = aeg_muutmine(a,b,c,koht,A_D);
                     }
                     else{
                        
                        if(keel){
                        printf(lcd_putc,"aasta"); 
                        }
                        else{
                        printf(lcd_putc,"year "); 
                        }  
                        
                     c = aeg_muutmine(a,b,c,koht,A_D);
                     }
                     lcd_uuendus = TRUE; 
                     break;
                     
            case 4:  ei_v2lju = FALSE;
                     break;
   
      
      }
      
      
      
      
      
      
      
      
      
      if(exit) {
      ei_v2lju = FALSE; // while loobist v2lja 
      }
      
      
   }
   
ei_v2lju = TRUE;         
select = FALSE;

   if(!exit) {
   
      if(A_D) {
      gca_ds1307_regs[DS1307_SECONDS_REG] = 0;  // vb parandada.    
      gca_ds1307_regs[DS1307_MINUTES_REG] = c; 
      gca_ds1307_regs[DS1307_HOURS_REG] = b; 
      gca_ds1307_regs[DS1307_DAY_OF_WEEK_REG]= a;
      
                                                  
      }
      else{
      gca_ds1307_regs[DS1307_DATE_REG] = a;
      gca_ds1307_regs[DS1307_MONTH_REG] = b;
      gca_ds1307_regs[DS1307_YEAR_REG] = c;
      
      }
      
   ds1307_set_date_time();
   }

exit = FALSE;


}



