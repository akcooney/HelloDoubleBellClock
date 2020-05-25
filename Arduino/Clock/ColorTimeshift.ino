uint32_t stationary_color_function()
{
  uint32_t return_color;
  //when it was static colors it was 0,80,0 (bright green)

  //I want this to go like this 7AM - 8PM it should be 0,80,0
  //I want to fade from 80-1 from 8PM - 9PM and 1-80 from 6AM - 7AM
  int current_hour = hour();

  //since we're just messing with green; do just changes to the green level
  int green_level = 0;

  //here's the run down
  if(current_hour < 7) green_level = 5;
  else if(current_hour < 8) green_level = minute()*75/60 + 5;
  else if(current_hour < 20) green_level = 80;
  else if(current_hour < 21) green_level = (60 - minute())*75/60 + 5;
  else green_level = 5;

  //convert to an actual color
  return_color = ring_strip.Color(0,green_level,0);

  return return_color;
}

uint32_t wiping_color_function()
{
  uint32_t return_color;

  //for reference it was 10,10,0 at full on
  //similar to the stationary color I want full on 7AM - 8PM
  //from 9PM - 6AM turn the wiping off
  //dim up uniformly otherwise

  //grab the current hour
  int current_hour = hour();
  //use this to help choose a dimming value
  int common_value = 0;

  if(current_hour < 7) common_value = 0;
  else if(current_hour < 8) common_value = minute()*10/60;
  else if(current_hour < 20) common_value = 10;
  else if(current_hour < 21) common_value = (60 - minute())*10/60;
  else common_value = 0;

  return ring_strip.Color(common_value,common_value,0);
}

uint32_t digit_color_function()
{
  uint32_t return_color;

  //I want this to go like this 7AM - 8PM it should be 0,80,0
  //I want to fade from 80-1 from 8PM - 9PM and 1-80 from 6AM - 7AM
  int current_hour = hour();

  //use this to help choose a dimming value
  int brightness_value = 0;

  //here's the brightness map
  if(current_hour < 7) brightness_value = 44;
  else if(current_hour < 8) brightness_value = minute()*56/60 + 44;
  else if(current_hour < 20) brightness_value = 100;
  else if(current_hour < 21) brightness_value = (60 - minute())*56/60 + 44;
  else brightness_value = 44;

  //finally do a color transition; which is TODO for sure

  //convert to HSV
  return_color = face_strip.gamma32(face_strip.ColorHSV(32<<8, 255, brightness_value));

  return return_color;
}
