#include <iostream>

using namespace std;

class Vector
{
public:
	int* ini;
	int* fin;
	int size;
	int Osize;
	
	
	Vector(int s) { ini = new int[size], size = s, fin = ini,Osize=s; }


	int* operator[](int pos)
	{
		if (ini == fin)
		{
			cout << "No hay\n";
			return nullptr;
		}
		else
		{
			int cont{ 0 };
			int* actual = ini;
			for (; actual < fin;actual++)
			{	
				cont++;
				if (cont == pos)
				{
					return actual;
				}
			}
		}
	}

	void push_back(int valor)
	{
		int* actual = fin;
		if (fin == ini + size)
		{
			actual = ini;
			int* Nuevo = new int[size*2];
			int* comienzo = Nuevo;
			for (;actual<fin;actual++,Nuevo++)
			{
				*Nuevo = *actual;
			}
			ini = comienzo;
			fin = Nuevo ;
			*fin = valor;
			fin++;
			size = size * 2;
		}
		else
		{
			*actual = valor;
			fin++;
		}		
	}
	void push_front(int valor)
	{
		bool primer = false;
		if (fin == ini + size)
		{
			int* actual = ini;
			int* Nuevo = new int[size * 2];
			int* comienzo = Nuevo;
			for (; actual < fin; actual++, Nuevo++)
			{
				*Nuevo = *actual;
			}
			ini = comienzo;
			fin = Nuevo;
			size = size * 2;

			actual = fin;
			for (; ini < actual; actual--)
			{
				*actual = *(actual - 1);
			}
			*ini = valor;
			fin++;


		}
		else
		{
			int* actual = fin;
			for (; ini<actual; actual--)
			{
				*actual = *(actual - 1);
			}
			*ini = valor;
			fin++;
		}
	}
	
	void pop_front()
	{
		if (fin == ini)
		{
			cout << "No hay elementos a eleminar\n";
		}
		else if ((fin == (ini + (size / 2)) && Osize<size))
		{
			int* actual = ini;
			int* Nuevo = new int[size / 2];
			int* Comienzo = Nuevo;
			for (; actual < fin; actual++, Nuevo++)
			{
				*Nuevo = *actual;
			}
			ini = Comienzo;
			fin = Nuevo;
			size = size / 2;

			actual = ini;
			for (; actual < fin; actual++)
			{
				*actual = *(actual + 1);
			}
			fin--;

		}
		else
		{
			
			int* actual = ini;
			for (; actual < fin; actual++)
			{
				*actual = *(actual + 1);
			}
			fin--;
		}
	}
	void pop_back()
	{
		int* actual = fin;
		if (fin == ini)
		{
			cout << "No hay elementos a eleminar\n";
		}
		else if ((fin == (ini + (size / 2)) && Osize<size))
		{
			int* actual = ini;
			int* Nuevo = new int[size / 2];
			int* Comienzo = Nuevo;
			for (; actual < fin; actual++, Nuevo++)
			{
				*Nuevo = *actual;
			}
			ini = Comienzo;
			fin = Nuevo;
			fin--;
			size = size / 2;

		}
		else
		{
			fin--;
			*fin = 0;
		}
	}

	void print()
	{
		for (int *i=ini;i<fin; i++)
		{
			cout << *i << " ";
		}
		cout << endl;
	}
		
	//~Vector();
	
};


int main()
{

	Vector vec(5);

	vec.print();
	vec.push_back(1);
	vec.print();
	vec.push_back(3);
	vec.print();
	vec.push_front(4);
	vec.print();
	vec.push_front(7);
	vec.print();
	vec.push_back(10);
	vec.print();
	vec.push_back(15);
	vec.print();
	vec.pop_back();
	vec.print();
	cout << "popfront (borrar 7)\n";
	vec.pop_front();
	vec.print();
	vec.pop_front();
	vec.print();
	vec.push_back(22);
	vec.print();

	vec.push_back(18);
	vec.print();

	vec.push_back(12);
	vec.print();

	vec.push_back(11);
	vec.print();

	vec.push_back(16);
	vec.print();
	vec.push_front(50);
	vec.print();

	vec.push_front(28);
	vec.print();
	vec.push_front(32);
	vec.print();

	
	cout<<*vec.operator[](5);
	return 0;
}

