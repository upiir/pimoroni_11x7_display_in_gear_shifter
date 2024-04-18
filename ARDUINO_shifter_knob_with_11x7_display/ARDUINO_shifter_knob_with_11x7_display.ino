// Simple project using Arduino UNO with Pimoroni 7x11px LED Matrix Display to display current gear for the manual transmission cars
// however, since the Pimoroni display is not supported on WOKWI, I´m simulating this display with NeoPixel canvas
// please watch all 3 youtube videos to understand all details

// created by upir, 2024
// youtube channel: https://www.youtube.com/upir_upir

// YouTube video: https://youtu.be/HcP48uCBzDQ
// Source files: https://github.com/upiir/pimoroni_11x7_display_in_gear_shifter
// Wokwi simulation: https://wokwi.com/projects/395488320396224513

// YouTube video part 1: https://youtu.be/QixtxaAda18
// YouTube video part 2: https://youtu.be/sZZFgSmYJjc

// Links from the video:
// Bambu Lab A1 mini 3D Printer: https://shareasale.com/r.cfm?b=2420414&u=3422904&m=138211&urllink=&afftrack=
// MOMO shifter knob: https://s.click.aliexpress.com/e/_DnKeTPb
// Pimoroni 7x11px LED Matrix Display: https://shop.pimoroni.com/products/11x7-led-matrix-breakout?variant=21791690752083
// Online Image Converter: https://lvgl.io/tools/imageconverter
// Breadboard wires: https://s.click.aliexpress.com/e/_Dkbngin
// Arduino UNO R3: https://s.click.aliexpress.com/e/_AXDw1h
// Arduino breadboard prototyping shield: https://s.click.aliexpress.com/e/_DlxEfPX
// Photopea (online graphics editor like Photoshop): https://www.photopea.com/

#include <Wire.h> // wire library is required for IIC/I2C communication
#include <Adafruit_GFX.h> // adafruit GFX is required for the IS31FL3731 chip
#include <Adafruit_IS31FL3731.h> // library for Pimoroni 11x7px LED matrix display (and Adafruit 16x9 LED matrix display)
#include <Adafruit_NeoPixel.h> // library for NeoPixels - only used for testing on WOKWI 

Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731(); // initialization of the Pimoroni 11x7px display

#define PIN_NEO_PIXEL 6  // Arduino pin that connects to NeoPixel
#define NUM_PIXELS 77 // The number of LEDs (pixels) on NeoPixel

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800); // set the NeoPixel (canvas) initialization, only used for WOKWI simulation

// our canvas for pimoroni 11x7px LED matrix display
byte canvas_7x11px[] = { // will be overwritten later on
  0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0
};



byte gear_r_map[] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xcc, 0x33, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x33, 0xcc, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x33, 0xff, 
  0xff, 0x00, 0x00, 0x00, 0x33, 0xff, 0x33, 
  0xff, 0x00, 0x00, 0x33, 0xff, 0x33, 0x00, 
  0xff, 0xff, 0xff, 0xff, 0x33, 0x00, 0x00, 
  0xff, 0x00, 0x00, 0x33, 0xff, 0x33, 0x00, 
  0xff, 0x00, 0x00, 0x00, 0x33, 0xff, 0x33, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x33, 0xff, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
};


byte gear_n_map[] = {
  0xff, 0xff, 0x33, 0x00, 0x00, 0x00, 0xff, 
  0xff, 0x33, 0xff, 0x33, 0x00, 0x00, 0xff, 
  0xff, 0x00, 0x33, 0xff, 0x33, 0x00, 0xff, 
  0xff, 0x00, 0x00, 0x33, 0xff, 0x33, 0xff, 
  0xff, 0x00, 0x00, 0x00, 0x33, 0xff, 0xff, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x33, 0xff, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
};


byte gear_5_map[] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xcc, 0x33, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0xcc, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0xcc, 
  0xff, 0x33, 0x00, 0x00, 0x33, 0xcc, 0x29, 
  0xff, 0xff, 0xff, 0xff, 0xcc, 0x33, 0x00, 
};

