#include <set>
#include "Subject.h"
#include "Observer.h"

// TODO : delete
#include <iostream>
using namespace std;

void Subject::attach (Observer *newView) {
    observers.insert(newView);
}

Subject::~Subject() {
    
}

void Subject::detach (Observer *formerView) {
    observers.erase(formerView);
}

void Subject::notifyObservers() {
    // Observer::iterator i;
    // for (i = observers.begin(); i != observers.end(); ++i) { 
    //     (*i)->update();
    // }   

    for (auto ob : observers) ob->notify();
}
