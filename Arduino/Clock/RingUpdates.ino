//setup some colors for the ring
const uint32_t elapsed_minutes_color  = ring_strip.Color(6, 6,  0);
const uint32_t blink_odd_color        = ring_strip.gamma32(ring_strip.ColorHSV(10<<8, 255,  128));
const uint32_t blink_even_color       = ring_strip.gamma32(ring_strip.ColorHSV(25<<8, 255,  128));
const uint32_t black                  = ring_strip.Color(0,   0,  0);

void RingUpdates()
{
    //First the ring (the precious!!!)
  int active_ring_led = 0;  //we need an LED to identify the LED which we're going to toggle and pivot around

  //compute which LED we are going to be using based on the minute
  active_ring_led = (minute()*RING_LEDS)/60;  //this will be a floor operation because it converts to float to int

  //roll from the first one up to the active one
  for(int led_counter = 0; led_counter < active_ring_led; led_counter++)
  {
    //set the "time has passed" color
    ring_strip.setPixelColor(led_counter, elapsed_minutes_color);
  }

  //for the active LED blink it on and off every second
  //to do this use modulus; on for the odd seconds off for the even
  if(second()%2 == 0) ring_strip.setPixelColor(active_ring_led, blink_odd_color);
  else                ring_strip.setPixelColor(active_ring_led, blink_even_color);

  //for the remainder of the ring, shut them off
  for(int led_counter = active_ring_led + 1; led_counter < RING_LEDS; led_counter++)
  {
    ring_strip.setPixelColor(led_counter, black);
  }

  return;
}
