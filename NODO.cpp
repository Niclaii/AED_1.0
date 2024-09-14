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

    template<class O>
    void add(T v, O ordenar)
    {
        nodo<T>* nuevonodo = new nodo<T>(v);
        nuevonodo->next = head;
        nodo<T>* current = head;
        nodo<T>* prev = nullptr;
        
         
        while (current != nullptr && ordenar(current->valor, v))
        {
            prev = current;
            current = current->next;

        }
        if (prev == nullptr)
        {
            nuevonodo->next = head;
            head = nuevonodo;
        }
        else
        {
            prev->next = nuevonodo;
            nuevonodo->next = current;
        }
    }

    void del(T v)
    {
        nodo<T>* pos = head;
        nodo<T>* prev = nullptr;

        while (pos != nullptr)
        {
            if (pos->valor == v)
            {
                if (prev == nullptr)
                {
                    head = pos->next;
                }
                else
                {
                    prev->next = pos->next;
                }
                delete pos;
                return;
            }
            prev = pos;
            pos = pos->next;
        }
    }

    bool find(T v, nodo<T>*& pos)
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



    void print()
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


    lista.add(5,asc);
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

    lista.del(10);
    cout << "Lista después de eliminar el nodo con valor 10: ";
    lista.print();

    LE<char>lista2;
    lista2.add('a',asc2);
    lista2.add('c', asc2);
    lista2.add('b',asc2);

    lista2.print();

    lista2.del('a');

    lista2.print();

    return 0;
}
