/*
 * Raccolgo le funzioni e le macro utili
 * 
 */
#define max(a,b) (a>b?a:b)
#define min(a,b) (a>b?b:a)
/*
 * 
 * Calcola la media mobile (filtro)
 * Può servire per ridurre l'entità del rumore
 * (variazioni veloci e casuali del valore letto)
 * 
 */

 int mediaBuffer[]={0,0,0,0,0}, mediaBufferPointer = 0;

 int movingAverage(int sampleInput){
    int somma = 0;
    mediaBuffer[mediaBufferPointer] = sampleInput;
    mediaBufferPointer++;
    mediaBufferPointer %= 5;

    for(int i = 0 ; i < 5 ; i++){
      somma += mediaBuffer[i];
    }
    return (somma / 5);
 }


 
