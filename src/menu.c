


void menu_test() {
   
   
   global_M_v6i_T = TRUE;
     
                                                             
   //setup_wdt(WDT_ON);  //l6pusirge probleem.
                                                             
   //setup_timer_1                                
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);                   
   enable_interrupts(INT_TIMER1);               
   //-------------------------------------                   
                                         
                         
                             
   enable_interrupts(GLOBAL);                   
   port_b_pullups(255);      
                                
    
   draw_menu();
   draw_pointer();                      

   
   control = &pointer_line; // control n2itab pointe line -le 

    

   while (TRUE) {
                                            
      restart_wdt();      
      
     
      if (select) {        
         select = FALSE;
         printf("\n\rSELECT menu");
        
         draw_adjust();             
         draw_menu();                 
         draw_pointer();   
                            
      }
     
      if (down) {             
         down = FALSE; 
         printf("\n\rUP menu");
         dec();  
      } 
      
      if (up) {                   
         printf("\n\rDOWN menu");     
         up = FALSE;
         inc();
      }
       
        
    
      if (exit) {        
       
         
         printf("\n\rEXIT menu");
         exit = FALSE;              
                          
         syda();          // Kui menyys vajutada exit siis l2heb t66funktsiooni     
         
         draw_menu();
         draw_pointer();
      }
    
    
     
                                 
      
      LCD_taustavalgus(); // 30 sec jooksul peab korra k2ivitama
        
      seaduri_TT_arvutus(); //Seda on vaja, et sedur t66taks ka menyy ajal
   }
}
                                                             
