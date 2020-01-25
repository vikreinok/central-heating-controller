///only the 18F4550 development kit has this pin
//#if __USB_PIC_PERIF__ && defined(__PCH__)
// #define USB_CON_SENSE_PIN PIN_B2 
//#endif

//#define USB_OPT_FOR_ROM 1 
//#include <usb_cdc.h>     

void USB_main()
{ 
   usb_cdc_init();   // Start cdc
   usb_init();      // Start USB
   
   for(;;)          //Forever
   {       
      usb_task();     // Test usb         
     
      if (usb_enumerated())                          
      {     
            printf(usb_cdc_putc,"Testib yhendust USB->Serial\n\r");
            //delay_ms (100);  
      }
   }
}
