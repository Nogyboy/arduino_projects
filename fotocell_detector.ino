const int digitalInputPin = 4;  // Pin de entrada digital
const int analogInputPin = A0;  // Pin de entrada analógica
const int outputPin = 2;        // Pin de salida digital

int digitalInputState = 0;      // Estado de la entrada digital
int analogInputValue = 0;       // Valor de la entrada analógica
long delayTime = 0;             // Tiempo de retardo en mili segundos
unsigned long setTime = 0;    // Tiempo de inicio del temporizador
bool outputActive = false;      // Estado de la salida digital

void setup() {
  pinMode(digitalInputPin, INPUT);
  pinMode(outputPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Leer el estado de la entrada digital
  digitalInputState = digitalRead(digitalInputPin);

  // Si la entrada digital cambia a activa (por ejemplo, de bajo a alto)
  if (digitalInputState == HIGH && outputActive == false) {
    // Fotocélula detectada
    outputActive = true;
//    Reiniciar contador
    setTime = 0;
    // Leer el valor de la entrada analógica (rango de 0 a 1023)
    analogInputValue = analogRead(analogInputPin);
    
    // Mapear el valor analógico al rango de tiempo deseado (10 segundos a 5 minutos)
    delayTime = map(analogInputValue, 0, 1023, 10000, 300000)/1000;

    // Tiempo de retardo
    Serial.println("Fotocélula detectada");
    Serial.println("Tiempo de espera: ");
    Serial.print(delayTime);
    
    // Activar la salida digital
    digitalWrite(outputPin, LOW);
  }

  // Comprobar si ha transcurrido suficiente tiempo
  if (setTime >= delayTime) {
    // Desactivar la salida digital
    digitalWrite(outputPin, HIGH);
    outputActive = false;
  }

  setTime=setTime+1;
  delay(1000);
}
