

float numbri_muutmine_main(float number)
{

//number = 0.213;
sprintf(string,"%.3f",number);
//printf("\n\rString on %s",string);
PUHASTA_LCD         
lcd_gotoxy(1,1);
lcd_send_byte(0,0x00E); // TEKITAB KURSORI
//printf(lcd_putc,"%s",string);
lcd_gotoxy(13,1);
lcd_putc('Y');
lcd_gotoxy(15,1);
lcd_putc('N');

if(kursori_asukoht_NM != 1) {
kursori_asukoht_NM = 1;
}
//printf("\n\rString on enne funkti %s",string);
stringi_asetamine(); //Nihutab komakoha 4 arvu ette, 0-ide vahele

//printf("\n\rL6pptulemus String2: %s",string);


string_uuendatud = TRUE;
kursor_uuendatud_NM = TRUE;
main_flag_NM = TRUE;

while(main_flag_NM) {
         
         if (string_uuendatud)  {
         string_uuendatud = FALSE;
         
         lcd_gotoxy(1,1);
         printf(lcd_putc,"%s",string);
         kursor_uuendatud_NM = TRUE;
         }
         if (kursor_uuendatud_NM) {
         kursor_uuendatud_NM = FALSE;
         
         lcd_gotoxy(kursori_asukoht_NM,1);
         lcd_send_byte(0,0x00E);
         }
         if (exit)  {
         exit = FALSE;
                                       
         main_flag_NM = FALSE;
         //select = TRUE;
         }
         
         if (select) {
            select = FALSE;
            stringi_arvu_muutmine(string[kursori_asukoht_NM-1]);
            
            string_uuendatud = TRUE;
         }
         
         //printf("\n\rKursori asukoht: %u  %u",kursori_asukoht_NM,main_flag_NM);
         
         if(up) { //Dec -
            up = FALSE;
            kursor_uuendatud_NM = TRUE;
            dec_NM();
            
         }
         if(down) { //Inc +
            down = FALSE;
            kursor_uuendatud_NM = TRUE;
            inc_NM();                
            
         }
         
         
}
if(numbri_muutmine_return) {
numbri_muutmine_return = FALSE;
//printf("\n\rReturn: %f",atof(string));
return atof(string);

}


}
