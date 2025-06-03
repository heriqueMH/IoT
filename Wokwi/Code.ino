#include <WiFi.h>
#include <PubSubClient.h>

#define TRIG_PIN 12
#define ECHO_PIN 14
#define PIR_PIN  27

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_topic = "TESTMACK1870/estacao1/resumo";  // Envia como JSON cru

WiFiClient espClient;
PubSubClient client(espClient);

int contadorPassagens = 0;
bool movimentoAnterior = false;

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("conectado.");
    } else {
      Serial.print("falha. Código: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);

  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado");

  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Sensor ultrassônico
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duracao = pulseIn(ECHO_PIN, HIGH);
  float distancia = duracao * 0.034 / 2;

  // Sensor PIR
  int movimento = digitalRead(PIR_PIN);
  if (movimento == HIGH && !movimentoAnterior) {
    contadorPassagens++;
    movimentoAnterior = true;
  } else if (movimento == LOW) {
    movimentoAnterior = false;
  }

  // Construção do JSON como string
  String payload = "{";
  payload += "\"estacao\":\"barueri\",";
  payload += "\"distancia\":" + String(distancia, 2) + ",";
  payload += "\"passagens\":" + String(contadorPassagens) + ",";
  payload += "\"rota\":\"linha-diamante\"";
  payload += "}";

  client.publish(mqtt_topic, payload.c_str());  // ENVIA JSON como TEXTO
  Serial.println("Publicado: " + payload);

  delay(2000);
}
