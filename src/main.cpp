#include <Arduino.h>

const int BLINK_ON_TIME = 2000;
const int MIN_WAIT_TIME = 5000;
const long ADDED_WAIT_TIME = 7000;
int led_pins[] = {10, 11, 12};
int led_output_one = 10;
int led_output_two = 11;
int led_output_three = 12;
int kip_input_pin_one = 2;
int kip_input_pin_two = 3;
int kip_input_pin_three = 4;
int blinking_mode = 0;

void testLEDs(int arr[], int arr_size) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < (arr_size - 1); j++) {
      digitalWrite(arr[j], HIGH);
    }
    delay(200);
    for (int j = 0; j < (arr_size - 1); j++) {
      digitalWrite(arr[j], LOW);
    }
    delay(200);
  }
}

int get_blinking_mode() {
  return digitalRead(kip_input_pin_three) +
         (digitalRead(kip_input_pin_two) << 1) +
         (digitalRead(kip_input_pin_one) << 2);
}

void blink_led(long wait_time, int output_pin, int blink_on_time = 0) {
  if (blink_on_time == 0) {
    blink_on_time = BLINK_ON_TIME;
  }
  digitalWrite(output_pin, HIGH);
  delay(blink_on_time);
  digitalWrite(output_pin, LOW);
  delay(wait_time);
}

void blink_leds(long wait_time, int random_value) {
  if (random_value < 13) {
    blink_led(wait_time, random_value);
    return;
  }

  if (random_value == 13) {
    digitalWrite(led_output_one, HIGH);
    digitalWrite(led_output_two, HIGH);
    delay(BLINK_ON_TIME);
    digitalWrite(led_output_one, LOW);
    digitalWrite(led_output_two, LOW);
    delay(wait_time);
    return;
  }

  digitalWrite(led_output_two, HIGH);
  digitalWrite(led_output_three, HIGH);
  delay(BLINK_ON_TIME);
  digitalWrite(led_output_two, LOW);
  digitalWrite(led_output_three, LOW);
  delay(wait_time);
}

void setup() {
  Serial.begin(9600);
  pinMode(led_output_one, OUTPUT);
  pinMode(led_output_two, OUTPUT);
  pinMode(led_output_three, OUTPUT);
  pinMode(kip_input_pin_one, INPUT);
  pinMode(kip_input_pin_two, INPUT);
  pinMode(kip_input_pin_three, INPUT);
  randomSeed(analogRead(0));
  testLEDs(led_pins, sizeof(led_pins));
}

void loop() {
  blinking_mode = get_blinking_mode();
  Serial.println(blinking_mode);
  long wait_time = random(1, ADDED_WAIT_TIME) + MIN_WAIT_TIME;
  int output_pin = led_output_one;
  int random_value = 0;

  switch (blinking_mode) {
  case 0:
    blink_led(wait_time, output_pin);
    break;
  case 1:
    random_value = random(0, 2) + output_pin;
    blink_led(wait_time, random_value);
    break;
  case 2:
    random_value = random(0, 3) + output_pin;
    blink_led(wait_time, random_value);
    break;
  case 3:
    random_value = random(0, 5) + output_pin;
    blink_leds(wait_time, random_value);
    break;
  case 4:
    random_value = random(0, 3) + output_pin;
    blink_led(500, random_value, 500);
    break;
  case 5:
    random_value = random(0, 3) + output_pin;
    blink_led(200, random_value, 200);
    break;
  default:
    random_value = random(0, 3) + output_pin;
    blink_led(wait_time, random_value);
    break;
  }
}
