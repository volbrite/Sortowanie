#include <iostream>
#include <iomanip>

using namespace std;

void WYPISZ_OPCJA()
{
    cout << "** Wybierz opcje programu: " << endl <<
            "*  ";
}

void WYPISZ_WSTEP()
{
    cout << "*********************************************" << endl <<
            "|         SORTOWANIE PRZEZ SCALANIE         |" << endl <<
            "|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|" << endl <<
            "|   Autor: Bizon Michal  |  Indeks: 195251  |" << endl <<
            "| ----------------------------------------- |" << endl <<
            "| Program sortuje 100 tablic n-elementowych |" << endl <<
            "|   n - ilosc elementow tablicy             |" << endl <<
            "|   r - ilosc wstepnie posortowanych el.    |" << endl <<
            "|___________________________________________|" << endl << endl;
}

void WYPISZ_PARAMETRY(int ilosc_elementow, double wstepnie_posortowane, int ZAKRES_LOSOWANIA)
{
		cout << "* Parametry programu: " << endl <<
				"*  - Ilosc tablic: 100" << endl <<
				"*  - Rozmiar tablicy: " << ilosc_elementow << endl;
	if (wstepnie_posortowane == 0)
		cout << "*  - Wstepnie posortowane: Posortowane odwrotnie" << endl;
	else
		cout << "*  - Wstepnie posortowane: " << wstepnie_posortowane << "%" << endl;
		cout <<	"*  - Zakres losowanych liczb (0-x): " << ZAKRES_LOSOWANIA << endl << endl;
}

void WYPISZ_MENU()
{
    cout << "|------------------------" << endl <<
            "| Opcje programu (opcje wyboru sa dostepne):" << endl <<
            "|  (z) - zakres losowania liczb w tablicach" << endl <<
            "|  (n) - ilosc elementow w kazdej tablicy" << endl <<
            "|  (r) - ilosc wstepnie posortowanych elementow" << endl <<
            "|  (E) - Wyjscie" << endl <<
            "|------------------------" << endl <<
            "|  (S) - Start symulacji" << endl <<
            "|------------------------" << endl << endl;
    WYPISZ_OPCJA();
}

void WYPISZ_ILOSC_ELEMENTOW()
{
    cout << "| Wybor ilosci elementow w kazdej tablicy:" << endl <<
            "|  0 - kazda tablica 10 000 elementow" << endl <<
            "|  1 - kazda tablica 50 000 elementow" << endl <<
            "|  2 - kazda tablica 100 000 elementow" << endl <<
            "|  3 - kazda tablica 500 000 elementow" << endl <<
            "|  4 - kazda tablica 1 000 000 elementow" << endl << endl;
    WYPISZ_OPCJA();
}

void WYPISZ_WSTEPNIE_POSORTOWANE()
{
    cout << "| Wybor wstepnie posortowanych elementow:" << endl <<
            "|  0 - Posortowana odwrotnie" << endl <<
            "|  1 - 25%" << endl <<
            "|  2 - 50%" << endl <<
            "|  3 - 75%" << endl <<
            "|  4 - 95%" << endl <<
            "|  5 - 99%" << endl <<
            "|  6 - 99.7%" << endl << endl;
    WYPISZ_OPCJA();
}
