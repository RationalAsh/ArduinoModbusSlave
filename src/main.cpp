//#define __ASSERT_USE_STDERR
#include <Arduino.h>
#include <modbusRTU.h>
//#include <assert.h>

#define DEN_PIN 14

modbusRTU mbus(Serial1);

uint16_t holding_registers[15];
int ledState = 0;
int progState = 0;
String keys;
int ctr = 0;

void setup() {
    // put your setup code here, to run once:
    //delay(5000);
    mbus.begin(115200, 2, DEN_PIN);
    Serial.begin(115200);
    Serial1.begin(115200);
    Serial1.setTimeout(0.017);
    pinMode(13, HIGH);
    //mbus.saddr = 1;
    mbus.setHoldingRegs(holding_registers, 15);
    for(int i=0; i<10; i++)
        holding_registers[i] = i;
    holding_registers[10] = 0;
}

void loop() {
    // put your main code here, to run repeatedly:
    mbus.checkMessages();

    for(int i=0; i<9; i++)
       holding_registers[i]++;
    
    digitalWrite(13, holding_registers[10] & 0xFF);
    //Serial.println(holding_registers[10], HEX);

    delay(10);
}

// handle diagnostic informations given by assertion and abort program execution:
// void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
//     // transmit diagnostic informations through serial link. 
//     Serial.println(__func);
//     Serial.println(__file);
//     Serial.println(__lineno, DEC);
//     Serial.println(__sexp);
//     Serial.flush();
//     // abort program execution.
//     abort();
// }