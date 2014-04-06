#include <iostream>
#include <time.h>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

#define PROG_WIELKOSCI_TABLICY 64

using namespace std;

int* Stworz_tablice(int ilosc_elementow);
int* Stworz_tablice(int* TAB_POM,int ilosc_elementow, int ile_sortowac, int ZAKRES_LOSOWANIA, int i);
void PRZYPISANIE(int** TABELA_SORTOWAN,int** TABELA, int ilosc_elementow, int rozmiar_tablicy);
void ZAPIS_CZASOW_DO_PLIKU(double TABELA_CZASOW[4][100],double TABELA_CZASOW_SUMY[4], int ilosc_elementow, double ile_posortowac, int zakres, int rozmiar_petli);

void Sortowanie_przez_Scalanie(int* TAB_POM, int* TABLICA, int lewy , int prawy);
int Sortowanie_Szybkie(int* TABLICA, int lewy , int prawy,int PIWOT, bool introspektywne);
void Sortowanie_Introspektywne(int* TABLICA, int poczatek,int koniec, int LIMIT, bool introspektywne);

void Sortowanie_Introspektywne_petla(int* TABLICA, int poczatek,int koniec, int LIMIT, bool introspektywne);
void Sortowanie_przez_kopcowanie(int* tablica,int lewy,int prawy);
void Kopiec(int* tablica, int poczatek,int koniec,int lewy);
int NAJLEPSZY_PIWOT(int* TABLICA, int lewy, int srodek, int prawy);

///-------------------------------------------------------
///	TWORZENIE TABLIC
///-------------------------------------------------------

int* Stworz_tablice(int ilosc_elementow)
{
	int* tablica = new int[ilosc_elementow];
	for(int i = 0; i < ilosc_elementow; i++)
		tablica[i] = NULL;
	return tablica;
}

int* Stworz_tablice(int* TAB_POM, int ilosc_elementow, int ile_posortowac, int ZAKRES_LOSOWANIA, int i)
{
	int* tablica = new int[ilosc_elementow];
	srand((unsigned)time(NULL)+i);

	if (ile_posortowac == 0)
	{
		for(int i = 0; i < ilosc_elementow; i++)
			tablica[i] = rand() % ZAKRES_LOSOWANIA;

		Sortowanie_przez_Scalanie(TAB_POM,tablica,0,ilosc_elementow-1);

		for (ile_posortowac ; ile_posortowac < ilosc_elementow/2 ; ile_posortowac++)
			swap(tablica[ile_posortowac],tablica[ilosc_elementow-1-ile_posortowac]);
	}
	else
	{
		int proc_wartosci = (ile_posortowac*ZAKRES_LOSOWANIA)/ilosc_elementow;
		for(int i = 0; i < ile_posortowac; i++)
			tablica[i] = rand() % proc_wartosci;

		Sortowanie_przez_Scalanie(TAB_POM,tablica,0,ile_posortowac-1);
		for (ile_posortowac ; ile_posortowac < ilosc_elementow ; ile_posortowac++)
			tablica[ile_posortowac] = proc_wartosci + rand() % (ZAKRES_LOSOWANIA-proc_wartosci);
	}
	return tablica;
};

///-------------------------------------------------------
///	NADPISYWANIE TABLICY I ZAPISYWANIE
///-------------------------------------------------------

void PRZYPISANIE(int** TABELA_SORTOWAN,int** TABELA, int ilosc_elementow, int rozmiar_tablicy)
{
	for (int y=0 ; y<rozmiar_tablicy ; y++)
		for (int x=0 ; x<ilosc_elementow ; x++)
			TABELA_SORTOWAN[y][x] = TABELA[y][x];
};

string Double_na_String(double numer)
{
   stringstream ss;
   ss << numer;
   return ss.str();
}

