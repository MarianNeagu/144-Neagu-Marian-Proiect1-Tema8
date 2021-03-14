#include <iostream>

class Multime
{
	int m_numberOfNumbers;
	int* m_set = nullptr;
public:

	// Constructori
	Multime(){m_numberOfNumbers = 0;}

	Multime(int numberOfNumbers)
	{
		m_numberOfNumbers = numberOfNumbers;
	}
	// ASTA NU O SA FIE AICI CA NU VREAU SA AIBE VALORI INITIALE
	// Multime(int numberOfNumbers, int initialValue)
	// {
	// 	m_numberOfNumbers = numberOfNumbers;
	// 	m_set = new int[m_numberOfNumbers];
	// 	for(int i = 0; i < m_numberOfNumbers; i++)
	// 		m_set[i] = initialValue;
	// }

	// TODO Constructor cu numOfNum si vector
	Multime(int numberOfNumbers, int array[])
	{
		m_numberOfNumbers = numberOfNumbers;
		m_set = new int[m_numberOfNumbers];
		for(int i = 0; i < m_numberOfNumbers; i++)
			m_set[i] = array[i];
	}
	// TODO Constructor de copiere

	~Multime()
	{
		delete[] m_set;
	}

	// Gets & Sets
	int GetNumberOfNumbers();
	int* GetSet();
	void SetNumberOfNumbers(int num);
    void SetSet(int v[]);

	// Metode
	void ConvertArrayToSet();
	void DisplaySet();
	bool CheckIfSet();

	// Operatori
	friend Multime operator+(Multime m1, Multime m2);
	friend Multime operator-(Multime m1, Multime m2);
	friend Multime operator*(Multime m1, Multime m2);

};

#pragma region Setere si Getere

// Done
int Multime::GetNumberOfNumbers()
{
	return m_numberOfNumbers;
}

// Done
int* Multime::GetSet()
{
	return m_set;
}

// Done
void Multime::SetNumberOfNumbers(int num)
{
    m_numberOfNumbers = num;
	m_set = new int[m_numberOfNumbers];
}

// Done
void Multime::SetSet(int v[])
{
	if(m_numberOfNumbers > 0)
	{
		for(int i = 0; i < m_numberOfNumbers; i++)
			m_set[i] = v[i];
	}
	else
		std::cout<<"EROARE! Numarul de numere din multime nu a fost setat.";
}

#pragma endregion

#pragma region Metode

void Multime::ConvertArrayToSet()
{
	bool doubleValueFound = false;
	if(m_numberOfNumbers <= 0)
		std::cout<<"Eroare! Numarul de numere al vectorului nu a fost setat."<<std::endl;
	else
	{
		for(int i = 0; i < m_numberOfNumbers - 1; i ++)
			for(int j = i + 1; j < m_numberOfNumbers; j++)
			{
				if (m_set[i] == m_set[j])
				{
					doubleValueFound = true;
					for(int k = j; k < m_numberOfNumbers - 1; k++)
					{
						m_set[k] = m_set[k+1];
					}

					m_numberOfNumbers --;
					j--;
				}
			}
	}
	if(!doubleValueFound)
		std::cout<<"Nu s-au gasit duplicate in vector. Vectorul este deja multime."<<std::endl;
	else
	{
		std::cout<<"Vectorul a fost schimbat in multime, duplicatele fiind eliminate."<<std::endl;
		std::cout<<"Multimea acum are "<<m_numberOfNumbers<<" numere si anume:"<<std::endl;
		DisplaySet();
	}
}

void Multime::DisplaySet()
{
	for(int i = 0; i < m_numberOfNumbers; i++)
		std::cout<<m_set[i]<<" ";
	std::cout<<std::endl;
}

bool Multime::CheckIfSet()
{
	if(m_numberOfNumbers <= 0)
		std::cout<<"Eroare! Numarul de numere al vectorului nu a fost setat."<<std::endl;
	else
	{
		for(int i = 0; i < m_numberOfNumbers - 1; i ++)
			for(int j = i + 1; j < m_numberOfNumbers; j++)
			{
				if (m_set[i] == m_set[j])
				{
					return false;
				}
			}
	}
	return true;
}

#pragma endregion

// TODO Le meniu interactiv
#pragma region Functii

Multime GetReunion(Multime m1, Multime m2)
{
	Multime reunionSet;

	if(!m1.CheckIfSet())
		std::cout<<"Nu s-a putut face reuniunea deoarece primul parametru nu este multime. Folositi functia de conversie inainte pentru acesta!"
		<<std::endl;
	else if(!m2.CheckIfSet())
		std::cout<<"Nu s-a putut face reuniunea deoarece al doilea parametru nu este multime. Folositi functia de conversie inainte pentru acesta!"
		<<std::endl;
	else if(!m1.CheckIfSet() && !m2.CheckIfSet())
		std::cout<<"Nu s-a putut face reuniunea deoarece ambii parametrii nu sunt multimi. Folositi functia de conversie inainte pentru amandoi!"
		<<std::endl;
	else
	{
		reunionSet.SetNumberOfNumbers(m1.GetNumberOfNumbers() + m2.GetNumberOfNumbers());
		
		int indexFromTheSecondHalf = m1.GetNumberOfNumbers();

		for (int i = 0; i < m1.GetNumberOfNumbers(); i++)
			{
				reunionSet.GetSet()[i] = m1.GetSet()[i];

			}

		for (int i = 0; i < m2.GetNumberOfNumbers(); i++)
			{
				reunionSet.GetSet()[indexFromTheSecondHalf] = m2.GetSet()[i];
				indexFromTheSecondHalf++;
			}

		// Acum reunionSet este practic combinatia dintre cele 2 seturi date
		// Mai jos convertim (daca e cazul) reunionSet in set (poate exista duplicate)
		if(!reunionSet.CheckIfSet())
		{
			reunionSet.ConvertArrayToSet();
		}
	}

	return reunionSet;
}

void MainMenu()
{
	
}

# pragma endregion

#pragma region Operatori

Multime operator+ (Multime m1, Multime m2)
{
	return GetReunion(m1, m2);
}

#pragma endregion

int main()
{
	// Primul ex
	// Multime m(4, 0);
	// m.SetNumberOfNumbers(10);
	// int v[10] = {6, 2, 3, 2, 2, 3, 5, 8, 3, 6};
	// m.SetSet(v);
	// m.ConvertArrayToSet();
	//END Primul ex

	// Al doilea ex
	// int v[10] = {6, 2, 3, 2, 2, 3, 5, 8, 3, 6};
	// Multime m1(4, v);
	// m1.DisplaySet(); // Pentru asta pur si simplu memoreaza cat ii pui tu la parametru
	// Multime m2(11, v); 
	// m2.DisplaySet(); // Pentru asta o sa puna numere random din memorie 
	// END Al doilea ex

	// Al treilea ex
	// Multime m(4);
	// int v[4] = {6, 2, 3, 2};
	// v[0] = v[3] = 23;
	// m.SetSet(v);
	// std::cout<<m.GetSet()[3]<<" "<<m.GetSet()[2]<<std::endl;
	// END Al treilea ex

	// Al 4-lea ex
	int v1[4] = {6, 2, 3, 1};
	int v2[6] = {3, 2, 8, 9, 1, 5};
	Multime m1(4, v1), m2(6, v2), reunionSet;

	reunionSet = m1 + m2;

	reunionSet.DisplaySet(); 
	// END Al 4-lea ex
	return 0;
}
