#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <math.h>


LiquidCrystal_I2C lcd(0x27,16,2);           //Create the LCD object with the given address and 16 columns x 2 rows

const byte ROWS = 4;                        //four rows of the keyboard
const byte COLS = 4;                        //four columns of the keyboard
char keys[ROWS][COLS] = {                   //Matrix with the keyboard elements (you can change them from here)
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'.','0','=','D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2};          //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6};          //connect to the column pinouts of the keypad

//It creates a keypad with the keymap given
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );





void setup(){
    Serial.begin(9600);

     // Initialize the LCD
    lcd.init();
  
    //Light the back of the LCD
    lcd.backlight();   
}




//FUNCTION TO NAVIGATE THROUGH THE MENU AND SHOW THE OPTIONS IN THE DISPLAY
int cursor = 0;                             //Cursor points to the actual option in the menu
int menuOptions=13;                          //Total amount of options in the menu
void menuNavigation(int upDown){

  //UPDATE THE CURSOR: up or down without crossing the limits
  if( upDown == 1){
    if(cursor < (menuOptions-1)){
      lcd.clear();  
      cursor++;  
    }      
  }else if( upDown == -1){
    if(cursor > 1){
      lcd.clear();  
      cursor--;
    }
  }
  //SELECT THE OPTION DESIRED
  String menu [menuOptions] = { {"SELECT OPTION:"},
                                {"1.- Add"}, 
                                {"2.- Subtract"}, 
                                {"3.- Multiply"}, 
                                {"4.- Divide"},
                                {"5.- Power"},
                                {"6.- Logarithm"},
                                {"7.- SquareRoot"},
                                {"8.- Sine"},
                                {"9.- Cosine"},
                                {"10.- Tangent"},
                                {"11.- 1 Grad Eq"},
                                {"12.- 2 Grad Eq"}
                              };                    
  
  //String that will be displayed. To concatenate an arrow '->' with the actual option
  String string_displayed = "";
  int aux = 0;
  for(int i = cursor; i < (cursor+2) ; i++){
      //If it is the last option, clear part of the screen (to not show garbage)
      if( i == menuOptions ){
        lcd.setCursor(0, aux);
        lcd.print("");       
        break;
      }
      //Draw an arrow in the beginning of the actual option (cursor), show the option and clear the string
      lcd.setCursor(0, aux);
      if( cursor != 0 && i == cursor ){
        string_displayed += "->";
      }
      string_displayed += menu[i];
      lcd.print(string_displayed);
      string_displayed = "";  
      aux++;
  }

}
  


  
//FUNCTION THAT INCLUDES THE OPERATOR IN THE STRING GIVEN. RETURNS THE STRING
String includeOperator(int chosenOption, String stringIntroduced){
  
  //CHECKS THE OPTION CHOSEN AND INCLUDES THE SYMBOL  
  if(chosenOption == 1){
          
    stringIntroduced+="+";
          
  }else if(chosenOption == 2){
          
    stringIntroduced+="-";
          
  }else if(chosenOption == 3){
          
    stringIntroduced+="*";
          
  }else if(chosenOption == 4){

    stringIntroduced+="/";
          
  }else if(chosenOption == 5){

    stringIntroduced+="pow(";
          
  }else if(chosenOption == 6){

    stringIntroduced+="log(";
          
  }else if(chosenOption == 7){

    stringIntroduced+="sqrt(";
          
  }else if(chosenOption == 8){

    stringIntroduced+="sin(";
          
  }else if(chosenOption == 9){

    stringIntroduced+="cos(";
          
  }else if(chosenOption == 10){

    stringIntroduced+="tan(";
          
  }

  return stringIntroduced;
}


//FUNCTION THAT IS CALLED TO COMPOSE THE EQUATION
String a = "";                //Storage A of the equation
String b = "";                //Storage B of the equation
String c = "";                //Storage C of the equation
int introducedLetter = 0;     //Index that indicates which letter is being introduced
void introduceEquation(char key){
  //THE 'x' given in the 'key' is to only show the equation info without concatenate something
  
  //If it is first grade equation  
  if( cursor == 11 ){
    lcd.setCursor(0, 0);
    lcd.print("Bx + C");
    if( introducedLetter == 0){
      if ( key != 'x'){
          b += key;
      }
      lcd.setCursor(0, 1);
      lcd.print("B=" + b);        
    }else if(introducedLetter == 1){
      if ( key != 'x'){
          c += key;
      }    
      lcd.setCursor(0, 1);
      lcd.print("C=" + c);      
    }
  }
  //If it is second grade equation
  else if( cursor == 12 ){
    lcd.setCursor(0, 0);
    lcd.print("Ax^2 + Bx + C");
    if( introducedLetter == 0){
      if ( key != 'x'){
          a += key;
      }
      lcd.setCursor(0, 1);
      lcd.print("A=" + a);        
    }else if(introducedLetter == 1){
      if ( key != 'x'){
          b += key;
      }    
      lcd.setCursor(0, 1);
      lcd.print("B=" + b);      
    }else{
      if ( key != 'x'){
          c += key;
      }    
      lcd.setCursor(0, 1);
      lcd.print("C=" + c);      
    }
  }
}


