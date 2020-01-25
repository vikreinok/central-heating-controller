

//--------------------------------
// Numbri muutmine int16 global varaibles
int1 main_flag_NM16, numbri_muutmine_return16 = FALSE, viimane_number_flag = FALSE;

int8 kursori_asukoht_NM16,viimane_number = 0,viimane_number2= 32;
char string16[8],
     string_min[8],
     string_max[8];





int8 stringi16_asetamine(int1 ymardamine, int8 mitu_arvu_peale_koma, signed int16 number,int8 arvkohtade_nr)
{
int8 a,
     viimane_arvkoht;

if(arvkohtade_nr == 6) {
sprintf(string16,"%6Ld",number);
}
else if (arvkohtade_nr == 5) {
sprintf(string16,"%5Ld",number);
}
else if (arvkohtade_nr == 4) {
sprintf(string16,"%4Ld",number);
}
else if (arvkohtade_nr == 3) {
sprintf(string16,"%3Ld",number);
}

for(a = 0; a <= 6; a++) {
   if(string16[a] == NULL) {
   viimane_arvkoht = a - 1;
   printf("\n\rViimane arvkoht1: %u",viimane_arvkoht);
   break;
   }
}

printf("\n\rString1: %s",string16);

if(ymardamine == TRUE) {
   if(mitu_arvu_peale_koma == 0) {
      if(string16[viimane_arvkoht] >= '5') {
         if(string16[viimane_arvkoht - 1] != '9') {
         string16[viimane_arvkoht - 1]++;
         }
      }
      if(string16[viimane_arvkoht - 1] >= '5') {
         if(string16[viimane_arvkoht - 2] != '9') {
         string16[viimane_arvkoht - 2]++;
         }
      }
   //number /= 100;
   string16[viimane_arvkoht] = NULL;
   string16[viimane_arvkoht - 1] = NULL;
   viimane_arvkoht -= 2;
   }
   if(mitu_arvu_peale_koma == 1) {
      if(string16[viimane_arvkoht] >= '5') {
      
      
      }
   //number /= 10;
   string16[viimane_arvkoht] = NULL;
   viimane_arvkoht--;
   }
 }
 
else {
   if(mitu_arvu_peale_koma == 0) {
   //number /= 100;
   string16[viimane_arvkoht] = NULL;
   string16[viimane_arvkoht - 1] = NULL;
   viimane_arvkoht -= 2;
   }
   if(mitu_arvu_peale_koma == 1) {
   //number /= 10;
   string16[viimane_arvkoht] = NULL;
   viimane_arvkoht--;
   }   
}
printf("\n\rViimane arvkoht2: %u",viimane_arvkoht);

printf("\n\rString2: %s",string16);

if(mitu_arvu_peale_koma == 2) {
string16[viimane_arvkoht + 1] = string16[viimane_arvkoht];
string16[viimane_arvkoht] = string16[viimane_arvkoht - 1];
string16[viimane_arvkoht - 1] = '.';
string16[viimane_arvkoht + 2] = NULL;
viimane_arvkoht ++;
}
if(mitu_arvu_peale_koma == 1) {
string16[viimane_arvkoht + 1] = string16[viimane_arvkoht];
string16[viimane_arvkoht] = '.';
string16[viimane_arvkoht + 2] = NULL;
viimane_arvkoht ++;
}
printf("\n\rViimane arvkoht3: %u",viimane_arvkoht);
printf("\n\rString3: %s",string16);


return viimane_arvkoht;



}


