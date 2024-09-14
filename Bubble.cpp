#include <iostream>

using namespace std;

template<class T>
class Asc
{
public:
	bool operator()(T a, T b)
	{
		return a > b;
	}
};
template<class T>
class Desc
{
public:
	bool operator()(T a, T b)
	{
		return b > a;
	}
};

template <class T, class O>

struct Bubble
{
	void operator()(T* ini, T* fin)
	{
		O op;
		bool sigue = true;
		while ((ini < fin) && sigue)
		{
			sigue = false;

			for (T* p = ini; p < fin; p++)
			{
				if (op(*p, *(p + 1)))
				{
					swap(*p, *(p + 1));
					sigue = true;
				}
			}
			fin--;
		}
	}
};

int main()
{

	int A[6] = { 6,5,4,3,2,1 };
	char B[6] = { 'b','a','c','d','e','f' };

	Bubble<int, Asc<int>> b;

	b(A, A + 5);

	for (int* p = A; p < A + 6; p++)
	{
		cout << *p << " ";
	}
	cout << "\n";


	Bubble<char, Desc<char>> c;

	c(B, B + 5);

	for (char* p = B; p < B + 6; p++)
	{
		cout << *p << " ";
	}
	cout << "\n";
};