//RESOLVES THE ACTUAL STORAGED EQUATION.
void resolveEquation(){
  if( cursor == 11){            //IF FIRST GRADE EQUATION WAS SELECTED -> resolve and show results
    String resultado;
    float aux = (-c.toDouble())/(b.toDouble());
    resultado = String(aux);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(b + "x + " + c );
    lcd.setCursor(0, 1);
    lcd.print("   x=" + resultado);          
  }else{                      //IF SECOND GRADE EQUATION WAS SELECTED -> resolve and show results
    float aux = (-b.toDouble() + sqrt(b.toDouble()*b.toDouble() - 4 * a.toDouble() * c.toDouble()))/(2*a.toDouble());
    float aux2 = (-b.toDouble() - sqrt(b.toDouble()*b.toDouble() - 4 * a.toDouble() * c.toDouble()))/(2*a.toDouble());
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(a + "x^2 + " + b + "x + " + c );
    lcd.setCursor(0, 1);
    lcd.print("x=" + String(aux) + "; x=" + String(aux2) ); 
  }
}

//FUNCTION THAT CHANGE THE POWERs, LOGARITHMs AND SQRTs TO THEIR RESULT IN THE STRING
String deleteHardOperations(String stringIntroduced){
  
  String alteredString = "";     //Returned string. It will have only basic operations at the return

  //Traverse the array looking for pow(), log() or sqrt()  ::: s - sqrt(number)  || p - power(number)  || l - log(number)
  for( int i = 0 ; i < stringIntroduced.length() ; i++ ){
    
    //How does it work FOR ALL THE IFs:
    //Keep copying the number or numbers involved in the operation till reaching ')'
    //Then calculate the operation with those number and concatenate it on the 'alteredString'
    //Update 'i' with the end of the operation to continue reading the string   
    if(stringIntroduced[i] == 's' && stringIntroduced[i+1] == 'q'){           //SQRT
      int index = i;
      String number = "";      
      while( stringIntroduced[index] != ')' ){
        if( ( stringIntroduced[index] >= '0' && stringIntroduced[index] <= '9') || stringIntroduced[index] == '.' ){
          number += stringIntroduced[index];
        }
        index++;        
      }
      number =  String( sqrt(number.toDouble() ) );
      alteredString += number;
      i = index;            
    }
    else if(stringIntroduced[i] == 'p'){      //POWER
      int index = i;
      String base = "";
      String exp = ""; 
      bool baseCopied = false;
      while( stringIntroduced[index] != ')' ){
        if( ( stringIntroduced[index] >= '0' && stringIntroduced[index] <= '9') || stringIntroduced[index] == '.' ){
          
          //If the base has been copied, then copy the exponent
          if( !baseCopied ){
            base += stringIntroduced[index];
          }else{
            exp += stringIntroduced[index];
          }
          
        } else if (stringIntroduced[index] == ','){
          //Activate the flag to start copying the exponent
          baseCopied = true;          
        }
        index++;        
      }       
      String number =  String( pow(base.toDouble(), exp.toDouble() ) );
      alteredString += number;
      i = index; 
    }
    else if(stringIntroduced[i] == 'l'){      //LOGARITHM
      int index = i;
      String number = "";      
      while( stringIntroduced[index] != ')' ){
        if( ( stringIntroduced[index] >= '0' && stringIntroduced[index] <= '9') || stringIntroduced[index] == '.' ){
          number += stringIntroduced[index];
        }
        index++;        
      }
      number = String( log10(number.toDouble() ) );
      alteredString += number;
      i = index;  
    }
    else if(stringIntroduced[i] == 's' && stringIntroduced[i+1] == 'i'){      //SINUS
      int index = i;
      String number = "";      
      while( stringIntroduced[index] != ')' ){
        if( ( stringIntroduced[index] >= '0' && stringIntroduced[index] <= '9') || stringIntroduced[index] == '.' ){
          number += stringIntroduced[index];
        }
        index++;        
      }
      number = String( sin(number.toDouble() ) );
      alteredString += number;
      i = index;  
    }
    else if(stringIntroduced[i] == 'c'){      //COSINUS
      int index = i;
      String number = "";      
      while( stringIntroduced[index] != ')' ){
        if( ( stringIntroduced[index] >= '0' && stringIntroduced[index] <= '9') || stringIntroduced[index] == '.' ){
          number += stringIntroduced[index];
        }
        index++;        
      }
      number = String( cos(number.toDouble() ) );
      alteredString += number;
      i = index;  
    }
    else if(stringIntroduced[i] == 't'){      //TANGENT
      int index = i;
      String number = "";      
      while( stringIntroduced[index] != ')' ){
        if( ( stringIntroduced[index] >= '0' && stringIntroduced[index] <= '9') || stringIntroduced[index] == '.' ){
          number += stringIntroduced[index];
        }
        index++;        
      }
      number = String( tan(number.toDouble() ) );
      alteredString += number;
      i = index;  
    } else {
      alteredString += stringIntroduced[i];     //If it isn't any of the hard operations, keep copying
    }
  }
  return alteredString;
}


