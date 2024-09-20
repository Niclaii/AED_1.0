#include <iostream>

using namespace std;

template <class T>
struct nodo
{
    T valor;
    nodo<T>* next;

    nodo(T v, nodo<T>* n = nullptr)
    {
        valor = v;
        next = n;
    }
};

template<class T>
class Asc
{
public:
    bool operator()(T a, T b)
    {
        return a < b;
    }
};
template<class T>
class Desc
{
public:
    bool operator()(T a, T b)
    {
        return b < a;
    }
};

template <class T>
struct LE
{
    nodo<T>* head = nullptr;

    ~LE()
    {
        while (head != nullptr)
        {
            nodo<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    template<class O>
    void findPrevAndCurrent(T v, O ordenar, nodo<T>*& prev, nodo<T>*& current)
    {
        prev = nullptr;
        current = head;

        while (current != nullptr && ordenar(current->valor, v))
        {
            prev = current;
            current = current->next;
        }
    }

    template<class O>
    void add(T v, O ordenar)
    {
        nodo<T>* prev = nullptr;
        nodo<T>* current = nullptr;
        findPrevAndCurrent(v, ordenar, prev, current);

        nodo<T>* nuevonodo = new nodo<T>(v);

        if (prev == nullptr)
        {
            // Insertar al principio de la lista
            nuevonodo->next = head;
            head = nuevonodo;
        }
        else
        {
            // Insertar en el medio o al final
            prev->next = nuevonodo;
            nuevonodo->next = current;
        }
    }

    template<class O>
    void del(T v, O ordenar)
    {
        nodo<T>* prev = nullptr;
        nodo<T>* current = nullptr;
        findPrevAndCurrent(v, ordenar, prev, current);

        // Si se encuentra el nodo a eliminar
        if (current != nullptr && current->valor == v)
        {
            if (prev == nullptr)
            {
                // El nodo a eliminar es la cabeza de la lista
                head = current->next;
            }
            else
            {
                // El nodo a eliminar está en el medio o al final
                prev->next = current->next;
            }
            delete current; // Libera la memoria del nodo eliminado
        }
    }

    bool find(T v, nodo<T>*& pos) const
    {
        pos = head;
        while (pos != nullptr)
        {
            if (pos->valor == v)
            {
                return true;
            }
            pos = pos->next;
        }
        return false;
    }

    void print() const
    {
        nodo<T>* actual = head;
        while (actual != nullptr)
        {
            cout << actual->valor << " -> ";
            actual = actual->next;
        }
        cout << "nullptr" << endl;
    }
};

int main()
{
    LE<int> lista;
    Asc<int> asc;
    Desc<int> desc;
    Asc<char> asc2;
    Desc<char> desc2;


    lista.add(5, asc);
    lista.add(10, asc);
    lista.add(15, asc);

    cout << "Lista después de agregar nodos: ";
    lista.print();

    nodo<int>* encontrado = nullptr;
    if (lista.find(10, encontrado))
    {
        cout << "Valor 10 encontrado en la lista." << endl;
    }
    else
    {
        cout << "Valor 10 no encontrado en la lista." << endl;
    }

    lista.del(10,asc);
    cout << "Lista después de eliminar el nodo con valor 10: ";
    lista.print();

    LE<char>lista2;
    lista2.add('a', asc2);
    lista2.add('c', asc2);
    lista2.add('b', asc2);

    lista2.print();

    lista2.del('a',asc);

    lista2.print();

    return 0;
}
