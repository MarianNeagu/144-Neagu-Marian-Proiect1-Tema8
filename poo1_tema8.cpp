#include <iostream>
#include <cstring>

int numberOfObjects_global;

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
		

		// Completare convertToSet
		bool doubleValueFound = false;

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

	
	Multime(int numberOfNumbers, int initialValue)
	{
		m_numberOfNumbers = numberOfNumbers;
		m_set = new int[m_numberOfNumbers];
		for(int i = 0; i < m_numberOfNumbers; i++)
			m_set[i] = initialValue;
	}

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
	void ReinitialiseSet(int numberOfNumbers, int array[]);

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
	m_numberOfNumbers = 0;
	delete[] m_set;
	m_set = nullptr;
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
	// if(!doubleValueFound)
	// 	std::cout<<"Nu s-au gasit duplicate in vector. Vectorul este deja multime."<<std::endl;
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

void Multime::ReinitialiseSet(int numberOfNumbers, int array[])
{
	m_numberOfNumbers = 0;
	delete[] m_set;
	m_set = nullptr;

	m_numberOfNumbers = numberOfNumbers;	
	m_set = new int[m_numberOfNumbers];

	for(int i = 0; i < m_numberOfNumbers; i++)
		m_set[i] = array[i];
	
	ConvertArrayToSet();
}

#pragma endregion

// TODO Le meniu interactiv
#pragma region Functii

Multime GetReunion(Multime m1, Multime m2)
{
	int v[1] = {0};
	Multime reunionSet, nullSet(1, v);
	if(m1.GetNumberOfNumbers() > 0 || m2.GetNumberOfNumbers() > 0)
	{
		

		if(!m1.CheckIfSet() && !m2.CheckIfSet())
			std::cout<<"Nu s-a putut face reuniunea deoarece niciun parametru nu este multime. Folositi comanda de conversie inainte pentru ambii!"
			<<std::endl;
		else if(!m1.CheckIfSet())
			std::cout<<"Nu s-a putut face reuniunea deoarece primul parametru nu este multime. Folositi comanda de conversie inainte pentru acesta!"
			<<std::endl;
		else if(!m2.CheckIfSet())
			std::cout<<"Nu s-a putut face reuniunea deoarece al doilea parametru nu este multime. Folositi comanda de conversie inainte pentru acesta!"
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
	return nullSet;
}

Multime GetIntersection(Multime m1, Multime m2)
{
	int v[1] = {0};
	Multime intersectionSet, nullSet(1, v);
	
	if(m1.GetNumberOfNumbers() > 0 || m2.GetNumberOfNumbers() > 0)
	{
		
		int numberOfEqualNumbers = 0;
		int currentIntersectionSetIndex = -1;

		if(!m1.CheckIfSet() && !m2.CheckIfSet())
			std::cout<<"Nu s-a putut face interesectia deoarece niciun parametru nu este multime. Folositi comanda de conversie inainte pentru ambii!"
			<<std::endl;
		else if(!m1.CheckIfSet())
			std::cout<<"Nu s-a putut face interesectia deoarece primul parametru nu este multime. Folositi comanda de conversie inainte pentru acesta!"
			<<std::endl;
		else if(!m2.CheckIfSet())
			std::cout<<"Nu s-a putut face interesectia deoarece al doilea parametru nu este multime. Folositi comanda de conversie inainte pentru acesta!"
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
				std::cout<<"Multimea vida"<<std::endl;

		}
	}
	else
		std::cout<<"Parametrii dati nu au valori."<<std::endl;
	

	return nullSet;
}

