#include <iostream>

using namespace std;

//TEMPLATES//

class Arr
{
    public:
        int A[10];

};

template <class T,int n=10>
class Arr2
{
    public:

        T A[n];

};

template <class T>
class nodo
{
public:

    T dato;
    nodo<T>* next;


};


template<class T>
class LE
{
public:
    nodo <T>* head;
};


//Functor//

template <class T>

class Funto
{
    T _x;
public:

    Funto(T x) : _x(x) {}

    int operator()(T a)
    {
        return _x + a;
    }

};

template <class T>
class Funto2
{
    T _x;
public:

    Funto2(T x) : _x(x) {}

    int operator()(T a)
    {
        return _x * a;
    }

};


template<class T>
void Tabla(T fu)
{
    for (int x = 0; x < 10; x++)
    {
        cout << fu(x) << endl;
    }
};


void swap(int* a, int* b)
{
    int* tmp = nullptr;
    *tmp = *a;
    *a = *b;
    *b = *tmp;
}

void Bubble(int * ini,int *fin)
{
    for (int* p = ini; p < fin; p++)
    {
        for (int* q = p + 1; q < fin; q++)
        {
            if (*p > *q)
            {
                swap(*p, *q);
            }
        }
        fin--;
    }
};









int main()
{
    for (int x{ 0 }; x < 10; x++)
    {
        cout << x << endl;
    }
    cout << endl;
    Arr obj;
    Arr2<int> obj1;
    Arr2<int,20> obj2;
    Arr2<char,20> obj3;

    LE<nodo<int>> Lista;

    Funto<int> A(10);
    cout << A(5) << endl; //IMPRIME 15
    cout << A(3) << endl; //IMPRIME 13

    cout << endl;

    Tabla(Funto<int>(100));// IMPRIME LA LISTA DE 100 HASTA 109
    
    cout << endl;

    Tabla(A);//IMPRIME DE 10 A 19 

    cout << endl;
    
    Tabla(Funto2<int>(100)); //IMPRIME LA LISTA DE 100 HASTA 900 PERO CADA CENTENA

    cout << endl;

    int B[10] = { 1,5,2,7,11,6,3,0,9,15 };

    Bubble(B, B + 10);
    for (int i=0; i < 10; i++)
    {
        cout << B[i];
    }



}
