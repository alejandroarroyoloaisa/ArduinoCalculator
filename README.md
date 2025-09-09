# Arduino Calculator

Es una Calculadora Básica para Arduino con pantalla LCD 16x2 y teclado matricial 4x4. Desarrollada en C++ desde Arduino IDE.

## Características

- Operaciones básicas: suma, resta, multiplicación, división.
- Funciones avanzadas: potencia, logaritmo, raíz cuadrada, seno, coseno, tangente.
- Resolución de ecuaciones de primer y segundo grado.
- Evaluación de funciones con variable `x`.
- Interfaz de usuario mediante menú navegable en el LCD.
- Entrada de datos mediante keypad 4x4.

## Hardware necesario

- Arduino UNO (u otro compatible)
- Pantalla LCD 16x2 con interfaz I2C
- Keypad matricial 4x4
- Cables de conexión

## Instalación

1. Clona este repositorio.
2. Instala las librerías necesarias en el IDE de Arduino:
   - [Keypad](https://playground.arduino.cc/code/keypad/)
   - [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
3. Conecta el hardware según la configuración de pines en el código.
4. Carga el archivo [`arduino-calculator.ino`](arduino-calculator.ino) en tu placa Arduino.

## Uso

- Ingresa números y operaciones usando el keypad.
- Navega por el menú con las teclas A (arriba), B (abajo), C (seleccionar) y D (menú/salir).
- El resultado se muestra en la pantalla LCD.

## Ejemplo de conexión

- Keypad filas: pines 5, 4, 3, 2 
- Keypad columnas: pines 9, 8, 7, 6 
- LCD I2C dirección: 0x27

---

Para más detalles revisa el código fuente en [`arduino-calculator.ino`](arduino-calculator.ino).
