#ifndef _HEAP_H
#define _HEAP_H

#include <string>
#include <iostream>
#include <vector>
#include "observer.hpp"

///Min-Heap-Klasse mit variablem Datentypen
template <typename T>
class Heap {
private:
    /** Größe des Array des Heap*/
    int _size;
    /** Speichert index für das nächste freie Element im Array des Heap*/
    int _next;
    /** Array: Speichert die Werte des Heap */
    T *_values;
    /**Liste der am Heap angemeldeten Beobachter*/
    Logger<T> *_logger;
    Counter<T> *_counter;

    bool isEmpty();
    bool isFull();
    void increase();
    void swap(T *a, T *b);
    int getStringLength(T i);
    void MinHeapify(int i);
    int left(int i);
    int right(int i);
    int parent(int i);

public:
    Heap(int size);
    Heap(int *values);
    ~Heap();
    void insert(int val);
    T minimum();
    void extractMin();

    void attachCounter(Counter<T> *c);
    void attachLogger(Logger<T> *l);
    void notify(int i, int num);
};

/** Der Construktor für die Klasse Heap.
 *  Erstellt ein Objekt der Klasse Heap.
 *  Größe des Heap is abhängig vom Übergabewert "size. */  
template <typename T>
Heap<T>::Heap(int size){
    _size = size;
    _next = 0;
    _values = new T[_size];
    _logger = new Logger<T>;
    _counter = new Counter<T>;
}

/** Zweiter Construktor für die Klasse Heap.
 *  Erstellt ein Objekt der Klasse Heap.
 *  Die Werte des übergebenen Arrays werden in den Heap Übernommen.
 *  Es wird angenommen, dass das ursprüngliche Array bereits geordnet ist. */ 
template <typename T>
Heap<T>::Heap(int *valueArray){
    _size = sizeof(valueArray);
    _next = _size;
    _values = new T[sizeof(valueArray)];
    for(int i=0; i<_size;i++)
        _values[i] = valueArray[i];
}

/** Destructor der Klasse Heap. 
 * Gibt den allokierten Speicher wieder frei. */
template <typename T>
Heap<T>::~Heap(){
    delete[] _values;
}

/** Überprüft, ob der Heap leer ist. */
template <typename T>
bool Heap<T>::isEmpty(){
    return _next == 0;
}

/** Überprüft, ob der Heap voll ist. */
template <typename T>
bool Heap<T>::isFull(){
    return _next == _size;
}

/** Findet die linke Child Node einer Node "i". */
template <typename T>
int Heap<T>::left(int i){ 
    return (2*i + 1); 
}

/** Findet die rechte Child Node einer Node "i". */
template <typename T>
int Heap<T>::right(int i){ 
    return (2*i + 2); 
}

/** Findet die parent Node einer Node "i". */
template <typename T>
int Heap<T>::parent(int i){ 
     return (i-1)/2;
}

/** Erhöht die Speicherkapazität des Arrays des Heaps.
 *  Zunächst wird die Größenvariableverdoppelt. 
 *  Die Werte des Array in einem temporäten Array gesperichert, 
 *  welches später dafür genutzt wird, um die Werte wieder im Array des Heap zu speichern. */
template <typename T>
void Heap<T>::increase(){
    _size = 1 + 2 * _size;

    T *tmp = new T[_size];
    for (int i = 0; i < _next; i++)
        tmp[i] = _values[i];

    delete[] _values;
    _values = tmp;
}

/** Vertauscht zwei Werte. */
template <typename T>
void Heap<T>::swap(T *a, T *b){
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

/** Fügt einen neuen Wert "val" in den Heap ein.
 *  Sortiert diesen wieder, falls die Heap-Bedingung verletzt wurde. */
template <typename T>
void Heap<T>::insert(int val){
    if (isFull())
        increase();
    
    _next++;
    int i = _next - 1; 
    _values[i] = val;  
  
    while (i != 0 && _values[parent(i)] > _values[i]) 
    { 
       swap(&_values[i], &_values[parent(i)]); 
       i = parent(i); 
    } 
    
    notify(1, val);
}

/** Gibt das kleinste Element des Heap zurück. */
template <typename T>
T Heap<T>::minimum(){
    if (isEmpty())
        return -1;
    
    return _values[0];
}

/** Entfernt das kleinste Element des Heaps.
 * Danach muss der Heap wieder sortiert werden.
 * Heap wird mit einem Heap-Sort sortiert. */
template <typename T>
void Heap<T>::extractMin(){
    int num = _values[0];
    if(_next == 0){
        std::cout << "Empty Heap!" << std::endl;
        std::cout << _next << std::endl;
        return;
    }
    if(_next == 1)
        _next--;  

    int root = _values[0]; 
    _values[0] = _values[_next-1]; 
    _next--;
    MinHeapify(0); 
    
    notify(2, num);
    return; 
}

/** Teil des Heap-Sort.
 * Siehe Funktion "extractMin()". */
template <typename T>
void Heap<T>::MinHeapify(int i){
    int l = left(i); 
    int r = right(i); 
    int smallest = i; 
    if (l < _next && _values[l] < _values[i]) 
        smallest = l; 
    if (r < _next && _values[r] < _values[smallest]) 
        smallest = r; 
    if (smallest != i) 
    { 
        swap(&_values[i], &_values[smallest]); 
        MinHeapify(smallest); 
    } 

}

/** Gibt die Anzahl der Stellen einer Zahl zurück.
 *  Bsp: 1700 hat 4 Stellen. 42 hat 2 Stellen. */
template <typename T>
int Heap<T>::getStringLength(T i){
    int j = 1;
	i /= 10;
	while(i != 0) {
		i /= 10;
		j ++;
	}
	return j;  
}

template <typename T>
void Heap<T>::notify(int i, int num){
    _logger->update(i, num);
    _counter->update();
}

template <typename T>
void Heap<T>::attachCounter(Counter<T> *c){
    _counter = c;
}

template <typename T>
void Heap<T>::attachLogger(Logger<T> *l){
    _logger = l;
}

#endif 
