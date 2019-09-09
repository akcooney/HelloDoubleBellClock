const uint32_t digit_color  = strip.gamma32(strip.ColorHSV( 273<<8, 255,  128));


void SevenSegment()
{
  //updates the seven segment display
  //just in case there's a timing issue grab the hour at the start

  //also since we're knocking off the leading 1; mod it
  int display_digit = hour();

  if(display_digit > 12) display_digit = display_digit - 12;
  if(display_digit == 0) display_digit = 12;
  display_digit = display_digit % 10; //knock off the 10's digit

  //reference the wikipedia article on the letters
  //the order is CDEFABG
  //it starts with the ring -> tens digit -> seven segment

  //we'll use this so I only have to write the loops once
  bool digit_on_not_off;

  //the A-Digit
  //decide what to do first
  //ring - tens - CDEFA  verticals 3; horizontal 1
  switch(display_digit)
  {
    case 2:
    case 3:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 0:
      //turn on the digit
      digit_on_not_off = true;
      break;
    default:
      //turn off the digit
      digit_on_not_off = false;
      break;
  }
  //loop once through the digit and use the bool to act
  for(int led_counter = RING_LEDS + LEADING_ONE_LEDS + 3*VERTICAL_SEG_LEDS + HORIZONTAL_SEG_LEDS;
      led_counter <     RING_LEDS + LEADING_ONE_LEDS + 3*VERTICAL_SEG_LEDS + 2*HORIZONTAL_SEG_LEDS;
      led_counter++)
      {
        if(digit_on_not_off)  strip.setPixelColor(led_counter, digit_color);
        else                  strip.setPixelColor(led_counter, black);
      }

  //Next the B digit
  //ring - tens - CDEFAB  verticals 3; horizontal 2
  switch(display_digit)
  {
    case 0:
    case 2:
    case 3:
    case 4:
    case 7:
    case 8:
    case 9:
      //turn on the digit
      digit_on_not_off = true;
      break;
    default:
      //turn off the digit
      digit_on_not_off = false;
      break;
  }
  //loop once through the digit and use the bool to act
  for(int led_counter = RING_LEDS + LEADING_ONE_LEDS + 3*VERTICAL_SEG_LEDS + 2*HORIZONTAL_SEG_LEDS;
      led_counter <     RING_LEDS + LEADING_ONE_LEDS + 4*VERTICAL_SEG_LEDS + 2*HORIZONTAL_SEG_LEDS;
      led_counter++)
      {
        if(digit_on_not_off)  strip.setPixelColor(led_counter, digit_color);
        else                  strip.setPixelColor(led_counter, black);
      }

  //Next the C digit
  //ring - tens - CDEFAB  verticals 0; horizontal 0
  switch(display_digit)
  {
    case 0:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      //turn on the digit
      digit_on_not_off = true;
      break;
    default:
      //turn off the digit
      digit_on_not_off = false;
      break;
  }
  //loop once through the digit and use the bool to act
  for(int led_counter = RING_LEDS + LEADING_ONE_LEDS + 0*VERTICAL_SEG_LEDS + 0*HORIZONTAL_SEG_LEDS;
      led_counter <     RING_LEDS + LEADING_ONE_LEDS + 1*VERTICAL_SEG_LEDS + 0*HORIZONTAL_SEG_LEDS;
      led_counter++)
      {
        if(digit_on_not_off)  strip.setPixelColor(led_counter, digit_color);
        else                  strip.setPixelColor(led_counter, black);
      }

  //Next the D digit
  //ring - tens - CDEFAB  verticals 1; horizontal 0
  switch(display_digit)
  {
    case 0:
    case 2:
    case 3:
    case 5:
    case 6:
    case 8:
    case 9:
      //turn on the digit
      digit_on_not_off = true;
      break;
    default:
      //turn off the digit
      digit_on_not_off = false;
      break;
  }
  //loop once through the digit and use the bool to act
  for(int led_counter = RING_LEDS + LEADING_ONE_LEDS + 1*VERTICAL_SEG_LEDS + 0*HORIZONTAL_SEG_LEDS;
      led_counter <     RING_LEDS + LEADING_ONE_LEDS + 1*VERTICAL_SEG_LEDS + 1*HORIZONTAL_SEG_LEDS;
      led_counter++)
      {
        if(digit_on_not_off)  strip.setPixelColor(led_counter, digit_color);
        else                  strip.setPixelColor(led_counter, black);
      }

  //Next the E digit
  //ring - tens - CDEFAB  verticals 1; horizontal 1
  switch(display_digit)
  {
    case 0:
    case 1:
    case 2:
    case 6:
    case 8:
      //turn on the digit
      digit_on_not_off = true;
      break;
    default:
      //turn off the digit
      digit_on_not_off = false;
      break;
  }
  //loop once through the digit and use the bool to act
  for(int led_counter = RING_LEDS + LEADING_ONE_LEDS + 1*VERTICAL_SEG_LEDS + 1*HORIZONTAL_SEG_LEDS;
      led_counter <     RING_LEDS + LEADING_ONE_LEDS + 2*VERTICAL_SEG_LEDS + 1*HORIZONTAL_SEG_LEDS;
      led_counter++)
      {
        if(digit_on_not_off)  strip.setPixelColor(led_counter, digit_color);
        else                  strip.setPixelColor(led_counter, black);
      }

  //Next the F digit
  //ring - tens - CDEFAB  verticals 2; horizontal 1
  switch(display_digit)
  {
    case 0:
    case 1:
    case 4:
    case 5:
    case 6:
    case 8:
    case 9:
      //turn on the digit
      digit_on_not_off = true;
      break;
    default:
      //turn off the digit
      digit_on_not_off = false;
      break;
  }
  //loop once through the digit and use the bool to act
  for(int led_counter = RING_LEDS + LEADING_ONE_LEDS + 2*VERTICAL_SEG_LEDS + 1*HORIZONTAL_SEG_LEDS;
      led_counter <     RING_LEDS + LEADING_ONE_LEDS + 3*VERTICAL_SEG_LEDS + 1*HORIZONTAL_SEG_LEDS;
      led_counter++)
      {
        if(digit_on_not_off)  strip.setPixelColor(led_counter, digit_color);
        else                  strip.setPixelColor(led_counter, black);
      }

  //Next the G digit
  //ring - tens - CDEFAB  verticals 4; horizontal 2
  switch(display_digit)
  {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 8:
    case 9:
      //turn on the digit
      digit_on_not_off = true;
      break;
    default:
      //turn off the digit
      digit_on_not_off = false;
      break;
  }
  //loop once through the digit and use the bool to act
  for(int led_counter = RING_LEDS + LEADING_ONE_LEDS + 4*VERTICAL_SEG_LEDS + 2*HORIZONTAL_SEG_LEDS;
      led_counter <     RING_LEDS + LEADING_ONE_LEDS + 4*VERTICAL_SEG_LEDS + 3*HORIZONTAL_SEG_LEDS;
      led_counter++)
      {
        if(digit_on_not_off)  strip.setPixelColor(led_counter, digit_color);
        else                  strip.setPixelColor(led_counter, black);
      }

  return;
}
