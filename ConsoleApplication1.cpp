#include <iostream>

using namespace std;

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

class Funto
{
    int _x;
public:

    Funto(int x) : _x(x) {}

    int operator()(int a)
    {
        return _x + a;
    }

};




int main()
{
    for (int x{ 0 }; x < 10; x++)
    {
        cout << x << endl;
    }

    Arr obj;
    Arr2<int> obj1;
    Arr2<int,20> obj2;
    Arr2<char,20> obj3;

    LE<nodo<int>> Lista;


}
