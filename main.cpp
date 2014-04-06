///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
///	Testy algorytmow sortowania
///	Autor:	Bizon Michal
///	Indeks: 195251
///---------------------------------------
///	Aby przetestowac dzialanie algorytmow (DEBUG), nalezy zmienic wartosc nr 1 tabeli "const int ilosc_elementow" na 100 i odkomentowac 
///	petle for po kazdym sortowaniu, tudziez po stworzeniu tablicy. Dla wygody uzytkownika wyswietlany jest tylko pierwszy
///	wiersz calej tablicy (wyswietlanie 100 wierszy po 100 elementow czterokrotnie (po kazdym sortowaniu) byloby uciazliwe).
///
///	Program dla kazdej partii sortowan (tj wszystkich 4) uzywa tablicy z tymi samymi wartosciami, aby testy byly wiarygodne.
///	Dlatego zostaly stworzone dwie tablice - jedna bazowa - TABLICA, przechowuje pierwotna tablice, druga pomocnicza - do
///	ktorej przypisywane sa pierwotne wartosci po kazdym sortowaniu, a dopiero pozniej sa sortowane.
///	
///	Pomiar czasu jest dokonywany z dokladnoscia do 0.001 [s], co w przypadku malych tablic jest niezbyt dokladne, jednak
///	przy wiekszych spelnia swoje zadanie.
///
///	Dla wygody przeprowadzenia analiz dane dotyczace czasow sortowan sa zapisywane do pliku tekstowego z pseudo-formatowaniem
///	
///	Mimo iz rozwiazanie jakie zastosowalem (odnosnie przesylania i sortowania jednego wiersza funkcji) nie jest idealne,
///	ale pozwala na dokladny pomiar czasu oraz wygodne zarzadzanie pamiecia.



#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>

#define ROZMIAR 100

#include "interfejs.h"					/// Interfejs programu - funkcje wywolujace menu itp
#include "funkcje.h"					/// Funkcje odpowiedzialne za sortowania i tworzenie tablic


using namespace std;

