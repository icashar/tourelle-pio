#include <Arduino.h>
#include <Servo.h>

Servo lower;
Servo upper;

const uint8_t lowerPin = 11;
const uint8_t upperPin = 9;
const uint8_t lowerPotPin = A2;
const uint8_t upperPotPin = A4;

// CONSTANTES DE CALIBRAGE <-- issues des tests

const int POT_MAX = 1023;
const int POT_MIN = 0;
const uint8_t LOWER_POT_DELAY = 20; //ms pour antirebond
const uint8_t UPPER_POT_DELAY = 20; //ms pour antirebond
const uint8_t POT_DELAY = LOWER_POT_DELAY > UPPER_POT_DELAY ? LOWER_POT_DELAY : UPPER_POT_DELAY;

const int LOWER_CW = 500;
const int LOWER_CCW = 2500;
const int UPPER_CW = 500;
const int UPPER_CCW = 2500;


void setup() {
  // déclarer l'usage des broches
  pinMode(lowerPotPin, INPUT);
  pinMode(upperPotPin, INPUT);

  // initialiser les servomoteurs
  lower.attach(lowerPin);
  upper.attach(upperPin);

  // placer les servomoteurs à l'origine
  lower.writeMicroseconds(1500);
  upper.writeMicroseconds(1500);
  delay(2000);

  // pour le déboggage
  Serial.begin(9600);
  delay(1000);
  Serial.println("Initialisation terminée.");
}

void loop() {

  // lire les valeurs sur les potentiomètres
  unsigned int lowerValue = analogRead(lowerPotPin);
  delay(POT_DELAY);
  unsigned int upperValue = analogRead(upperPotPin);
  delay(POT_DELAY);

  // mapper les valeurs minimales et maximales du potentiomètre aux valeurs minimales
  // et maximales des servomoteurs
  unsigned int lowerInput = map(lowerValue, POT_MIN, POT_MAX, LOWER_CCW, LOWER_CW);
  unsigned int upperInput = map(upperValue,POT_MIN, POT_MAX, UPPER_CCW, UPPER_CW);

  // contrôler les positions des servomoteurs
  lower.writeMicroseconds(lowerInput);
  upper.writeMicroseconds(upperInput);
  // Messages pour le déboggage
  Serial.print(" Lower pot value : ");
  Serial.print(lowerValue);
  Serial.print(" | Servo signal : ");
  Serial.println(lowerInput);
  Serial.println();
  Serial.print("Upper pot value : ");
  Serial.print(upperValue);
  Serial.print(" | Servo signal : ");
  Serial.println(upperInput);

}
