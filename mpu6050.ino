/*
 * Funzioni relative alla getione dell'accellerometro
 * MPU6050 in modalità semplice.
 * 
 * 
 */
#include "I2Cdev.h"
#include "MPU6050.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 gyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

/*
 * Inizializza il sensore
 */
void gyroSetup(){
      // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
        // initialize device
    debugStream->println("Initializing I2C devices...");
    gyro.initialize();
    gyro.setZGyroOffset (6);
    // verify connection
    debugStream->println("Testing device connections...");
    debugStream->println(gyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

/*
 * 
 * 
 * Legge il giroscopio (asse Z) ed applica il filtro a media mobile
 * 
 */
#define FILTER_TAPS 10
int16_t gyroRead(){
  int16_t gx,gy,gz;
  static int16_t buffer[FILTER_TAPS];
  static int bufferPointer = 0;
  int32_t somma = 0;
  
  gyro.getRotation(&gx, &gy, &gz);
  buffer[bufferPointer] = (gz/64);
  bufferPointer = (bufferPointer+1) % FILTER_TAPS;
  for(int i= 0 ; i < FILTER_TAPS; i++){
    somma += buffer[i];
  }
  return somma/FILTER_TAPS;
}
