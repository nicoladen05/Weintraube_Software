#define DIR_PIN 12
#define STEP_PIN 13

#define JOYX_PIN A0
#define JOYY_PIN A1
#define JOY_CLICK_PIN 7

#define TOUCH_SENSOR_PIN 5

#define BUZZER_PIN 2

int step_number = 0;
int step_count = 0;
bool count = false;
int joyX;
int joyY;
int step_delay;

int joyClick;

int measurement_state = 0;
int up_step_count = 0;


void setup() {
pinMode(DIR_PIN, OUTPUT);
pinMode(STEP_PIN, OUTPUT);
    
pinMode(JOY_CLICK_PIN, INPUT_PULLUP);

pinMode(TOUCH_SENSOR_PIN, INPUT_PULLUP);

pinMode(BUZZER_PIN, OUTPUT);

Serial.begin(9600);

beep(50, 3);
beep(50, 2);
beep(50, 1);
}

void loop() {
    Serial.println(measurement_state);
    
    joyX = analogRead(JOYX_PIN);
    joyY = analogRead(JOYY_PIN);
    joyClick = digitalRead(JOY_CLICK_PIN);

    if (joyX >= 510) { //stick down
        digitalWrite(DIR_PIN, LOW);
        digitalWrite(STEP_PIN, HIGH);
        digitalWrite(STEP_PIN, LOW);
    }

    if (joyX <= 500) { //stick up
        digitalWrite(DIR_PIN, HIGH);
        digitalWrite(STEP_PIN, HIGH);
        digitalWrite(STEP_PIN, LOW);
    }

    if (joyClick == LOW) {
        // start the measurement
        measurement_state = 1;
        beep(50,3);
    }

    //push upward
    if (measurement_state == 1) {
        beep(50,2);
        digitalWrite(DIR_PIN, HIGH);
        digitalWrite(STEP_PIN, HIGH);
        digitalWrite(STEP_PIN, LOW);

        up_step_count++;

        //stop once up_step_count reaches 500
        if (up_step_count == 500) {
            measurement_state = 2;
            beep(50, 1);
            delay(50);
            beep(50, 1);
            step_count = 0;
        }
    }

    //move downwards until TOUCH_SENSOR_PIN reads HIGH
    if (measurement_state == 2) {
        digitalWrite(DIR_PIN, LOW);
        digitalWrite(STEP_PIN, HIGH);
        digitalWrite(STEP_PIN, LOW);

        step_count++;

        if (digitalRead(TOUCH_SENSOR_PIN) == HIGH) {
            beep(200, 1);
            measurement_state = 3;

        }
    }

    //print out result
    if (measurement_state == 3);
        Serial.println("Distance measured: ");
        Serial.print(step_count);
        measurement_state = 0;   
}


void OneStep(bool dir){
    if (dir == true) {
        digitalWrite(DIR_PIN, HIGH);
        digitalWrite(STEP_PIN, HIGH);
        delay(1);
        digitalWrite(STEP_PIN, LOW);
        digitalWrite(DIR_PIN, LOW);
    }
    else {
        digitalWrite(DIR_PIN, LOW);
        digitalWrite(STEP_PIN, HIGH);
        delay(1);
        digitalWrite(STEP_PIN, LOW);
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


