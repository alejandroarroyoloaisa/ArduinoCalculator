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
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char key;
char number1;
char number2;

void setup(){
   Serial.begin(9600);

     // Inicializar el LCD
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();
}
  
void loop(){

  key = keypad.getKey();
  if(!number1){
    number1 = key;
  }else if(!number2){
    number2 = key;
  }else if(key == 'A'){
    lcd.setCursor(0, 0);

    int x = number1 - '0';
    int y = number2 - '0';

    String cadena = "";
    cadena+=number1;
    cadena+=" + ";
    cadena+=number2;
    cadena+=" = ";
    cadena+= (x+y);
    //lcd.print(x + " + " + y + " = "+ (x+y) );
    lcd.print(cadena);

    number1 = number2 = NULL;
  }else if(key == 'B'){
    lcd.setCursor(0, 0);

    int x = number1 - '0';
    int y = number2 - '0';

    String cadena = "";
    cadena+=number1;
    cadena+=" - ";
    cadena+=number2;
    cadena+=" = ";
    cadena+= (x-y);
    //lcd.print(x + " + " + y + " = "+ (x+y) );
    lcd.print(cadena);

    number1 = number2 = NULL;
  }
  //if (key){
  //  lcd.print(key);
  //}

}