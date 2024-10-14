#include <iostream>

using namespace std;

class Deque
{
public:
	int** base;
	int size;
	int cont;
	int** ini;
	int** fin;
	int* ini2;
	int* fin2;
	Deque(int s) { base = new int* [size], size = s, ini = base + (size / 2), fin = ini, *ini=new int[size], ini2 = *ini + size/2, fin2 = ini2, cont = 0; }

	void push_back(int valor)
	{
		if (ini == fin)
		{
			if (ini2 == fin2)
			{
				*ini2 = valor;
				fin2++;
				cont++;
			}
			else if (fin2 == ini2 + size)
			{
				*fin2 = valor;
				fin++;
				fin2 = *fin;
				cont++;
			}
			else
			{
				*fin2 = valor;
				fin2++;
				cont++;
			}
		}
		else
		{
			if (fin2 == *fin)
			{
				*fin2 = valor;
				fin2++;
				cont++;
			}
			else if (fin2 == *fin + size)
			{
				*fin2 = valor;
				fin++;
				fin2 = *fin;
				cont++;
			}
			else
			{
				*fin2 = valor;
				fin2++;
				cont++;
			}
		}

	}
	void push_front(int valor)
	{
		if (ini2 == *ini)
		{
			*ini2 = valor;
			ini--;
			ini2 = *(ini +size);	
			cont++;
		}
		else if (ini2 == fin2)
		{
			*ini2 = valor;
			ini2--;
			cont++;
		}
		else
		{
			ini2--;
			*ini2 = valor;
			cont++;
		}
		
	}
	void pop_back()
	{
		if (ini2 == fin2)
		{
			cout << "No hay elementos para eliminar\n";
		}
		else if (fin2 == *ini)
		{
			ini--;
			fin2 = *ini + 5;
			cont--;
		}
		else
		{
			fin2--;
			cont--;
		}
	}
	void pop_front()
	{

		if (ini2 == fin2)
		{
			cout << "No hay elementos\n";
		}
		else if (ini2 == *ini + 5)
		{
			ini++;
			ini2 = *ini;
			cont--;
		}
		else
		{
			ini2++;
			cont--;
		}
	}

	void print()
	{
		int* actual = ini2;
		for (int i = 0; i < cont; actual++, i++)
		{
			cout << *actual << " ";
		}
		cout << endl;
	}
};









int main()
{
	Deque deck(5);
	deck.push_back(1);
	deck.push_back(3);
	deck.push_back(5);
	deck.push_back(2);
	deck.push_back(8);
	deck.push_back(10);
	deck.print();

	deck.push_front(7);

	deck.print();

	deck.pop_back();
	deck.print();
	deck.pop_front();
	deck.print();

	return 0;
}
	




