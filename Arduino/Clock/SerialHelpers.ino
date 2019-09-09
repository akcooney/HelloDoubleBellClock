//parse the datetimestring and set the time with it
void parseDateTimeString(String inputString)
{
  //this was validated, although there might be some possible invalid date and day combinations that 
  setTime(
    inputString.substring(0,2).toInt(), //the hour
    inputString.substring(3,5).toInt(), //the minute
    inputString.substring(6,8).toInt(), //the second
    inputString.substring(9,11).toInt(), //the day
    inputString.substring(12,14).toInt(), //the month
    inputString.substring(15,19).toInt() //the year
    );

  //sync the time to the RTC as well
  RTC.set(now());
  
  return;
}

//validates an incoming time set string
bool validateDateTimeString(String validationString)
{
  //default to not validated
  bool result = false;

  //we'll have many nested if statements
  //once you clear all the checks then we have validated the string
  //first check the length it should be based off of this
  //HH:MM:SS DD MM YYYY - total of 19 characters
  if(validationString.length() >= 19)
  {
    //it's long enough; check all the right spots for digit characters
    if((isDigit(validationString[0]))&&
      (isDigit(validationString[1]))&&
      (isDigit(validationString[3]))&&
      (isDigit(validationString[4]))&&
      (isDigit(validationString[6]))&&
      (isDigit(validationString[7]))&&
      (isDigit(validationString[9]))&&
      (isDigit(validationString[10]))&&
      (isDigit(validationString[12]))&&
      (isDigit(validationString[13]))&&
      (isDigit(validationString[15]))&&
      (isDigit(validationString[16]))&&
      (isDigit(validationString[17]))&&
      (isDigit(validationString[18])))
      {
        //ok we have enough to convert everything into numbers
        //verify that the hour is 0-23
        //verify that the minute is 0-59
        //verify that the second is 0-59
        //verify that the day is 0-31
        //verify that the month is 1-12
        //verify that the year is >1970

        if(23 >= validationString.substring(0,1).toInt() >= 0)
        {
          if(59 >= validationString.substring(3,4).toInt() >= 0)
          {
            if(59 >= validationString.substring(6,7).toInt() >= 0)
            {
              result = true;
            }
            else
            {
              Serial.println("Validation Error: Seconds out of bounds");
            }
          }
          else
          {
            Serial.println("Validation Error: Minutes out of bounds");
          }
        }
        else
        {
          Serial.println("Validation Error: Hour out of bounds");
        }

        
      }
      else
      {
        Serial.println("Failed Validation: expected numberic digits");
      }
  }
  else
  {
    Serial.println("Failed Validation: string not long enough");
  }

  return result;
}

//prints the current time to serial
void printTime()
{
  // digital clock display of the time
  //go to the newline
  Serial.println();
  printDigits(hour());
  Serial.print(":");
  printDigits(minute());
  Serial.print(":");
  printDigits(second());
  Serial.print(" ");
  printDigits(day());
  Serial.print(" ");
  printDigits(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.print(" HH:MM:SS DD MM YYYY > "); 
}

//prints all digits as two numbers
void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
