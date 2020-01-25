

void draw_menu(void) {

int a,b = 0;

PUHASTA_LCD                                             

a = menu_window_start - 1;                                               
lcd_gotoxy(1,1); 

   if(keel){ 
      while (menu_EST[a][b]){               
      lcd_putc(menu_EST[a][b]);
      b++;
      }                              
   }
   else{ 
      while (menu_ENG[a][b]){    
      lcd_putc(menu_ENG[a][b]);    
      b++;
      }    
   }
   
b = 0;      
a++;
lcd_gotoxy(1,2); 

   if(keel){                   
      while (menu_EST[a][b]){
      lcd_putc(menu_EST[a][b]);  
      b++;          
      }      
   }
   else{ 
      while (menu_ENG[a][b]){
      lcd_putc(menu_ENG[a][b]);  
      b++;          
      }

   }

} 





void draw_pointer(void) {
   if (pointer_line == menu_window_start) { // if the pointer_line is equal to the menu_window_start...
      lcd_gotoxy(16,1); // print the indicator on line 1 of the display
      lcd_putc("<");
      lcd_gotoxy(16,2);
      lcd_putc(" ");
   }
   else { // ...otherwise the indicator goes on the bottom line of the display
      lcd_gotoxy(16,1);
      lcd_putc(" ");
      lcd_gotoxy(16,2);
      lcd_putc("<");
   }
}

void modulaator_T_t1(void);
                                       
void draw_adjust(void) {
   exit = FALSE;
   //setup_wdt(WDT_OFF);
 
   
   switch (pointer_line) {
      case 1:  //t2iteteguri_piir(2800,200); //5400 100, 28000 ja 200 on v22rtused 
               //graafik_tegur_conv2int8(graafik_tegur);
               //grafik_tegur_conv2sint16(graafik_tegur_conv2int8(graafik_tegur));
               //numbri_muutmine_int16_main(sint16_muutuja,11200,29700,2);
               //graafiku_funktsioon();
               Voldid_temp_conv();
               //modulaator_T_t1(); // oli varem 3 jan
               //USB_main(); //taasta includi, st see on kommenteeritud
               //graafiku_funktsioon(1450);
               //Kellataimeri_funktsioon();
               break;           
      case 2:  keele_valik();                              
               //n2ita_arvset = FALSE;
               //control = &value2;
               break;                          
      case 3:  graafiku_valik_kasutajaliides();
               break;
      case 4:  graafiku_nihutamine_kasutajaliides();                                                                       
               break;
      case 5:  graafiku_piiramine_max_kasutajaliides();
               break;
      case 6:  graafiku_piiramine_min_kasutajaliides();
               break;                       
      case 7:  //numbri_muutmine_main(0.123); //
               break;
      case 8:  //numbri_muutmine_main(213); //
               break;
      case 9:  //numbri_muutmine_main(213); //
               break;
      case 10: Aeg();      
               break;           
      case 11: aeg_kuup2ev_main(TRUE); // A_D TRUE = aeg 
               break;
      case 12: aeg_kuup2ev_main(FALSE);
               break;       
      case 13: suuna_valik();
               //sint16_muutuja = numbri_muutmine_int16_main(sint16_muutuja,-2000,7800,2,1);
               break;
      case 14: kellaprog_nr = 1;
               kellaprogramm_main();   
               break;
      case 15: kellaprog_nr = 0;
               kellaprogramm_main();
               break;         
      case 16: alseadistuse_seadistamine();
               break;
                                                
               
      }
                  
                  
   //setup_wdt(WDT_ON); 
 
}

void inc(void) {
   int8 hi_limit = 16; // casi nr.
      if (*control < hi_limit) {
         *control = *control + 1;
         if (*control > (menu_window_start + 1)) {
            menu_window_start++;
            draw_menu();
         }
         draw_pointer();
      }
}

void dec(void) {
   int8 lo_limit = 1; // local variable, lower limit
      if (*control > lo_limit) { // check to see if whatever control points at is indeed above the lo_limit
         *control = *control - 1; // if it can be decremented, take one away from it
         if (*control < menu_window_start) { // control points to "pointer_line", and we have to check to see if
                                 // we have to move the display window now
            menu_window_start--; // so we decrement menu_window_start, and...
            draw_menu(); // ...redraw the whole menu (which has changed)
         }
         draw_pointer(); // must redraw the indicator, because we moved it
      }    
}                       


