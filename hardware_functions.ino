void WiFlyStartup(){

  //wdt_enable(WDTO_8S); // start WDT to 8 secs
  Serial.println(F("WiFly begin"));
  WiFly.begin();    // startup the WiFly

  Serial.print(F("WiFly joining "));
  Serial.println(ssid);
  // Join the WiFi network
  if (WiFly.join(ssid, passphrase)) {

    Serial.print(F("joined, WiFly's IP is "));
    String IP = WiFly.ip();
    Serial.print(IP);
    if(IP.length() < 9){
      Serial.println(F(" bad IP, restarting.."));
      WiFlyStartup();
    }
    else{
      Serial.println(F(" OK.."));
    }
    //wdt_disable(); //disable WDT

  }
  else{
    Serial.print(F(".. fail, try again "));
    wiflyFailure ++;
    if(wiflyFailure > maxWiflyFailure){
      Serial.println(F("can't connect to router, try reseting...."));
      forceReset(); 
    }
    WiFlyStartup();
  } 

}

void forceReset(){
  Serial.println(F("lost connection to Cosm too long, try reseting...."));
  delay(500);
  pinMode(resetPin, OUTPUT);
}
