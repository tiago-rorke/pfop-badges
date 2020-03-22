
#define NUM_LEDS 3
const int LED_PIN[] = {0, 1, 4};


// ================== GENERAL VARS ================== //

// target led pwm level
#define BRIGHTNESS_MAX 30
#define BRIGHTNESS_MIN 5
// time spent at brightness
#define ON_DELAY_MAX 1000
#define ON_DELAY_MIN 100
// time before next led fade on
#define INTERVAL_MAX 3000
#define INTERVAL_MIN 1000
// fade speed
#define FADE_DELAY 20

// active == being touched
boolean active = false;

long timer;

int pwm[NUM_LEDS];
int brightness[NUM_LEDS]; 

// random twinkling during passive state
long led_timer[NUM_LEDS];
int on_delay[NUM_LEDS]; 
int interval; 
int led_index; // "current" led in pattern
// individual led states
int led_state[NUM_LEDS];
  // -1 = led off, inactive
  // 0 = led off, waiting to fade on
  // 1 = fading led on
  // 2 = led at brightness, waiting to fade off
  // 3 = fading led off


// =================== TOUCH VARS =================== //

#define SEND_PIN 2
#define RECEIVE_PIN 3
#define SAMPLES 15
#define THRESHOLD 45
#define TOUCH_BRIGHTNESS_MAX 100
#define FLICKER_RATE 30
#define PULSE_SPEED_DECAY 0.95

#include <CapacitiveSensor.h>
CapacitiveSensor cap1 = CapacitiveSensor(SEND_PIN, RECEIVE_PIN);

// store touch capacitance readings
long touch;

float touch_brightness;
float touch_pulse_speed;
boolean touch_fade_in; // toggle pulsing between fade in and fade out


void setup() {

  for(int i=0; i<NUM_LEDS; i++) {
    pinMode(LED_PIN[i], OUTPUT);
  }
  init_leds();

  twinkling_init();
}


void loop() {

  update_leds();

  touch = cap1.capacitiveSensor(SAMPLES);

  if(!active && touch > THRESHOLD) {
    timer = millis();
    active = true;
    init_leds();
    touch_brightness = TOUCH_BRIGHTNESS_MAX;
    touch_pulse_speed = touch_brightness;
    touch_fade_in = false;
  } else if (active && touch <= THRESHOLD) {
    active = false;
    twinkling_init();
  }

  if(!active) { // leds are twinkling slowly

    long now = millis();
    
    for(int i=0; i<NUM_LEDS; i++) {     
      switch(led_state[i]) {

        case 0: // led off, waiting to fade on
          if(now - led_timer[i] > interval) {
            led_state[i] = 1;
            led_timer[i] = now;
            led_init(i);
            led_timer[i] = now;
          }
          break;

        case 1: // fading led on
          if(now - led_timer[i] > FADE_DELAY) {
            pwm[i]++;
            if(pwm[i] > brightness[i]) {
              pwm[i] = brightness[i];
              led_state[i] = 2;
            }
            led_timer[i] = now;
          }
          break;

        case 2: // led at brightness, waiting to fade off
          if(now - led_timer[i] > on_delay[i]) {
            led_state[i] = 3;
            led_timer[i] = now;
          }
          break;

        case 3: // fading led off
          if(now - led_timer[i] > FADE_DELAY) {
            pwm[i]--;
            if(pwm[i] < 0) {
              pwm[i] = 0;
              led_state[i] = -1;
              init_next_led();
            }
            led_timer[i] = now;
          }
          break;
          
      }
    }
      
  } else { // leds are flickering randomly (brownian motion)
      
    for(int i=0; i<NUM_LEDS; i++) {
      pwm[i] += random(-FLICKER_RATE, FLICKER_RATE);
      pwm[i] = constrain(pwm[i], 0, TOUCH_BRIGHTNESS_MAX);
    }
    
    // I quite liked this pulsing effect, but wasn't able to make space for it on the attiny45 alongside the capsense lib
    /*
    if(!touch_fade_in) {
      touch_brightness -= touch_pulse_speed;
      if(touch_brightness < 0) {
        touch_brightness = 0;
        touch_fade_in = true;
        touch_pulse_speed *= PULSE_SPEED_DECAY;
      }
    } else {
      touch_brightness += touch_pulse_speed;
      if(touch_brightness >= TOUCH_BRIGHTNESS_MAX) {
        touch_brightness = TOUCH_BRIGHTNESS_MAX;
        touch_fade_in = false;
        touch_pulse_speed *= PULSE_SPEED_DECAY;

      }
    }
    */
  }

}


void init_leds() {
  for(int i=0; i<NUM_LEDS; i++) {
    pwm[i] = 0;
    digitalWrite(LED_PIN[i], LOW);
  }

}

void update_leds() {
  for(int i=0; i<NUM_LEDS; i++) { 
    if(pwm[i] > 0) {
      analogWrite(LED_PIN[i], pwm[i]);
    } else {
      digitalWrite(LED_PIN[i], LOW);
    }    
  }  
}

void twinkling_init() {
  interval = random(INTERVAL_MIN, INTERVAL_MAX);
  for(int i=0; i<NUM_LEDS; i++) {
    led_state[i] = -1;
  }
  led_index = floor(random(0,3));
  led_init(led_index);
  init_next_led();
  timer = millis();
  init_leds();
}

void led_init(int led) {
  led_state[led] = 1;
  brightness[led] = random(BRIGHTNESS_MIN, BRIGHTNESS_MAX);
  on_delay[led] = random(ON_DELAY_MIN, ON_DELAY_MAX);
}

void init_next_led() {
  if(random(0,2) > 0) {
    led_index++;
  } else {
    led_index--;
  }
  if(led_index<0) {
    led_index = NUM_LEDS -1;
  } else {
    led_index %= NUM_LEDS;
  }
  if(led_state[led_index] == -1) {
    led_state[led_index] = 0;
    interval = random(INTERVAL_MIN, INTERVAL_MAX);
  } else {
    init_next_led();
  }
}