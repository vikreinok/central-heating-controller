
signed int16 graafiku_funktsioon(signed int16 v2lis6hk) 
{
    //graafik_tegur, // M6jutab graafiku nurka
    //graafik_null,  // Tegur mis m6jutab v2ikest temp. t6usu 0 c kraadi juures
    //graafik_y,     // Graafiku asend y skaalal 20c v2lis6hu temp juures. Norm on 20 (nagu v2lis6hk-ki)
    //graafik_max,   // Grrafiku max v22rtus. Graafiku v2ljund ei saa iialgi olla suurem kui see v22rtus.
    //kyttevesi,     //(Funktsiooni väljund)
    //v2lis6hk;      //Andmed andurilt (need tuleb natuke muundada et n2ev v2lja arusaadavamalt)
                   //See toimub funkts ADC_temp_conv
    
             
//Paned v22rtused muutujatesse.
//2 viimast arvu on arvud peale koma.
// graafik_tegur = -1600;
// graafik_null = -458; 
// graafik_y = 255;   
// graafik_max = 8550;        
// v2lis6hk = -3500;   
                                                                 
                                 
signed int16 kyttevesi;
signed int16 v2lis6hk_null;
                                                                                                    
//P6hiline valem. 
kyttevesi  = (signed int16)(((signed int32)((signed int16)(v2lis6hk - 2000)) * graafik_tegur)/1000) + (2000 + graafik_y);

      //T6usu 0C juures programmikood.
      if((v2lis6hk <= 500) && (v2lis6hk >= -500))  {
         if(v2lis6hk >= 0)  {          
         //T6usu 0C juures programmikood valem.
         v2lis6hk_null = 500 - v2lis6hk;
         }
         else {
         //T6usu 0C juures programmikood valem.
         v2lis6hk_null = v2lis6hk + 500 ;
         }
         kyttevesi += (signed int16)(  (  (  (signed int32)v2lis6hk_null *  ((signed int32)graafik_null * graafik_tegur)  )  ) / 1000000);
      }
                              
//Seaduri komponendi lisamine nagu graafik_y kunagi..  
kyttevesi += seaduri_komponent;
                                    
//Kellaprogrammi komponendi lisamine nagu graafik_y    // vb prandada.
kyttevesi += KT_graafiku_muut;  

//V2ljundi maksimaalse v22rtuse piiramine.
if (kyttevesi >= graafik_max) {
kyttevesi = graafik_max;
}
//V2ljundi minimaalse v22rtuse piiramine.
if (kyttevesi <= graafik_min) {
kyttevesi = graafik_min;
}

//N2itan tulemusi RS232 emulaatori kaudu.
//printf("\n\r%3.2Lw %3.2Lw",v2lis6hk,kyttevesi); 

return kyttevesi;

}




