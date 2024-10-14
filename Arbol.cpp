#include <iostream>

using namespace std;

class Nodo
{
public:
    int valor;
    Nodo* next; // Hijo derecho
    Nodo* prev; // Hijo izquierdo

    Nodo(int v) : valor(v), next(nullptr), prev(nullptr) {}
};

class BinaryTree
{
public:
    Nodo* raiz;

    BinaryTree() : raiz(nullptr) {}

    void insert(int valor)
    {
        Nodo* nuevo_nodo = new Nodo(valor);

        if (raiz == nullptr)
        {
            raiz = nuevo_nodo;
            return;
        }

        Nodo* actual = raiz;
        Nodo* padre = nullptr;

        while (actual != nullptr)
        {
            padre = actual;
            if (valor < actual->valor)
            {
                actual = actual->prev; // Mover al hijo izquierdo
            }
            else if (valor > actual->valor)
            {
                actual = actual->next; // Mover al hijo derecho
            }
            else
            {
                // El valor ya existe en el árbol
                std::cout << "Este elemento ya existe" << std::endl;
                delete nuevo_nodo;
                return;
            }
        }

        // Ahora, `padre` es el nodo al que debemos agregar el nuevo nodo como hijo
        if (valor < padre->valor)
        {
            padre->prev = nuevo_nodo; // Insertar como hijo izquierdo
        }
        else
        {
            padre->next = nuevo_nodo; // Insertar como hijo derecho
        }
    }


    void remove(int valor)
    {
        if (raiz == nullptr)
        {
            cout << "No hay elementos en el árbol\n";
            return;
        }
        else
        {
            Nodo* actual = raiz;
            Nodo* padre = nullptr;

            // Buscar el nodo a eliminar y su padre
            while (actual != nullptr && actual->valor != valor)
            {
                padre = actual;
                if (valor < actual->valor)
                    actual = actual->prev; // Mover al hijo izquierdo
                else
                    actual = actual->next; // Mover al hijo derecho
            }

            if (actual == nullptr)
            {
                cout << "El elemento " << valor << " no se encuentra en el árbol\n";
                return;
            }

            // Caso 1: El nodo es una hoja (no tiene hijos)
            if (actual->prev == nullptr && actual->next == nullptr)
            {
                if (padre == nullptr)
                {
                    // El nodo a eliminar es la raíz
                    delete raiz;
                    raiz = nullptr;
                }
                else if (padre->prev == actual)
                {
                    delete actual;
                    padre->prev = nullptr;
                }
                else if (padre->next == actual)
                {
                    delete actual;
                    padre->next = nullptr;
                }
            }
            // Caso 2: El nodo tiene un solo hijo (derecho)
            else if (actual->prev == nullptr && actual->next != nullptr)
            {
                if (padre == nullptr)
                {
                    // El nodo a eliminar es la raíz
                    Nodo* temp = raiz;
                    raiz = raiz->next;
                    delete temp;
                }
                else if (padre->prev == actual)
                {
                    padre->prev = actual->next;
                    delete actual;
                }
                else if (padre->next == actual)
                {
                    padre->next = actual->next;
                    delete actual;
                }
            }
            // Caso 2: El nodo tiene un solo hijo (izquierdo)
            else if (actual->prev != nullptr && actual->next == nullptr)
            {
                if (padre == nullptr)
                {
                    // El nodo a eliminar es la raíz
                    Nodo* temp = raiz;
                    raiz = raiz->prev;
                    delete temp;
                }
                else if (padre->prev == actual)
                {
                    padre->prev = actual->prev;
                    delete actual;
                }
                else if (padre->next == actual)
                {
                    padre->next = actual->prev;
                    delete actual;
                }
            }
            // Caso 3: El nodo tiene dos hijos
            else
            {
                // Encontrar el sucesor en orden (mínimo del subárbol derecho)
                Nodo* sucesorPadre = actual;
                Nodo* sucesor = actual->next;
                while (sucesor->prev != nullptr)
                {
                    sucesorPadre = sucesor;
                    sucesor = sucesor->prev;
                }

                // Reemplazar el valor del nodo a eliminar por el valor del sucesor
                actual->valor = sucesor->valor;

                // Eliminar el sucesor
                if (sucesorPadre->prev == sucesor)
                {
                    sucesorPadre->prev = sucesor->next;
                }
                else
                {
                    sucesorPadre->next = sucesor->next;
                }
                delete sucesor;
            }
        }
    }




        
    Nodo* find(int valor)
    {
        Nodo* actual = raiz;

        if (actual == nullptr)
        {
            std::cout << "No hay elementos en el árbol" << std::endl;
            return nullptr;
        }

        while (actual != nullptr)
        {
            if (actual->valor == valor)
            {
                std::cout << "Se encontró el elemento: " << valor << std::endl;
                return actual;
            }
            else if (valor < actual->valor)
            {
                actual = actual->prev; // Mover al hijo izquierdo
            }
            else // valor > actual->valor
            {
                actual = actual->next; // Mover al hijo derecho
            }
        }

        std::cout << "El elemento " << valor << " no se encuentra en el árbol" << std::endl;
        return nullptr;
    }

    // Método opcional para imprimir el árbol en orden
    void mostrarInorder(Nodo* nodo)
    {
        if (nodo != nullptr)
        {
            mostrarInorder(nodo->prev);
            std::cout << nodo->valor << " ";
            mostrarInorder(nodo->next);
        }
    }

    void mostrarInorder()
    {
        mostrarInorder(raiz);
        std::cout << std::endl;
    }
};

int main()
{
    BinaryTree arbol;

    arbol.find(5);        // No hay elementos en el árbol
    arbol.insert(5);
    arbol.find(5);        // Se encontró el elemento: 5
    arbol.insert(2);
    arbol.insert(7);
    arbol.find(2);        // Se encontró el elemento: 2
    arbol.find(7);  
    arbol.mostrarInorder(); // Debería imprimir: 2 5 7// Se encontró el elemento: 7
    arbol.remove(7);
    arbol.mostrarInorder(); // Debería imprimir: 2 5 7

    return 0;
}
