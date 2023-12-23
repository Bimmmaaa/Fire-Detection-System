#include <ThingerESP8266.h>
#include <ESP8266WIFI.h>

#define USERNAME "*****"
#define DEVICE_ID "*****"
#define DEVICE_CREDENTIAL "*****"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

const char* ssid = "*****";
const char* password = "*****";

String kondisi = "";

#define FLAME_PIN 5
#define BUZZER_PIN 2
#define LED_PIN 4

unsigned long previousMillis = 0;
const long interval = 3000;

void setup() {
  Serial.begin(9600);
  pinMode(FLAME_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    digitalWrite(LED_PIN, LOW);
  }
  digitalWrite(LED_PIN, HIGH);
  thing.add_wifi(ssid, password);

  thing["Dataku"] >> [](pson & out)
  {
    out["kondisi"] = kondisi;
  };
}

void loop() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    int api = digitalRead(FLAME_PIN);
    if(api == 0)
    {
      digitalWrite(BUZZER_PIN, HIGH);
      kondisi = "Ada Api";
      thing.call_endpoint("FireDetectionSystem");
    }
    else
    {digitalWrite(BUZZER_PIN, LOW);
    kondisi = "Aman";
    }
    thing.handle();
    Serial.println(api);
  }

}
