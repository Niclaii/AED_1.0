#include <iostream>

// Clase Nodo
class Nodo {
public:
    int* valores;  // Arreglo dinámico de valores
    Nodo* next;
    int top;
    int block_size;  // Tamaño del bloque

    // Constructor del nodo
    Nodo(int size) : next(nullptr), top(0), block_size(size) {
        valores = new int[block_size];
        // Inicializar el array con algún valor seguro (por ejemplo, 0)
        for (int i = 0; i < block_size; ++i) {
            valores[i] = 0;
        }
    }

    // Destructor para liberar memoria
    ~Nodo() {
        delete[] valores;
    }
};

// Clase ListaEnlazada
class ListaEnlazada {
private:
    Nodo* head;
    int block_size;  // Tamaño del bloque para todos los nodos

public:
    // Constructor con tamaño de bloque
    ListaEnlazada(int size) : head(nullptr), block_size(size) {}

    // Destructor para limpiar todos los nodos
    ~ListaEnlazada() {
        Nodo* actual = head;
        while (actual != nullptr) {
            Nodo* temp = actual;
            actual = actual->next;
            delete temp;
        }
    }

    // Insertar al final
    void insert_back(int valor) {
        if (!head) {
            head = new Nodo(block_size);
            head->valores[head->top++] = valor;
            return;
        }

        Nodo* actual = head;
        while (actual->next != nullptr) {
            actual = actual->next;
        }

        if (actual->top == block_size) {
            actual->next = new Nodo(block_size);
            actual = actual->next;
        }
        actual->valores[actual->top++] = valor;
    }

    // Insertar al frente
    void insert_front(int valor) {
        if (!head || head->top == block_size) {
            Nodo* nuevo = new Nodo(block_size);
            nuevo->valores[nuevo->top++] = valor;
            nuevo->next = head;
            head = nuevo;
        }
        else {
            for (int i = head->top; i > 0; --i) {
                head->valores[i] = head->valores[i - 1];
            }
            head->valores[0] = valor;
            head->top++;
        }
    }

    // Insertar en el medio en una posición dada
    void insert_middle(int valor, int posicion) {
        if (!head) {
            insert_back(valor);
            return;
        }

        Nodo* actual = head;
        int index = 0;

        // Encontrar el nodo donde debe ser insertado el valor
        while (actual != nullptr && index + actual->top <= posicion) {
            index += actual->top;
            actual = actual->next;
        }

        // Si el bloque está lleno, crear uno nuevo
        if (actual && actual->top == block_size) {
            Nodo* nuevo = new Nodo(block_size);
            nuevo->next = actual->next;
            actual->next = nuevo;
            actual = nuevo;
        }

        if (!actual) {
            insert_back(valor);
            return;
        }

        // Insertar en la posición correcta dentro del bloque actual
        int relative_pos = posicion - index;
        for (int i = actual->top; i > relative_pos; --i) {
            actual->valores[i] = actual->valores[i - 1];
        }
        actual->valores[relative_pos] = valor;
        actual->top++;
    }

    // Mostrar la lista enlazada
    void mostrar_lista() {
        Nodo* actual = head;
        while (actual != nullptr) {
            for (int i = 0; i < actual->top; ++i) {
                std::cout << actual->valores[i] << " ";
            }
            actual = actual->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    ListaEnlazada lista(4);  // Crear la lista con tamaño de bloque de 4

    // Insertar elementos en la lista
    lista.insert_back(2);
    lista.insert_back(4);
    lista.insert_back(6);
    lista.insert_back(8);
    lista.insert_back(10);  // Debería crear un nuevo nodo
    lista.insert_front(1);  // Insertar al frente
    lista.insert_middle(5, 2);  // Insertar en el medio (antes de 4)

    // Mostrar la lista
    lista.mostrar_lista();

    return 0;
}
