/*
 * Raccolgo le funzioni relative al sensore di linea
 * ATTENZIONE: indipendentemente dall'algoritmo seguilinea utilizzato è essenziale che la 
 * risposta dei sensori sia equalizzata.
 * 
 */


/*
 *  Legge il valore istantaneo dei sensori ottici
 *  Memorizza il valore in una vettore globale.
 *  1023 -> bianco
 *  0 -> nero
 */
void readLine(){
  rawLineVector[0] = analogRead(A0);
  rawLineVector[1] = analogRead(A1);
  rawLineVector[2] = analogRead(A2);
  rawLineVector[3] = analogRead(A3);
  rawLineVector[4] = analogRead(A4);
}

void breadLine(){
  if (analogRead(A0) < lineThreshold[0]) bLineVector[0] = true;
  else bLineVector[0] = false;
  if (analogRead(A1) < lineThreshold[1]) bLineVector[1] = true;
  else bLineVector[1] = false;
  if (analogRead(A2) < lineThreshold[0]) bLineVector[2] = true;
  else bLineVector[2] = false;
  if (analogRead(A3) < lineThreshold[0]) bLineVector[3] = true;
  else bLineVector[3] = false;
  if (analogRead(A4) < lineThreshold[0]) bLineVector[4] = true;
  else bLineVector[4] = false;  
}
/*
 * Funzione peso dei sensori
 */
int sampleLineError(){
  return (1023-analogRead(A0)) * 2 + (1023-analogRead(A1)) - (1023-analogRead(A3)) - 2 * (1023-analogRead(A4));
}

/*
 * Stampa i valori del vettore che memorizza l'ultimo campione
 * dei sensori di linea.
 * Utile in fase di taratura o di debugging.
 * OPS.....utilizzo il puntatore......
 */
void printLineVector (int *lineVector ){
  String outstring = String(lineVector[0])+","
                     +String(lineVector[1])+","
                     +String(lineVector[2])+","
                     +String(lineVector[3])+","
                     +String(lineVector[4]);
  debugStream->println(outstring);
}

/*
 * Under construction
 */

void lineSensorsCal(){
  Serial.println("Inizio procedura di calibrazione");
}

/*
 * Conversione ad 1 bit
 */
bool onebitADC(int threshold, int value){
  if(value > threshold) return true;
  return false;
}
