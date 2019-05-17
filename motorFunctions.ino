/*
 * Raccolgo le funzioni relative al driver dei motori
 * Driver hardware: L9110
 * 
 */

//Definizione alias PIN controllo motore
//Motore sinistro
#define AIA 3
#define AIB 4
//Motore destro
#define BIA 5
#define BIB 6

/*
 * Rotazione motore sinistro:
 * 255: full speed CW(CCW)
 * 0:   stop
 * -255: full speed CCW(CW)
 */
void setLeftMotorSpeed(int motorSpeed){
  if (motorSpeed > 255) motorSpeed = 255;
  if (motorSpeed < -255) motorSpeed = -255;
  if(motorSpeed >= 0 ) {
    digitalWrite(AIB, LOW);
    analogWrite(AIA, abs(motorSpeed));
  }
  else {
    digitalWrite(AIA, LOW);
    analogWrite(AIB, abs(motorSpeed));
  }
}

/*
 * Rotazione motore destro:
 * 255: full speed CW(CCW)
 * 0:   stop
 * -255: full speed CCW(CW)
 */

void setRightMotorSpeed(int motorSpeed){
  if (motorSpeed > 255) motorSpeed = 255;
  if (motorSpeed < -255) motorSpeed = -255;
  if(motorSpeed >= 0 ) {
    digitalWrite(BIB, LOW);
    analogWrite(BIA, abs(motorSpeed));
  }
  else {
    digitalWrite(BIA, LOW);
    analogWrite(BIB, abs(motorSpeed));
  }
}

/*
 * Drivers initialization
 */

void initMotorsDriver(){
  digitalWrite(AIA, LOW); pinMode(AIA, OUTPUT); 
  digitalWrite(AIB, LOW); pinMode(AIB, OUTPUT); 
  digitalWrite(BIA, LOW); pinMode(BIA, OUTPUT); 
  digitalWrite(BIB, LOW); pinMode(BIB, OUTPUT); 
}

/*
 * Test dei motori: sommario
 */
void testMotors(){
  setRightMotorSpeed(64);
  setLeftMotorSpeed(64);
  delay(1000);
  setRightMotorSpeed(-64);
  setLeftMotorSpeed(-64);
  delay(1000);
  setRightMotorSpeed(0);
  setLeftMotorSpeed(0);
}
/*
 * Stabilisce i parametri ciematici del robot:
 * Velocità di traslazione  (-255 <= drift <= 255)
 * e di rotazione ((-255 <= rotation <= 255)
 * 
 */
void setBotMotion(int drift, int rotation){
  setRightMotorSpeed(drift+rotation);
  setLeftMotorSpeed(drift-rotation);
}



/*
 * Utilizza la lettura dell'accellerometro per stabilizzare
 * la rotazione
 */
void setBotMotionFB(int drift, int rotationReference){
  static int16_t error;
  int rotation;
  //rotation = -rotationReference + gyroRead();
  rotation = rotationReference - gyroRead();
  setRightMotorSpeed(drift+rotation);
  setLeftMotorSpeed(drift-rotation);
}

/*
 * Effettua una evoluzione di prova per testare la stabilizzazione
 * della rotazione
 */
void testLineMotion(){

  uint32_t mycounter = 0;
  int speedIteration = 0;

  while(speedIteration < 256){
    setBotMotionFB(speedIteration, 0);
    if(millis() - mycounter > 20){
      speedIteration++;
      mycounter = millis();
    } 
  }
  while(speedIteration > 0){
    setBotMotionFB(speedIteration, 0);
    if(millis() - mycounter > 5){
      speedIteration--;
      mycounter = millis();
    } 
  }
   while(speedIteration < 255){
    setBotMotionFB(-speedIteration, 0);
    if(millis() - mycounter > 20){
      speedIteration++;
      mycounter = millis();
    } 
  }
  while(speedIteration > 0){
    setBotMotionFB(-speedIteration, 0);
    if(millis() - mycounter > 5){
      speedIteration--;
      mycounter = millis();
    } 
  }  
  setBotMotion(0, 0);
}


/*
 * Da implementare !!!!!1
 */
void testCurve(){
  
}
