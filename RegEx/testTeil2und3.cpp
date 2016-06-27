
// Testrahmen fuer 2. und 3. Teilaufgabe

#include <iostream>

using namespace std;

#include "FSA.h"
#include "RE.h"

#include "Transform.h"
#include "TestOrakel.h"

#include <iostream>
#include <string>

using namespace std;


// Systematischer Test

// Ein Testfall besteht aus einem regulaeren Ausdruck (RE)
// und einem Eingabestring.
// 
// Testorakel match ueberprueft ob string s enthalten in regex r.
// 
// closure und Tranformater RE -> NFA korrekt, falls Testorakel gleiches
// Ergebnis liefert wie Ausfuehrung des resultierenden NFA.

bool testClosureTransform(RE* r, string s) {
  NFA nfa = transform(r);
  FSA fsa(nfa);
  bool b1 = fsa.run(s);
  bool b2 = match(r,s);
  bool b = b1 == b2;

  cout << "Test case: " << r->pretty() << "   " << s << "\n";
  cout << "Test result: " << b << endl;
  cout << "match: " << b2 << endl;
  cout << "run: " << b1 << endl;

  return b;
}

int main() {

    RE* r3 = new Alt (new Phi(), new Ch('c'));
  
    testClosureTransform(r3, "ab");


    {
      RE* r = new Star (new Ch('a'));

      testClosureTransform(r, "");
      testClosureTransform(r, "a");
      testClosureTransform(r, "b");

    }

    {
      RE* r = new Star (new Conc(new Ch('a'), new Ch('b')));

      testClosureTransform(r, "");
      testClosureTransform(r, "ab");
      testClosureTransform(r, "abab");
      testClosureTransform(r, "b");

    }

    // TODO: mehr Tests

}
