#include <DHT.h>

#define FIRE_SENSOR_PIN 2  // Fire sensor digital output
#define MQ_SENSOR_PIN A0   // MQ sensor analog output
#define DHT_PIN 5          // DHT11 data pin
#define BUZZER_PIN 6       // Buzzer pin
 
#define DHTTYPE DHT11
DHT dht(DHT_PIN, DHTTYPE);

int mqThreshold = 400;  // Gas sensor threshold
float tempThreshold = 30.0;  // Temperature threshold

void setup() {
    pinMode(FIRE_SENSOR_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    dht.begin();
    Serial.begin(9600);
}

void loop() {
    int fireStatus = digitalRead(FIRE_SENSOR_PIN);
    int mqValue = analogRead(MQ_SENSOR_PIN);
    float temperature = dht.readTemperature();

    Serial.print("MQ Sensor Value: ");
    Serial.print(mqValue);
    Serial.print(" | Temperature: ");
    Serial.println(temperature);

    // OR Condition (Buzzer ON if any one condition is met)
    if (fireStatus == LOW || mqValue > mqThreshold || temperature > tempThreshold) {
        digitalWrite(BUZZER_PIN, HIGH);
        Serial.println("Alert! Buzzer ON");
    } 
    else {
        digitalWrite(BUZZER_PIN, LOW);
    }

    // AND Condition (Example: Buzzer only ON if Fire AND High Gas detected)
    /*
    if (fireStatus == LOW && mqValue > mqThreshold) {
        digitalWrite(BUZZER_PIN, HIGH);
        Serial.println("Fire AND High Gas! Buzzer ON");
    } else {
        digitalWrite(BUZZER_PIN, LOW);
    }
    */

    delay(500);
}
