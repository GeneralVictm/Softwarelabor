/**
 * @file   aufgabe2-pointer.c
 * @brief  Aufgabe2 - Pointermanipulationen
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// Falls notwendig erweitern Sie die Liste der includes

/**
   @brief Aufgabe2a: Scannen durch einen String
   @param [in] char* pattern
   @param [in] char* input
   @return char*

Input ist ein String der aus alphanumerischen Zeichen besteht die
durch :: getrennt sein koennen. Als Beispiele betrachte man

<p>

<ul>
  <li> "Ha::ll::o"
  <li> "47::11"
</ul>

Ihre Aufgabe ist es eine Funktion zu schreiben die den
laengsten suffix (Endung) liefert der kein :: enthaelt.
Laengste Endungen fuer unsere Beispiele:
<ul>
  <li> "o"
  <li> "11"
</ul>

<p>

Input ist der String (char pointer), das Ergebnis soll als
return Wert geliefert werden, welcher ein Zeiger auf den
Anfang der laengsten Endung ohne :: ist.

 */

char* extract(char* pattern, char* input) {
    int pat_length = strlen(pattern), length = strlen(input);
    char current[pat_length+1];
    current[pat_length] = '\0';
    char* output = input;

    for(int i = 0; i < length; i++) {
        if(strlen(input) < pat_length) {
            return output;
        }
        for(int j = 0; j < pat_length; j++) {
            current[j] = *(input+j);
        }
        if(strcmp(current, pattern) == 0) {
            output = input+pat_length;
        }
        input++;
    }

    return output; // Ihre Loesung
}

/**
   @brief Aufgabe2b: Variation von 2a
   @param [in] char* pattern
   @param [in] char* input
   @param [out] char** output

Das Ergebnis soll hier nicht als return Wert geliefert werden.
Anstatt wird ein pointer auf einen pointer verwendet.
Wieso reicht ein pointer nicht aus?
*/

void extract2(char* pattern, char* input, char** output) {
    int pat_length = strlen(pattern), length = strlen(input);
    char current[pat_length+1];
    current[pat_length] = '\0';
    *output = input;

    for(int i = 0; i < length; i++) {
        if(strlen(input) < pat_length) {
            return;
        }
        for(int j = 0; j < pat_length; j++) {
            current[j] = *(input+j);
        }
        if(strcmp(current, pattern) == 0) {
            *output = input+pat_length;
        }
        input++;
    }
}

/**
   @brief Aufgabe2c: Weitere Variation von Scannen
   @param [in] char* input
   @return int

Input ist ein String der aus einer Liste von alphanumerischen Woertern
die durch Leerzeichen (white-space) getrennt sind.
Ihre Aufgabe ist es eine Funktion zu schreiben, die die Anzahl der
Woerter zaehlt.
<p>
Beispiel:  "Ha ll o 5"
<p>
Soll liefern 4
*/

int count(char* input) {
    int count = 0;
    bool wasWS = true;

    while(*input != '\0') {
        if(*input == ' ') {
            wasWS = true;
        } else {
            if(wasWS) count++;
            wasWS = false;
        }
        input++;
    }

    return count; // Muss durch Ihre Loesung ersetzt werden
}


/**
   @brief Aufgabe2d: Aufsammeln von Woertern. Erweiterung von Aufgabe2c.
   @param [in] char* line
   @param [in] int maxwords
   @param [out] char* words[]
   @return int Anzahl aufgesammelter Woerter

Gegeben (als Input) ist ein String der aus einer Liste von alphanumerischen
Woertern die durch Leerzeichen (white-space) getrennt sind.
Ihre Aufgabe ist es die Woerter in einem Array von Strings aufzusammeln.
Das Array von Strings words wird pre-allokiert mit fester Groesse (maxwords).
Die Anzahl der aufgesammelten Woerter wird als return Wert zurueck
geliefert.

*/

int breakIntoWords(char* line, int maxwords, char* words[]) {
    char word[strlen(line)];
    int count = 0, index = 0, length = 0;
    bool wasWS = true;

    while(*line != '\0' && count < maxwords) {
        if(*line == ' ') {
            if(!wasWS && *word != '\0') {
                words[index] = malloc(strlen(word));
                strcpy(words[index], word);
                length = 0;
                index++;
            }
            wasWS = true;
        } else {
            if(wasWS) count++;
            word[length] = *line;
            length++;
            word[length] = '\0';
            wasWS = false;
        }
        line++;
    }

    if(length > 0 && *word != '\0') {
        words[index] = malloc(strlen(word));
        strcpy(words[index], word);
    }

    return count; // Ihre Loesung
}

// Kram zum Testen
typedef enum {
  OK,
  FAIL
} Test;

Test testCount(char* input, int expected) {
  Test t;

  if(expected == count(input)) {
    t = OK;
  }
  else {
    t = FAIL;
  }
  return t;
}

typedef struct {
  char* input;
  int expected;
} TestCase;


void runTests(int no, TestCase test[]) {
  Test t;
  int i;

  for(i=0; i < no; i++) {
    printf("Test %d: ", i);
    t = testCount(test[i].input, test[i].expected);
    if(OK == t)
      printf("OK \n");
    if(FAIL == t)
      printf("FAIL \n");
  }
}

Test testExtract(char* pattern, char* input, char* expected) {
  Test t;

  if(0 == strcmp(expected, extract(pattern, input))) {
    t = OK;
  }
  else {
    t = FAIL;
  }
  return t;
}

typedef struct {
    char* pattern;
    char* input;
    char* expected;
} TestCaseEx;


void runTestsEx(int no, TestCaseEx test[]) {
  Test t;
  int i;

  for(i=0; i < no; i++) {
    printf("Test %d: ", i);
    t = testExtract(test[i].pattern, test[i].input, test[i].expected);
    if(OK == t)
      printf("OK \n");
    if(FAIL == t)
      printf("FAIL \n");
  }
}


int main() {
    // Extract-Test
    printf("Teste extract-Methode:\n");
    const int testNumber = 6;
    TestCaseEx testsEx[6] = {
        {"", "", ""},
        {"::", "Ha::ll::o", "o"},
        {"::", "", ""},
        {"-", "-Ha-ll-o", "o"},
        {"bla", "Dies bla ist bla ein bla Test", " Test"},
        {"+", "+", ""}
    };

    runTestsEx(testNumber,testsEx);


    // Count-Tests
    printf("Teste count-Methode:\n");
    const int testNo = 9;
    TestCase tests[9] = {
        {"", 0},
        {"Hallo", 1},
        {"  Hallo", 1},
        {"Hallo", 1},
        {"  Hallo  ", 1},

        {"Hal lo", 2},
        {" Hal lo", 2},
        {"Hal lo ", 2},
        {" Hal lo  ", 2}
    };

    runTests(testNo,tests);


    // split string Test
    printf("Teste split-Methode:\n");
    char line[] = "this is a test";
    int nwords;
    char* words[10];

	nwords = breakIntoWords(line, 10, words);
	for(int i = 0; i < nwords; i++)
		printf("%s\n", words[i]);

    char anotherLine[] = "this is another test";
    char* otherWords[10];
    nwords = breakIntoWords(anotherLine, 10, otherWords);
	for(int i = 0; i < nwords; i++)
		printf("%s\n", otherWords[i]);

    return EXIT_SUCCESS;
}
