#include <iostream>

using namespace std;

template <class T>
class Pila {
private:
    struct Nodo {
        T valor;
        Nodo* siguiente;
    };
    Nodo* top = nullptr;

public:
    Pila() : top(nullptr) {}

    void Push(T valor) {
        Nodo* nuevo = new Nodo;
        nuevo->valor = valor;
        nuevo->siguiente = top;
        top = nuevo;
    }

    T Pop() {
        if (top == nullptr) {
            std::cout << "Stack vacio" << std::endl;
            return T();
        }
        Nodo* tmp = top;
        T valor = tmp->valor;
        top = top->siguiente;
        delete tmp;
        return valor;
    }

    void Print() {
        Nodo* actual = top;
        while (actual != nullptr) {
            std::cout << actual->valor << " ";
            actual = actual->siguiente;
        }
        std::cout << std::endl;
    }
};


template <class T>
class Cola {
private:
    struct Nodo {
        T valor;
        Nodo* siguiente;
    };
    Nodo* head = nullptr;
    Nodo* tail = nullptr;

public:
    Cola() : head(nullptr), tail(nullptr) {}

    void Push(T valor) {
        Nodo* nuevo = new Nodo;
        nuevo->valor = valor;
        nuevo->siguiente = nullptr;
        if (tail == nullptr) {
            head = tail = nuevo;
        }
        else {
            tail->siguiente = nuevo;
            tail = nuevo;
        }
    }

    T Pop() {
        if (head == nullptr) {
            std::cout << "Queue vacio" << std::endl;
            return T();
        }
        Nodo* tmp = head;
        T valor = tmp->valor;
        head = head->siguiente;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete tmp;
        return valor;
    }

    void Print() {
        Nodo* actual = head;
        while (actual != nullptr) {
            std::cout << actual->valor << " ";
            actual = actual->siguiente;
        }
        std::cout << std::endl;
    }
};

int main() {

    Pila<int> pila;
    std::cout << "Pila:\n";
    pila.Print();
    pila.Push(1);
    pila.Push(2);
    pila.Push(3);
    pila.Print(); 
    pila.Pop();
    pila.Print(); 

    
    Cola<int> cola;
    std::cout << "\nCola:\n";
    cola.Print();
    cola.Push(1);
    cola.Push(2);
    cola.Push(3);
    cola.Print(); 
    cola.Pop();
    cola.Print();

    return 0;
}