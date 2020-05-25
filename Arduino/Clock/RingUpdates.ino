//setup some colors for the ring
const uint32_t black            = ring_strip.Color(0,   0,  0);
//colors moved to main clock function

void RingUpdates(uint32_t stationary_color, uint32_t wiping_color)
{
  //Updates for the ring (the precious!!!)
  int stationary_ring_led = 0;  //we need an LED to identify the LED which we're going to toggle and pivot around
  int wiping_ring_led = 0; //used to keep track of which LED to light during animation

  //compute which LED we are going to be using based on the minute; this is if we're blinking
  stationary_ring_led = (minute()*RING_LEDS)/60;  //this will be a floor operation because it converts to float to int

  //compute which LED we are going to flash right now, because up until the even second we want to wipe through the ring
  //this overflows... try again
  wiping_ring_led = ((((millis()-millis_at_second_start)/10) * RING_LEDS) / 100); //also a floor operation
  //this is written this way to avoid overflows

  //every other second wipe either a color or black
  if(second()%2 == 0) 
  {
    if(wiping_ring_led >= 0)
    {
      //OK we have a valid index becuase the wipe is in the visible part of the ring
      ring_strip.setPixelColor(wiping_ring_led, wiping_color);
    }
  }
  else
  {
    //we should be dimming the strip
    if(wiping_ring_led >= 0)
    {
      //OK we have a valid index becuase the wipe is in the visible part of the ring
      ring_strip.setPixelColor(wiping_ring_led, black);
    }
  }

  //set the stationary LED
  ring_strip.setPixelColor(stationary_ring_led, stationary_color);
  
  return;
}
