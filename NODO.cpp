#include <iostream>

using namespace std;


template<class T>
struct nodo
{
    T valor;
    nodo<T>* next;
    nodo(T v, nodo<T>* n = null)
    {
        valor = v;
        next = n;
    }
};

template <class T , class U>
struct LE
{
    nodo<T>* head = NULL;
    void add(T v)
    {
        head->valor = v;
        head->next;                                         ///MODIFICAR
    }
    void del(T v)
    {
        nodo<T>* pos = head;
        while (pos != nullptr;)
        {
            if (pos->valor == v)
            {
                delete pos;
                break;
            }
            else
            {
                pos->next;
            }
        }
    }
    bool find(T v, nodo<T>*& pos)
    {
        pos = head;
        while (;pos<)
        {
            if (pos->valor == v)
            {
                break;
            }
            else
            {
                pos->next;
            }
        }
        return 
    }
    void print()
    {
        for()
    }
};




int main()
{
    
    nodo<int>* b = new nodo<int>(5, 0);










}

