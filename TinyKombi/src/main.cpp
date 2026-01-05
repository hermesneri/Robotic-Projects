#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "MotorControl.h"

#define FRONT 1
#define BACK 2
#define STOP 0

#define MOTOR_RIGHT 1
#define MOTOR_LEFT 2
#define MOTOR_BOTH 3

// --- Configurações do Access Point ---
const char *ssid = "Kombi";
const char *password = "12345678";

// --- Configurações de IP Fixo ---
IPAddress local_IP(192, 168, 100, 1);
IPAddress gateway(192, 168, 100, 1);
IPAddress subnet(255, 255, 255, 0);

bool farolLigado = false;

AsyncWebServer server(80);

// --- Funções Auxiliares ---
void parar()
{
  Serial.println("Parar");
  MotorControl::controlMotorDc(MOTOR_BOTH, STOP);
}

void frente()
{
  Serial.println("Frente");
  MotorControl::controlMotorDc(MOTOR_BOTH, FRONT);
}

void tras()
{
  Serial.println("Tras");
  MotorControl::controlMotorDc(MOTOR_BOTH, BACK);
}

void esquerda() 
{ 
  Serial.println("Esquerda"); 
  MotorControl::controlMotorDc(MOTOR_LEFT, FRONT);
}

void direita() 
{ 
  Serial.println("Direita"); 
  MotorControl::controlMotorDc(MOTOR_RIGHT, FRONT);
}

void ligarFarol() { Serial.println("Ligar Farol"); }
void desligarFarol() { Serial.println("Desligar Farol"); }
void buzinar() { Serial.println("Buzinar"); }

void setup()
{
  Serial.begin(115200);
  Serial.println("Iniciando Kombi System (SPIFFS)...");

  MotorControl::setMotorPin(5, 6, 9, 10); 

  parar();
  delay(3000);
  
  // --- INICIALIZAÇÃO SPIFFS ---
  if (!SPIFFS.begin(true))
  {
    Serial.println("Erro ao montar SPIFFS");
    return;
  }

  // --- CONFIGURAÇÃO DO IP FIXO ---
  Serial.print("Configurando AP... ");
  if (!WiFi.softAPConfig(local_IP, gateway, subnet))
  {
    Serial.println("Falha ao configurar IP estático!");
  }

  // Inicia o Access Point
  WiFi.softAP(ssid, password);

  Serial.println("Pronto.");
  Serial.print("Endereço IP do AP: ");
  Serial.println(WiFi.softAPIP());

  // --- Rotas ---
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/index.html", "text/html"); });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/style.css", "text/css"); });

  server.on("/control", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    if (request->hasParam("cmd")) {
      String cmd = request->getParam("cmd")->value();
      if (cmd == "F") frente();
      else if (cmd == "B") tras();
      else if (cmd == "L") esquerda();
      else if (cmd == "R") direita();
      else if (cmd == "S") parar();
      else if (cmd == "H_ON") buzinar();
      else if (cmd == "W") {
        farolLigado = !farolLigado;
        Serial.println(farolLigado ? "Ligar Farol" : "Desligar Farol");
        farolLigado ? ligarFarol() : desligarFarol();
      }
    }
    request->send(200, "text/plain", "OK"); });

  server.begin();
  parar();
}

void loop()
{
}