void ZAPIS_CZASOW_DO_PLIKU(double TABELA_CZASOW[4][100],double TABELA_CZASOW_SUMY[4], int ilosc_elementow,int wybor_1,
						   double ile_posortowac,int wybor_2, int zakres, int rozmiar_petli)
{
    for (int sortowanie = 1 ; sortowanie <= 4 ; sortowanie++)
    {
        string nazwa = Double_na_String(sortowanie) +
                       "_sort_n" + Double_na_String((double)(wybor_1)) +
                       "_r" + Double_na_String(wybor_2) +
                       "_z" + Double_na_String((double)(zakres)) + ".csv";
        cout << "**Czasy algorytmu " << sortowanie << " zostana zapisane do pliku: " << nazwa << endl;

        ofstream plik(nazwa.c_str());
        if(plik.good() == true )
        {
            for (int i = 0; i < rozmiar_petli ; i++)
                plik << TABELA_CZASOW[sortowanie-1][i] << endl;
            plik.close();
            cout << "Zapis zakonczony poprawnie." << endl << endl;
        }
        else
            cout << "* BLAD! NIE MOZNA UTWORZYC PLIKU!" << endl << endl;
    }

}

///-------------------------------------------------------
///	SORTOWANIA: SCALANIE / QUICKSORT / INTROSPEKTYWNE
///-------------------------------------------------------

void Sortowanie_przez_Scalanie(int* TAB_POM,int* TABLICA, int lewy , int prawy)
{
    int srodek,wsk_lewy,wsk_srodek,i; /// inicjalizacja zmiennych
    srodek = (lewy + prawy + 1) / 2; /// wybor srodkowego elementu danego podzialu
    if(srodek - lewy > 1) Sortowanie_przez_Scalanie(TAB_POM, TABLICA, lewy, srodek-1); ///Dziel rekurencyjnie
	if(prawy - srodek > 0) Sortowanie_przez_Scalanie(TAB_POM, TABLICA, srodek, prawy);

    /**
     * Inicjalizacja wskaznikow / tymczasowych wartosci elementow lewy i srodek
     * I rozpoczecie procedury sortowania elementow w "podtablicach"
    */
	wsk_lewy = lewy; wsk_srodek = srodek;
	for(i = lewy; i <= prawy; i++)
	{
		if ((wsk_lewy == srodek) || ((wsk_srodek <= prawy) && (TABLICA[wsk_lewy] > TABLICA[wsk_srodek])))
		{
			TAB_POM[i] = TABLICA[wsk_srodek];
			wsk_srodek++;
		}
		else
		{
			TAB_POM[i] = TABLICA[wsk_lewy];
			wsk_lewy++;
		}
	}
    /**
     * Przypisanie posortowanych elementow do tablicy glownej
     */
	for(i = lewy; i <= prawy; i++)
	{
		TABLICA[i] = TAB_POM[i];
	}
};

int Sortowanie_Szybkie(int* TABLICA, int lewy , int prawy,int PIWOT, bool introspektywne)
{

    int i,j,piwot;
    if (introspektywne == true) /// czy uzyc sortowania jako czesci introspektywnego - okreslenie Piwotu
		piwot = PIWOT;
	else
        piwot = TABLICA[(lewy+prawy)/2]; /// jezeli nie to wskaz srodek jako optymalny piwot

    i = lewy ; j = prawy; /// przypisanie wskaznika (w formie wartosci) dla przegladania tablicy

    while (1) /// dopuki nie sprawdzi calej tablicy
	{
        while (TABLICA[i] < piwot) /// dopuki element mniejszy od piwotu, zwiekszaj numer elementu az trafisz na wiekszy od niego
			i++;

        while (TABLICA[j] > piwot) /// dopuki element wiekszy od piwotu, zmniejszaj numer elementu az trafisz na mniejszy od niego
			j--;

        swap(TABLICA[i],TABLICA[j]); /// zamien oba nie pasujace elementy ze soba miejscami
        i++; j--; /// i przesun sie do kolejnych elementow

        if ( (introspektywne == true) && (i>=j) ) ///jezeli elementy beda rowne sobie (dojda do "piwotu") to zwroc (dla introspektywnego) wskaznik na lewy element lub przerwij petle
			return i;
		if (i>=j)
			break;
	}
	if (lewy < j)
		Sortowanie_Szybkie(TABLICA,lewy,j,PIWOT,introspektywne);
	if (i < prawy)
		Sortowanie_Szybkie(TABLICA,i,prawy,PIWOT,introspektywne);

	return 0;
};

