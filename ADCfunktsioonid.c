int16 adc_keskmine(int8 adc_kanal)
{
int16 adc_v22rtus,
      adc_v22rtus_sum = 0,
      max,
      min;
int8  loendur;
int1  valmis; //= adc_done();

//disable_interrupts(GLOBAL);
                                    
set_adc_channel(adc_kanal);
delay_us(3);
adc_v22rtus = read_adc();
max = adc_v22rtus;                                  
min = adc_v22rtus;


for(loendur = 0; loendur < 10; loendur++) {

valmis = adc_done();
while(!valmis) {   
valmis = adc_done();
//printf("!");
}
//valmis = FALSE;

//delay_us(10); //3
adc_v22rtus = read_adc();

adc_v22rtus_sum += adc_v22rtus;
//printf("\r\nADC %Lu",adc_v22rtus_sum);
   if(adc_v22rtus >= max) {
   max = adc_v22rtus;
   //printf("\r\nMAX %Lu",max);
   }
   if(adc_v22rtus <= min) {
   min = adc_v22rtus;
   //printf("\r\nMIN %Lu",min);
   }
}
//printf("\r\nMin %Lu",min);
//printf("\r\nMax %Lu",max);
adc_v22rtus_sum -= max;
adc_v22rtus_sum -= min;
//printf("\r\nADC %Lu",adc_v22rtus_sum);
adc_v22rtus_sum = adc_v22rtus_sum >> 3 ; // jagan 8-ga ehk nihutan 3 kohta paremale.

//enable_interrupts(GLOBAL);
return adc_v22rtus_sum;

}





void yleslaadimine(int16 aeg_ms)
{
          
int8 n = 1;


aeg_ms /= 16;                                               

PUHASTA_LCD           
lcd_gotoxy(1,1);       
lcd_putc("Ecomatic: EC-12M");
lcd_gotoxy(1,2);               
lcd_putc("________________");                       

                               
//lcd_send_byte(0,0b1111);   
for(;n<17;n++) {           
   //printf("\n\rARV aeg ms on %Lu",aeg_ms);       
   lcd_gotoxy(n,2);                      
   lcd_send_byte(1,0b11111111);                 
   delay_ms(aeg_ms);                           
                                       
   }                                   
                                   
}
