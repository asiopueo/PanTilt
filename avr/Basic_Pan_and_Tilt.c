#include <Servo.h>

#define ROTATE_PIN 9
#define TILT_PIN 10

// max,min up,down right,left are raw servo numbers 0-180
#define MAX_TILT_DOWN 140     // Remember this is a 0-180 scale (standard arduino servo numbers)
#define MAX_TILT_UP 60        // Remember this is a 0-180 scale (standard arduino servo numbers)
#define MAX_ROTATE_LEFT 20    // Remember this is a 0-180 scale (standard arduino servo numbers)
#define MAX_ROTATE_RIGHT 170  // Remember this is a 0-180 scale (standard arduino servo numbers)

#define TILT_CENTERED 40 // This is based on a 0-100 scale
#define ROTATE_CENTERED 49 // This is basedon a 0-100 scale

Servo rotateServo;
Servo tiltServo;

int tiltSteps;
int rotateSteps;

int tiltTimePerStep;
int rotateTimePerStep;

int rotatePos = ROTATE_CENTERED;
int tiltPos = TILT_CENTERED;

int remRotateGoTo = ROTATE_CENTERED;
int remTiltGoTo = TILT_CENTERED;

long remTiltTime;
long remRotateTime;

boolean headInPosition = false;

int rotate, tilt, time;


void setup()
{
    rotateServo.attach(ROTATE_PIN);
    tiltServo.attach(TILT_PIN);

    rotatePos = ROTATE_CENTERED;
    tiltPos = TILT_CENTERED;

    moveHeadNow(rotatePos, tiltPos);
    delay(1000);
}

void loop()
{
    randomHead();
}

void randomHead()
{
    rotate = random(1, 100);
    tilt = random(1, 100);
    time = random(250, 2000);

    rampHead(rotate, tilt, time);
    delay(random(100, 1000));
}
