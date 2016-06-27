
// Ein moeglicher Rahmen fuer Aufgabe 4, zweite Teilaufgabe,
// uebersetze regulaeren Ausdruck in einen NFA.
// Der Einfachheit in ein .h File gepackt.


#include <iostream>

using namespace std;

#include "FSA.h"
#include "RE.h"


int nameSupply;

void init() {
  nameSupply = 0;
}

int fresh() {
  return nameSupply++;
}


// Macht die eigentliche Arbeit
NFA transformWorker(RE *r);

// Schnittstelle fuer Benutzer
// Ruecksetzen des "name supplies" zur Generierung von eindeutigen Zustaenden
// Aufruf von transform2
NFA transform(RE *r) {
  init();
  return transformWorker(r);
}


// Wir liefern einen NFA zurueck mit genau einem Start und
// genau einem Stop(end)zustand.
NFA transformWorker(RE *r) {
  vector<Transition> ts;
  int start, stop;

  switch(r->ofType()) {

  case EpsType: // TODO
  case ChType: // TODO
  case StarType: // TODO
  case ConcType: // TODO

  // Phi: Akzeptiert kein Wort
  // NFA besteht aus einem Start und Stopzustand und *keiner* Transition
  case PhiType: 
    start = fresh();
    stop = fresh();
    return NFA(ts, start, stop);

  case AltType: {
     Alt* r2 = (Alt*) r;

     // 1. Baue NFAs der linken und rechten Alternative
     NFA n1 = transformWorker(r2->getLeft());
     NFA n2 = transformWorker(r2->getRight());

     // 2. Generieren neuen Start-/Stopzustand.
     //    Sammle Start-/Stopzustaende von n1 und n2
     // N.B. Annahme: finals besteht aus genau einem Zustand
     start = fresh();
     stop = fresh();
     int n1_start = n1.getInitial();
     int n1_stop  = n1.getFinals()[0];
     int n2_start = n2.getInitial();
     int n2_stop  = n2.getFinals()[0];


     // 3. Sammle Transitionen auf von n1 und n2.
     //    Verbinde neuen Start-/Endzustand mit alten Start-/Endzustaenden.
     vector<Transition> t1 = n1.getTransitions();
     vector<Transition> t2 = n2.getTransitions();

     ts.insert(ts.end(),t1.begin(),t1.end());
     ts.insert(ts.end(),t2.begin(),t2.end());
     ts.push_back(Transition(start, n1_start));
     ts.push_back(Transition(start, n2_start));
     ts.push_back(Transition(n1_stop, stop));
     ts.push_back(Transition(n2_stop, stop));

     return NFA(ts,start,stop);
  }
      


  } // switch


} // transformWorker



