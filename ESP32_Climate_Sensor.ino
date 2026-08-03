#include <Arduino.h>
#include <HomeSpan.h>
#include <DHT.h>

#define DHT_PIN  4
#define DHT_TYPE DHT22

constexpr unsigned long SENSOR_INTERVAL_MS = 3000;

DHT dht(DHT_PIN, DHT_TYPE);

struct DEV_ClimateSensor : Service::TemperatureSensor {

  SpanCharacteristic *temperature;
  SpanCharacteristic *humidity;

  unsigned long lastReadTime = 0;

  DEV_ClimateSensor()
      : Service::TemperatureSensor() {

    // Temperature service
    temperature =
        new Characteristic::CurrentTemperature(0.0);

    // Humidity service
    new Service::HumiditySensor();

    humidity =
        new Characteristic::CurrentRelativeHumidity(0.0);
  }

  void loop() override {

    if (millis() - lastReadTime < SENSOR_INTERVAL_MS) {
      return;
    }

    lastReadTime = millis();

    float newHumidity = dht.readHumidity();
    float newTemperature = dht.readTemperature();

    if (isnan(newTemperature) || isnan(newHumidity)) {
      Serial.println("Failed to read from DHT22 sensor.");
      return;
    }

    newTemperature =
        constrain(newTemperature, -40.0f, 80.0f);

    newHumidity =
        constrain(newHumidity, 0.0f, 100.0f);

    if (fabs(
            temperature->getVal<float>() -
            newTemperature
        ) >= 0.1f) {

      temperature->setVal(newTemperature);
    }

    if (fabs(
            humidity->getVal<float>() -
            newHumidity
        ) >= 0.1f) {

      humidity->setVal(newHumidity);
    }

    Serial.print("Temperature: ");
    Serial.print(newTemperature, 1);
    Serial.print(" C   ");

    Serial.print("Humidity: ");
    Serial.print(newHumidity, 1);
    Serial.println(" %");
  }
};

void setup() {

  Serial.begin(115200);
  delay(1000);

  dht.begin();

  homeSpan.begin(
      Category::Sensors,
      "ESP32 Climate Sensor"
  );

  new SpanAccessory();

  new Service::AccessoryInformation();
  new Characteristic::Identify();

  new DEV_ClimateSensor();
}

void loop() {
  homeSpan.poll();
}