int main()
{
	int* TABELA[ROZMIAR];				/// Glowna tablica - ["ROZMIAR" wierszy] X ["ilosc_elementow" kolumn]
	int* TABELA_SORTOWAN[ROZMIAR];		/// Wykozystanie tej samej tablicy dla kazdego sortowania
	int* TAB_POM;						/// Tablica pomocnicza wysylana do funkcji sortowania przez scalanie
	double TABELA_CZASOW[4][ROZMIAR];	/// Aby bez problemow zapisac dane do pliku umiescilem je w tabeli
	double TABELA_CZASOW_SUMY[4] = {0,0,0,0};		/// Sumy takze
	int wybor_1 = 0 , wybor_2 = 0;								/// sterowanie opcjami programu
	const int ilosc_elementow[5] = {10000 , 50000 , 100000 , 500000 , 1000000};	/// rozmiar kazdego wiersza w tablicy
	const double wstepnie_posortowane[7] = {0 , 25 , 50 , 75 , 95 , 99 , 99.7};	/// ilosc wstepnie posortowanych elementow

	int ZAKRES_LOSOWANIA = 999;			/// Zakres (0-x), z ktorego uzytkownik losuje liczby
	char opcja;							/// Sterowanie glownym menu - do petli switch

	time_t start, koniec;				/// Zliczanie czasu pomiedzy wykonaniem sie operacji
	double roznica;						/// oraz roznica miedzy nimi

	bool Zamknij = false , introspektywne = false;		/// Introspektywne - aby odroznic kiedy qiucksort ma dzialac samodzielnie
														///					a kiedy jedynie partycjonowac tablice dla introsorta
	WYPISZ_WSTEP();
    cin.get();
	while (Zamknij != true)
	{
        system("clear");									/// Wypisanie interfejsu graficznego programu oraz
		WYPISZ_PARAMETRY(ilosc_elementow[wybor_1],		/// parametrow symulacji
			wstepnie_posortowane[wybor_2],ZAKRES_LOSOWANIA);
		WYPISZ_MENU();
		cin >> opcja;

		switch (opcja)
		{
		case 'Z':
		case 'z':
			{
                system("clear");
				cout << "** Wprowadz maksymalna wartosc przedzialu (od 0-x):" << endl <<
						"* x = ";
				cin >> ZAKRES_LOSOWANIA;
                system("clear");
				break;
			}

		case 'N':
		case 'n':
			{
                system("clear");
				WYPISZ_ILOSC_ELEMENTOW();	/// Wypisanie dostepnych opcji wyboru

				do cin >> wybor_1;			/// Maksymalna wartoscia jest 4
				while (wybor_1 > 4); 
                system("clear");
				break;
			}

		case 'R':
		case 'r':
			{
                system("clear");
				WYPISZ_WSTEPNIE_POSORTOWANE();
				do cin >> wybor_2;
				while (wybor_2 > 6);
                system("clear");
				break;
			}

		case 'S':
		case 's':
			{
                system("clear");
				cout << "*  ROZPOCZYNAM SORTOWANIA:" << endl <<
						"^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
				WYPISZ_PARAMETRY(ilosc_elementow[wybor_1],wstepnie_posortowane[wybor_2],ZAKRES_LOSOWANIA);

                ///	Zadeklarowanie wielkosci tablic TAB_POM i TABELA_SORTOWAN dla danego "przebiegu" funkcji - wypelniane NULL'ami

				TAB_POM = Stworz_tablice(ilosc_elementow[wybor_1]);
				for (int i=0 ; i<ROZMIAR ; i++)
					TABELA_SORTOWAN[i] = Stworz_tablice(ilosc_elementow[wybor_1]);
				
				///	Budowanie TABLICY
				///	Na podstawie parametrow wylicza ile elementow ma byc posortowane poczatkowo,
				///	jezeli wartosc "ile_posortowac" wynosi 0, to program najpierw sortuje tablice 
				///	za pomoca Sortowania przez Scalanie, a nastepnie odwraca tabele (pierwszy z ostatnim itd)
				///	funkcja swap(A[n],A[m]). 
				///	
				///	W innym wypadku funkcja wylicza, jakie wartosci powinny byc z danego zakresu (np 25% z 1000 
				///	to 250), losuje liczby z tego przedzia�u, sortuje je, a nastepnie losuje liczby z zakresu 250-1000.
				///	
				///	Zmienna i jest przekazana aby rand by� lepszy, tj aby nie bylo obok siebie (np TABLICA[0] i TABLICA[1])
				///	takich samych wartosci randa generowanego na podstawie aktualnego czasu
				cout << "** Buduje tablice. "<<endl;
				int ile_posortowac = wstepnie_posortowane[wybor_2] * ilosc_elementow[wybor_1] * 0.01;
				time(&start);
				for (int i=0 ; i<ROZMIAR ; i++)
					TABELA[i] = Stworz_tablice(TAB_POM,ilosc_elementow[wybor_1],ile_posortowac,ZAKRES_LOSOWANIA,i);
				time(&koniec);
				roznica = difftime(koniec,start);
				cout << "Tablice utworzone i posortowane wstepnie. Czas tej operacji to: " << roznica << " [s]" << endl << endl;


				

				///	***********************************************
				///	Algorytmy SORTOWANIA
				///	***********************************************
				///	Sortowanie przez SCALANIE
				cout << "** Rozpoczynam sortowanie wlasciwe." << endl << endl;				
				PRZYPISANIE(TABELA_SORTOWAN,TABELA,ilosc_elementow[wybor_1],ROZMIAR);

				cout << "* SORTOWANIE PRZEZ SCALANIE" << endl;
				
				for (int i=0 ; i<ROZMIAR ; i++)
				{
					start = clock();
					Sortowanie_przez_Scalanie(TAB_POM,TABELA_SORTOWAN[i],0,ilosc_elementow[wybor_1]-1);
					koniec = clock();
					TABELA_CZASOW_SUMY[0] += ((koniec-start)/(double)CLOCKS_PER_SEC);
					TABELA_CZASOW[0][i] = ((koniec-start)/(double)CLOCKS_PER_SEC);
				}
				cout << "Sortowanie przez scalanie. Czas tej operacji to: " << TABELA_CZASOW_SUMY[0] << " [s]" << endl << endl;
				/*
				for (int i=0 ; i<100 ; i++)
					cout << setw(4) << TABELA_SORTOWAN[0][i];
				cout << endl;
				*/
				

				///	Sortowanie SZYBKIE
				cout << "* SORTOWANIE SZYBKIE" << endl;
				PRZYPISANIE(TABELA_SORTOWAN,TABELA,ilosc_elementow[wybor_1],ROZMIAR);

				time(&start);
				for (int i=0 ; i<ROZMIAR ; i++)
				{
					start = clock();
					Sortowanie_Szybkie(TABELA_SORTOWAN[i],0,ilosc_elementow[wybor_1]-1,0, introspektywne);
					koniec = clock();
					TABELA_CZASOW_SUMY[1] += ((koniec-start)/(double)CLOCKS_PER_SEC);
					TABELA_CZASOW[1][i] = ((koniec-start)/(double)CLOCKS_PER_SEC);
				}
				cout << "Sortowanie szybkie. Czas tej operacji to: " << TABELA_CZASOW_SUMY[1] << " [s]" << endl << endl;
				/*
				for (int i=0 ; i<100 ; i++)
					cout << setw(4) << TABELA_SORTOWAN[0][i];
				cout << endl;
				*/
				

				///	Sortowanie INTROSPEKTYWNE
				int LIMIT = (int)floor(2* (log( (float)(ilosc_elementow[wybor_1]) ) / log( (float)2 )));
				introspektywne = true;
				cout << "* SORTOWANIE INTROSPEKTYWNE" << endl;
				PRZYPISANIE(TABELA_SORTOWAN,TABELA,ilosc_elementow[wybor_1],ROZMIAR);

				time(&start);
				for (int i=0 ; i<ROZMIAR ; i++)
				{
					start = clock();
					Sortowanie_Introspektywne(TABELA_SORTOWAN[i],0,ilosc_elementow[wybor_1]-1,LIMIT,introspektywne);
					koniec = clock();
					TABELA_CZASOW_SUMY[2] += ((koniec-start)/(double)CLOCKS_PER_SEC);
					TABELA_CZASOW[2][i] = ((koniec-start)/(double)CLOCKS_PER_SEC);
				}
				
				cout << "Sortowanie introspektywne. Czas tej operacji to: " << TABELA_CZASOW_SUMY[2] << " [s]" << endl << endl;
				/*
				for (int i=0 ; i<100 ; i++)
					cout << setw(4) << TABELA_SORTOWAN[0][i];
				cout << endl;
				*/
				
                
				///	Sortowanie przez Kopcowanie
				cout << "* SORTOWANIE PRZEZ KOPCOWANIE" << endl;
				PRZYPISANIE(TABELA_SORTOWAN,TABELA,ilosc_elementow[wybor_1],ROZMIAR);

				time(&start);
				for (int i=0 ; i<ROZMIAR ; i++)
				{
					start = clock();
					Sortowanie_przez_kopcowanie(TABELA_SORTOWAN[i],0,ilosc_elementow[wybor_1]-1);
					koniec = clock();
					TABELA_CZASOW_SUMY[3] += ((koniec-start)/(double)CLOCKS_PER_SEC);
					TABELA_CZASOW[3][i] = ((koniec-start)/(double)CLOCKS_PER_SEC);
				}
				cout << "Sortowanie przez kopcowanie. Czas tej operacji to: " << TABELA_CZASOW_SUMY[3] << " [s]" << endl << endl;
				/*
				for (int i=0 ; i<100 ; i++)
					cout << setw(4) << TABELA_SORTOWAN[0][i];
				cout << endl;
				*/
				
				ZAPIS_CZASOW_DO_PLIKU(TABELA_CZASOW,TABELA_CZASOW_SUMY,ilosc_elementow[wybor_1],wybor_1,
									  ile_posortowac,wybor_2,ZAKRES_LOSOWANIA,ROZMIAR);

				cout << "** Rozpoczynam czyszczenie tablic." << endl;
				for (int i=0 ; i<ROZMIAR ; i++) 
				{
					delete TABELA[i];
					delete TABELA_SORTOWAN[i];
				}
				TABELA_CZASOW_SUMY[0] = 0;	TABELA_CZASOW_SUMY[1] = 0;
				TABELA_CZASOW_SUMY[2] = 0;	TABELA_CZASOW_SUMY[3] = 0;
				introspektywne = false;
				cout << "Zakonczono oczyszczanie. " << endl;

                cin.get();
				break;
			}

		case 'E':
		case 'e':
			{
				Zamknij = true;
				break;
			}

		default:
			{
                system("clear");
				cout << "|------------------------|" << endl <<
						"| NIEZNANA OPCJA POGRAMU |" << endl <<
						"|------------------------|" << endl << endl;
                cin.get();
                system("clear");
				break;
			}
		}
	}
	return 0;
}

