// Main fuer Teilaufgabe 1
// Bitte weitere Testfaelle hinzufuegen.

#include "Transform.h"
#include <iostream>

using namespace std;

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

    // (c(a+b))
    RE* r = new Conc (new Ch('c'), new Alt(new Ch('a'), new Ch('b')));
    cout << r->pretty() << endl;


    return 0;
}
