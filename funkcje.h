/**
 * @brief Funkcja tworzy pusta tablice (wypelniona NULL'ami) z dynamiczna alokacja pamieci (wedle wyboru uzytkownika)
 *
 * @param ilosc_elementow - ilosc elementow wybrana przez uzytkownika
 * @return int - zwraca zbudowana pusta tablice, ktora jest przypisywana do tablicy w glownej petli programu
 */
int* Stworz_tablice(int ilosc_elementow);

/**
 * @brief Funkcja tworzy tablice wypelniona *ilosc_elementow* elementami z zakresu *ZAKRES_LOSOWANIA*,
 * a nastepnie sortuje czesc tablicy wedle ilosci *ile_sortowac*
 *
 * @param TAB_POM - Tablica pomocnicza (pierwotnie pusta) przekazywana do funkcji tylko w celu sortowania wstepnego -
 * wymagana do sortowania przez scalanie - algorytmu wykozystanego do posortowania wstepnego tablicy
 * @param ilosc_elementow - ilosc elementow okreslona przez uzytkownika, okresla wielkosc tworzonej tablicy
 * @param ile_sortowac - sortowanie wstepne tablicy elementow
 * @param ZAKRES_LOSOWANIA - zakres (0 - x) - przedzial, z ktorego losowane beda liczby do danej tablicy
 * @param i - jako ze do program tworzy od razu 100 takich tabel (dla lepszej analizy dzialania algorytmow), przekazywany jest
 * numer aktualnie tworzonej tablicy - dodanie go do RAND'a podczas losowania liczb zapobiega utworzeniu dwoch takich samych
 * tabel obok siebie
 * @return int - zwraca tablice (w formie tablicy jednowymiarowej o wielkosci *[ilosc_elementow]* i przypisuje ja jako dany wiersz
 * tablicy dwuwymiarowej o rozmiarze *[100][ilosc_elementow]* w petli glownej programu
 */
int* Stworz_tablice(int* TAB_POM,int ilosc_elementow, int ile_sortowac, int ZAKRES_LOSOWANIA, int i);

/**
 * @brief Funkcja przypisujaca wartosci tabeli pierwotnej (utworzonej przed rozpoczeciem sortowan) do tablicy, na ktorej wykonywane
 * sa sortowania - bez tej funkcji sortowanie odbywaloby sie tylko pierwszym algorytmem, a kolejne sortowalyby juz poukladana tabele
 *
 * @param TABELA_SORTOWAN - tabela, na ktorej wykonywane sa sortowania
 * @param TABELA - tabela przechowujaca pierwotnie utworzona tablice
 * @param ilosc_elementow - ilosc elementow kazdego wiersza tablicy (rozmiar X)
 * @param rozmiar_tablicy - ilosc wierszy (rozmiar Y - ustawione na 100)
 */
void PRZYPISANIE(int** TABELA_SORTOWAN,int** TABELA, int ilosc_elementow, int rozmiar_tablicy);

/**
 * @brief Algorytm sortowania przez scalanie
 *
 * \details Do funkcji jest przekazywany za kazdym razem jeden wiersz (jedna instancja / zestaw liczb sortowanych)
 *
 * @param TAB_POM - tablica pomocnicza - wymagana do uzycia w algorytmie Sortowania przez Scalanie;
 * @param TABLICA - tablica sortowana
 * @param lewy - wskaznik (w postaci wartosci) na lewa granice podzialu tablicy
 * @param prawy - wskaznik (w postaci wartosci) na prawa granice podzialu tablicy
 */
void Sortowanie_przez_Scalanie(int* TAB_POM, int* TABLICA, int lewy , int prawy);

