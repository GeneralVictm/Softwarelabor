// Main fuer Teilaufgabe 1
// Bitte weitere Testfaelle hinzufuegen.

#include "Transform.h"
#include <iostream>

using namespace std;

bool testExec(RE* r, string s) {
  NFA nfa = transform(r);
  FSA fsa(nfa);
  bool b1 = fsa.run(s);
  bool b2 = match(r,s);

  return b1 == b2;
}

int main()
{
    // phi + c
    RE* r3 = new Alt (new Phi(), new Ch('c'));

    // c + phi
    RE* r4 = new Alt (new Ch('c'), new Phi());

    cout << r3->pretty() << endl;

    cout << r3->simp()->pretty() << endl;

    // c**
    RE* r5 = new Star(new Star (new Ch('c')));

    cout << r5->pretty() << endl;
    cout << r5->simp()->pretty() << endl;

    // phi*
    RE* r6 = new Star(new Phi());

    cout << r6->pretty() << endl;
    cout << r6->simp()->pretty() << endl;

    // (phi + c) + c**
    RE* r7 = new Alt(r3,r5);

    cout << r7->pretty() << endl;
    // exhaustively apply simplifications
    cout << simpFix(r7)->pretty() << endl;

    RE* r8 = new Alt(r5,r7);

    cout << r8->pretty() << endl;
    cout << simpFix(r8)->pretty() << endl;

    // (c(a+b))
    RE* r = new Conc (new Ch('c'), new Alt(new Ch('a'), new Ch('b')));
    cout << r->pretty() << endl;

    // (ab)*
    RE * r1 = new Star(new Conc(new Ch('a'), new Ch('b')));

    string s1 = "abab";
    cout << testExec(r1,s1) << endl;

    string s2 = "ababa";
    cout << testExec(r1,s2) << endl;

    string s3 = "abc";
    cout << testExec(r1,s3) << endl;

    string s4 = "ca";
    cout << testExec(r,s4) << endl;

    string s5 = "cb"; //???
    cout << testExec(r,s5) << endl;

    string s6 = "cab";
    cout << testExec(r,s6) << endl;


    return 0;
}