Multime GetDifference(Multime m1, Multime m2)
{
	int v[1] = {0};
	Multime differenceSet, nullSet(1,v);
	

	if(m1.GetNumberOfNumbers() > 0 || m2.GetNumberOfNumbers() > 0)
	{
		
		int numberOfEqualNumbers = 0;
		int currentIntersectionSetIndex = -1;

		if(!m1.CheckIfSet() && !m2.CheckIfSet())
			std::cout<<"Nu s-a putut face diferenta deoarece niciun parametru nu este multime. Folositi comanda de conversie inainte pentru ambii!"
			<<std::endl;
		else if(!m1.CheckIfSet())
			std::cout<<"Nu s-a putut face diferenta deoarece primul parametru nu este multime. Folositi comanda de conversie inainte pentru acesta!"
			<<std::endl;
		else if(!m2.CheckIfSet())
			std::cout<<"Nu s-a putut face diferenta deoarece al doilea parametru nu este multime. Folositi comanda de conversie inainte pentru acesta!"
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
				std::cout<<"Multimea vida."<<std::endl;
			}
		}
	}
	else
		std::cout<<"Parametrii dati nu au valori."<<std::endl;
	return nullSet;
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
		
		// multime[i].SetNumberOfNumbers(numberOfNumbers);
		// multime[i].SetSet(array);

		Multime multime_temp(numberOfNumbers, array);
		multime[i] = multime_temp;

		std::cout<<"Elementele multimii au fost citite! Multimea "<<i+1<<" este:"<<std::endl;
		std::cout<<multime[i]<<std::endl;
	}
	std::cout<<"~ Multimile au fost salvate! Cele "<<numberOfObjects<<" multimi citite sunt:"<<std::endl;
	for(int i = 0; i < numberOfObjects; i++)
		std::cout<<i+1<<". "<<multime[i];
	numberOfObjects_global = numberOfObjects;
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

