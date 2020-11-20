#include "ESP8266WiFi.h"

String _ssid;
String _pass;


void setup() 
{
    Serial.begin(9600);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(2000);
    Serial.println("Setup done");
}

void loop() 
{
    wifiNetworkSelection();
    connectToWiFi();

}

/**
 * If not conected, conects to wifi.
 * Global variables are used as credentials.
 */
void connectToWiFi(void) 
{
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Connecting to WiFi");
        
        WiFi.begin(_ssid, _pass); //Comencem una conexió WiFi
        int contador = 0;
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.println("Connecting ...");
            contador ++;
            
            if (contador == 10) //Sortim si no conecta 
                break;
        }
        Serial.println(WiFi.localIP());
    }
}


/**
 * Asks users for network SSID and password to connect to network.
 * User is asked by console (EOL char must be removed).
 * Stores data on global variables.
 */
void wifiNetworkSelection(void)
{
    if (WiFi.status() !=WL_CONNECTED) {
        Serial.println("Select network to connect");

        //GET SSID
        Serial.println("SSID? >");
        while (!Serial.available());
        String ssid = Serial.readString();
        ssid[ssid.length() - 1] = '\0'; //REMOVE ENDLINE CHAR
        _ssid = ssid;
        Serial.print("SSID > ");
        Serial.println(_ssid);
        delay(1000);
        
        //GET PASSWORD
        Serial.print("Password? > ");
        while (!Serial.available());
        String pass = Serial.readString();
        pass[pass.length() - 1] = '\0'; //REMOVE ENDLINE CHAR
        _pass = pass;
        Serial.print("PWD > ");
        Serial.println(_pass);
        delay(1000);
    }
}