void Sortowanie_Introspektywne(int* TABLICA, int poczatek,int koniec, int LIMIT, bool introspektywne)
{
	int i,j,liczba;
    ///Sortowanie_Introspektywne_petla zawieta sortowania przez kopcowanie i sortowanie szybkie
	Sortowanie_Introspektywne_petla(TABLICA,poczatek,koniec,LIMIT,introspektywne);

    /// Dokonczenie skladania / sortowania tablicy poprzez proste sortowanie przez wstawianie
	for(i = poczatek; i <= koniec; i++)
	{
		liczba = TABLICA[i]; j = i;
		while((j != poczatek) && (liczba < TABLICA[j-1]))
		{
			TABLICA[j] = TABLICA[j-1];
			j--;
		}
		TABLICA[j] = liczba;
	}
}

///-------------------------------------------------------
///	FUNKCJE INTROSORTA + SORTOWANIE PRZEZ KOPCOWANIE
///-------------------------------------------------------

void Sortowanie_Introspektywne_petla(int* TABLICA, int poczatek,int koniec, int LIMIT, bool introspektywne)
{
	int WSKAZNIK_PODZIALU;

	while ((koniec-poczatek) > PROG_WIELKOSCI_TABLICY)
	{
		if (LIMIT == 0)
		{
			Sortowanie_przez_kopcowanie(TABLICA,poczatek,koniec);
			return;
		}

		LIMIT--;

		WSKAZNIK_PODZIALU = Sortowanie_Szybkie(TABLICA,poczatek,koniec,
                                               NAJLEPSZY_PIWOT(TABLICA,poczatek,poczatek+((koniec-poczatek)/2)+1,koniec),
                                               introspektywne);

		Sortowanie_Introspektywne_petla(TABLICA,WSKAZNIK_PODZIALU,koniec,LIMIT,introspektywne);
		koniec = WSKAZNIK_PODZIALU;
	}
}

void Sortowanie_przez_kopcowanie(int* tablica,int lewy,int prawy)
{
	int n = (prawy+1) - lewy;
	int i;

	for (i = n/2 ; i>= 1 ; i--)
	{
		Kopiec(tablica,i,n,lewy);
	}
	for (i=n; i > 1; i--)
	{
		swap(tablica[lewy],tablica[lewy+i-1]);
		Kopiec(tablica,1,i-1,lewy);
	}
};

void Kopiec(int* tablica, int poczatek,int koniec,int lewy)
{
	int liczba = tablica[lewy+poczatek-1];
	int potomek;

	while (poczatek <= koniec/2)
	{
		potomek = 2*poczatek;
		if ( (potomek < koniec) && (tablica[lewy+potomek-1] < tablica[lewy+potomek]))
			potomek++;
		if (liczba >= tablica[lewy+potomek-1])
			break;
		tablica[lewy+poczatek-1] = tablica[lewy+potomek-1];
		poczatek = potomek;
	}
	tablica[lewy+poczatek-1] = liczba;
};

int NAJLEPSZY_PIWOT(int* TABLICA, int lewy, int srodek, int prawy)
{
	if (TABLICA[srodek] < TABLICA[lewy])
	{
		if (TABLICA[prawy] < TABLICA[srodek])
			return TABLICA[srodek];
		else
		{
			if (TABLICA[prawy] < TABLICA[lewy])
				return TABLICA[prawy];
			else
				return TABLICA[lewy];
		}
	}
	else
	{
		if (TABLICA[prawy] < TABLICA[srodek])
		{
			if (TABLICA[prawy] < TABLICA[lewy])
				return TABLICA[lewy];
			else
				return TABLICA[prawy];
		}
		else
			return TABLICA[srodek];
	}
}
