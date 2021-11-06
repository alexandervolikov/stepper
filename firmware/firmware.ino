#include <Stepper.h> 
#include <EEPROM.h>

#define STEPS 800 //steps per cicle
#define dirPin 2
#define stepPin 3
#define enPin 4

Stepper stepper(STEPS, 2, 3);
#define motorInterfaceType 1

const uint8_t timeOut = 10;
const uint8_t packetSize = 16;

uint8_t SerialBuffer[packetSize];

void setup() {

  Serial.begin(9600);
  Serial.setTimeout(timeOut);
  
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  delay(1000);
  digitalWrite(enPin, HIGH);
  delay(3000);
  
  if (Serial.available() > 0) {
    serial_read();
    motor();
  }
  else{
    for (uint8_t i=0; i<packetSize; i++){
      SerialBuffer[i] = eeprom_read(i);
    }
    if (SerialBuffer[0] != 255){
      motor();
    }
  }

}
void loop() {
  
}

void serial_read(){
  clearSerialBuffer();
  Serial.readBytes(SerialBuffer, packetSize);
  for (uint8_t i=0; i<packetSize; i++){
    eeprom_write(i, SerialBuffer[i]);
  }
}

void eeprom_write (uint16_t adr, uint8_t val) {
  for (uint8_t i = 0; i < 3; i++) {
    EEPROM.write(adr*3 + i, val);
    delay(5);
  }
}

uint8_t eeprom_read(uint16_t adr) {
  if (EEPROM.read(adr*3) == EEPROM.read(adr*3 + 1) ||
      EEPROM.read(adr*3) == EEPROM.read(adr*3 + 2)) {
    return EEPROM.read(adr*3);
  }
  else if (EEPROM.read(adr*3 + 1) == EEPROM.read(adr*3 + 2)) {
    return EEPROM.read(adr*3 + 1);
  }
  else {
    return 0;
  }

}

void motor(){

  uint32_t speed_ = SerialBuffer[0] << 24 | SerialBuffer[1] << 16 |SerialBuffer[2] << 8 |SerialBuffer[3];
  uint32_t step_ = SerialBuffer[4] << 24 | SerialBuffer[5] << 16 |SerialBuffer[6] << 8 |SerialBuffer[7];
  uint32_t number_of_steps = SerialBuffer[8] << 24 | SerialBuffer[9] << 16 |SerialBuffer[10] << 8 |SerialBuffer[11];
  uint32_t time_of_delay = SerialBuffer[12] << 24 | SerialBuffer[13] << 16 |SerialBuffer[14] << 8 |SerialBuffer[15];
  
  for (byte i=0; i<number_of_steps; i++){
    
    digitalWrite(enPin, LOW);
    delay(1);
    stepper.setSpeed(speed_);
    stepper.step(step_);
    digitalWrite(enPin, HIGH);
    delay(time_of_delay);

  }
}

void clearSerialBuffer() {
  for(uint8_t k = 0; k < packetSize; k++) {
    SerialBuffer[k] = 0;
  }
}  
