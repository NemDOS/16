#ifndef _OBSERVER_H
#define _OBSERVER_H

#include <string>


template <typename T> class Heap;

template <typename T>
class Logger {
    private:
        Heap<T> *_heap;
        std::string _changes;

    public:
        Logger(Heap<T> *heap){
            _heap = heap;
            _heap->attachLogger(this);
            _changes = new std::string[100];
        }
        void logOn(Heap<T> *heap);
        void update(int i, int num);    
};

template <typename T>
class Counter {
    private:
        Heap<T> *_heap;
        
    public:
        unsigned int _amountChanges = 0;
        Counter(Heap<T> *heap){
            _heap = heap;
            _heap->attachCounter(this);
        }
        void logOn(Heap<T> *heap);
        void update(); 
};

template <typename T>
void Logger<T>::logOn(Heap<T> *heap){
    _heap = heap;
    _heap->attachCounter(this);
}

template <typename T>
void Counter<T>::logOn(Heap<T> *heap){
    _heap = heap;
    _heap->attachCounter(this);
}

template <typename T>
void Logger<T>::update(int i, int num){
    std::string str;
    switch (i) {
        case 1: //1 wenn insert
            str.append("Insert: ");
            break;
        
        case 2: //2 wenn extractMin
            str.append("ExtractMin: ");
            break;
    }
    std::cout << "THROUGH SWITCH" << std::endl;
    
    str.append(",");
    std::cout << "COPING" << std::endl;
    _changes += str;
    std::cout << "COPIED" << std::endl;
}

template <typename T>
void Counter<T>::update(){
    _amountChanges++;
}

#endif
