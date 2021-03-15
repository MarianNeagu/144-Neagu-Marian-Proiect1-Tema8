#include <iostream>
#include <cstring>

class Multime
{
	int m_numberOfNumbers;
	int* m_set = nullptr;
public:

	// Constructori
	Multime(){m_numberOfNumbers = 0;m_set = new int[m_numberOfNumbers];}

	// Constructor doar cu numberOfNumbers - val vectorului vor fi toate 0
	Multime(int numberOfNumbers)
	{
		m_numberOfNumbers = numberOfNumbers;
		m_set = new int[m_numberOfNumbers];
		for(int i = 0; i < m_numberOfNumbers; i++)
			m_set[i] = 0;
	}
	
	// TODO (optional)
	// Multime(int array[])
	// {
	// 	//m_numberOfNumbers = sizeof(array) / sizeof(array[0]);
	// }

	// Constructor cu numOfNum si vector - aici elementele vor fi cele din vectorul transmis
	Multime(int numberOfNumbers, int array[])
	{
		m_numberOfNumbers = numberOfNumbers;
		m_set = new int[m_numberOfNumbers];
		for(int i = 0; i < m_numberOfNumbers; i++)
			m_set[i] = array[i];
	}

	// ASTA NU O SA FIE AICI CA NU VREAU SA AIBE VALORI INITIALE
	// Multime(int numberOfNumbers, int initialValue)
	// {
	// 	m_numberOfNumbers = numberOfNumbers;
	// 	m_set = new int[m_numberOfNumbers];
	// 	for(int i = 0; i < m_numberOfNumbers; i++)
	// 		m_set[i] = initialValue;
	// }

	// Constructor de copiere
	Multime (const Multime &multime)
	{
		m_numberOfNumbers = multime.m_numberOfNumbers;
		m_set = new int[m_numberOfNumbers];
		for(int i = 0; i < m_numberOfNumbers; i++)
			m_set[i] = multime.m_set[i];
	};

	~Multime()
	{
		delete[] m_set;
		m_set = nullptr;

	}

	// Gets & Sets
	int GetNumberOfNumbers();
	int* GetSet();
	void SetNumberOfNumbers(int num);
    void SetSet(int v[]);
	void InitializeSet(int numberOfNumbers);

	// Metode
	void ConvertArrayToSet();
	void DisplaySet(); // nu stiu daca mai are neaparat rost, fiindca am suprascris <<
	bool CheckIfSet();
	void ChangeElementAtIndex(int index, int newElem);

