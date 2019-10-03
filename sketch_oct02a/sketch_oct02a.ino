#include <ESP8266WiFi.h>

#define SSID_REDE "cvidal"
#define SENHA_REDE "cvidalsp"
#define INTERVALO_ENVIO_API 30000

char EnderecoApi[] = "192.168.43.191:3333/datas";
long lastConnectionTime;
WiFiClient client;

void FazConexaoWiFi(void);
void EnviaDadosParaApi(String StringDados);

void EnviaDadosParaApi(String StringDados){
  if (client.connect(EnderecoApi, 80)){
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: 192.168.43.191:3333/datas");
    client.print("Connection: close\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print("\n\n");
    client.print(StringDados);

    lastConnectionTime = millis();
    Serial.println("- Informações enviadas à API!");
  }  
}

void FazConexaoWiFi(void) {
  client.stop();
  Serial.println("Conectando-se à rede WiFi");
  Serial.println();
  delay(1000);
  WiFi.begin(SSID_REDE, SENHA_REDE);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");  
  }

  Serial.println("");
  Serial.println("WiFi conectado com sucesso!");
  Serial.println("IP obtido: ");
  Serial.println(WiFi.localIP());

  delay(1000);
}

void setup() {
  Serial.begin(9600);
  lastConnectionTime = 0;
  FazConexaoWiFi();
  Serial.println("Planta IoT com ESP8266 NodeMCU");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(client.connected()){
    client.stop();
    Serial.println("- Desconectado da API");
    Serial.println();  
  }

  if(!client.connected()&& (millis() - lastConnectionTime > INTERVALO_ENVIO_API)){
    Serial.println("Enviando dados para API");
    EnviaDadosParaApi("dados hahahah batata");
  }
  delay(1000);



  
}
