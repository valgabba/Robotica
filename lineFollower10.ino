/*
 * Template per programma segui linea di base.
 * Il progetto suddivide il codice in più files.
 * Il modello di programmazione è procedurale (per funzioni)
 * Le funzioni sono raggruppate in file separati.
 * Per interpretare correttamente lo scope ed il life time delle variabili
 * bisogna ricordare che in arduino IDE, all'atto della compilazione viene fatto un mescolone e
 * compilato un singolo file sorgente.
 * Per il lavoro di gruppo e' necessario acquisire uno stile di programmazione il più possibile ordinato e codificato
 * 
 * Versione 1.0
 *
 */

#include <NewPing.h>
#define pippo 2

#define __VERSION__   "1.0"
#define TRIGGER_PIN   12 // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN      13 // Arduino pin tied to echo pin on ping sensor.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.
#define OBSTACLE_DISTANCE 20

#define SAMPLING_TIME 100
#define KP 10
#define SPEED 80

NewPing sonarSensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

unsigned long debugPrintTimeMarker, cycleStartTime, obstacleDistance, cycleTime;
int lineThreshold[]={512,512,512,512,512};
int rawLineVector[5], equalizedLineVector[5], rawLineVectorMax[5], rawLineVectorMin[5];
int bLineVector[5];

Stream *debugStream;

/************************* SETUP ***************************/
void setup() {
  Serial.begin(115200);
  debugStream = &Serial;
  String hello = "Version "+ String(__VERSION__) + "Compilation date: " + String(__DATE__) + "   "+String(__TIME__);
  debugStream->println(hello);
  delay(2000);
  //Inizilizzo il canale bluetooth
  btInit();
  //Inizializzo il giroscopio
  gyroSetup();
  //Inizializzo i drivers dei motori
  initMotorsDriver();
  //Testo il giroscopio
  //testLineMotion();
}
/************************* SETUP ***************************/

int angleError;

/************************* MAIN ***************************/
void loop() {
  //btEcho();
  //Misuro il tempo impiegato a fare un ciclo ,non è necessario.....giusto per avere un'idea
  cycleTime = millis() - cycleStartTime;
  cycleStartTime = millis();
  //Questa funziona ritarda il ciclo per il tempo necessario a fare la misura (quanto ?)
  //obstacleDistance = sonarSensor.ping_cm();
  //Questa funziona acuisisce 5 misure a fa la mediana (ancora + ritardo)
  //obstacleDistance = sonarSensor.convert_cm(sonarSensor.ping_median(10));
  //Leggo il sensore di linea
  readLine();
  breadLine();
  //angleError = map(sampleLineError(), -2048, 2048, -255,255);
  //setBotMotion(SPEED, -KP*angleError );
  //setBotMotionFB(SPEED, 200 );


  if(!bLineVector[1] && bLineVector[2] && !bLineVector[3]) setBotMotion(SPEED,0);
  else if(!bLineVector[1] && !bLineVector[2] && bLineVector[3]) setBotMotion(0,-100);
  else if(bLineVector[1] && !bLineVector[2] && !bLineVector[3]) setBotMotion(0,+100);
  else setBotMotion(SPEED,0);


 
  if(cycleStartTime > debugPrintTimeMarker + 100){
    /*
    Serial.print("Tempo di ciclo (ms): ");
    Serial.print(cycleTime);
    Serial.print(" Distanza (cm): ");
    Serial.println(obstacleDistance);
    Serial.print(" mediana (cm): ");
    Serial.println(median(obstacleDistance));
    */
    printLineVector (rawLineVector);
    printLineVector (bLineVector);
    debugPrintTimeMarker = cycleStartTime;
    //debugStream->println(gyroRead());
  }
}
/************************* MAIN ***************************/
