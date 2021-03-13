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
	//ASTA NU O SA FIE AICI CA NU VREAU SA AIBE VALORI INITIALE
	Multime(int numberOfNumbers, int initialValue)
	{
		m_numberOfNumbers = numberOfNumbers;
		m_set = new int[m_numberOfNumbers];
		for(int i = 0; i < m_numberOfNumbers; i++)
			m_set[i] = initialValue;
	}

	//TODO Constructor cu numOfNum si vector


	~Multime()
	{
		delete[] m_set;
	}

	// Metode
	void ConvertArrayToSet();
	void DisplaySet();

	// Gets & Sets
	int GetNumberOfNumbers();
	int* GetSet();
	void SetNumberOfNumbers(int num);
    void SetSet(int v[]);
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
		std::cout<<"Eroare! Numarul de numere al vectorului nu a fost setat.";
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
}

#pragma endregion

// TODO Le meniu interactiv
void MainMenu()
{
	
}

int main()
{
	Multime m(4, 0);
	m.SetNumberOfNumbers(10);

	int v[10] = {6, 2, 3, 2, 2, 3, 5, 8, 3, 6};
	m.SetSet(v);

	m.ConvertArrayToSet();

	// v[0] = v[3] = 23;

	// m.SetSet(v);
	// std::cout<<m.GetSet()[3]<<" "<<m.GetSet()[2]<<std::endl;

	return 0;
}