byte gear_4_map[] = {
  0x00, 0x00, 0x00, 0x00, 0x33, 0xff, 0x33, 
  0x00, 0x00, 0x00, 0x33, 0xff, 0x33, 0x00, 
  0x00, 0x00, 0x33, 0xff, 0x33, 0x00, 0x00, 
  0x00, 0x33, 0xff, 0x33, 0x00, 0x00, 0x00, 
  0x33, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0x33, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
};


byte gear_3_map[] = {
  0x33, 0xcc, 0xff, 0xff, 0xff, 0xcc, 0x33, 
  0xcc, 0x33, 0x00, 0x00, 0x00, 0x33, 0xcc, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x33, 0xff, 0x33, 
  0x00, 0x00, 0x00, 0x33, 0xff, 0x33, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0xcc, 0x33, 0x00, 0x00, 0x00, 0x33, 0xcc, 
  0x33, 0xcc, 0xff, 0xff, 0xff, 0xcc, 0x29, 
};


byte gear_2_map[] = {
  0x29, 0xcc, 0xff, 0xff, 0xff, 0xcc, 0x33, 
  0xcc, 0x33, 0x00, 0x00, 0x00, 0x33, 0xcc, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x33, 0xff, 0x33, 
  0x00, 0x00, 0x00, 0x33, 0xff, 0x33, 0x00, 
  0x00, 0x00, 0x33, 0xff, 0x33, 0x00, 0x00, 
  0x00, 0x33, 0xff, 0x33, 0x00, 0x00, 0x00, 
  0x33, 0xff, 0x33, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
};


byte gear_1_map[] = {
  0x00, 0x00, 0x33, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x33, 0xff, 0xff, 0x00, 0x00, 0x00, 
  0x33, 0xff, 0x33, 0xff, 0x00, 0x00, 0x00, 
  0xff, 0x33, 0x00, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
};

byte gear_h_pattern_map[] = {
  0x2e, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x2e, 
  0x2e, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x2e, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 
  0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 
  0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x2e, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x2e, 
  0x2e, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x2e, 
};


const unsigned char* gear_images_array[] = {
	gear_r_map,
	gear_h_pattern_map, //gear_n_map,
  gear_1_map,
  gear_2_map,
  gear_3_map,
  gear_4_map,
  gear_5_map
};

// circle, 255 in the middle, 0 around the edges
byte bitmap_circle[] = {
  0x02, 0x0d, 0x17, 0x1b, 0x17, 0x0d, 0x02,
  0x1b, 0x30, 0x41, 0x47, 0x41, 0x30, 0x1b,
  0x3b, 0x5b, 0x74, 0x7d, 0x74, 0x5b, 0x3b,
  0x5b, 0x86, 0xa7, 0xb3, 0xa7, 0x86, 0x5b,
  0x74, 0xa7, 0xcf, 0xe0, 0xcf, 0xa7, 0x74,
  0x7d, 0xb3, 0xe0, 0xff, 0xe0, 0xb3, 0x7d,
  0x74, 0xa7, 0xcf, 0xe0, 0xcf, 0xa7, 0x74,
  0x5b, 0x86, 0xa7, 0xb3, 0xa7, 0x86, 0x5b,
  0x3b, 0x5b, 0x74, 0x7d, 0x74, 0x5b, 0x3b,
  0x1b, 0x30, 0x41, 0x47, 0x41, 0x30, 0x1b,
  0x02, 0x0d, 0x17, 0x1b, 0x17, 0x0d, 0x02,
};

// smoothstep function, will return value between 0-1
// based on - https://stackoverflow.com/questions/28889210/smoothstep-function
float smoothstep(float edge0, float edge1, float x)
{
  // Scale, bias and saturate x to 0..1 range
  x = constrain((x - edge0) / (edge1 - edge0), 0.0, 1.0);
  // Evaluate polynomial
  return x * x * (3 - 2 * x);
}


int offset = -200; // offset variable for animation
int offset_inc = 10; // offset increment for setting the speed of the animation

