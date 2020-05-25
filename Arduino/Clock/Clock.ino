#include <TimeLib.h>
#include <AsyncDelay.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <DS1307RTC.h>

//Defines for the purpose of setting up the LED display
//pin for the NeoPixels
#define RING_LED_PIN  6   //the pin with the ring LED
#define FACE_LED_PIN  12  //the pin with the face LED string
//descriptors for the LED clock
#define RING_LEDS 46          //number of LEDs in the minute ring
#define LEADING_ONE_LEDS 8    //number of LEDs in the leading number 1 for the hours
#define VERTICAL_SEG_LEDS 4   //number of LEDs in each vertical segment in the 7 segment display
#define HORIZONTAL_SEG_LEDS 2 //number of LEDs in each horizontal segment in the 7 segment display
/*All of these LEDs are in a string in the following order:
1. The Ring LEDs come first on the Ring LED strip on the RING_LED_PIN; there is nothing else

Then there is a second string on the face and it is wired like so:
1. The rightmost vertical segment; top to bottom
2. The lower horizontal
3. The middle horizontal
4. The upper horizontal
5. The middle vertical segment; top to bottom
6. The leading one's digit; bottom to top

In short it's wired in this order: BCDGAFE + Leading

This made sense while it was getting wired, not from a software perspective

Since the whole string is serial all operaitons work by accessing the correct indicies for each segment
*/

//these are for the purpose of printing our time on the serial port
AsyncDelay clockPrintDelay;   //this delay is for doing non-blocking prints on the command line
bool clockPrinting = true;     //determines if we should be printing our time

//these are for the purpose of handling incoming serial data
String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

//holds information about the strip
Adafruit_NeoPixel ring_strip(  //the count is computed at compile time, and is rather complicated
                          RING_LEDS,
                          RING_LED_PIN,  //use the LED pin identified above
                          NEO_GRB + NEO_KHZ800); //these are based on the string of LEDs that I have

Adafruit_NeoPixel face_strip(  //the count is computed at compile time, and is rather complicated
                          LEADING_ONE_LEDS + 4 * VERTICAL_SEG_LEDS + 3 * HORIZONTAL_SEG_LEDS,
                          FACE_LED_PIN,  //use the LED pin identified above
                          NEO_GRB + NEO_KHZ800); //these are based on the string of LEDs that I have

unsigned long millis_at_second_start;
int last_second;

void setup() {
  //Initialize the display; this must be first to avoid any fun startup junk
  //if the LEDs all fire on we could have power supply trouble
  ring_strip.begin();
  face_strip.begin();
  ring_strip.show();
  face_strip.show();

  // initialize serial:
  Serial.begin(9600);
  // reserve 50 bytes for the inputString; set strings should be 20 or less
  inputString.reserve(50);

  //setup the clock print delay
  //every second is obnoxious; set to every 5
  //make them sweat
  clockPrintDelay.start(5000, AsyncDelay::MILLIS);

  //set the clock source from the RTC
  //this will make sure time comes from the RTC and gets set to the RTC
  setSyncProvider(RTC.get);

  //this is used to help set the millis into second so we can keep track of how many miliseconds we are into this second
  millis_at_second_start = 0;
  last_second =0;

}

void loop() {
  //--------------------------------TIME HACKS------------------------------------------------
  //This section keeps track of the number of miliseconds we're into the current second
  //It would be better if I extend the time library to do this instead
  if(last_second != second())
  {
    //save the current second
    last_second = second();
    //save the current millis
    millis_at_second_start = millis();
  }
  //these get used to do animations
  
  //--------------------------------LED STRING MATH SECTION------------------------------------
  //This section contians all the code to set the clock LEDs
  //It computes the ring setup
  //It also computes and sets the seven segment portion based on the time as well

  //for now use hardcoded colors to restructure the function
  //TODO: make these colors time aware
  uint32_t common_digit_color = digit_color_function();

  //call the updates necessary for the ring
  RingUpdates(stationary_color_function(), wiping_color_function());

  //updates the numberic display
  TensDigit(common_digit_color);    //updates the tens digit
  SevenSegment(common_digit_color); //updates the seven segment display

  //at the end of all this execute the strip update
  ring_strip.show();
  face_strip.show();

  //--------------------------------SERIAL CLOCK SETTING SECTION-------------------------------
  //Everything here is related to setting the clock with a serial string
  //Ideally it would move to another file, but it had to be within the loop
  //I have broken this out into some other helper functions, but there is still quite a bit

  //once a new line arrives, setup a new prompt and try and process the string
  if (stringComplete) {
    //the user hit enter, it is time to process the string

    //moves to the next line for cosmetic reasons
    Serial.println(' ');

    //this performs string validation
    if(validateDateTimeString(inputString))
    {
      //valid string; parse for time information
      //this function will set the time if all goes well
      parseDateTimeString(inputString);
    }
    
    // clear the string; so the user can fill it back up if needed
    inputString = "";
    //tell the serial handler that the string is incomplete so it knows to wait for a return
    stringComplete = false;
    //restart the periodic clock updates which stopped once a character was pressed
    clockPrinting = true;
  }

  //if the clock is running then print an update every 1 s
  //this conditional is required to use async delay; which avoids blocking waits (yay)
  if (clockPrintDelay.isExpired())
  {
    //it's time to print, but should we?
    if(clockPrinting) printTime();

    //kick off the next clock print
    clockPrintDelay.repeat();
  }
}


/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;

    //if we get any new character, stop the time printing
    //this gets restarted once we get a string to process
    clockPrinting = false;
    
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\r') {
      stringComplete = true;
    }
    else
    {
      Serial.print(inChar);
    }
  }
}