	// Operatori
	friend Multime operator+ (Multime m1, Multime m2);
	friend Multime operator- (Multime m1, Multime m2);
	friend Multime operator* (Multime m1, Multime m2);
	Multime& operator= (const Multime &multime)
	{
		// mai intai dezalocam memoria pe care o avea m_set
		delete[] m_set;
		m_numberOfNumbers = 0;
		m_set = nullptr;

		// acum assignment
		m_numberOfNumbers = multime.m_numberOfNumbers;
		m_set = new int[m_numberOfNumbers];
		for(int i = 0; i < m_numberOfNumbers; i++)
			m_set[i] = multime.m_set[i];
		return *this;
	}
	friend std::istream& operator>> (std::istream& in,  Multime& multime);
	friend std::ostream& operator<< (std::ostream& out, const Multime& multime);
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


void Multime::InitializeSet(int numberOfNumbers)
{
	m_numberOfNumbers = numberOfNumbers;
	m_set = new int[m_numberOfNumbers];
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
	// else
	// {
	// 	std::cout<<"Vectorul a fost schimbat in multime, duplicatele fiind eliminate."<<std::endl;
	// 	std::cout<<"Multimea acum are "<<m_numberOfNumbers<<" numere si anume:"<<std::endl;
	// DisplaySet();
	// }
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

void Multime::ChangeElementAtIndex(int index, int newElem)
{
	if(index >= 0 && index < m_numberOfNumbers)
		m_set[index] = newElem;
	else
		std::cout<<"Indexul introdus nu exista in multime!"<<std::endl;
}

#pragma endregion

// TODO Le meniu interactiv
#pragma region Functii

Multime GetReunion(Multime m1, Multime m2)
{
	if(m1.GetNumberOfNumbers() > 0 || m2.GetNumberOfNumbers() > 0)
	{
		Multime reunionSet;

		if(!m1.CheckIfSet() && !m2.CheckIfSet())
			std::cout<<"Nu s-a putut face reuniunea deoarece niciun parametru nu este multime. Folositi functia de conversie inainte pentru ambii!"
			<<std::endl;
		else if(!m1.CheckIfSet())
			std::cout<<"Nu s-a putut face reuniunea deoarece primul parametru nu este multime. Folositi functia de conversie inainte pentru acesta!"
			<<std::endl;
		else if(!m2.CheckIfSet())
			std::cout<<"Nu s-a putut face reuniunea deoarece al doilea parametru nu este multime. Folositi functia de conversie inainte pentru acesta!"
			<<std::endl;
		else
		{
			reunionSet.InitializeSet(m1.GetNumberOfNumbers() + m2.GetNumberOfNumbers());
			
			int indexFromTheSecondHalf = m1.GetNumberOfNumbers();

			for (int i = 0; i < m1.GetNumberOfNumbers(); i++)
				reunionSet.ChangeElementAtIndex(i, m1.GetSet()[i]);

			for (int i = 0; i < m2.GetNumberOfNumbers(); i++)
			{
				reunionSet.ChangeElementAtIndex(indexFromTheSecondHalf, m2.GetSet()[i]);
				indexFromTheSecondHalf++;
			}

			// Acum reunionSet este practic combinatia dintre cele 2 seturi date
			// Mai jos convertim (daca e cazul) reunionSet in set (poate exista duplicate)
			if(!reunionSet.CheckIfSet())
				reunionSet.ConvertArrayToSet();

		}

		return reunionSet;
	}
	else
		std::cout<<"Parametrii dati nu au valori."<<std::endl;
	return 0;
}

Multime GetIntersection(Multime m1, Multime m2)
{
	
	if(m1.GetNumberOfNumbers() > 0 || m2.GetNumberOfNumbers() > 0)
	{
		Multime intersectionSet;
		int numberOfEqualNumbers = 0;
		int currentIntersectionSetIndex = -1;

		if(!m1.CheckIfSet() && !m2.CheckIfSet())
			std::cout<<"Nu s-a putut face interesectia deoarece niciun parametru nu este multime. Folositi functia de conversie inainte pentru ambii!"
			<<std::endl;
		else if(!m1.CheckIfSet())
			std::cout<<"Nu s-a putut face interesectia deoarece primul parametru nu este multime. Folositi functia de conversie inainte pentru acesta!"
			<<std::endl;
		else if(!m2.CheckIfSet())
			std::cout<<"Nu s-a putut face interesectia deoarece al doilea parametru nu este multime. Folositi functia de conversie inainte pentru acesta!"
			<<std::endl;
		else
		{
			// Mai intai calculam cata memorie trebuie alocata pentru multime
			for(int i = 0; i < m1.GetNumberOfNumbers(); i++)
				for(int j = 0; j < m2.GetNumberOfNumbers(); j++)
					if(m1.GetSet()[i] == m2.GetSet()[j])
						numberOfEqualNumbers++;

			// Daca exista numere egale atunci alocam memoria necesara si atribuim valorile corespunzatoare
			if(numberOfEqualNumbers)
			{
				intersectionSet.InitializeSet(numberOfEqualNumbers);
				
				for(int i = 0; i < m1.GetNumberOfNumbers(); i++)
					for(int j = 0; j < m2.GetNumberOfNumbers(); j++)
						if(m1.GetSet()[i] == m2.GetSet()[j])
						{	
							currentIntersectionSetIndex++;
							intersectionSet.ChangeElementAtIndex(currentIntersectionSetIndex, m1.GetSet()[i]);
	
						}

				return intersectionSet;
			}
			else
				std::cout<<"Multimile sunt disjuncte!"<<std::endl;

		}
	}
	else
		std::cout<<"Parametrii dati nu au valori."<<std::endl;
	return 0;
}

Multime GetDifference(Multime m1, Multime m2)
{
	if(m1.GetNumberOfNumbers() > 0 || m2.GetNumberOfNumbers() > 0)
	{
		Multime differenceSet;
		int numberOfEqualNumbers = 0;
		int currentIntersectionSetIndex = -1;

		if(!m1.CheckIfSet() && !m2.CheckIfSet())
			std::cout<<"Nu s-a putut face diferenta deoarece niciun parametru nu este multime. Folositi functia de conversie inainte pentru ambii!"
			<<std::endl;
		else if(!m1.CheckIfSet())
			std::cout<<"Nu s-a putut face diferenta deoarece primul parametru nu este multime. Folositi functia de conversie inainte pentru acesta!"
			<<std::endl;
		else if(!m2.CheckIfSet())
			std::cout<<"Nu s-a putut face diferenta deoarece al doilea parametru nu este multime. Folositi functia de conversie inainte pentru acesta!"
			<<std::endl;
		else
		{
			int numberOfNumbers_differenceSet = 0;
			// Mai intai cata memorie trebuie alocata pentru setul ce trebuie returnat
			for(int i = 0; i < m1.GetNumberOfNumbers(); i++)
			{
				bool sameElementInBoth = false;
				for(int j = 0; j < m2.GetNumberOfNumbers(); j++)
					if(m1.GetSet()[i] == m2.GetSet()[j])
						sameElementInBoth = true;
				if(!sameElementInBoth)
					numberOfNumbers_differenceSet++;
			}	
			// Daca exista numere care sunt in m1 dar nu si in m2, atunci atribuim aceste numere multimii noi
			if(numberOfNumbers_differenceSet)
			{
				differenceSet.InitializeSet(numberOfNumbers_differenceSet);
				int currentIndex = 0;
				for(int i = 0; i < m1.GetNumberOfNumbers(); i++)
				{
					bool sameElementInBoth = false;
					for(int j = 0; j < m2.GetNumberOfNumbers(); j++)
						if(m1.GetSet()[i] == m2.GetSet()[j])
							sameElementInBoth = true;
					if(!sameElementInBoth)
					{
						differenceSet.ChangeElementAtIndex(currentIndex, m1.GetSet()[i]);
						currentIndex++;
					}
				}
				return differenceSet;
			}
			else // diferenta e multimea vida
			{
				std::cout<<"Diferenta este multimea vida."<<std::endl;
			}
		}
	}
	else
		std::cout<<"Parametrii dati nu au valori."<<std::endl;
	return 0;
}

Multime* _ReadTheObjects(int &numberOfObjects)
{
	Multime* multime = new Multime[numberOfObjects];

	for(int i = 0; i < numberOfObjects; i++)
	{
		int numberOfNumbers = 0;
		std::cout<<"~ Multimea curenta de citit este "<<i+1<<" ~"<<std::endl;
		std::cout<<"Introduceti numarul de valori pe care sa le aiba multimea:"<<std::endl;
		std::cin>>numberOfNumbers;
		int* array = new int[numberOfNumbers];
		std::cout<<"Introduceti elementele multimii"<<std::endl;
		for(int i = 0; i < numberOfNumbers; i++)
		{
			std::cout<<"Elementul "<<i+1<<": ";
			std::cin>>array[i];
		}
		multime[i].SetNumberOfNumbers(numberOfNumbers);
		multime[i].SetSet(array);
		std::cout<<"Elementele multimii au fost citite! Multimea "<<i+1<<" este:"<<std::endl;
		std::cout<<multime[i]<<std::endl;
	}
	std::cout<<"~ Multimile au fost salvate! Cele "<<numberOfObjects<<" multimi citite sunt:"<<std::endl;
	for(int i = 0; i < numberOfObjects; i++)
		std::cout<<i+1<<". "<<multime[i];
	return multime;

}

void ReadNObjects(Multime* &multime)
{
	int numberOfObjects;
	
	std::cout<<"Introduceti numarul de multimi de citit: "<<std::endl;
	std::cin>>numberOfObjects;

	multime = new Multime[numberOfObjects];
	multime = _ReadTheObjects(numberOfObjects);
}

// TODO
void MainMenu(Multime* &multime)
{
	
}


# pragma endregion

#pragma region Operatori

Multime operator+ (Multime m1, Multime m2)
{
	return GetReunion(m1, m2);
}
Multime operator- (Multime m1, Multime m2)
{
	return GetDifference(m1, m2);	
}
Multime operator* (Multime m1, Multime m2)
{
	return GetIntersection(m1, m2);
}

std::istream& operator>> (std::istream& in,  Multime& multime)
{
    in>>multime.m_numberOfNumbers;
	multime.m_set = new int[multime.m_numberOfNumbers];
    for(int i = 0; i < multime.m_numberOfNumbers; i++)
		in>>multime.m_set[i];
	return in;
}

std::ostream& operator<< (std::ostream& out, const Multime& multime)
{
	std::cout<<"{";
	for(int i = 0; i < multime.m_numberOfNumbers - 1; i++)
		out<<multime.m_set[i]<<", ";

	out<<multime.m_set[multime.m_numberOfNumbers - 1];
	std::cout<<"}"<<std::endl;

	return out;
}

#pragma endregion

int main()
{
	std::cout<<"Neagu Marian-Madalin - Tema 8. Clasa ~Multime~"<<std::endl<<std::endl;
	std::cout<<"Introdu y pentru a porni sau n pentru a iesi: ";
	char comanda;
	std::cin>>comanda;
	while(toupper(comanda) != 'Y')
	{
		if(toupper(comanda) == 'N')
			return 0;
		else
			std::cout<<"Comanda neacceptata.."<<std::endl;
		std::cout<<"Introdu y pentru a porni sau n pentru a iesi: ";
		std::cin>>comanda;
	}
	
	std::cout<<std::endl<<"~ Pentru inceput este nevoie sa introduceti multimile dorite ~"<<std::endl;

	Multime* multime;
	ReadNObjects(multime);

	MainMenu(multime);

	return 0;
}
