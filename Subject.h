#ifndef SUBJECT_H
#define SUBJECT_H

#include <set>

class Observer;

class Subject {
    public:
        void attach( Observer* );
        void detach( Observer* );
        void notifyObservers();
        virtual ~Subject()=0;
    
    private:
        std::set<Observer*> observers;
}; 


#endif