void nullid_ette(int1 negatiivne_number,int1 negatiivne)
{

int8  a,
      esimene_arvkoht,
      esimene_min_arvkoht,
      string16_esimene_arvkoht,
      string16_komakoht,
      min_esimene_arvkoht = 1,
      max_esimene_arvkoht = 1;



for(a = 0; a < 8; a++)  {
//printf("\n\rstring%u on: %u - %c",a,string16[a],string16[a]);
   if(string16[a] == '-') {
   string16_komakoht = a + 1;
   }
   if((string16[a] != NULL) && (string16[a] != ' ') && (string16[a] != '-')) {
   esimene_arvkoht = a + 1;
   break;
   }
}
string16_esimene_arvkoht = esimene_arvkoht;
esimene_min_arvkoht = esimene_arvkoht;

for(a = 0; a < 8; a++)  {
//printf("\n\rstring%u on: %u - %c",a,string_min[a],string_min[a]);
   if((string_min[a] != NULL)&&(string_min[a] != ' ')&&(string_min[a] != '-')) {
   esimene_arvkoht = a + 1;
   break;
   }
}
min_esimene_arvkoht = esimene_arvkoht;
if(esimene_arvkoht < esimene_min_arvkoht) {
esimene_min_arvkoht = esimene_arvkoht;
}

for(a = 0; a < 8; a++)  {
//printf("\n\rstring%u on: %u - %c",a,string_max[a],string_max[a]);
   if((string_max[a] != NULL)&&(string_max[a] != ' ')&&(string_max[a] != '-')) {
   esimene_arvkoht = a + 1;
   break;
   }
}
max_esimene_arvkoht = esimene_arvkoht;
if(esimene_arvkoht < esimene_min_arvkoht) {
esimene_min_arvkoht = esimene_arvkoht;
}

printf("\n\rS16 %u",string16_esimene_arvkoht);
printf("\n\rmax %u",max_esimene_arvkoht);
printf("\n\rmin %u",min_esimene_arvkoht);
printf("\n\remin %u",esimene_min_arvkoht);
//-------



a = 1;
if((string16_esimene_arvkoht - esimene_min_arvkoht) != 0) {
   while(string16[esimene_min_arvkoht - 1] != '0' ){
   //printf("\n\r  String on %s",string16);
   a++;
   string16[string16_esimene_arvkoht - a] = '0';
   //printf("\n\r  String on %s",string16);
   }
}
if(negatiivne_number) {
string16[string16_komakoht - a] = '-';
}

a = 1;
if((!negatiivne) && (( min_esimene_arvkoht - esimene_min_arvkoht) > 0)) {
   while(string_min[esimene_min_arvkoht - 1] != '0' ){
   a++;
   string_min[min_esimene_arvkoht - a] = '0';
   }
}
a = 1;
if((!negatiivne) && (( max_esimene_arvkoht - esimene_min_arvkoht) > 0)) {
   while(string_max[esimene_min_arvkoht - 1] != '0' ){
   a++;
   string_max[max_esimene_arvkoht - a] = '0';
   }
}



}


void dec_NM16(int8 viimane_arvkoht3,int1 negatiivne)
{  
   int1 a,
        b;

   printf("\n\rKursori asukoht: %u",kursori_asukoht_NM16);
   printf("\n\rViimane_arvkoht: %u",viimane_arvkoht3);
   printf("\n\rString16.%u:  %c %u",kursori_asukoht_NM16 - 2,string16[kursori_asukoht_NM16 -2],string16[kursori_asukoht_NM16 -2]);
   
   v6rdluste_algus_dec16:
   if(((string16[kursori_asukoht_NM16 - 2]  >= '0') && (string16[kursori_asukoht_NM16 - 2] <= '9')) || (string16[kursori_asukoht_NM16 - 2] =='-') ) {
   a = TRUE;
   }
   else if(negatiivne && (string16[kursori_asukoht_NM16 - 2] ==' ')) {
   a = TRUE;
   }
   else {
   a = FALSE;
   }
   if(string16[kursori_asukoht_NM16 - 2] == '.') {
   b = TRUE;
   }
   if((kursori_asukoht_NM16 > viimane_arvkoht3 + 2) || (kursori_asukoht_NM16 == 1)   ) {
   a = FALSE;
   b = FALSE;
   }

   

   if(a)  {
   kursori_asukoht_NM16 --;
   printf("\n\rA");
   }
   else if(b) {
   kursori_asukoht_NM16 --;
   kursori_asukoht_NM16 --;
   printf("\n\rB");
   }
   else if(kursori_asukoht_NM16 != 1) { // else if selleks, et ei teeks ringe
      printf("\n\rC");
      if(kursori_asukoht_NM16 == 13) {
      kursori_asukoht_NM16 = viimane_arvkoht3 + 1 ; // 9 on Viimase numbri asukoht
      goto v6rdluste_algus_dec16;
      }
      if(kursori_asukoht_NM16 == 15) {
      kursori_asukoht_NM16 = 13;
      }
      //if(kursori_asukoht_NM16 != 13) {
      //kursori_asukoht_NM16 = 15;
      //}
   }
}


