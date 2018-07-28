
// #1
// This routine camps here until move is done
//
// rotateGoTo: Final rotate position
// tiltGoTo: Final tilt position
// howLong: Total time of movement in milliseconds 
// (Position is 0-100 scale)
void rampHead(int rotateGoTo, int tiltGoTo, int howLong)  
{
    tiltSteps = tiltPos - tiltGoTo; // Total number of steps
    rotateSteps = rotatePos - rotateGoTo; // Total number of steps
    tiltTimePerStep = howLong/abs(tiltSteps); // How many milliseconds per step
    rotateTimePerStep = howLong/abs(rotateSteps);  // How many milliseconds per step
    remTiltTime = millis(); // Reset our "clock"
    remRotateTime = millis();  // Reset our "clock"

    while (rotatePos != rotateGoTo || tiltPos != tiltGoTo) // Wait until both servos are in position
    {
        // This is the same as the "blink without delay" Aduino example
        if(millis() >= remRotateTime + rotateTimePerStep && rotatePos != rotateGoTo)
        {
            if (rotateSteps < 0) // Determine which way we are moving the servo
            {
                rotatePos++;
            }
        else
        {
            rotatePos--;
        }

        int tempRotate = map(rotatePos, 0, 100, MAX_ROTATE_LEFT, MAX_ROTATE_RIGHT); // Convert from our 0-100 scale to servo min/max as defined in constants
        tempRotate = constrain(tempRotate, MAX_ROTATE_LEFT, MAX_ROTATE_RIGHT); // Protect against overflows and bad math
        rotateServo.write(tempRotate); // Move the servo
        remRotateTime = millis();  // Reset our "clock"
    }

        if(millis() >= remTiltTime + tiltTimePerStep && tiltPos != tiltGoTo) // This is the same as the "blink without delay" Aduino example
        {
            if (tiltSteps < 0) // Determine which way we are moving the servo
            {
                tiltPos++;
            }
            else
            {
                tiltPos--;
            }
          
            int tempTilt = map(tiltPos,0,100,MAX_TILT_DOWN,MAX_TILT_UP); // Convert from our 0-100 scale to servo min/max as defined in constants
            tempTilt = constrain(tempTilt, MAX_TILT_UP, MAX_TILT_DOWN);  // Protect against overflows and bad math
            tiltServo.write(tempTilt); // Move the servo
            remTiltTime = millis(); // Reset our "clock"
        }
    }

    headInPosition = true; // We have left the "while" loop --we are done, head is in position, set the "we are done" flag to true
}


// #2
// rotateGoTo: Final rotate position
// tiltGoTo: Final tilt position
// (Position is 0-100 scale)
void moveHeadNow(int rotateGoTo, int tiltGoTo)
{
    int tempRotate = map(rotateGoTo, 0, 100, MAX_ROTATE_LEFT, MAX_ROTATE_RIGHT); // Convert from our 0-100 scale to servo min/max as defined in constants
    tempRotate = constrain(tempRotate, MAX_ROTATE_LEFT, MAX_ROTATE_RIGHT); // Protect against overflows and bad math
    rotateServo.write(tempRotate); // Move the servo
    rotatePos = rotateGoTo;
    int tempTilt = map(tiltGoTo, 0, 100, MAX_TILT_DOWN, MAX_TILT_UP); // Convert from our 0-100 scale to servo min/max as defined in constants
    tempTilt = constrain(tempTilt, MAX_TILT_UP, MAX_TILT_DOWN); // Protect against overflows and bad math
    tiltServo.write(tempTilt); // Move the servo
    tiltPos = tiltGoTo;
    headInPosition = true; // We are done, head is in position, set the "we are done" flag to true
}

// #3
// You must keep calling on this routine to keep your servos stepping to where you want them to go 
// --> boolean headInPosition becomes true when move is done
// rotateGoTo: final rotate position
// tiltGoTo: final tilt position
// howLong: total move time in milliseconds (Position is 0-100 scale!)
// (Position is 0-100 scale)
void rampHeadStep(int rotateGoTo, int tiltGoTo, int howLong)
{

    if (remRotateGoTo != rotateGoTo || remTiltGoTo != tiltGoTo) // Goto got changed, prep for new move
    {
        remRotateGoTo = rotateGoTo;   // Remember current goto move
        remTiltGoTo = tiltGoTo;       // Remember current goto move

        headInPosition = false;       // Clear "we are done" flag

        tiltSteps = tiltPos - tiltGoTo;       // Total number of steps
        rotateSteps = rotatePos - rotateGoTo; // Total number of steps

        tiltTimePerStep = howLong / abs(tiltSteps); // Milliseconds per step
        rotateTimePerStep = howLong / abs(rotateSteps);  // Milliseconds per step

        remTiltTime = millis();       // Reset our "clock"
        remRotateTime = millis();      // Reset our "clock"
    }

    if(rotatePos == rotateGoTo && tiltPos == tiltGoTo) // We got to where we were going. Set the "we are done" flag
    {
        headInPosition = true; // Your main loop code could watch for this flag to change to know the head is done moving
    }

    if (rotatePos != rotateGoTo) // If current position does not = where we want to go
    {
        if(millis() >= remRotateTime + rotateTimePerStep && rotatePos != rotateGoTo) // This is the same as the "blink without delay" Aduino example
        {
            if (rotateSteps < 0) // Which way are we moving the servo?
            {
                rotatePos++;
            }
            else
            {
                rotatePos--;
            }
            int tempRotate = map(rotatePos, 0, 100, MAX_ROTATE_LEFT, MAX_ROTATE_RIGHT); // Convert from our 0-100 scale to servo min/max as defined in constants
            tempRotate = constrain(tempRotate, MAX_ROTATE_LEFT, MAX_ROTATE_RIGHT); // Protect against overflows and bad math
            rotateServo.write(tempRotate); // Move the servo
            remRotateTime = millis(); // Reset our "clock"
        }
    }
    if (tiltPos != tiltGoTo) // If current position does not = where we want to go
    {
        if(millis() >= remTiltTime + tiltTimePerStep && tiltPos != tiltGoTo)  // This is the same as the "blink without delay" Aduino example
        {
            if (tiltSteps<0) // Which way are we moving the servo?
            {
                tiltPos++;
            }
            else
            {
                tiltPos--;
            }

            int tempTilt = map(tiltPos, 0, 100, MAX_TILT_DOWN, MAX_TILT_UP); // Convert from our 0-100 scale to servo min/max as defined in constants
            tempTilt = constrain(tempTilt, MAX_TILT_UP, MAX_TILT_DOWN); // Protect against overflows and bad math
            tiltServo.write(tempTilt); // Move the servo
            remTiltTime = millis();   // Reset our "clock"
        }
    }
}
