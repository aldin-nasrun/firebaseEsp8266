
/**
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2020 mobizt
 *
*/

#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>


#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

//1. Change the following info

#define FIREBASE_HOST "eggcubator-d446f-default-rtdb.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "4KYOs3lhfrbQdWKqAu9P5JkMgTtn6nwUV1WqC07i"
#define WIFI_SSID "WIFI_HOME"
#define WIFI_PASSWORD "sidorejo"

//2. Define FirebaseESP8266 data object for data sending and receiving
FirebaseData fbdo;


void setup()
{

  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


  //3. Set your Firebase info

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //4. Enable auto reconnect the WiFi when connection lost
  Firebase.reconnectWiFi(true);

  

  /*

  If you want to get the data in realtime instead of using get, see the stream examples.
  If you want to work with JSON, see the FirebaseJson, jsonObject and jsonArray examples.

  If you have questions or found the bugs, feel free to open the issue here https://github.com/mobizt/Firebase-ESP8266

  */




}

void loop()
{


  //6. Try to get int data from Firebase
  //The get function returns bool for the status of operation
  //fbdo requires for receiving the data
  if(Firebase.getInt(fbdo, "/LED_Status"))
  {
    //Success
    if(fbdo.intData() == 1){
      digitalWrite(LED_BUILTIN,LOW);
      }else{
        digitalWrite(LED_BUILTIN,HIGH);
      }
    Serial.print("Get int data success, int = ");
    Serial.println(fbdo.intData());

  }else{
    //Failed?, get the error reason from fbdo

    Serial.print("Error in getInt, ");
    Serial.println(fbdo.errorReason());
  }

  /*

  In case where you want to set other data types i.e. bool, float, double and String, you can use setBool, setFloat, setDouble and setString.
  If you want to get data which you known its type at specific node, use getInt, getBool, getFloat, getDouble, getString.
  If you don't know the data type at specific node, use get and check its type.

  The following shows how to get the variant data

  */

// if(Firebase.get(fbdo, "/LED_Status"))
//  {
//    //Success
//    Serial.print("Get variant data success, type = ");
//    Serial.println(fbdo.dataType());
//
//    if(fbdo.dataType() == "int"){
//      Serial.print("data = ");
//      Serial.println(fbdo.intData());
//    }else if(fbdo.dataType() == "bool"){
//      if(fbdo.boolData())
//        Serial.println("data = true");
//      else
//        Serial.println("data = false");
//    }
//
//  }else{
//    //Failed?, get the error reason from fbdo
//
//    Serial.print("Error in get, ");
//    Serial.println(fbdo.errorReason());
//  }
}
