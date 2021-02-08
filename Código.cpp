//Arduino - Modulo Ethernet

#include <PubSubClient.h>


#include <UIPEthernet.h>


#include <SPI.h>

//CE-39-C2-F2-BC-BC

//Define o endereço MAC que será utilizado
byte mac[] = {0xCE, 0x39, 0xC2, 0xF2, 0xBC, 0xBC};

int pin2 = 2;

bool sensor; 

//Variavel de mensagem do MQTT
bool mensagem;

//inicia o cliente Ethernet
EthernetClient client;
//Inicia o client MQTT
PubSubClient mqttClient(client);

void setup() {
    //inicia o controlador Ethernet e solicita um IP para o servidor de DHCP
    Ethernet.begin(mac);

    //inicia o monitor Serial
    Serial.begin(9600);

    //Define o IP e porta TCP do Broker MQTT
    mqttClient.setServer("54.173.148.114",1883);

    //Exibe as informações do IP do Arduino
    Serial.print("O IP do Arduino e: ");
    Serial.print(Ethernet.localIP());

    //Exibe as informações da mascara de rede
    Serial.print(" A mascara de rede do arduino e: ");
    Serial.println(Ethernet.subnetMask());

    //Exibe as informações do Gateway 
    Serial.print("O Gateway do Arduino e: ");
    Serial.println(Ethernet.gatewayIP());

    Serial.println("");

    delay(5000);

            }

void loop() {

    //Cria um nome do Client MQTT e conecta com o servidor
    mqttClient.connet("felipecaseiro");

    //sensor esta exibindo as informações do pin2
    sensor = digitalRead(pin2);

    if  (sensor == 0){
        mensagem = mqttClient.publish("rack", "Rack Fechado.");
        Serial.print("O estado do sensor e: ");
        Serial.println("Rack Fechado");
        delay(5000);
    }

    else {
        mensagem = mqttClient.publish("rack", "Rack Aberto");
        Serial.print("O estado do sensor e: ");
        Serial.println("Rack Aberto");
        delay(5000);
  
    }

  mqttClient.loop();

  delay(500);

}
