#include <iostream>

using namespace std;

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
		return a > b;
	}
};


template<class T>
class Nodo
{
public:

	T valor;
	Nodo* next;
	Nodo* prev;

	Nodo(T v) { next = nullptr, valor = v,prev = nullptr; }
};

template<class T,class O>
class LE
{
public: 
	Nodo<T>* head;
	O orden;
	LE() { head = nullptr; }
	
	void push_front(T valor)
	{
		orden;
		Nodo<T>* nuevo_nodo = new Nodo<T>(valor);
		nuevo_nodo->next = head;
		head = nuevo_nodo;
	}
	void push_back(T valor)
	{
		orden;
		Nodo<T>* nuevo_nodo = new Nodo<T>(valor);
		Nodo<T>* actual = head;
		if (head != nullptr)
		{
			while (actual->next != nullptr)
			{
				actual->prev = actual;
				actual = actual->next;
			}
			actual->next = nuevo_nodo;
			
		}
		else
		{
			head = nuevo_nodo;
		}

	}

	void push_anywhere(T valor, int pos)
	{
		orden;
		int contador{0};
		Nodo<T>* nuevo_nodo = new Nodo<T>(valor);
		Nodo<T>* actual = head;

		if (head != nullptr)
		{
			while (actual->next != nullptr)
			{
				actual->prev = actual;
				actual = actual->next;
				contador++;
			}
			actual = head;
			if (pos <= contador)
			{
				for (int i{ 0 }; i < pos-1; i++)
				{
					actual = actual->next;
				}
				Nodo<T>* tmp = actual->next;
				actual->prev = actual;
				actual->next = nuevo_nodo;
				actual = actual->next;
				actual->next = tmp; 
			}
			else
			{
				cout << "No existe esa posicion.\n";
				return;
			}
		}
		else
		{
			head = nuevo_nodo;
		}
	}

	void pop_front()
	{
		orden;
		Nodo<T>* actual = head;
		actual->prev = actual;

		if (head != nullptr)
		{
			actual = actual->next;
			actual->prev = nullptr;
			head = actual;			
		}
		else
		{
			cout << "No hay nada para eliminar.\n";
			return;
		}
		delete actual->prev;
	}

	void pop_back()
	{
		orden;
		Nodo<T>* actual = head;
		actual->prev=actual;
		if (head != nullptr)
		{
			Nodo<T>* anterior = actual;
			while (actual->next != nullptr)
			{
				anterior->prev = anterior;
				anterior = actual;
				actual = actual->next;
			}
			anterior->next = nullptr;
			
		}
		else
		{
			cout << "No hay nada para eliminar.\n";
			return;
		}
	}

	void pop_pos(int pos)
	{
		orden;
		int contador{ 0 };
		Nodo<T>* actual = head;
		if (head != nullptr)
		{
			Nodo<T>* prev = actual;
			while(actual->next != nullptr)
			{
				prev = actual;
				actual = actual->next;
				contador++;
			}
			if (contador > pos)
			{
				actual = head;
				prev = actual;
				for (int i{ 0 }; i < contador-1; i++)
				{
					prev = actual;
					actual = actual->next;
				}
				Nodo<T>* tmp = actual->next;
				actual = nullptr;
				prev->next = tmp;
			}
			else
			{
				cout << "No hay esa cantidad de elementos.\n";
			}
			
		}
		else
		{
			cout << "No hay nada para eliminar.\n";
			return;
		}
	}
	void pop_anywhere(T aEliminar)
	{
		Nodo<T>* actual = head;
		Nodo<T>* prev = actual;
		bool eliminado = false;
		while (actual->valor != aEliminar || actual->next!=nullptr)
		{
			if (actual->valor == aEliminar)
			{
				prev->next = actual->next;
				actual = nullptr;
				eliminado = true;
				break;
			}
			prev = actual;
			actual = actual->next;
		}
		
		if (eliminado == false)
		{
			cout << "No se encontro el elemento a eliminar.\n";
		}
		

	}

	bool find(T valor)
	{
		Nodo<T>* actual = head;
		
		while (actual->next != nullptr)
		{
			if (actual->valor != valor)
			{
				actual->prev = actual;
				actual = actual->next;
			}
			else
			{
				cout << "Se encontro el elemento elegido(" << valor << ")\n";
				return true;
			}
		}
		cout << "No se encontro el elemento elegido(" << valor << ")\n";
		return false;
	}

	void Reversion()
	{
		int contador{ 0 };
		Nodo<T>* actual = head;
		while (actual->next != nullptr)
		{
			actual->prev = actual;
			actual = actual->next;
			contador++;

		}
		
		Nodo<T>* cambio = head;
		Nodo<T>* tmp = new Nodo<T>(0);
		for (int i{ 0 };i < (contador / 2);i++)
		{
			
			tmp->valor = actual->valor;
			actual->valor = cambio->valor;
			cambio->valor = tmp->valor;
			
			cambio = cambio->next;
			actual = actual->prev;
		}



	}

	void print()
	{
		Nodo<T>* actual = head;
		while (actual != nullptr)
		{
			cout << actual->valor << " -> ";
			actual = actual->next;
		}
		cout << "nullptr\n";
	}
};

int main()
{
	LE<int,Asc<int> >lista;
	lista.push_front(10);
	lista.print();
	lista.push_back(11);
	lista.print();
	lista.push_front(5);
	lista.push_front(6);
	lista.push_front(12);
	lista.print();
	lista.push_anywhere(50,4);
	lista.print();

	cout << "pop anywhere\n";

	lista.pop_anywhere(6);
	lista.print();
	lista.pop_back();
	lista.print();
	lista.pop_front();
	lista.print();
	lista.pop_pos(2);
	lista.print();
	lista.pop_pos(100);
	lista.print();
	lista.find(100);
	lista.find(5);
	lista.Reversion();
	lista.print();
	lista.Reversion();
	lista.print();

	cout << "CHARS\n";

	LE<char,Asc<char>> lista2;
	lista2.push_front('a');
	lista2.print();
	lista2.push_back('g');
	lista2.print();
	lista2.push_front('L');
	lista2.push_front('P');
	lista2.push_front('K');
	lista2.print();
	lista2.push_anywhere('Z', 4);
	lista2.print();

	cout << "pop anywhere\n";
	lista2.pop_anywhere('P');
	lista2.print();
	lista2.pop_back();
	lista2.print();
	lista2.pop_front();
	lista2.print();
	lista2.pop_pos(1);
	lista2.print();
	lista2.pop_pos(100);
	lista2.print();
	lista2.find('X');
	lista2.find('P');
	lista2.Reversion();
	lista2.print();
	lista2.Reversion();
	lista2.print();

	return 0;
}