/**
 * @brief Algorytm sortowanie szybkiego
 *
 * \details Do funkcji przekazywana jest tablica (jeden wiersz), a nastepnie wykonywany jest na niej algorytm sortowania szybkiego.
 *  Funkcja ta jest rowniez wykozystywana podczas sortowania introspektywnego - stad zmienna bool introspektywne.
 * Funkcja dzieli tablice wg. Piwotu - dla introspektywnego okreslany wg algorytmu wyboru Piwotu, dla szybkiego testy wykazaly, ze
 * szybszy jest podzial tablicy na pol.
 *
 * Nastepnie poprawnosc polozenia elementu w tablicy jest sprawdzany - jezeli jest po "zlej stronie" liczby okreslajacej srodek tablicy
 * (piwot) zostaja zamienione - jezeli nie to przesuwany jest wskaznik lewego i prawego elementu do czasu znalezienia takiej "pary".
 * Nastepnie wstepnie posortowana tablica jest dzielona na mniejsze, az do rozbicia na najmniejsze mozliwe podtablice
 *
 * @param TABLICA - Tablica (jeden wiersz) zawieracajaca sortowany zestaw liczb
 * @param lewy - Wartosc lewego elementu
 * @param prawy - Wartosc prawego elementu
 * @param PIWOT - Zmienna uzywana przez sortowanie introspektywne. Element podzialu tablicy jest wybierany na podstawie algorytmu
 * @param introspektywne - okresla jak uzywac sortowania szybkiego - implementacja dla sortowania introspektywnego nieco rozni sie niz w
 * przypadku sortowania szybkiego
 * @return int - Zwraca posortowany wiersz tablicy do petli glownej programu
 */
int Sortowanie_Szybkie(int* TABLICA, int lewy , int prawy,int PIWOT, bool introspektywne);

/**
 * @brief Algorytm Sortowania Introspektywnego
 *
 * \details Funkcja Najpierw "dzieli" tablice kilka czesci i sortuje po kolei kolejne sekcje - uzywajac sortowania przez kopcowanie.
 * Po wstepnym posortowaniu tablicy zostaje ona poddana sortowaniu szybkiemu (ze wskazanym Piwotem wyznaczonym przez funkcje NAJLEPSZY_PIWOT).
 * Nastepnie wywolywana jest rekurencyjnie petla sortowania introspektywnego, a numer elementu na ktorym zostalo zakonczone dane sortowanie jest
 * okreslana przez numer elementu zwracany przez sortowanie szybkie. Po podziale tablicy na mniej niz (64 elementy) sortowanie dopelnia sortowanie
 * przez wstawianie - ktore dziala bardzo dobrze dla prawie posortowanych tabel
 *
 * @param TABLICA - Tablica (jeden wiersz) zawieracajaca sortowany zestaw liczb
 * @param poczatek - poczatek podzialu tablicy - wskaznik na element tablicy przekazywany do petli Introsorta
 * @param koniec - koniec podzialu tablicy
 * @param LIMIT - tablica jest wstepnie sortowana przez algorytm sortowania przez kopcowanie, a gdy zostanie posortowana do pewnego
 * stopnia, zostaje przekazana do sortowania szybkiego
 * @param introspektywne - zmienna decydujaca jak ma dzialac sortowanie szybkie
 */
void Sortowanie_Introspektywne(int* TABLICA, int poczatek,int koniec, int LIMIT, bool introspektywne);

/**
 * @brief Algorytm sortowania przez kopcowanie
 *
 * @param tablica - Tablica (jeden wiersz) zawieracajaca sortowany zestaw liczb
 * @param lewy - wskaznik (nr elementu) lewej granicy sortowanej czesci tablicy
 * @param prawy - wskaznik (nr elementu) prawej granicy sortowanej czesci tablicy
 */
void Sortowanie_przez_kopcowanie(int* tablica,int lewy,int prawy);

/**
 * @brief Funkcja zapisujaca czasy sortowan do plikow - osobnych dla kazdego sortowania
 *
 * @param TABELA_CZASOW[][] - przechowuje czasy sortowania poszczegolnego wiersza
 *  -# Rozmiar Y - czasy poszczegolnego sortowania
 *  -# Rozmiar X - czas sortowania kazdego wiersza tabeli
 * @param TABELA_CZASOW_SUMY[] - Czas wykonania kazdego algorytmu (suma czasow wykonania sortowan na 100 tablicach)
 * @param ilosc_elementow - ilosc elementow kazdej tablicy
 * @param wybor_1 - przekazywana w celu okreslenia nazwy pliku wynikowego
 * @param ile_posortowac - ilosc wstepnie posortowanych elementow
 * @param wybor_2 - okreslenie ilosci posortowanych elementow - do nazwy pliku
 * @param zakres - zakres (0 - x), z ktorego losowane sa liczby w tablicach
 * @param rozmiar_petli - ilosc wierszy (instancji tablic) do sortowania
 */
void ZAPIS_CZASOW_DO_PLIKU(double TABELA_CZASOW[4][100],double TABELA_CZASOW_SUMY[4], int ilosc_elementow, int wybor_1,
						   double ile_posortowac, int wybor_2, int zakres, int rozmiar_petli);
