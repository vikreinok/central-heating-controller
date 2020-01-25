

void modulaator_T_t1 () 
{

//printf("\n\rPID_sum on %Ld",PID_sum);

   if(PID_sum > 0) {                                                            
   Pos_Neg = TRUE;  
   }
   else{                      
   Pos_Neg = FALSE;
   }
                                                                
PID_sum = labs(PID_sum); //apsoluutv22rtus muutujast PID sum

if (PID_sum < MIN_PID_sum)  {
PID_sum = MIN_PID_sum;    
}
   
//printf("\n\rPID_sum on %Ld %u",PID_sum,Pos_Neg);

if((PID_sum > t2iteteguri_piirv22rtus)) {
//Periood const.
periood = MIN_PERIOOD;     

impulls = ((unsigned int32)PID_sum * MIN_PERIOOD)/10000;
}
else {                                                                              
//Impulls const.
impulls = MIN_IMPULLS;

periood = (unsigned int32)(MIN_IMPULLS * 10000)/PID_sum;
}
   
//printf("\n\r%Ld     %Lu      %Lu      %u",a,periood,impulls,Pos_Neg);

                           
if((periood % 100) >= 50){
periood+=100;
}
if((impulls % 100) >= 50){
impulls+=100;
}

periood/=100;
impulls/=100;

}


//#define K_P     0.10
//#define K_I     1.10
//#define K_D     0.00 
                            


struct PID_DATA pidData;  


void Init_PID(void)
{
  pid_Init(K_P * SCALING_FACTOR, K_I * SCALING_FACTOR , K_D * SCALING_FACTOR , &pidData);
}


                   
                        
#int_Timer0 
void PID_main(void)
{       
  //int16_t referenceValue, measurementValue, inputValue;
  set_timer0(28036); // 10hz @ 24 Mhz                             
  tick_100ms = TRUE;
  tick_100ms_v2 = TRUE;
  lugeja++;                  
  //signed int16 error;  
                   
   
                           
                                  
      //referenceValue = 0;      
      //measurementValue = 1023;  
                              
                               
      //inputValue = pid_Controller(referenceValue, measurementValue, &pidData);
      
      PID_sum = pid_Controller(arvutatud_kyttevee_temp, reaalne_kyttevee_temp, &pidData);
      
      printf("\n\r%Lu    %Ld    %Ld",lugeja,PID_sum,(arvutatud_kyttevee_temp - reaalne_kyttevee_temp) );
                       
                              
                                 
}                 


