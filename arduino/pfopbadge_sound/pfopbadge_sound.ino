
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

// active == reacting to sound
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


// =================== SOUND VARS =================== //

#define SOUND_PIN A1

// to store adc microphone reading
int sound;

// set relative sound thresholds for each LED
int thres0 = 200;
int thres1 = 250;
int thres2 = 350;
int thres3 = 450;

// an offset for quickly tweaking the thresholds
int thres_mod = 80;

int sound_timeout = 1000;


void setup() {

  thres0 += thres_mod;
  thres1 += thres_mod;
  thres2 += thres_mod;

  for(int i=0; i<NUM_LEDS; i++) {
    pinMode(LED_PIN[i], OUTPUT);
  }
  init_leds();

  twinkling_init();
}


void loop() {

  update_leds();

  sound = analogRead(SOUND_PIN);

  if(!active && sound > thres0) {
    timer = millis();
    active = true;
    init_leds();
  } else if (active && millis()-timer > sound_timeout) {
    timer = millis();
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

  } else { // leds are reacting to sound    

    if (sound > thres0) {
      pwm[0] = map(sound, thres0, thres1, 0, BRIGHTNESS_MAX);
    } else {
      pwm[0] = 0;
    }
    if (sound > thres1) {
      pwm[1] = map(sound, thres1, thres2, 0, BRIGHTNESS_MAX);
    } else {
      pwm[1] = 0;
    }
    if (sound > thres2) {
      pwm[2] = map(sound, thres2, thres3, 0, BRIGHTNESS_MAX);
    } else {
      pwm[2] = 0;
    }

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