int8 inc_NM16()
   {
   int1 a;
        


   printf("\n\rKursori asukoht: %u",kursori_asukoht_NM16);
   printf("\n\rString16.%u:  %c %u",kursori_asukoht_NM16,string16[kursori_asukoht_NM16],string16[kursori_asukoht_NM16]); 
   
   
   if((string16[kursori_asukoht_NM16]  >= '0') && (string16[kursori_asukoht_NM16] <= '9')) {
   a = TRUE;
   }
   else {
   a = FALSE;
   }
   if(kursori_asukoht_NM16 >= viimane_number2) {
   a = FALSE;
   }
   
   if(a)  { // || (string16[kursori_asukoht_NM16] == '-')
   kursori_asukoht_NM16 ++;
      while(!viimane_number_flag) {
      viimane_number  = kursori_asukoht_NM16 ;
      break;
      }   
   printf("\n\rA");
   }
   else if(string16[kursori_asukoht_NM16]== '.') {
   kursori_asukoht_NM16++;
   kursori_asukoht_NM16++;
      while(!viimane_number_flag) {
      viimane_number  = kursori_asukoht_NM16 ;
      break;
      }   
   printf("\n\rB");
   }
   else {
      viimane_number2 = viimane_number;
      viimane_number_flag = TRUE;
      printf("\n\rC");
      
      if(kursori_asukoht_NM16 == 13) {
      kursori_asukoht_NM16 = 15; 
      }
      if(kursori_asukoht_NM16 == 15)  {
      kursori_asukoht_NM16 = 15;
      }
      if(kursori_asukoht_NM16 != 15) {
      kursori_asukoht_NM16 = 13;
      }
      
   }  
   printf("\n\rString16.%u:  %c %u",kursori_asukoht_NM16,string16[kursori_asukoht_NM16],string16[kursori_asukoht_NM16]); 

//lcd_gotoxy(kursori_asukoht_NM,1);
//lcd_send_byte(0,0x00E);

return viimane_number2;
}


int8 kontrolli_j2rgmist()
{
int8 ret;
if(string_max[kursori_asukoht_NM16] !=  '.') { 
//printf("\n\rA %c",string_max[kursori_asukoht_NM16]);
   if( (string_max[kursori_asukoht_NM16] ==  NULL) || (string_max[kursori_asukoht_NM16] == ' ') ) {
   ret =  1;
   }
   else if( (string_max[kursori_asukoht_NM16]) < (string16[kursori_asukoht_NM16]) ) {
   ret =  2;
   }
   else {
   ret =  1;
   }
}
else {
//printf("\n\rB");
   if( (string_max[kursori_asukoht_NM16 + 1] ==  NULL) || (string_max[kursori_asukoht_NM16 + 1] == ' ') ) {
   ret =  1;
   }
   else if( (string_max[kursori_asukoht_NM16 + 1]) < (string16[kursori_asukoht_NM16 + 1]) ) {
   ret =  2;
   }
   else {
   ret =  1;
   }
}
return  ret;
}


