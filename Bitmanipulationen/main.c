/**
 * @file   main.c
 * @brief  Aufgabe1 - Bit Manipulationen
 */

#include <stdio.h>
#include <stdlib.h>
// Falls notwendig erweitern Sie die Liste der includes


/**
   @brief Aufgabe1a: Vertauschen von Bytes
   @param [in] short int i
   @return short int

Schreiben Sie eine Funktion die das Low Byte (Bits 0-7) und
das High Byte (Bits 8-15) vertauscht.
Z.B. aus der Zahl 0x4020 wird die Zahl 0x2040.
*/

short int switchLowHighByte(short int i) {
    // funktioniert nur mit positiven Zahlen, mehr war aber auch nicht gefordert?
    unsigned short int highByte, lowByte, input;
    input = i;

    highByte = input & 0xFF00;
    lowByte = input & 0x00FF;

    highByte = highByte >> 8;
    lowByte = lowByte << 8;

    return highByte | lowByte;
}


typedef enum {
  Stop = 0,
  Start = 1,
  Finish = 5,
  Fail = 255
} Status;


typedef enum {
  One = 1,
  Fifteen = 15,
  Last = 255
} Numbers;

/**
   @brief Aufgabe1b: Serialisierung von Datenstrukturen
   @param [in] Status s
   @param [in] Numbers n
   @param [out] short int* data

Gegeben sind zwei enums. Ihre Aufgabe ist es jeweils Werte der
beiden enums in ein Datenpacket der Groesse 16Bit zu packen (serialisieren).
Werte des enums Status sollen dabei in das Low Byte und Werte
des enums Numbers sollen in das High Byte gepackt werden.
*/


void serialize(Status s, Numbers n, short int* data) {
    unsigned short int lowByte, highByte;

    lowByte = s;
    highByte = n << 8;

    *data = lowByte | highByte;
}

/**
   @brief Aufgabe1c: Deserialisierung von Datenstrukturen
   @param [in] short int data
   @param [out] Status* s
   @param [out] Numbers* n

Schreiben Sie eine Funktion die Werte der enums Status und Number
aus einem 16Bit Wert entpackt (deserialisiert).
Wir nehmen an, dass die enum Werte mittels der serialize Funktion
verpackt wurden.
*/

void deserialize(short int data, Status* s, Numbers* n) {
    unsigned short int input;
    input = data;

    *s = input & 0x00FF;
    *n = (input & 0xFF00) >> 8;
}


enum TestEnum {
  OK,
  FAIL
};
typedef enum TestEnum Test;

Test testLowHigh(short int i) {
  Test t;
  if(i == switchLowHighByte(switchLowHighByte(i)))
    t = OK;
  else
    t = FAIL;

  return t;
}

Test testSD(Status s, Numbers n) {
 Test t;
 short int data;
 Status s2;
 Numbers n2;

 // Test execution
 serialize(s, n, &data);
 deserialize(data, &s2, &n2);

 if(s2 == s && n2 == n) {
    t = OK;
 }
 else {
    t = FAIL;
 }
 return t;
}

int main() {
    // Test für Switch
    short int zahl = 0x2040;
    printf("Eingabe: %x \n", zahl);
    zahl = switchLowHighByte(zahl);
    printf("Ausgabe der Switch-Funktion: %x \n", zahl);
    printf("Teste nun, ob die Zahl korrekt zum Ursprung gewandelt wird, wenn man die Funktion doppelt ausfuehrt.\n");
    Test t = testLowHigh(zahl);
    if (t == OK) {
        printf("Test erfolgreich!\n");
    }
    else if (t == FAIL) {
        printf("Test nicht erfolgreich!\n");
    }

    // Test für Serialisierung
    Status s = Finish;
    Numbers n = Fifteen;
    printf("Teste Serialisierung mit Status %d und Number %d \n", s, n);
    Test t1 = testSD(s, n);
    if (t1 == OK) {
        printf("Test erfolgreich!\n");
    }
    else if (t1 == FAIL) {
        printf("Test nicht erfolgreich!\n");
    }
    Status s1 = Fail;
    Numbers n1 = Last;
    printf("Teste Serialisierung mit Status %d und Number %d \n", s1, n1);
    Test t2 = testSD(s1, n1);
    if (t2 == OK) {
        printf("Test erfolgreich!\n");
    }
    else if (t2 == FAIL) {
        printf("Test nicht erfolgreich!\n");
    }

    return 0;
}
