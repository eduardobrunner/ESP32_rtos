#include "modulo1.h"
#include "modulo2.h"

void setup()
{
    Serial.begin(115200);

    modulo1_launch();
    modulo2_launch();
}

void loop()
{
    // data_t msgToModulo;

    // strcpy(msgToModulo.msg, "CO2 [ppm] :");
    // msgToModulo.valor = 555;

    // Serial.println("Enviando msg to Modulo 1");
    // modulo1_send(&msgToModulo);

    // delay(100);
    
    //delay(10000);
    //modulo1_kill();
    //delay(10000);
    //modulo1_launch();
}
