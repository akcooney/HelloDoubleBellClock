//const uint32_t digit_color_base  = face_strip.gamma32(face_strip.ColorHSV( 32<<8, 255,  120));
//so this is super annoying; but the Hue needs to be left shifted to work; everything else seems OK
//uint32_t digit_color; //holds the digit color allows us to do time based dimming

//remember it's wired BCDGAFE + Leading

void SevenSegment(uint32_t digit_color)
{
  
  //updates the seven segment display
  //just in case there's a timing issue grab the hour at the start

  //also since we're knocking off the leading 1; mod it
  int display_digit = hour();

  //adjust the display digit to be 1-12 for the purpose of the clockface
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
  //remember it's wired BCDGAFE + Leading
  // so we need BCDG which is two vertical and two horizontal
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
  for(int led_counter = 2*VERTICAL_SEG_LEDS + 2*HORIZONTAL_SEG_LEDS;
      led_counter <     2*VERTICAL_SEG_LEDS + 3*HORIZONTAL_SEG_LEDS;
      led_counter++)
      {
        if(digit_on_not_off)  face_strip.setPixelColor(led_counter, digit_color);
        else                  face_strip.setPixelColor(led_counter, black);
      }

  //Next the B digit
  //remember it's wired BCDGAFE + Leading
  //so we're first
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
  for(int led_counter = 0*VERTICAL_SEG_LEDS + 0*HORIZONTAL_SEG_LEDS;
      led_counter <     1*VERTICAL_SEG_LEDS + 0*HORIZONTAL_SEG_LEDS;
      led_counter++)
      {
        if(digit_on_not_off)  face_strip.setPixelColor(led_counter, digit_color);
        else                  face_strip.setPixelColor(led_counter, black);
      }

  //Next the C digit
  //remember it's wired BCDGAFE + Leading
  //so we need to go past B
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
  for(int led_counter = 1*VERTICAL_SEG_LEDS + 0*HORIZONTAL_SEG_LEDS;
      led_counter <     2*VERTICAL_SEG_LEDS + 0*HORIZONTAL_SEG_LEDS;
      led_counter++)
      {
        if(digit_on_not_off)  face_strip.setPixelColor(led_counter, digit_color);
        else                  face_strip.setPixelColor(led_counter, black);
      }

  //Next the D digit
  //remember it's wired BCDGAFE + Leading
  //so we need to go past BC
  //D is horizontal
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
  for(int led_counter = 2*VERTICAL_SEG_LEDS + 0*HORIZONTAL_SEG_LEDS;
      led_counter <     2*VERTICAL_SEG_LEDS + 1*HORIZONTAL_SEG_LEDS;
      led_counter++)
      {
        if(digit_on_not_off)  face_strip.setPixelColor(led_counter, digit_color);
        else                  face_strip.setPixelColor(led_counter, black);
      }

  //Next the E digit
  //remember it's wired BCDGAFE + Leading
  //so we need to go past BCDGAF
  //E is vertical
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
  for(int led_counter = 3*VERTICAL_SEG_LEDS + 3*HORIZONTAL_SEG_LEDS;
      led_counter <     4*VERTICAL_SEG_LEDS + 3*HORIZONTAL_SEG_LEDS;
      led_counter++)
      {
        if(digit_on_not_off)  face_strip.setPixelColor(led_counter, digit_color);
        else                  face_strip.setPixelColor(led_counter, black);
      }

  //Next the F digit
  //remember it's wired BCDGAFE + Leading
  //so we need to go past BCDGA
  //F is vertical
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
  for(int led_counter = 2*VERTICAL_SEG_LEDS + 3*HORIZONTAL_SEG_LEDS;
      led_counter <     3*VERTICAL_SEG_LEDS + 3*HORIZONTAL_SEG_LEDS;
      led_counter++)
      {
        if(digit_on_not_off)  face_strip.setPixelColor(led_counter, digit_color);
        else                  face_strip.setPixelColor(led_counter, black);
      }

  //Next the G digit
  //remember it's wired BCDGAFE + Leading
  //so we need to go past BCD
  //G is horizontal
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
  for(int led_counter = 2*VERTICAL_SEG_LEDS + 1*HORIZONTAL_SEG_LEDS;
      led_counter <     2*VERTICAL_SEG_LEDS + 2*HORIZONTAL_SEG_LEDS;
      led_counter++)
      {
        if(digit_on_not_off)  face_strip.setPixelColor(led_counter, digit_color);
        else                  face_strip.setPixelColor(led_counter, black);
      }

  return;
}
