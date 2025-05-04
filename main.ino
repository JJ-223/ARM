#include <Servo.h>

Servo servo[4];
int default_angle[4] = {75, 90, 90, 60};

float z_angle;
float z_length;

float y_angle;
float y_length;

void setup()
{
    Serial.begin(115200);
    servo[0].attach(7);
    servo[1].attach(6);
    servo[2].attach(5);
    servo[3].attach(2);

    servo_T.attach(4);//grabber twister
    servo_W.attach(3);//grabber up down

    for (size_t i = 0; i < 4; i++)
    {
        servo[i].write(default_angle[i]);
    }
    servo_T.write(45);
    servo_W.write(90);
}

byte angle[4];
byte pre_angle[4];
long t = millis();

void loop()
{

    servo_W.write(45);
    
    if (Serial.available())
    {
        Serial.readBytes(angle, 4);
        for (size_t i = 0; i < 4; i++)
        {
            if (angle[i] != pre_angle[i])
            {
                servo[i].write(angle[i]);
                pre_angle[i] = angle[i];
            }
        }
        t = millis();
    }

    if (millis() - t > 1000)
    {
        for (size_t i = 0; i < 4; i++)
        {
            servo[i].write(default_angle[i]);
            pre_angle[i] = default_angle[i];
        }

        servo_T.write(45);
        servo_W.write(90);
    }
}