int8 kontrolli_eelmist()
{
int8 ret;
if(string_min[kursori_asukoht_NM16 - 1] !=  '.') { 
printf("\n\rA %c",string_max[kursori_asukoht_NM16]);
   if( (string_min[kursori_asukoht_NM16 - 2] ==  NULL) || (string_min[kursori_asukoht_NM16 - 2] == ' ') ) {
   ret =  1;
   }
   else if( (string_min[kursori_asukoht_NM16 - 2]) < (string16[kursori_asukoht_NM16 - 2]) ) {
   ret =  2;
   }
   else {
   ret =  1;
   }
}
else {
printf("\n\rB");
   if( (string_min[kursori_asukoht_NM16  - 3] ==  NULL) || (string_min[kursori_asukoht_NM16 - 3] == ' ') ) {
   ret =  1;
   }
   else if( (string_min[kursori_asukoht_NM16 - 3]) < (string16[kursori_asukoht_NM16 - 3]) ) {
   ret =  2;
   }
   else {
   ret =  1;
   }
}
return  ret;
}



void stringi_arvu_muutmine_NM16(char arv,int1 negatiivne)
{
int1 muutus = FALSE;
int8 j2rgmine,
     eelmine;

if(kursori_asukoht_NM16 == 13) {
//main_flag_NM = FALSE;
//numbri_muutmine_return = TRUE;
//select = TRUE;
}
if(kursori_asukoht_NM16 == 15) {
//main_flag_NM = FALSE;
//select = TRUE;
}
if(kursori_asukoht_NM16 == 1) {
   if((arv == ' ') || (arv == 0)) {
   arv = '-';
   string16[kursori_asukoht_NM16-1] = arv;
   select = TRUE;
   }
   else if( arv == '-') {
   
   }
}

while(!select)  {

   vilkuv_kursor();
   
   if(!negatiivne) {
      j2rgmine = kontrolli_j2rgmist();
      //j2rgmine = 2;
      printf("\n\rJ2rgmine on: %u",j2rgmine);
      if(up && (arv <= (string_max[kursori_asukoht_NM16 - 1] -  j2rgmine )))  {
      up = FALSE;
      arv++;
      muutus = TRUE;
      }
      eelmine = kontrolli_eelmist();
      printf("\n\rEelmine on: %u",eelmine);
      //eelmine = 1;
      if(down && (arv >= (string_min[kursori_asukoht_NM16 - 1] - eelmine )))  {
      down = FALSE;
      arv--;
      muutus = TRUE;
      }
   }
   if(muutus) {
   muutus = FALSE;
   lcd_gotoxy(kursori_asukoht_NM16,1);
   //lcd_send_byte(0,arv);
   lcd_putc(arv);
   lcd_gotoxy(kursori_asukoht_NM16,1);
   lcd_send_byte(0,0x00E);
   }
  

}
select = FALSE;
string16[kursori_asukoht_NM16-1] = arv;


printf("\n\rArv on: %c",arv);


}






