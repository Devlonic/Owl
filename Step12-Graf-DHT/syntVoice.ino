void oneSynt(int number) {
      debug(number,"onesyntcalled");
      mp3_play(83);
      delay(1000);
      mp3_play(1);
      delay(1000);
      mp3_play(70);
      delay(1000);
}
void twoToFourSynt(int number) {
      debug(number,"twoToFourSyntcalled");
      mp3_play(80);
      delay(1000);
      mp3_play(number);
      delay(1000);
      mp3_play(71);
      delay(1000);
}
void fiveToNineSynt(int number) {
      debug(number,"fiveToNineSyntcalled");
      mp3_play(80);
      delay(1000);
      mp3_play(number);
      delay(1000);
      mp3_play(72);
      delay(1000);
}
void decSynt(int number, int firPart, int secPart) {
    debug(secPart,"decSyntcalled");
    if(secPart == 1) {
          mp3_play(83);
          delay(1000);
          mp3_play(firPart*10);
          delay(1000);
          mp3_play(1);
          delay(1000);
          mp3_play(70);
          delay(1000);
        } else if(secPart > 1 && secPart < 5) {
          mp3_play(80);
          delay(1000);
          mp3_play(firPart*10);
          delay(1000);
          mp3_play(secPart);
          delay(1000);
          mp3_play(71);
          delay(1000);
        } else if(secPart > 4 && secPart < 10) {
          mp3_play(80);
          delay(1000);
          mp3_play(firPart*10);
          delay(800);
          mp3_play(secPart);
          delay(1000);
          mp3_play(72);
          delay(1000);
        }
}
String synthNumberVoice(int number) {
  int firPart = -1; // -1 for checkin bitness of number
  int secPart = -1;  
  if (number < 99 && number > 9) { // checking rigtly number
    firPart = number / 10; // first part of number
    secPart = number % 10; // second part
  } else if(number > 99){
    return "Erorr!";
  }
  if(firPart == -1) { // if number is less than 10
      if(number == 1) { // if lost 1 day
        oneSynt(number);
      } else if(number > 1 && number < 5) { // if lost 2-4 days
        twoToFourSynt(number); // 2-4
      } else if(number > 4 && number < 10) { // if lost 5-9 days
        fiveToNineSynt(number); // 5-9
      } 
  } else if(firPart == 1 || (firPart > 1 && secPart == 0)) { // if lost 10-19 or 20,30,40 days
      fiveToNineSynt(number); // 10-19, 20,30,40,50...
  } else if(firPart > 1 && secPart > 0) { // if number is more than 20 and second numeral is not a zero
      decSynt(number, firPart, secPart);  // > 20, 21,22,31,32...
  } 
  return "ok!";
}
int strTimetoIntHour(String curTime) {
    String hourStr = curTime.substring(0,2);
    int curHourInt = hourStr.toInt();
    return curHourInt;
}
int strTimetoIntMinute(String curTime) {
    String minuteStr = curTime.substring(3,5); // 18:22:45 
    int curMinInt = minuteStr.toInt();
    return curMinInt;
}
int strTimetoIntSecond(String curTime) {
    String secondStr = curTime.substring(6,8);
    int curSecInt = secondStr.toInt();
    return curSecInt;
}
int strDaytoIntCount(String date) {
  String takenDate = date; // Thu Jan 19 2017 //get current date by server
  String temp = takenDate.substring(4); // get first 4 symbols contents day of week
  String temp2 = temp.substring(0, 6);
  int countDayInMonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
  String day,month;
  
  day = temp2.substring(4,6);
  month = temp2.substring(0,3);
  

  int dayInt, monthInt;
  int countDay, countMonth;
  dayInt = day.toInt();
  if(month == "Jan") {
    monthInt = 1;  
    countMonth = 12;
  } else if(month == "Feb") {
    monthInt = 2;    
    countMonth = 11;
  } else if(month == "Mar") {
    monthInt = 3;    
    countMonth = 10;
  }  else if(month == "Apr") {
    monthInt = 4;    
    countMonth = 9;
  }  else if(month == "May") {
    monthInt = 5;    
    countMonth = 8;
  }  else if(month == "Jun") {
    monthInt = 6;    
    countMonth = 7;
  }  else if(month == "Jul") {
    monthInt = 7;    
    countMonth = 6;
  }  else if(month == "Aug") {
    monthInt = 8;    
    countMonth = 5;
  }  else if(month == "Sep") {
    monthInt = 9;    
    countMonth = 4;
  }  else if(month == "Oct") {
    monthInt = 10;  
    countMonth = 3;  
  }  else if(month == "Nov") {
    monthInt = 11;
    countMonth = 2;
  }  else if(month == "Dec") {
    monthInt = 12;  
    countMonth = 1; 
  }
  int countDayToEndMonth = countDayInMonth[monthInt] - dayInt;
  if(monthInt != 12){
    countDay = countDayToEndMonth + countDayInMonth[12]; // adding remaining days of current month and remaining months 
  } else {
    countDay = countDayToEndMonth; // adding remaining days of current month and remaining months 
  }
  return countDay;
}
