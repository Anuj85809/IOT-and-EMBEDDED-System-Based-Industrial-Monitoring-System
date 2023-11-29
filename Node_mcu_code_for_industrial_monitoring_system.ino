#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "ANUJ AGGARWAL";
const char* password = "INDIA1234";

ESP8266WebServer server(80);

String page = "";
double ldrValue;
double tempValue;
double gasValue;
double fireValue;

void setup(void) {
  delay(1000);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", []() {
    String fireAlert = (fireValue < 200) ? "<h4 style='color: red;'>Fire Detected Alert!!!</h4>" : "";
    String ldrAlert = (ldrValue < 100) ? "<h4 style='color: green;'>Light is Currently turned On!!!</h4>" : "";
    String tempAlert = (tempValue > 300) ? "<h4 style='color: red;'>Turning On Exhaust Fan (Issue : Temperature Raised above 300 Value)!!!</h4>" : "";
    String gasAlert = (gasValue > 170) ? "<h4 style='color: red;'>GAS Leakage Detected Alert!!! Evacuation Required Immediately </h4>" : "";
    page = "<html><head><style>body { background-color: #f0f0f0; text-align: center; } h1, h3, h4 { color: #333; } </style><script>setTimeout(function(){ location.reload(true); }, 500);</script></head><body><h1>LDR Sensor Value</h1><h3>Data:</h3><h4>" + ldrAlert + String(ldrValue) + "</h4><br><h1>Temp Sensor Value</h1><h3>Data:</h3><h4>" + tempAlert + String(tempValue) + "</h4>" + "<br><h1>Gas Sensor Value</h1><h3>Data:</h3><h4>" + gasAlert + String(gasValue) +  "</h4><br><h1>Fire Sensor Value</h1><h3>Data:</h3><h4>" + fireAlert + String(fireValue) + "</h4></body></html>";
    server.send(200, "text/html", page);
  });

  server.begin();
  Serial.println("Web server started!");
}

void loop(void) {
  delay(40);
  if (Serial.available() > 0) {
    String sensorData = Serial.readStringUntil('\n');
    Serial.println(sensorData);
    sscanf(sensorData.c_str(), "%lf,%lf,%lf,%lf", &ldrValue, &tempValue, &gasValue, &fireValue);
    Serial.print("LDR Value :");
    Serial.println(ldrValue);
    Serial.print("Temp Value :");
    Serial.println(tempValue);
    Serial.print("Gas Value :");
    Serial.println(gasValue);
    Serial.print("Fire Value :");
    Serial.println(fireValue);
    server.handleClient();
  }
}