int16 numbri_muutmine_int16_main2(signed int16 number, signed int16 min,
                                 signed int16 max,int8 mitu_arvu_peale_koma,
                                 int1 ymardamine)
{
int1  string_uuendatud, 
      kursor_uuendatud_NM16,
      negatiivne,
      negatiivne_number;
int8  viimane_arvkoht,
      viimane_arvkoht_inc_dec,
      arvkohtade_nr;


number =  14334;




if(number > max) {
number = max;
}
if(number < min) {
number = min;
}

if((number < 0)) {
negatiivne_number = TRUE;
}
else {
negatiivne_number = FALSE;
}

if((number < 0) || (min < 0) || (max< 0)) {
negatiivne = TRUE;
}
else {
negatiivne = FALSE;
}

if(negatiivne) {
printf("\n\rA");
   if((number > -10000) && (min > -10000) && (max > -10000)) {
   arvkohtade_nr = 5;
   }
   else if((number > -1000) && (min > -1000) && (max > -1000)) {
   arvkohtade_nr = 4;
   }
   else if((number > -100) && (min > -100) && (max > -100)) {
   arvkohtade_nr = 3;
   }
   else {
   arvkohtade_nr = 6;
   }
}
else {
printf("\n\rB");
   if((number < 10000) && (min < 10000) && (max < 10000)) {
   arvkohtade_nr = 4;
   }
   else if((number < 1000) && (min < 1000) && (max < 1000)) {
   arvkohtade_nr = 3;
   }
   else {
   arvkohtade_nr = 5;
   }
   if(negatiivne) {
   arvkohtade_nr++;
   }
}
printf("\n\rArvkohtade_nr on: %u",arvkohtade_nr);
stringi16_asetamine(ymardamine, mitu_arvu_peale_koma, max, arvkohtade_nr);
string_max[0] = string16[0];
string_max[1] = string16[1];
string_max[2] = string16[2];
string_max[3] = string16[3];
string_max[4] = string16[4];
string_max[5] = string16[5];
string_max[6] = string16[6];


stringi16_asetamine(ymardamine, mitu_arvu_peale_koma, min, arvkohtade_nr);
string_min[0] = string16[0];
string_min[1] = string16[1];
string_min[2] = string16[2];
string_min[3] = string16[3];
string_min[4] = string16[4];
string_min[5] = string16[5];
string_min[6] = string16[6];


viimane_arvkoht = stringi16_asetamine(ymardamine, mitu_arvu_peale_koma, number, arvkohtade_nr);

printf("\n\rString max on enne funkti %s",string_max);
printf("\n\rString min on enne funkti %s",string_min);
printf("\n\rString num on enne funkti %s",string16);
printf("\n\rString num on enne funkti VIIMANE ARVKOHT %u",viimane_arvkoht);

//----------------------------------

nullid_ette(negatiivne_number,negatiivne);

printf("\n\rL6pp String on %s",string16);
printf("\n\rL6pp String on %s",string_min);
printf("\n\rL6pp String on %s",string_max);


//----------------------------------

//printf("\n\rString on %s",string);
lcd_send_byte(0,0x01); // PUHASTAB LCD
lcd_gotoxy(1,1);
lcd_send_byte(0,0x00E); // TEKITAB KURSORI
//printf(lcd_putc,"%s",string);
lcd_gotoxy(13,1);
lcd_putc('Y');
lcd_gotoxy(15,1);
lcd_putc('N');

if(kursori_asukoht_NM16 != 1) {
kursori_asukoht_NM16 = 1;
}
if(negatiivne) {
kursori_asukoht_NM16 = 2;
}
printf("\n\rString on enne funkti %s",string16);



string_uuendatud = TRUE;
kursor_uuendatud_NM16 = TRUE;
main_flag_NM16 = TRUE;

while(main_flag_NM16) {
         
         if (string_uuendatud)  {
         string_uuendatud = FALSE;
         
         lcd_gotoxy(1,1);
         printf(lcd_putc,"%s",string16);
         kursor_uuendatud_NM16 = TRUE;
         }
         if (kursor_uuendatud_NM16) {
         kursor_uuendatud_NM16 = FALSE;
         
         lcd_gotoxy(kursori_asukoht_NM16,1);
         lcd_send_byte(0,0x00E);
         }
         
         if (select) {
            select = FALSE;
            stringi_arvu_muutmine_NM16(string16[kursori_asukoht_NM16 - 1],negatiivne);
            
            string_uuendatud = TRUE;
         }
         
         //printf("\n\rKursori asukoht: %u",kursori_asukoht_NM16);
         
         if(down) { //Dec -
            down = FALSE;
            kursor_uuendatud_NM16 = TRUE;
            dec_NM16(viimane_arvkoht_inc_dec,negatiivne);
            
         }
         if(up) { //Inc +
            up = FALSE;
            kursor_uuendatud_NM16 = TRUE;
            viimane_arvkoht_inc_dec= inc_NM16();
            
         }
         
         
}
if(numbri_muutmine_return16) {
numbri_muutmine_return = FALSE;
printf("\n\rReturn: %3.2Lw",atol(string16));
return atol(string16);

}


}