void MainMenu(Multime* &multime)
{
	int comanda = -1;	
	while(comanda != 0)
	{
		std::cout<<std::endl;
		std::cout<<"Intoduceti numarul operatiunii pe care doriti sa o executati: "<<std::endl;
		std::cout<<"0. Iesire"<<std::endl;
		std::cout<<"1. Afiseaza datele introduse"<<std::endl;
		std::cout<<"2. Verifica daca un parametru citit este multime"<<std::endl;
		std::cout<<"3. Conversie din vector in multime a unui parametru citit (elimina duplicatele)"<<std::endl;
		std::cout<<"4. Reuniunea a doua multimi"<<std::endl;
		std::cout<<"5. Diferenta a doua multimi"<<std::endl;
		std::cout<<"6. Intersectia a doua multimi"<<std::endl;
		std::cout<<"7. Citire a n multimi (Atentie! Multimile salvate la inceput vor fi inlocuite!)"<<std::endl;
		std::cout<<"Comanda: ";
		std::cin>>comanda;
		
		if(comanda == 0)
			break;
		else if(comanda == 1)
		{
			std::cout<<"Datele salvate sunt:"<<std::endl;
			for(int i = 0; i < numberOfObjects_global; i++)
				std::cout<<i+1<<". "<<multime[i];
		}
		else if(comanda == 2)
		{
			int indexMultime;
			std::cout<<"Datele salvate sunt:"<<std::endl;
			for(int i = 0; i < numberOfObjects_global; i++)
				std::cout<<i+1<<". "<<multime[i];
			
			std::cout<<"Introduceti numarul corespunzator vectorului pe care doriti sa il verificati: ";
			std::cin>>indexMultime;
			if(indexMultime >= 0 && indexMultime <= numberOfObjects_global)
			{
				if(multime[indexMultime-1].CheckIfSet())
					std::cout<<"~ Vectorul este multime! ~"<<std::endl;
				else
				{
					char comanda_yn;
					std::cout<<"~ Vectorul NU este multime! Doriti sa il convertiti in multime? [y/n]: ";
					std::cin>>comanda_yn;
					if(toupper(comanda_yn) == 'Y')
					{
						multime[indexMultime-1].ConvertArrayToSet();
						std::cout<<"~ Vectorul a fost convertit in multime! Acum arata astfel:"<<std::endl<<multime[indexMultime-1];
					}
				}
			}
			else
				std::cout<<"Numarul introdus nu este valid.."<<std::endl;
		}
		else if(comanda == 3)
		{
			int indexMultime;
			std::cout<<"Datele salvate sunt:"<<std::endl;
			for(int i = 0; i < numberOfObjects_global; i++)
				std::cout<<i+1<<". "<<multime[i];

			std::cout<<"Introduceti numarul corespunzator vectorului pe care doriti sa il convertiti in multime: ";
			std::cin>>indexMultime;

			if(indexMultime >= 0 && indexMultime <= numberOfObjects_global)
			{
				if(multime[indexMultime-1].CheckIfSet())
					std::cout<<"~ Vectorul este deja multime! ~"<<std::endl;
				else
				{
					multime[indexMultime-1].ConvertArrayToSet();
					std::cout<<"~ Vectorul a fost convertit in multime! Acum arata astfel:"<<std::endl<<multime[indexMultime-1];
				}
			}
			else
				std::cout<<"Numarul introdus nu este valid.."<<std::endl;
		}
		else if(comanda == 4)
		{
			int indexMultime1, indexMultime2;
			std::cout<<"Datele salvate sunt:"<<std::endl;
			for(int i = 0; i < numberOfObjects_global; i++)
				std::cout<<i+1<<". "<<multime[i];
			std::cout<<"Introduceti numarul corespunzator primei multimi: ";
			std::cin>>indexMultime1;
			std::cout<<"Introduceti numarul corespunzator celei de-a doua multime: ";
			std::cin>>indexMultime2;
			
			if(multime[indexMultime1 - 1].CheckIfSet() && multime[indexMultime2 - 1].CheckIfSet())
			{
				std::cout<<"Reuniunea celor doua multimi este: "<<std::endl;
				std::cout<<multime[indexMultime1 - 1] + multime[indexMultime2 - 1];
			}
				

		}
		else if(comanda == 5)
		{
			int indexMultime1, indexMultime2;
			std::cout<<"Datele salvate sunt:"<<std::endl;
			for(int i = 0; i < numberOfObjects_global; i++)
				std::cout<<i+1<<". "<<multime[i];
			std::cout<<"Introduceti numarul corespunzator primei multimi: ";
			std::cin>>indexMultime1;
			std::cout<<"Introduceti numarul corespunzator celei de-a doua multime: ";
			std::cin>>indexMultime2;
			
			if(multime[indexMultime1 - 1].CheckIfSet() && multime[indexMultime2 - 1].CheckIfSet())
			{
				std::cout<<"Diferenta celor doua multimi este: "<<std::endl;
				std::cout<<multime[indexMultime1 - 1] - multime[indexMultime2 - 1];
			}
				
		}
		else if(comanda == 6)
		{
			int indexMultime1, indexMultime2;
			std::cout<<"Datele salvate sunt:"<<std::endl;
			for(int i = 0; i < numberOfObjects_global; i++)
				std::cout<<i+1<<". "<<multime[i];
			std::cout<<"Introduceti numarul corespunzator primei multimi: ";
			std::cin>>indexMultime1;
			std::cout<<"Introduceti numarul corespunzator celei de-a doua multime: ";
			std::cin>>indexMultime2;
			
			if(multime[indexMultime1 - 1].CheckIfSet() && multime[indexMultime2 - 1].CheckIfSet())
			{
				std::cout<<"Intersectia celor doua multimi este: "<<std::endl;
				std::cout<<multime[indexMultime1 - 1] * multime[indexMultime2 - 1];
			}
			
		}
		else if(comanda == 7)
		{
			std::cout<<"test";
			multime = nullptr;
			numberOfObjects_global = 0;
			ReadNObjects(multime);
		}
		else
			std::cout<<"Comanda introdusa nu este acceptata. Reincercati.."<<std::endl;
	}
	std::cout<<"Iesire..";
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
	delete[] multime.m_set;
	multime.m_numberOfNumbers = 0;
	multime.m_set = nullptr;
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


void Demo()
{
	int v1[5] = {1,2,1,2,3};
	Multime m(5,v1);
	std::cout<<m<<std::endl;

	int v2[3] = {1,2, 2};
	m.ReinitialiseSet(3, v2);
	std::cout<<m<<std::endl;
}

int main()
{

	Demo();

	// Mesaj la inceput
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
	
	std::cout<<std::endl<<"~ Pentru inceput este nevoie sa introduceti multimile dorite ~"<<std::endl<<std::endl;

	Multime* multime;
	ReadNObjects(multime);
	MainMenu(multime);

	return 0;
}