/*
signed int16 graafiku_funktsioon() 
{
//Deklareerin muutujad
signed int16 graafik_tegur, // M6jutab graafiku nurka
             graafik_null,  // Tegur mis m6jutab v2ikest temp. t6usu 0 c kraadi juures
             graafik_y,     // Graafiku asend y skaalal 20c v2lis6hu temp juures. Nom on 20 (nagu v2lis6hk-ki)
             graafik_max,   // Grrafiku max v22rtus. Graafiku v2ljus ei saa iialgi olla suurem kui see v22rtus.
             kyttevesi,     //(Funktsiooni väljund)
             v2lis6hk;      //Andmed andurilt (need tuleb natuke muundada et n2ev v2lja arusaadavamalt)
                            //See toimub funkts ADC_temp_conv
   
//Muud tegurid vajalkud funktsiooni koostamiseks.
signed int16 kyttevesi_ilma_null,   //kyttevee tulemus  ennem kui ta l2bib nn. t6usu 0C juures programmikoodi.
             eelmine_tulemus,       //Muutuja, et saada teada kyttevee muutus 1C kraadi v2lis6hu muutuse kohta. 
             eelmise_praeguse_vahe, //Muutuja, et saada teada kyttevee muutus 1C kraadi v2lis6hu muutuse kohta.
             vahe_null_l2hedal;     //Muutuja et saada teada vahe t6usu 0C kraadi juures.


int16       loendur, 
            loendur_nr2;
            
signed int16 v2lis6hk_null;

//Paned v22rtused muutujatesse.
//2 viimast arvu on arvud peale koma.
graafik_tegur = -1600;
graafik_null = -458;
graafik_y = 255;  
graafik_max = 8550;

//Programmikood {} vahel teostub 5 korda alustades 0-ist.
for(loendur_nr2 = 1; loendur_nr2 < 6; loendur_nr2++) {

   if(loendur_nr2 != 0) {
   
      graafik_tegur += 300;
      
   }
   v2lis6hk = -3500;
   
   printf("\n\rV2lis6hk Graafik_nr_%Lu",loendur_nr2 );
   
   //Programmikood {} vahel teostub 10 korda alustades 0-ist.
   for(loendur = 0; loendur < 55; loendur++) {
      
      v2lis6hk += 100;
      
      
      eelmine_tulemus = kyttevesi;
      //P6hiline valem. 
      kyttevesi  = (signed int16)(((signed int32)((signed int16)(v2lis6hk - 2000)) * graafik_tegur)/1000) + (2000 + graafik_y);
      //kyttevee tulemus  ennem kui ta l2bib nn. t6usu 0C juures programmikoodi.
      kyttevesi_ilma_null = kyttevesi;
      
      //T6usu 0C juures programmikood.
      if((v2lis6hk <= 500) && (v2lis6hk >= -500))  {
         if(v2lis6hk >= 0)  {          //((v2lis6hk <= 500) && (v2lis6hk >= 0))
         //T6usu 0C juures programmikood valem.
         v2lis6hk_null = 500 - v2lis6hk;
         //kyttevesi += ((signed int32)(500 - v2lis6hk) * graafik_null * graafik_tegur)/1000000;
         }
         else {
         //T6usu 0C juures programmikood valem.
         v2lis6hk_null = v2lis6hk + 500 ;
         //kyttevesi += ((signed int32)(500 + v2lis6hk) * graafik_null * graafik_tegur)/1000000;
         }
          //printf("\n\rT6us nulli juures - %Ld",
          //((signed int32)(((signed int32)v2lis6hk_null * ((signed int32)graafik_null * graafik_tegur)) / 1000000)) );
          
          
         kyttevesi += (signed int16)(  (  (  (signed int32)v2lis6hk_null *  ((signed int32)graafik_null * graafik_tegur)  )  ) / 1000000);
      }
      
      //Kood et saada teada kyttevee muutus 1C kraadi v2lis6hu muutuse kohta.
      if(v2lis6hk == 1000) {
      //Tulemus 10C kraadi juures
      eelmine_tulemus = kyttevesi;
      }
      if(v2lis6hk == 1500) {
      //Tulemus 15C kraadi juures jagatud 5 et saada muutus 1C kraadi kohta.
      eelmise_praeguse_vahe = (eelmine_tulemus - kyttevesi)/5;
      }
      
      //Programmikood, et saada teada vahe t6usu 0C kraadi juures.
      if(v2lis6hk == 0) {
      vahe_null_l2hedal = kyttevesi - kyttevesi_ilma_null;
      }
      
      //V2ljundi maksimaalse v22rtuse piiramine.
      if (kyttevesi >= graafik_max) {
      kyttevesi = graafik_max;
      }
      //N2itan tulemusi RS232 emulaatori kaudu.
      printf("\n\r%3.2Lw %3.2Lw",v2lis6hk,kyttevesi); 
   }
   //N2itan tulemusi RS232 emulaatori kaudu.
   
   printf("\n\rGraafik nr. %Lu",loendur_nr2 + 1);
   printf("\n\rKV muutus 1C kraadi V6 muutuse kohta: %3.2Lw",eelmise_praeguse_vahe);
   printf("\n\rGraafiku nurga tegur: %3.2Lw",graafik_tegur);
   printf("\n\rGraafiku t6usu tegur 0C kraadi juures: %3.2Lw",graafik_null);
   printf("\n\rGraafiku t6us 0C kraadi juures: %3.2Lw",vahe_null_l2hedal);
   printf("\n\rGraafiku asukoht Y teljel: 20.00 + %3.2Lw",graafik_y);
   
}   

//Funktsiooni v2ljund muutuja.
return kyttevesi;

}
*/


/*
signed int16 graafiku_funktsioon() 
{
signed int16 graafik_tegur, // M6jutab graafiku nurka
             graafik_null,  // Tegur mis m6jutab v2ikest temp. t6usu 0 c kraadi juures
             graafik_y,     // Graafiku asend y skaalal 20c v2lis6hu temp juures. Norm on 20 (nagu v2lis6hk-ki)
             graafik_max,   // Grrafiku max v22rtus. Graafiku v2ljund ei saa iialgi olla suurem kui see v22rtus.
             kyttevesi,     //(Funktsiooni väljund)
             v2lis6hk;      //Andmed andurilt (need tuleb natuke muundada et n2ev v2lja arusaadavamalt)
                            //See toimub funkts ADC_temp_conv
             
             
//Paned v22rtused muutujatesse.
//2 viimast arvu on arvud peale koma.
graafik_tegur = -1600;
graafik_null = -458; 
graafik_y = 255;  
graafik_max = 8550; 
v2lis6hk = -3500;

//P6hiline valem. 
kyttevesi  = (signed int16)(((signed int32)(v2lis6hk - 2000) * graafik_tegur)/1000)+ (2000 + graafik_y);

//T6usu 0C juures programmikood.
if((v2lis6hk <= 500) && (v2lis6hk >= -500))  {
   if((v2lis6hk <= 500) && (v2lis6hk >= 0))  {
   //T6usu 0C juures programmikood valem.
   kyttevesi += ((signed int32)(500 - v2lis6hk) * graafik_null * graafik_tegur)/1000000;
   }
   else {
   //Funktsioon  t6us 0 kraadi juures
   kyttevesi += ((signed int32)(500 + v2lis6hk) * graafik_null * graafik_tegur)/1000000;
   }
}

//V2ljundi maksimaalse v22rtuse piiramine.
if (kyttevesi >= graafik_max) {
kyttevesi = graafik_max;
}

//N2itan tulemusi RS232 emulaatori kaudu.
//printf("\n\r%3.2Lw %3.2Lw",v2lis6hk,kyttevesi); 

return kyttevesi;

}
*/
