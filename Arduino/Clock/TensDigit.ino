//This tab updates the leading 1

void TensDigit()
{
  //determine if it's time to turn on the leading 1

  //at the end this will determine if the leading one is on or not
  bool leading_one_on = false;

  //the logic for this gets rather nasty
  //a look-up table is far better
  switch(hour())
  {
    case 0:   //12 something (looks odd I know)
    case 10:  
    case 11:
    case 12:
    case 22:  //10 PM
    case 23:  //11 PM - see above for midnight
      leading_one_on = true;
      break;
    default:
      leading_one_on = false;
      break;
  }

  //loop through our leading 1 LEDs
  for(int led_counter = VERTICAL_SEG_LEDS*4 + HORIZONTAL_SEG_LEDS*3; led_counter < VERTICAL_SEG_LEDS*4 + HORIZONTAL_SEG_LEDS*3 + LEADING_ONE_LEDS; led_counter++)
  {
    if(leading_one_on)  face_strip.setPixelColor(led_counter, digit_color);
    else                face_strip.setPixelColor(led_counter, black);
  }
  
  return;
}
