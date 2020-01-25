
void dec_NM()
{                                          

   v6rdluste_algus_dec:
   if((string[kursori_asukoht_NM - 2]  >= '0') && (string[kursori_asukoht_NM - 2] <= '9') )  {
   kursori_asukoht_NM --;  
   }
   else if(string[kursori_asukoht_NM - 2] == '.') {
   kursori_asukoht_NM --;
   kursori_asukoht_NM --;
   }
   else if(kursori_asukoht_NM != 1) { // else if selleks, et ei teeks ringe
      
      if(kursori_asukoht_NM == 13) {
      kursori_asukoht_NM = 8; // 9 on Viimase numbri asukoht
      goto v6rdluste_algus_dec;
      }
      if(kursori_asukoht_NM == 15) {
      kursori_asukoht_NM = 13;
      }
      if(kursori_asukoht_NM != 13) {
      kursori_asukoht_NM = 15;
      }
   }
}


void inc_NM()
{

   if(string[kursori_asukoht_NM]  >= '0' && string[kursori_asukoht_NM] <= '9'  )  {
   kursori_asukoht_NM ++;
   }
   else if(string[kursori_asukoht_NM] == '.' ) {
   kursori_asukoht_NM ++;
   kursori_asukoht_NM ++;
   }
   else {
      if(kursori_asukoht_NM == 15) {
      kursori_asukoht_NM = 15; 
      }
      if(kursori_asukoht_NM == 13) {
      kursori_asukoht_NM = 15;
      }
      if(kursori_asukoht_NM != 15) {
      kursori_asukoht_NM = 13;
      }
      
   }  
   

//lcd_gotoxy(kursori_asukoht_NM,1);
//lcd_send_byte(0,0x00E);


}


void stringi_asetamine()//(char string[8])
{
int8 a = 0,b = 0,c = 0,e = 0;
char string2[8];
printf("\n\rString %s",string);

//strcpy(string2,string);
string2[0] = string[0];
string2[1] = string[1];
string2[2] = string[2];
string2[3] = string[3];
string2[4] = string[4];
string2[5] = string[5];
string2[6] = string[6];
string2[7] = string[7];

for(a = 0; a < 6; a++) {

   if(string2[a] == '.') {
   b = a;
   break;
   }
}


//strcpy(string2,"0000000");
string2[0] = '0';
string2[1] = '0';
string2[2] = '0';
string2[3] = '0';
string2[4] = '0';
string2[5] = '0';
string2[6] = '0';
string2[7] = NULL;

b = 4 - b; //4 on taetud komakoha asukoht
e = 8 - b; //7 on viimane liige, et mitte yletada

for(c = 0; c < e; c++) {
string2[c + b] = string[c];
}

//strcpy(string, string2); //mmutsin 8 jan testimatta
string[0] = string2[0];
string[1] = string2[1];
string[2] = string2[2];
string[3] = string2[3];
string[4] = string2[4];
string[5] = string2[5];
string[6] = string2[6];
string[7] = NULL;
}



void stringi_arvu_muutmine(char arv)
{
int1 muutus = FALSE;


if(kursori_asukoht_NM == 13) {
main_flag_NM = FALSE;
numbri_muutmine_return = TRUE;
select = TRUE;
}
if(kursori_asukoht_NM == 15) {
main_flag_NM = FALSE;
select = TRUE;
}

while(!select)  {

   vilkuv_kursor();
  
   if(down && (arv <= '8'))  {
   down = FALSE;
   arv++;
   muutus = TRUE;
   }
   if(up && (arv >= '1'))  {
   up = FALSE;
   arv--;
   muutus = TRUE;
   }
   if(muutus) {
   muutus = FALSE;
   lcd_gotoxy(kursori_asukoht_NM,1);
   
   lcd_putc(arv);
   lcd_gotoxy(kursori_asukoht_NM , 1);
   lcd_send_byte(0,0x00E);
   }
  

}
exit = FALSE;
select = FALSE;
string[kursori_asukoht_NM-1] = arv;


   
//printf(lcd_putc,"Tere");  
//lcd_gotoxy(2,1);
//lcd_putc(' ');
//lcd_send_byte(1,0x00100000); 
//lcd_setcursor_vb(1, 1);  // Cursor is visible and blinking

                                                  
}



