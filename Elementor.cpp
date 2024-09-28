#include <iostream>

using namespace std;

template<class T>
class Nodo
{
public:
    T* arr;
    Nodo<T>* next;
    int top;
    int tam;


    Nodo(int size) : next(nullptr), top(0), tam(size) 
    {
        arr = new T[tam];
    }


    ~Nodo()
    {
        delete[] arr;
    }
};

template<class T>
class ListaEnlazada
{
private:
    Nodo<T>* head;
    int tam;

public:

    ListaEnlazada(int size) : head(nullptr), tam(size) {}

    ~ListaEnlazada() 
    {
        Nodo<T>* actual = head;
        while (actual != nullptr) 
        {
            Nodo<T>* temp = actual;
            actual = actual->next;
            delete temp;
        }
    }

     Nodo<T>* find(T valor)
     {
        Nodo<T>* actual = head; while (actual != nullptr) 
        {
            for (int i = 0; i < actual->top; i++) 
            {
                if (actual->arr[i] == valor) 
                {
                    return actual; 
                }

            } actual = actual->next; } return nullptr; 
    }

     void eliminar(T valor)
     {
         Nodo<T>* nodo = find(valor); 
         if (nodo != nullptr) 
         {
             for (int i = 0; i < nodo->top; i++) 
             {
                 if (nodo->arr[i] == valor) 
                 { 
                     for (int j = i; j < nodo->top - 1; j++)
                     {
                         nodo->arr[j] = nodo->arr[j + 1]; 
                     }
                     nodo->top--; 
                     while (nodo->next != nullptr && nodo->top < nodo->tam) 
                     {
                         nodo->arr[nodo->top] = nodo->next->arr[0];
                         nodo->top++; 
                         for (int k = 0; k < nodo->next->top - 1; k++)
                         {
                             nodo->next->arr[k] = nodo->next->arr[k + 1];
                         } 
                         nodo->next->top--; 
                         if (nodo->next->top == 0)
                         {
                             Nodo<T>* temp = nodo->next;
                             nodo->next = nodo->next->next; 
                             delete temp;
                         }
                     } 
                     return;
                 }
             }
         }
     }





    void insert_back(T valor)
    {
        if (!head)
        {
            head = new Nodo<T>(tam);
            head->arr[head->top++] = valor;
            return;
        }

        Nodo<T>* actual = head;
        while (actual->next != nullptr)
        {
            actual = actual->next;
        }

        if (actual->top == tam) 
        {
            actual->next = new Nodo<T>(tam);
            actual = actual->next;
        }
        actual->arr[actual->top++] = valor;
    }


    void insert_front(T valor)
    {
        if (!head || head->top == tam)
        {
            Nodo<T>* nuevo = new Nodo<T>(tam);
            nuevo->arr[nuevo->top++] = valor;
            nuevo->next = head;
            head = nuevo;
        }
        else 
        {
            for (int i = head->top; i > 0; --i)
            {
                head->arr[i] = head->arr[i - 1];
            }
            head->arr[0] = valor;
            head->top++;
        }
    }


    void insert_middle(T valor, int posicion)
    {
        Nodo<T>* actual;
        int relative_pos;
        find(posicion, actual, relative_pos);

        if (!actual)
        {
            insert_back(valor);
            return;
        }

        if (actual->top < tam)
        {

            for (int i = actual->top; i > relative_pos; --i) 
            {
                actual->arr[i] = actual->arr[i - 1];
            }
            actual->arr[relative_pos] = valor;
            actual->top++;
        }
        else
        {

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



    void ordenar_lista() {
        if (!head || !head->next) return;

        bool swapped;
        do 
        {
            swapped = false;
            Nodo<T>* actual = head;


            while (actual != nullptr) 
            {
                for (int i = 0; i < actual->top - 1; ++i)
                {
                    if (actual->arr[i] > actual->arr[i + 1]) 
                    {
                        std::swap(actual->arr[i], actual->arr[i + 1]);
                        swapped = true;
                    }
                }


                if (actual->next != nullptr && actual->top > 0 && actual->next->top > 0)
                {
                    if (actual->arr[actual->top - 1] > actual->next->arr[0]) 
                    {
                        std::swap(actual->arr[actual->top - 1], actual->next->arr[0]);
                        swapped = true;
                    }
                }
                actual = actual->next;
            }
        } while (swapped);
    }


    void Imprimir() 
    {
        Nodo<T>* actual = head;
        while (actual != nullptr)
        {
            for (int i = 0; i < actual->top; ++i)
            {
                std::cout << actual->arr[i] << " ";
            }
            actual = actual->next;
            cout << " -> ";
        }
        std::cout << std::endl;
    }
};

int main()
{
    ListaEnlazada<int> lista(5);
    cout << "lista en blanco \n";
    lista.Imprimir();
    cout << "--------------------------- \n";



    lista.insert_back(1);
    lista.insert_back(2);
    lista.insert_back(3);
    lista.insert_back(4);
    lista.insert_back(5);

    lista.ordenar_lista();

    lista.Imprimir();

    lista.insert_back(6);
    lista.insert_back(7);
    lista.insert_back(8);
    lista.insert_back(9);

    lista.ordenar_lista();

    lista.Imprimir();


    lista.eliminar(2);
    lista.Imprimir();
    lista.eliminar(4);
    lista.Imprimir();
    lista.eliminar(6);
    lista.Imprimir();
    lista.eliminar(8);

    lista.Imprimir();
    lista.ordenar_lista();

    lista.Imprimir();

    return 0;
}
