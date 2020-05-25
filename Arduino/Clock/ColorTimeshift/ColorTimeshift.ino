uint32_t stationary_color_function()
{
  return ring_strip.Color(0,80,0);
}

uint32_t wiping_color_function()
{
  return ring_strip.Color(10,10,0);
}

uint32_t digit_color_function()
{
  return face_strip.gamma32(face_strip.ColorHSV(32<<8, 255, 120));
}
