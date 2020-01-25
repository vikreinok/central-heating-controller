signed int16 numbri_muutmine_int16_main (signed int16 number, signed int16 min,
                                 signed int16 max,int8 mitu_arvu_peale_koma,
                                 int8 mitu_arvu_ei_n2ita)

{
//mitu_arvu_ei_n2ita   max 4
//mitu_arvu_peale_koma  max 3

int1 LCD_uuendatud;
int1 exit_flag = FALSE;
int8 loendur;
signed int16 number_ennem;

number_ennem = number;

   if(number > max) {
   number = max;
   }
   else if(number < min) {
   number = min;
   }
   
   if(mitu_arvu_ei_n2ita != 0) {
   mitu_arvu_peale_koma -= mitu_arvu_ei_n2ita;
   
      if(mitu_arvu_ei_n2ita  == 1)   {    
      number/=10;
      min/=10;
      max/=10;
      }
      else if(mitu_arvu_ei_n2ita  == 2) {
      number/=100;
      min/=100;
      max/=100;
      }
      else if(mitu_arvu_ei_n2ita  == 3) {  
      number/=1000;
      min/=1000;
      max/=1000;
      }
      else {                               
      number/=10000;
      min/=10000;
      max/=10000;
      }
      
   }


//number = -12345;
KURSOR_V2LJAS
PUHASTA_LCD                                 
main_flag_NM16 = TRUE;
LCD_uuendatud = TRUE;


   while(main_flag_NM16) {
         
         if (LCD_uuendatud)  {
         LCD_uuendatud = FALSE;
         
         
         lcd_gotoxy(1,1);
         
            if      (mitu_arvu_peale_koma == 0) {
            printf(lcd_putc,"%5.0w   ",number);
            }
            else if (mitu_arvu_peale_koma == 1) {
            printf(lcd_putc,"%4.1w   ",number);
            }
            else if (mitu_arvu_peale_koma == 2) {
            printf(lcd_putc,"%3.2w   ",number);
            }
            else {
            printf(lcd_putc,"%2.3w   ",number);
            }
            
         //printf(lcd_putc,"%s",string16);
         //kursor_uuendatud_NM16 = TRUE;
         }
         if (exit) {
         exit = FALSE;
         main_flag_NM16 = FALSE;
         exit_flag = TRUE;

         }
         if (select) {
            select = FALSE;
            exit_flag = FALSE;
            main_flag_NM16 = FALSE;
         }
         
         //printf("\n\rLoendur: %u",loendur);
         

         if(down||up) { //Dec -
         
            if(timer0_tick) {
            timer0_tick = FALSE;
               if(loendur < 255) {
                  loendur++;
               }
            
            }
            if(up) {
            up = FALSE;
            LCD_uuendatud = TRUE;
               if(number >= (min + loendur ) )  {
               number = number - loendur;
               }
               else {
               number = min;
               }
            
            }
            if(down) {
            down = FALSE;
            LCD_uuendatud = TRUE;
               if(number <= (max - loendur ) )  {
               number = number + loendur;
               }
               else {
               number = max;
               }
            }
         }
         else if(timer0_tick && loendur > 0) {
            timer0_tick = FALSE;
            loendur = loendur >> 2;
         
         }
         
         

   }

main_flag_NM16 = TRUE;

   if(exit_flag) {
   exit_flag = FALSE;
   return number_ennem;
   }
   else {
   
      if(mitu_arvu_ei_n2ita  == 1)   {    
      number*=10;
      }
      else if(mitu_arvu_ei_n2ita  == 2) {
      number*=100;
      }
      else if(mitu_arvu_ei_n2ita  == 3) {  
      number*=1000;
      }
      else {                               
      number*=10000;
      }
      
   return number;
   }
   
}







