
//GS: code borrowed from some other tutorial--I forget where; I did, however, verify the formulas & equations and all in the datasheet, and it was good enough.
//    ~Gabriel
//------------------------------------------------------------------------------------------------------------------------------------------
//printTemp()
//------------------------------------------------------------------------------------------------------------------------------------------
void printTemp()
{
  float V = analogRead(tempPin)/1023.0*5.0;
  float degC = (V - 0.5)*100.0; //C
  float degF = degC*9.0/5.0 + 32.0; //F
  
  move_cursor_to_end(); //press ctrl + end to make sure cursor is at the very end of the document, in case the user moved the cursor duing the pause
  Keyboard.print(F("Room temp = ")); Keyboard.print(degC); Keyboard.print(F(" deg C, or ")); Keyboard.print(degF); Keyboard.println(F(" deg F."));
}
