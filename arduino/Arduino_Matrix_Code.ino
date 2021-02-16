 /*
Matrix: 
A simple pressure sensor matrix made from two sheets of spandex with conductive threads sewed into the halves
and a piece of Velostat or Eeonyx piezoresistive material in between.

parsing through this grid by switching individual rows/columns to be
HIGH, LOW or INPUT (high impedance) to detect location and pressure.
>> http://howtogetwhatyouwant.at/
*/

// This entire process can be expanded to fit a bigger matrix

#define numRows 3
#define numCols 3
#define sensorPoints numRows*numCols

int rows[] = {A0, A1, A2};  // connection points on the teensy LC board 
int cols[] = {11,10,9};     // connection points on the teensy LC board
int incomingValues[sensorPoints] = {};
int incomingval = 0;
int count = 0;
int thresh = 0;
int S0 = 0;
int S1 = 0;
int S2 = 0;
int S3 = 0;
int S4 = 0;
int S5 = 0;
int S6 = 0;
int S7 = 0;
int S8 = 0;
int wait = 1000;

void setup() {
// set all rows and columns to INPUT (high impedance):
  for (int i = 0; i < numRows; i++) { 
    pinMode(rows[i], INPUT_PULLUP); 
    } 
  for (int i = 0; i < numCols; i++) { 
    pinMode(cols[i], INPUT); 
    } 
  thresh = startline();
  Serial.begin(115200); 
} 


int startline() {
  while (count < wait) {
    for (int colCount = 0; colCount < numCols; colCount++) { 
    pinMode(cols[colCount], OUTPUT); // set as OUTPUT 
    digitalWrite(cols[colCount], LOW); // set LOW 
    for (int rowCount = 0; rowCount < numRows; rowCount++) { 
      incomingValues[colCount * numRows + rowCount] = analogRead(rows[rowCount]); // read INPUT 
      }// end rowCount 
    pinMode(cols[colCount], INPUT); // set back to INPUT! 
    }// end colCount 
 
    for (int i = 0; i < sensorPoints; i++) { 
      incomingval = incomingValues[i];
      if (i == 0){
        S0 = S0 + incomingValues[i];
      }
      else if (i == 1){
        S1 = S1+ incomingValues[i];
      }
      else if (i == 2){
        S2 = S2 + incomingValues[i];
      }
      else if (i == 3){
        S3 = S3+ incomingValues[i];
      }
      else if (i == 4){
        S4 = S4 + incomingValues[i];
      }
      else if (i == 5){
        S5 = S5+ incomingValues[i];
      }
      else if (i == 6){
        S6 = S6+ incomingValues[i];
      }
      else if (i == 7){
        S7 = S7+ incomingValues[i];
      }
      else if (i == 8){
        S8 = S8+ incomingValues[i];
      }
      Serial.print(incomingval); 
      if (i < sensorPoints - 1) {
        Serial.print(","); 
      } 
    }
  Serial.println(); 
  delay(10); 
  count = count + 1;
  }
  thresh = ((S0/wait) + (S1/wait) + (S2/wait) + (S3/wait) + (S4/wait) + (S5/wait) + (S6/wait) + (S7/wait) + (S8/wait))/9;
  delay(100);
}


void loop() { 
  for (int colCount = 0; colCount < numCols; colCount++) { 
    pinMode(cols[colCount], OUTPUT); // set as OUTPUT 
    digitalWrite(cols[colCount], LOW); // set LOW 
    for (int rowCount = 0; rowCount < numRows; rowCount++) { 
      incomingValues[colCount * numRows + rowCount] = analogRead(rows[rowCount]); // read INPUT 
      }// end rowCount 
    pinMode(cols[colCount], INPUT); // set back to INPUT! 
    }// end colCount 

    //Serial.print("test");
    //Serial.print(sensorPoints);
    // Print the incoming values of the grid: 
    for (int i = 0; i < sensorPoints; i++) { 
      incomingval = incomingValues[i]-thresh;
      Serial.print(abs(incomingval)); 
      // Serial.print(i);
      if (i < sensorPoints - 1) {
        Serial.print(","); 
      } 
    }
  Serial.println(); 
  delay(10); 
}