//FUNCTION THAT CALCULATES ANSWER BY GIVING AN STRING. RETURNS THE ANSWER
float calculateAnswer(String stringIntroduced){
  float answer = 0;                                     //Float with the answer
  String numberAux = "";                                //Actual number recognized
  char symbolRecognized;                                //Actual symbol recognized
  bool firstNumber = true;                              //FLAG that marks if it is the first number recognized

  //Before calculate the answer, lets convert the string into basic operations only
  stringIntroduced = deleteHardOperations(stringIntroduced);
  
  //Traverse the array char by char
  for(int i = 0 ; i < stringIntroduced.length() ; i++){
    //If it is a number, concatenate it
    if(stringIntroduced[i] != '+' && stringIntroduced[i] != '-' && stringIntroduced[i] != '*' && stringIntroduced[i] != '/'){

      numberAux += stringIntroduced[i];
            
    }
    //If it is a symbol
    else{
      //If it is the first number saved, add it to the answer 
      if(firstNumber){
        answer += numberAux.toFloat();
        numberAux = "";
        firstNumber = false;
      }

      symbolRecognized = stringIntroduced[i];           //save the symbol recognized

      //Traverse the array looking for the number to apply the symbol recognized. It finishes by finding another symbol or by ending the array
      int j;
      for(j = i+1 ; j < stringIntroduced.length() ; j++){
        if(stringIntroduced[j] != '+' && stringIntroduced[j] != '-' && stringIntroduced[j] != '*' && stringIntroduced[j] != '/'){
          numberAux += stringIntroduced[j];
        }else{
          break;
        }
      }
      
      //Checks the symbol and apply the operation (the three next lines are to check the operations on monitor)
      //Serial.print(answer);
      //Serial.print(symbolRecognized);
      //Serial.print(numberAux + "\n");
      if( symbolRecognized == '+'){
        answer += numberAux.toFloat();        
      }else if( symbolRecognized == '-'){
        answer -= numberAux.toFloat();
      }else if( symbolRecognized == '*'){
        answer *= numberAux.toFloat();        
      }else if( symbolRecognized == '/'){
        answer /= numberAux.toFloat();        
      }

      //If the array isnt finished, clear the numberAux string
      if( j < stringIntroduced.length() ){
        numberAux = "";               
      }
            
      i=j-1;            //Updates the array pointer to match the new position                                   
    }
  }
  //IF 'firstNumber' FLAG IS UP BY THIS POINT: There is only one number so it is the answer
  if(firstNumber){
    answer = numberAux.toFloat();
  }
  return answer;
}




