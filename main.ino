#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12

#define JOYX_PIN A0
#define JOYY_PIN A1
#define JOY_CLICK_PIN 7

#define BUZZER_PIN 2

#define VOLT_PIN A2

int step_number = 0;
int step_count = 0;
bool count = false;
int joyX;
int joyY;
int step_delay;

int joyClick;


void setup() {
pinMode(STEPPER_PIN_1, OUTPUT);
pinMode(STEPPER_PIN_2, OUTPUT);
pinMode(STEPPER_PIN_3, OUTPUT);
pinMode(STEPPER_PIN_4, OUTPUT);

pinMode(JOY_CLICK_PIN, INPUT_PULLUP);

pinMode(BUZZER_PIN, OUTPUT);

Serial.begin(9600);

beep(50, 3);
beep(50, 2);
beep(50, 1);
}

void loop() {
    joyX = analogRead(JOYX_PIN);
    joyY = analogRead(JOYY_PIN);
    joyClick = digitalRead(JOY_CLICK_PIN);

    if (joyX >= 510) { //stick down
        step_delay = map(joyX, 510, 1023, 50, 2);

        OneStep(false);
        delay(step_delay);
        step_count++;
    }

    if (joyX <= 500) { //stick up
        step_delay = map(joyX, 500, 0, 50, 2);

        OneStep(true);
        delay(step_delay);
    }

    if (joyClick == LOW) {
        if (count) {
            beep(50, 1);
            Serial.print("Steps counted: ");
            Serial.println(step_count);
            delay(50);
            count = false;

        }
        else {
            beep(50, 2);
            step_count = 0; 
            count = true;
            delay(50);
        }
    }

}


void OneStep(bool dir){

  int set1[4]={HIGH,LOW,LOW,LOW};
  int set2[4]={LOW,HIGH,LOW,LOW};
  int set3[4]={LOW,LOW,HIGH,LOW};
  int set4[4]={LOW,LOW,LOW,HIGH};

  if (dir){
  digitalWrite(STEPPER_PIN_1, set1[step_number]);
  digitalWrite(STEPPER_PIN_2, set2[step_number]);
  digitalWrite(STEPPER_PIN_3, set3[step_number]);
  digitalWrite(STEPPER_PIN_4, set4[step_number]);
  }

  else {
  digitalWrite(STEPPER_PIN_1, set4[step_number]);
  digitalWrite(STEPPER_PIN_2, set3[step_number]);
  digitalWrite(STEPPER_PIN_3, set2[step_number]);
  digitalWrite(STEPPER_PIN_4, set1[step_number]);
  }
  
step_number++;
  if(step_number > 3){
    step_number = 0;
  }
}

void beep(int length, int pitch) {
    for (int i = 0; i < length; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(1);
        digitalWrite(BUZZER_PIN, LOW);
        delay(pitch);
    }
}


