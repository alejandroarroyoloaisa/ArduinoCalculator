#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27,16,2);  //

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'.','0','+','='}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char key;
char number1;
char number2;

int cursor = 0;
int menuOptions=5;
void menuNavigation(int upDown){

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
  //1.- Addition
  //2.- Subtraction
  //3.- Multiplication
  //4.- Division
  String menu [menuOptions] = { {"SELECT THE OPTION DESIRED:"},
                                {"1.- Add"}, 
                                {"2.- Sub"}, 
                                {"3.- Mult"}, 
                                {"4.- Div"}
                              };                    
  
  String string_displayed = "";
  int aux = 0;
  for(int i = cursor; i < (cursor+2) ; i++){
      if( i == 5){
        lcd.setCursor(0, aux);
        lcd.print("");       
        break;
      }
      lcd.setCursor(0, aux);
      if( cursor != 0 && i == cursor){
        string_displayed += "->";
      }
      string_displayed += menu[i];
      lcd.print(string_displayed);
      string_displayed = "";  
      aux++;
  }

}

void setup(){
   Serial.begin(9600);

     // Inicializar el LCD
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();
}
  
bool inTheMenu = true;
void loop(){

  key = keypad.getKey();
  if( inTheMenu ){
    if(key == 'A'){
      menuNavigation(-1);   
    }else if(key == 'B'){
      menuNavigation(1);
    }else if(key == 'C'){
      lcd.clear();
      inTheMenu = false;
    }else{
      menuNavigation(0);
    }
  }
  

}