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

template <class T,class O>
struct LE
{
    nodo<T>* head = nullptr;
    O ordenar;



    ~LE()
    {
        while (head != nullptr)
        {
            nodo<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void add(T v)
    {
        nodo<T>* prev = nullptr;
        nodo<T>* current = nullptr;
        find(v, prev, current);

        nodo<T>* nuevonodo = new nodo<T>(v);

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

    void add1(T v)
    {
        nodo<T>* prev = nullptr;
        
        if (!find(v, prev, current))
        {
            if (prev == nullptr)
                head = new nodo<T>(v,head);
            else
               prev->next = new nodo<T>(v, prev->next);

        }
    }



    void del(T v)
    {
        nodo<T>* prev = nullptr;
        nodo<T>* current = nullptr;
        find(v, prev, current);

        if (current != nullptr && current->valor == v)
        {
            if (prev == nullptr)
            {
                head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            delete current; 
        }
    }

    void find(T v, nodo<T>*& prev, nodo<T>*& current) 
    {
        prev = nullptr;
        current = head;

        while (current != nullptr && ordenar(current->valor, v))
        {
            prev = current;
            current = current->next;
        }
    }

    bool find(T v, nodo<T>*& prev)
    {
        prev = null;
        nodo<T>* p=head;
        for (; p && ordenar(p->valor, v); prev = p, p = p->next);
        if (p && p->valor == v)
            return true;
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
  
    LE<int, Asc<int>> lista;
    Asc<int> asc;
    Desc<int> desc;
    Asc<char> asc2;
    Desc<char> desc2;


    lista.add(5);
    lista.add(10);
    lista.add(10);
    lista.add(15);

    cout << "Lista después de agregar nodos: ";
    lista.print();

 
    lista.del(10);
    cout << "Lista después de eliminar el nodo con valor 10: ";
    lista.print();

    LE<char,Asc<char>>lista2;
    lista2.add('a');
    lista2.add('c');
    lista2.add('b');

    lista2.print();

    lista2.del('a');

    lista2.print();

    return 0;
}
