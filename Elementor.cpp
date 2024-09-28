#include <iostream>


template<class T>
class Nodo {
public:
    T* arr;  
    Nodo<T>* next;
    int top;
    int tam;  

  
    Nodo(int size) : next(nullptr), top(0), tam(size) {
        arr = new T[tam];
    }

  
    ~Nodo() {
        delete[] arr;
    }
};


template<class T>
class ListaEnlazada {
private:
    Nodo<T>* head;
    int tam; 

public:

    ListaEnlazada(int size) : head(nullptr), tam(size) {}


    ~ListaEnlazada() {
        Nodo<T>* actual = head;
        while (actual != nullptr) {
            Nodo<T>* temp = actual;
            actual = actual->next;
            delete temp;
        }
    }


    void find(int posicion, Nodo<T>*& nodo_encontrado, int& relative_pos) {
        Nodo<T>* actual = head;
        int index = 0;


        while (actual != nullptr && index + actual->top <= posicion) {
            index += actual->top;
            actual = actual->next;
        }

        if (actual == nullptr) {
            nodo_encontrado = nullptr;
            relative_pos = -1;
            return;
        }

        nodo_encontrado = actual;
        relative_pos = posicion - index;
    }


    void insert_back(T valor) {
        if (!head) {
            head = new Nodo<T>(tam);
            head->arr[head->top++] = valor;
            return;
        }

        Nodo<T>* actual = head;
        while (actual->next != nullptr) {
            actual = actual->next;
        }

        if (actual->top == tam) {
            actual->next = new Nodo<T>(tam);
            actual = actual->next;
        }
        actual->arr[actual->top++] = valor;
    }


    void insert_front(T valor) {
        if (!head || head->top == tam) {
            Nodo<T>* nuevo = new Nodo<T>(tam);
            nuevo->arr[nuevo->top++] = valor;
            nuevo->next = head;
            head = nuevo;
        }
        else {
            for (int i = head->top; i > 0; --i) {
                head->arr[i] = head->arr[i - 1];
            }
            head->arr[0] = valor;
            head->top++;
        }
    }


    void insert_middle(T valor, int posicion) {
        Nodo<T>* actual;
        int relative_pos;
        find(posicion, actual, relative_pos);

        if (!actual) {
            insert_back(valor);
            return;
        }

        if (actual->top < tam) {

            for (int i = actual->top; i > relative_pos; --i) {
                actual->arr[i] = actual->arr[i - 1];
            }
            actual->arr[relative_pos] = valor;
            actual->top++;
        }
        else {

            Nodo<T>* nuevo = new Nodo<T>(tam);
            nuevo->next = actual->next;
            actual->next = nuevo;

            int mitad = tam / 2;
            for (int i = 0; i < mitad; ++i) {
                nuevo->arr[i] = actual->arr[mitad + i];
            }
            nuevo->top = mitad;
            actual->top = mitad;

            insert_middle(valor, posicion); 
        }
    }


    void eliminar(int posicion) {
        Nodo<T>* actual;
        int relative_pos;
        find(posicion, actual, relative_pos);

        if (!actual) {
            std::cout << "No se pudo encontrar la posición para eliminar.\n";
            return;
        }

 
        for (int i = relative_pos; i < actual->top - 1; ++i) {
            actual->arr[i] = actual->arr[i + 1];
        }
        actual->top--;

    
        if (actual->top == 0) {
        
            if (actual == head) {
                head = head->next;
                delete actual;
            }
            else {
      
                Nodo<T>* prev = head;
                while (prev->next != actual) {
                    prev = prev->next;
                }
                prev->next = actual->next;
                delete actual;
            }
        }
    }


    void ordenar_lista() {
        if (!head || !head->next) return;  

        bool swapped;
        do {
            swapped = false;
            Nodo<T>* actual = head;

 
            while (actual != nullptr) {
                for (int i = 0; i < actual->top - 1; ++i) {
                    if (actual->arr[i] > actual->arr[i + 1]) {
                        std::swap(actual->arr[i], actual->arr[i + 1]);
                        swapped = true;
                    }
                }

    
                if (actual->next != nullptr && actual->top > 0 && actual->next->top > 0) {
                    if (actual->arr[actual->top - 1] > actual->next->arr[0]) {
                        std::swap(actual->arr[actual->top - 1], actual->next->arr[0]);
                        swapped = true;
                    }
                }
                actual = actual->next;
            }
        } while (swapped);
    }


    void Imprimir() {
        Nodo<T>* actual = head;
        while (actual != nullptr) {
            for (int i = 0; i < actual->top; ++i) {
                std::cout << actual->arr[i] << " ";
            }
            actual = actual->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    ListaEnlazada<int> lista(5);  


    lista.insert_back(11);  
    lista.insert_back(4);
    lista.insert_back(2);
    lista.insert_back(8);
    lista.insert_back(10);  
    lista.insert_front(1);  
    lista.insert_middle(5, 3);  

    lista.ordenar_lista();


    lista.Imprimir();


    lista.eliminar(1);  


    lista.Imprimir();

    return 0;
}
