
#int_TIMER1 
void TIMER1_isr() {
//printf("\n\rTIMER0 t66tab %u",repeat_delay_count);   
timer0_tick = TRUE;  // parandada nimi  
                      
   if ((temp & 0xf0) != 0xf0) { // a button is down
                              // temp stores the state of port b          
                              // mask off the 4 MS bits by ANDing with 0xf0
                              // if this masked value is not equal to 0xf0, then a button is down
      if (initial_delay && ++repeat_delay_count == 10) { // if initial_delay is true and repeat_delay_count is 8...
         initial_delay = FALSE; // ...turn off the initial_delay
      }
      else if (!initial_delay || do_debounce) { // if initial_delay is false OR do_debounce is true
         do_debounce = FALSE; // set do_debounce to false
         
         if (!input(PIN_B7) && initial_delay) { // if the "select" button is down AND initial_delay is true
            select = TRUE; // ... make "select" true
            printf("\n\rSELECT");
         }
         if (!input(PIN_B5)) {
            down = TRUE;
            printf("\n\rUP");
         }
         if (!input(PIN_B6)) {
            up = TRUE;                        
            printf("\n\rDOWN");        
         }
         if (!input(PIN_B4)) {
            exit = TRUE;
            printf("\n\rEXIT");  
            }
             
      }                        
   }
}
                                           
                                          
#int_RB                                      
void RB_isr() {     // Rakendub nii t6usul kui ka langusel.     
                                     
   //printf("\n\rint_RB rakendus");  
   temp = input_b();//portb; // read state of portb and store in temp
   set_timer1(0); //timer 1 will go off 87 ms from now at 24 mhz
   do_debounce = TRUE;//true          
   repeat_delay_count = 0; // this variable has to do with the initial time delay and the rapid fire that follows  
   initial_delay = TRUE; // do the "initial delay" before going into rapid fire mode //true
   
   nuppu_on_vajutatud = TRUE;                                                                                
   nuppu_vajutati = TRUE;        
   nuppu_oldi_vajutatud = TRUE;
}                                            


                                                   


#INT_EXT                                                                                                         
void ext_isr() 
{                                                                    
//int pullside_arv;
//printf("\n\rtimer3_count %Ld",timer3_count);

TT_pullside_loendur_int++; 

if(L2H_flag) { // L2H_flag == TRUE
//pullside_arv++;
L2H_flag = FALSE;
count_nul = timer3_count;  
ext_int_edge(H_TO_L);
printf("\n\rL -> H");   
}                                                          
else {                                                                    
L2H_flag = TRUE;           
count_pos = timer3_count;
ext_int_edge(L_TO_H);                              
printf("\n\rH -> L");   
}                                            

arvuta_uus_TT = TRUE;   

/*
if( ((count_nul > seadur_min) && (count_pos > seadur_min)) &&
    ((count_pos < seadur_max) && (count_nul < seadur_max))    ) {  
    
//pulsside pikkused on suuremad seadur_min v22rtusest
printf("\n\rNUL %Ld",count_nul);               
printf("\n\rPOS %Ld",count_pos);

seaduri_t2itetegur = ((float)count_pos)/(count_pos + count_nul);

printf("\n\rTT %.4f",seaduri_t2itetegur);
     
seadur_kinnitatud = TRUE;
}
else  {
printf("\n\rPulls ei ole piiride vahel");
seadur_kinnitatud = FALSE;
//count_nul = 0;
//count_pos = 0;
}              
*/

timer3_count = 0;       

}


#INT_TIMER3
void TIMER3_isr()
{
//set_timer3(0);    
timer3_count++;   //intterupt Period = 0,0873813 s T3 prescaler 1:8
t66funkts_taastamine_loendur++;
taustavalgustuse_loendur++;               


if(nuppu_on_vajutatud) {
nuppu_on_vajutatud = FALSE;
t66funkts_taastamine_loendur = 0; 
}

if(t66funkts_taastamine_loendur > 680) {
t66funkts_taastamine_loendur = 0;
exit = TRUE;
}

//printf("\n\r+1");
}

