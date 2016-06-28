
// Ein moeglicher Rahmen fuer Aufgabe 4, zweite Teilaufgabe,
// uebersetze regulaeren Ausdruck in einen NFA.
// Der Einfachheit in ein .h File gepackt.


#include <iostream>

using namespace std;

#include "FSA.h"
#include "TestOrakel.h"


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

      case EpsType: {
          start = fresh();
          stop = fresh();
          ts.push_back(Transition(start, stop));
          return NFA(ts, start, stop);
      }
      case ChType: {
          Ch* r2 = (Ch*) r;
          start = fresh();
          stop = fresh();
          ts.push_back(Transition(start, r2->getChar(), stop));
          return NFA(ts, start, stop);
      }
      case StarType: {
          Star* r3 = (Star*) r;

          NFA n = transformWorker(r3->getRE());

          start = fresh();
          stop = fresh();
          int n_start = n.getInitial();
          int n_stop = n.getFinals()[0];
          vector<Transition> t = n.getTransitions();

          ts.insert(ts.end(),t.begin(),t.end());
          ts.push_back(Transition(start, n_start));
          ts.push_back(Transition(n_stop, n_start));
          ts.push_back(Transition(n_stop, stop));
          ts.push_back(Transition(start, stop));

          return NFA(ts, start, stop);
      }
      case ConcType: {
          Conc* r4 = (Conc*) r;

          NFA n1 = transformWorker(r4->getLeft());
          nameSupply--;
          NFA n2 = transformWorker(r4->getRight());

          vector<Transition> t1 = n1.getTransitions();
          vector<Transition> t2 = n2.getTransitions();

          ts.insert(ts.end(),t1.begin(),t1.end());
          ts.insert(ts.end(),t2.begin(),t2.end());

          return NFA(ts, n1.getInitial(), n2.getFinals()[0]);
      }
      // Phi: Akzeptiert kein Wort
      // NFA besteht aus einem Start und Stopzustand und *keiner* Transition
      case PhiType: {
        start = fresh();
        stop = fresh();
        return NFA(ts, start, stop);
      }
      case AltType: {
         Alt* r5 = (Alt*) r;

         // 1. Baue NFAs der linken und rechten Alternative
         NFA n3 = transformWorker(r5->getLeft());
         NFA n4 = transformWorker(r5->getRight());

         // 2. Generieren neuen Start-/Stopzustand.
         //    Sammle Start-/Stopzustaende von n1 und n2
         // N.B. Annahme: finals besteht aus genau einem Zustand
         start = fresh();
         stop = fresh();
         int n3_start = n3.getInitial();
         int n3_stop  = n3.getFinals()[0];
         int n4_start = n4.getInitial();
         int n4_stop  = n4.getFinals()[0];


         // 3. Sammle Transitionen auf von n1 und n2.
         //    Verbinde neuen Start-/Endzustand mit alten Start-/Endzustaenden.
         vector<Transition> t3 = n3.getTransitions();
         vector<Transition> t4 = n4.getTransitions();

         ts.insert(ts.end(),t3.begin(),t3.end());
         ts.insert(ts.end(),t4.begin(),t4.end());
         ts.push_back(Transition(start, n3_start));
         ts.push_back(Transition(start, n4_start));
         ts.push_back(Transition(n3_stop, stop));
         ts.push_back(Transition(n4_stop, stop));

         return NFA(ts,start,stop);
      }

  } // switch

} // transformWorker



