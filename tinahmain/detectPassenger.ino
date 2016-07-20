#define IR_THRESH 100
#define MAX_NOISE_AMP 10

int IRVal = 0;

void detectPassenger(){
  if (analogRead(IRLEFT)> IR_THRESH) {
    //passenger detected on the left
    //turn on a dime
    if(analogRead(IRLEFT)<IRVal){
      hardStop();
      IRVal = 0;
    } else {
      IRVal = analogRead(IRLEFT);
    }
    motor.speed(LMOTOR, -200);
    motor.speed(RMOTOR, 200);

  } else if (analogRead(IRRIGHT) > IR_THRESH) {
    if(analogRead(IRRIGHT)<IRVal){
      hardStop();
      IRVal = 0;
    } else {
      IRVal = analogRead(IRRIGHT);
    }
  }
  pickupPassenger();
}

void pickupPassenger() {
  adjustGripper();

  armExtend();
  if (digitalRead(GRIPPERCONTACT)) {
    gripperClose();
    armRaise();
  }
}

void adjustGripper(){
  int armServo = 0;
  int maxArmServo = 180;
  int armShoulder = analogRead(ARM1);
  int armElbow = analogRead(ARM2);
  int gripIR = analogRead(GRIPPERIR);

  int prevLoIR, prevHiIR;
  int servoSpeed = 5;
  int motorSpeed = 50;

  do {
    RCServo2.write(armServo);
    armServo += servoSpeed;
    if (armServo > maxArmServo)
      break;

    prevLoIR = gripIR - MAX_NOISE_AMP;
    prevHiIR = gripIR + MAX_NOISE_AMP;
    gripIR = analogRead(GRIPPERIR);
  } while (gripIR > prevLoIR && gripIR < prevHiIR);
}

void adjustChassis(int overShoot) {
  int gripIR = analogRead(GRIPPERIR);
  int prevLoIR, prevHiIR;

  int motorSpeed = 50;
  if (overShoot)
    motorSpeed = -50;

  do {
    motor.speed(LMOTOR, motorSpeed);
    motor.speed(RMOTOR, motorSpeed);

    prevLoIR = gripIR - MAX_NOISE_AMP;
    prevHiIR = gripIR + MAX_NOISE_AMP;
    gripIR = analogRead(GRIPPERIR);
  } while (gripIR > prevLoIR && gripIR < prevHiIR);

  hardStop();
}