int animation_status = 0; // 0 = not playing

int current_gear = 0;  // -1 = R, 0 = N, 1 = 1, 2 = 2, ...
int previous_gear = 0; // previous gear, only play animations if the new gear is different from the previous gear

int gear_image = 0;


void setup() {

  pinMode(A0, INPUT); // set pin A0 as input to read analog voltage from the Hall Sensor
  pinMode(A1, INPUT); // set pin A1 as input to read analog voltage from the Hall Sensor
  pinMode(A2, INPUT); // set pin A2 as input to read analog voltage from the Hall Sensor
  pinMode(A3, INPUT); // set pin A3 as input to read analog voltage from the Hall Sensor  

  NeoPixel.begin();  // initialize the NeoPixel object

  Serial.begin(9600);
  //Serial.println("ISSI swirl test");

  if (! ledmatrix.begin(0x75)) {
    //Serial.println("IS31 not found");
    //while (1); // commented out for the WOKWI simulation, since the Pimoroni display is not connected/supported on WOKWI
  }
  //Serial.println("IS31 found!");
}

void loop() { // main loop


  // calculating the current gear
  int hall_0_value = analogRead(A0); // read the analog value on pin A0, value will be between 0 - 1023
  int hall_1_value = analogRead(A1); // read the analog value on pin A1, value will be between 0 - 1023
  int hall_2_value = analogRead(A2); // read the analog value on pin A2, value will be between 0 - 1023
  int hall_3_value = analogRead(A3); // read the analog value on pin A3, value will be between 0 - 1023

  int percentage_value_0 = round(abs(hall_0_value - 512) / 5.12); // convert hall value to range 0-100%
  int percentage_value_1 = round(abs(hall_1_value - 512) / 5.12); // convert hall value to range 0-100%
  int percentage_value_2 = round(abs(hall_2_value - 512) / 5.12); // convert hall value to range 0-100%
  int percentage_value_3 = round(abs(hall_3_value - 512) / 5.12); // convert hall value to range 0-100%


/*  Serial.print(" A0: ");
  Serial.print(percentage_value_0);  
  Serial.print(" A1: ");
  Serial.print(percentage_value_1);  
  Serial.print(" A2: ");
  Serial.print(percentage_value_2);  
  Serial.print(" A3: ");
  Serial.print(percentage_value_3);  
  Serial.println("");*/
  
    

  // calculate the current gear
  // hall sensors are arranged like this
  //
  //   A0               A3
  //      1     3     5
  //      │     │     │
  //      ├─────┼─────┘
  //      │     │     │
  //      2     4     R
  //   A1               A2

  if (percentage_value_0 > 30 && percentage_value_3 > 30) {
    current_gear = 3; // 3rd gear
  }
  else if (percentage_value_1 > 30 && percentage_value_2 > 30) {
    current_gear = 4; // 4th gear
  }
  else if (percentage_value_0 > 30) {
    current_gear = 1; // 1st gear
  }
  else if (percentage_value_3 > 30) {
    current_gear = 5; // 5th gear
  }
  else if (percentage_value_1 > 30) {
    current_gear = 2; // 2nd gear
  }
  else if (percentage_value_2 > 30) {
    current_gear = -1; // reverse
  }
  else {
    current_gear = 0; // neutral
  }
  // ----------- end calculating the current gear

/*  Serial.print("current_gear: ");
  Serial.print(current_gear);
  Serial.print("   previous_gear: ");  
  Serial.print(previous_gear);    
  Serial.print("   animation_status: ");  
  Serial.print(animation_status);   
  Serial.print("   offset: ");  
  Serial.println(offset);   */

   

  // determine if the play the animation
  if (animation_status == 0) { // no animation is currently playing
    if (current_gear != previous_gear) { // current gear is different = play the animation
      animation_status = 1;
      offset_inc = 10;
      gear_image = previous_gear;

    }
  }

  if (animation_status == 1) { // animation is playing
    if ((offset < 400) && (offset_inc > 0)) {
      offset = offset + offset_inc;
    } else {
      // switch images here
      gear_image = current_gear;
      offset_inc = -10;
    }

    if ((offset >= -200) && (offset_inc < 0)) {
      offset = offset + offset_inc;
    } 

    if ((offset <= -200) && (offset_inc < 0)) {
      animation_status = 0;
      previous_gear = gear_image;
    }
  }




  // draw on our canvas
  for (uint8_t pixel = 0; pixel < 77; pixel++) {

    // smoothstep function(s)
    float smoothstep_inner = smoothstep(offset - 100, offset - 5, bitmap_circle[pixel]); // inner circle for smoothstep
    float smoothstep_outer = smoothstep(offset + 100, offset + 5, bitmap_circle[pixel]); // outer circle for smoothstep
    // reveal the image
    //float reveal_image = smoothstep_inner * bitmap_digit_3[pixel]; // revealing the "bitmap_digit_3" image
    float reveal_image = smoothstep_inner * gear_images_array[gear_image+1][pixel]; // revealing the "bitmap_digit_3" image
    
    canvas_7x11px[pixel] = constrain(reveal_image + (smoothstep_inner * smoothstep_outer * 255.0), 0, 255);
  }


  // Transfer the content of the 11x7 canvas to the 11x7 display
  // Since the Adafruit library is made for 16x9 display, we need to do this in two steps
  //
  // This is the placement of Pimoroni 11x7px content on Adafruit 16x9px canvas
  //
  // A => first half of the 11x7 content  - 7x6px
  // B => second half of the 11x7 content - 7x5px
  // empty => pixel not used
  //
  //
  //     0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1
  //     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
  //    ┌─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐
  //   0│A│A│A│A│A│A│A│ │B│B│B│B│B│B│B│ │        Pimoroni 11x7px (7x11px)
  //    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
  //   1│A│A│A│A│A│A│A│ │B│B│B│B│B│B│B│ │            ┌──┬───────────────┐
  //    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤            │O │ A A A A A A A │
  //   2│A│A│A│A│A│A│A│ │B│B│B│B│B│B│B│ │            │  │ A A A A A A A │
  //    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤      ┌─────┘  │ A A A A A A A │
  //   3│A│A│A│A│A│A│A│ │B│B│B│B│B│B│B│ │      │o 3-5V  │ A A A A A A A │
  //    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤      │o SDA   │ A A A A A A A │
  //   4│A│A│A│A│A│A│A│ │B│B│B│B│B│B│B│ │      │o SCL   │ A A A A A A A │
  //    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤      │o -     │ B B B B B B B │
  //   5│A│A│A│A│A│A│A│ │ │ │ │ │ │ │ │ │      │o GND   │ B B B B B B B │
  //    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤      └─────┐  │ B B B B B B B │
  //   6│ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │            │  │ B B B B B B B │
  //    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤            │O │ B B B B B B B │
  //   7│ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │            └──┴───────────────┘
  //    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
  //   8│ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
  //    └─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘
  //

  // this is step 1...
  for (uint8_t x = 0; x < 7; x++) {
    for (uint8_t y = 0; y < 6; y++) {
      ledmatrix.drawPixel(x, y, canvas_7x11px[y * 7 + x] / 4); // transfer first half of the picture
    }
  }
  // and this is step 2
  for (uint8_t x = 8; x < 15; x++) {
    for (uint8_t y = 0; y < 5; y++) {
      ledmatrix.drawPixel(x, y, canvas_7x11px[ (7 * 6) + y * 7 + (x - 8)] / 4); // transfer second half of the picture
    }
  }


  // Neopixel code below
  // neopixels are only used to simulate the content of the Pimoroni 11x7px display inside WOKWI emulator

  // clear neopixels
  NeoPixel.clear();  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called
  // transfer the content of the 11x7 canvas to neopixels
  for (uint8_t pixel = 0; pixel < 77; pixel++) {
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(canvas_7x11px[pixel], canvas_7x11px[pixel], canvas_7x11px[pixel]));
  }
  NeoPixel.show(); // show all the set pixels on neopixel canvas
}



