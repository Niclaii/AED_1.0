#include <iostream>

// Clase Nodo
template<class T>
class Nodo {
public:
    T* arr;  // Arreglo dinámico de arr
    Nodo<T>* next;
    int top;
    int tam;  // Tamaño del bloque

    // Constructor del nodo
    Nodo(int size) : next(nullptr), top(0), tam(size) {
        arr = new T[tam];
    }

    // Destructor para liberar memoria
    ~Nodo() {
        delete[] arr;
    }
};

// Clase ListaEnlazada
template<class T>
class ListaEnlazada {
private:
    Nodo<T>* head;
    int tam;  // Tamaño del bloque para todos los nodos

public:
    // Constructor con tamaño de bloque
    ListaEnlazada(int size) : head(nullptr), tam(size) {}

    // Destructor para limpiar todos los nodos
    ~ListaEnlazada() {
        Nodo<T>* actual = head;
        while (actual != nullptr) {
            Nodo<T>* temp = actual;
            actual = actual->next;
            delete temp;
        }
    }

    // Método find para encontrar el nodo y la posición relativa dentro del nodo
    void find(int posicion, Nodo<T>*& nodo_encontrado, int& relative_pos) {
        Nodo<T>* actual = head;
        int index = 0;

        // Buscar el nodo y la posición correcta
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

    // Insertar al final
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

    // Insertar al frente
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

    // Insertar en el medio en una posición dada
    void insert_middle(T valor, int posicion) {
        Nodo<T>* actual;
        int relative_pos;
        find(posicion, actual, relative_pos);

        if (!actual) {
            insert_back(valor);
            return;
        }

        if (actual->top < tam) {
            // Si hay espacio, inserta el valor directamente
            for (int i = actual->top; i > relative_pos; --i) {
                actual->arr[i] = actual->arr[i - 1];
            }
            actual->arr[relative_pos] = valor;
            actual->top++;
        }
        else {
            // Si el bloque está lleno, divide y reubica
            Nodo<T>* nuevo = new Nodo<T>(tam);
            nuevo->next = actual->next;
            actual->next = nuevo;

            int mitad = tam / 2;
            for (int i = 0; i < mitad; ++i) {
                nuevo->arr[i] = actual->arr[mitad + i];
            }
            nuevo->top = mitad;
            actual->top = mitad;

            insert_middle(valor, posicion);  // Reintenta la inserción
        }
    }

    // Eliminar un valor en una posición dada
    void eliminar(int posicion) {
        Nodo<T>* actual;
        int relative_pos;
        find(posicion, actual, relative_pos);

        if (!actual) {
            std::cout << "No se pudo encontrar la posición para eliminar.\n";
            return;
        }

        // Desplazar los arr hacia la izquierda dentro del nodo
        for (int i = relative_pos; i < actual->top - 1; ++i) {
            actual->arr[i] = actual->arr[i + 1];
        }
        actual->top--;

        // Si el nodo está vacío después de eliminar el valor
        if (actual->top == 0) {
            // Si es el nodo cabeza
            if (actual == head) {
                head = head->next;
                delete actual;
            }
            else {
                // Encontrar el nodo anterior para eliminar el nodo vacío
                Nodo<T>* prev = head;
                while (prev->next != actual) {
                    prev = prev->next;
                }
                prev->next = actual->next;
                delete actual;
            }
        }
    }

    // Ordenar los elementos de la lista de manera ascendente sin usar vector
    void ordenar_lista() {
        if (!head || !head->next) return;  // No es necesario ordenar si hay un solo nodo

        bool swapped;
        do {
            swapped = false;
            Nodo<T>* actual = head;

            // Vamos a recorrer los nodos
            while (actual != nullptr) {
                // Dentro de cada nodo ordenamos el arreglo
                for (int i = 0; i < actual->top - 1; ++i) {
                    if (actual->arr[i] > actual->arr[i + 1]) {
                        std::swap(actual->arr[i], actual->arr[i + 1]);
                        swapped = true;
                    }
                }

                // Ahora ordenamos los valores entre nodos
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

    // Mostrar la lista enlazada
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
    ListaEnlazada<int> lista(5);  // Crear la lista con tamaño de bloque de 5

    // Insertar elementos en la lista
    lista.insert_back(11);  // Insertar 11 al principio
    lista.insert_back(4);
    lista.insert_back(2);
    lista.insert_back(8);
    lista.insert_back(10);  // Debería crear un nuevo nodo
    lista.insert_front(1);  // Insertar al frente
    lista.insert_middle(5, 3);  // Insertar en el medio (después de 4)

    // Ordenar la lista
    lista.ordenar_lista();

    // Mostrar la lista
    lista.Imprimir();

    // Eliminar un valor
    lista.eliminar(1);  // Eliminar en la posición 1 (segundo valor)

    // Mostrar la lista después de eliminar
    lista.Imprimir();

    return 0;
}
