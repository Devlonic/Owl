void mp3setup() {
   mp3_set_serial(Serial);    
   mp3_set_volume(jsonReadtoInt(configSetup, "voiceVolume"));
   delay(10);  
}
void alert() {  
      Serial.println("Start alert!");
      alertStart = true;
      delay(10);
      mp3_play(91);
      delay(10);
      long int previousMillis =  millis();
      while(millis() - previousMillis < 4000) {
           
        if(millis() - previousMillis >= 0 && millis() - previousMillis <= 500 ) { digitalWrite(led, LOW); Serial.print(" LOW");}
        if(millis() - previousMillis >= 500 && millis() - previousMillis <= 1000 ) { digitalWrite(led, HIGH); Serial.print(" HIGH");}       
        if(millis() - previousMillis >= 1000 && millis() - previousMillis <= 1500 ) { digitalWrite(led, LOW); Serial.print(" LOW");}
        if(millis() - previousMillis >= 1500 && millis() - previousMillis <= 2000 ) { digitalWrite(led, HIGH); Serial.print(" HIGH");}       
        if(millis() - previousMillis >= 2000 && millis() - previousMillis <= 2500 ) { digitalWrite(led, LOW); Serial.print(" LOW");}
        if(millis() - previousMillis >= 2500 && millis() - previousMillis <= 3000 ) { digitalWrite(led, HIGH); Serial.print(" HIGH");}
        if(millis() - previousMillis >= 3000 && millis() - previousMillis <= 3500 ) { digitalWrite(led, LOW); Serial.print(" LOW");}
        if(millis() - previousMillis >= 3500 && millis() - previousMillis <= 4000 ) { digitalWrite(led, HIGH); Serial.print(" HIGH");}

        HTTP.handleClient();
        Serial.println(millis() - previousMillis);
      }
      digitalWrite(led, HIGH);
      alertStart = false;
      Serial.println("[ALERT] Stop alert.");
}
void doorbell() {
  Serial.println("Bell activated");
  alertStart = true;
  delay(10);
  mp3_play(92);
  delay(10);
  //send_message(1);
  long int previousMillis =  millis();
      while(millis() - previousMillis < 4000) {
           
        if(millis() - previousMillis >= 0 && millis() - previousMillis <= 500 ) { digitalWrite(led, LOW); Serial.print(" LOW");}
        if(millis() - previousMillis >= 500 && millis() - previousMillis <= 1000 ) { digitalWrite(led, HIGH); Serial.print(" HIGH");}       
        if(millis() - previousMillis >= 1000 && millis() - previousMillis <= 1500 ) { digitalWrite(led, LOW); Serial.print(" LOW");}
        if(millis() - previousMillis >= 1500 && millis() - previousMillis <= 2000 ) { digitalWrite(led, HIGH); Serial.print(" HIGH");}       
        if(millis() - previousMillis >= 2000 && millis() - previousMillis <= 2500 ) { digitalWrite(led, LOW); Serial.print(" LOW");}
        if(millis() - previousMillis >= 2500 && millis() - previousMillis <= 3000 ) { digitalWrite(led, HIGH); Serial.print(" HIGH");}
        if(millis() - previousMillis >= 3000 && millis() - previousMillis <= 3500 ) { digitalWrite(led, LOW); Serial.print(" LOW");}
        if(millis() - previousMillis >= 3500 && millis() - previousMillis <= 4000 ) { digitalWrite(led, HIGH); Serial.print(" HIGH");}
        
        HTTP.handleClient();
        Serial.println(millis() - previousMillis);
      }
      
      
      digitalWrite(led, HIGH);
      alertStart = false;
      Serial.println("[DOORBELL] Stop DOORBELL.");
}
void dutyNY(String recievedTime, String recievedDate) {
  int curtime = strTimetoIntHour(recievedTime);
  int daytonye = strDaytoIntCount(recievedDate);
  if(curtime >= 20 && !todaySaid && curtime < 24 && !todaySaid && daytonye != 0) {
      cristmasTimer(recievedDate); // if >=20:00 and not said before
      todaySaid = true;
  } else if(curtime >= 0 && curtime < 20 && todaySaid && daytonye != 0) { 
    todaySaid = false; // new day before 24:00
  }
  
  if(daytonye == 0) {
    int curSec = strTimetoIntSecond(recievedTime);
    int curMinute = strTimetoIntMinute(recievedTime);
    int curHour = strTimetoIntHour(recievedTime);
   if(daytonye == 0 && curHour >= 23 && curMinute >= 59 && curSec >= 45 && !twothreesaid[3] && twothreesaid[2] && twothreesaid[1] && twothreesaid[0]) {
      twothreesaid[3] = true;
      delay(5000);
      for(int j = 10; j > 0; j--) {
         mp3_play(j);
         blink();
         delay(800); 
      }  
      mp3_play(100); // NEW YEAR!!!
      
      delay(3000);
      mp3_play(100); // NEW YEAR!!!
      delay(3000);
      mp3_play(100); // NEW YEAR!!!
      delay(3000);
    } else if(daytonye == 0 && curHour >= 23 && curMinute >= 59 && !twothreesaid[2] && twothreesaid[1] && twothreesaid[0]) { 
      mp3_play(99); // create   До нового року залишилось менше хвилини!    
      twothreesaid[2] = true;
    } else if(daytonye == 0 && curHour >= 23 && curMinute >= 50 && !twothreesaid[1] && twothreesaid[0]) { 
      mp3_play(98); // create   До нового року залишилось менше десяти хвилин!  
      twothreesaid[1] = true;
    } else if(daytonye == 0 && curHour >= 23 && !twothreesaid[0]) { // trouble
        mp3_play(97); // create   До нового року залишилось менше години!
      twothreesaid[0] = true;
  } 
}
}
void cristmasTimer(String date) {
  int daytonye = strDaytoIntCount(date);
  if(daytonye <= 49) {
    synthNumberVoice(daytonye);
  }
  
  
}

 