String stringDisplayed = "";                //String. Contains the actual operation to calculate
bool inTheMenu = false;                     //True = you are in the menu ; False = you are not in the menu
bool restartFlag = false;                   //Flag to clear the screen
char key;                                   //Key pressed on the keyboard
bool equationMenu = false;                  //True = you are in the equation resolver menu ; False = you are not in the equation resolver menu
void loop(){

  key = keypad.getKey();                    //Get the key from the keyboard

  //If the key pressed is a number or a decimal point
  if( ( key >= '0' && key <= '9') || key == '.'){
    //If 'restartFlag' is on (it happens after pressing '='), clear the screen and string read
    if(restartFlag){                
      restartFlag = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      stringDisplayed = "";   
    }

    //If equation resolver is selected, help introducing the numbers
    if(equationMenu){ 
      lcd.clear();
      introduceEquation(key);
    }
    //If it is not the equation resolver, but string are far too long, scroll
    else if( stringDisplayed.length() >= 16 ){
      lcd.scrollDisplayLeft();
      lcd.print(key);                         //Print the number pressed
      stringDisplayed += key;
    }
    //If it is not the equation resolver, and the string isnt too long
    else{
      lcd.print(key);                         //Print the number pressed
      stringDisplayed += key;
    }
  }

  
  //If not in the menu and press 'A' -> delete the last char
  if( key == 'A' && !inTheMenu && !equationMenu ){
    if( stringDisplayed.length() >= 16 ){
      stringDisplayed.remove(stringDisplayed.length()-1);
      lcd.clear();
      lcd.print(stringDisplayed);             //Print again the string but without the last char 
      int aux = stringDisplayed.length() - 16;
      for(int i = 0 ; i < aux ; i++){
        lcd.scrollDisplayLeft();        
      }      
    }else{
      stringDisplayed.remove(stringDisplayed.length()-1);
      lcd.clear();
      lcd.print(stringDisplayed);             //Print again the string but without the last char      
    }

  }
  //If not in the menu and press 'B' -> put a ')'
  if( key == 'B' && !inTheMenu && !equationMenu){
    stringDisplayed += ')';
    lcd.clear();
    lcd.print(stringDisplayed);
    int aux = stringDisplayed.length() - 16;
    for(int i = 0 ; i < aux ; i++){
      lcd.scrollDisplayLeft();        
    }
  }
  //If not in the menu and press 'C' -> put a ','
  if( key == 'C' && !inTheMenu && !equationMenu){                       
    stringDisplayed += ',';
    lcd.clear();
    lcd.print(stringDisplayed);
    int aux = stringDisplayed.length() - 16;
    for(int i = 0 ; i < aux ; i++){
      lcd.scrollDisplayLeft();        
    }
  }
  
  //IF in the equation resolver you push 'C', goes to the next letter of the equation. If it isnt any letter left, resolve and restart then
  if(equationMenu && key == 'C'){
    introducedLetter++;
    if( (cursor == 11 && introducedLetter > 1 ) || (cursor == 12 && introducedLetter > 2 ) ){
      resolveEquation();
      a = b = c = "";
      introducedLetter = -1;   
    }else{
      lcd.clear();  
      introduceEquation('x');   //Just to show something when selected EQUATION RESOLVER in the menu
    }      
  }
  
  //If not in the menu and press '=', calculate the answer and show it. Restart flag now ON
  if( key == '=' && !inTheMenu && !equationMenu){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(stringDisplayed);
    lcd.setCursor(0, 1);
    lcd.print('=');
    lcd.print( calculateAnswer(stringDisplayed) );
    lcd.setCursor(stringDisplayed.length(), 0);
    //restartFlag = true;
  }  


  //If the key was D and you are not yet in the menu, you have chosen the MENU so it flags true
  if( (key == 'D' && !inTheMenu)){
    lcd.clear();    
    inTheMenu = true;
  }
  //If you are in the menu you can navigate through it, choose an option or leave without choosing
  else if( inTheMenu ){
    
      if(key == 'A'){                       //UP IN THE MENU
        menuNavigation(-1);   
      }else if(key == 'B'){                 //DOWN IN THE MENU
        menuNavigation(1);
      }else if(key == 'C'){                 //CHOOSE THE OPTION IN THE MENU. Clear the display and leave the menu. The option is memorized with 'cursor'
        lcd.clear();
        
        if( cursor == 11 || cursor == 12 ){ //If equation resolver was selected, flag it and show start info
          equationMenu = true;
          a = b = c = "";
          introducedLetter = 0;                    
          lcd.clear();
          if(cursor == 12){                 //Second grade equation
            lcd.setCursor(0, 0);
            lcd.print("Ax^2 + Bx + C");
            lcd.setCursor(0, 1);
            lcd.print("A=");
          }
          if(cursor == 11){               //First grade equation
            lcd.setCursor(0, 0);
            lcd.print("Bx + C");  
            lcd.setCursor(0, 1);
            lcd.print("B="); 
          }      
          inTheMenu = false;
        }else{
          equationMenu = false;
          stringDisplayed = includeOperator(cursor, stringDisplayed);            //PUTS OPERATOR IN THE STRING
          if( stringDisplayed.length() >= 16 ){
            cursor = 0;
            lcd.print(stringDisplayed);
            int aux = stringDisplayed.length() - 16;
            for(int i = 0 ; i < aux ; i++){
              lcd.scrollDisplayLeft();        
            }
            inTheMenu = false;  
          }else{
            cursor = 0;                                                            //Clear the chosen option
            lcd.print(stringDisplayed);                                            
            inTheMenu = false;
          }  
        }
            
      }else if(key == 'D'){                 //LEAVE THE MENU WITHOUT CHOOSING ANY OPTION. Clear the display and the 'cursor', leave the menu.
        lcd.clear();
        lcd.print(stringDisplayed);
        cursor = 0;
        inTheMenu = false;
      }else{                                //You are not choosing any option yet (to show something at least)
        menuNavigation(0);
      }
  }
}


//TODOs
//1.- Rounds big numbers and dont know why