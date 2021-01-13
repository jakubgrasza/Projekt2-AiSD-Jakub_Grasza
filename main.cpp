#include <iostream>
#include <ctime>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <iomanip>

using namespace std;

int R, sposob, nr_dzialania; // zmienne potrzebne do prawidlowego dzialania rozmiaru tablicy, wyboru algorytmu sortujacego oraz poslugiwania sie menu programu
long int N; // zmienna potrzebna do okreslenia przedzialu losowanych liczb
clock_t start, stop; // zmienne start i stop do przechowywania cykli zegara
double czas; // zmienna czas typu double potrzebna do okreslenia czasu dzialania algorytmu w sekundach
ofstream out; // deklaracja strumienia wyjscia do pliku
ifstream in;  // deklaracja strumienia wejscia z pliku

void generatorCiagow(int *Tab, int R, long int N) // funkcja realizujaca generowanie ciagow calkowitych liczb losowych z przedzialu od 0 do podanego przez uzytkownika N i zapisujaca je do pliku "losowe.txt"
{
    srand((unsigned)time(NULL)); // konfiguracja maszyny losujacej
    out.open("losowe.txt",ios::out); // otwarcie pliku "losowe.txt" do ktorego wypisane zostana wylosowane liczby
    for(int i=0; i<R; i++)
        {
            Tab[i] = rand()%(N +1); // wylosowanie do tablicy liczb z przedzialu od 0 do podanego przez uzytkownika N
        }
    for(int i=0; i<R-1; i++)
    {
        out<<Tab[i]<<" "; // wypisanie wylosowanych liczb do pliku "losowe.txt"
    }
    out<<Tab[R-1];
    out.close(); // zamkniecie strumienia wyjsciowego do pliku
};

void scalanie(int *Tab, int left, int middle, int right) // funkcja scalajaca podtablice
{
   int i, j, k; // zmienne iteracyjne do petli "for"
   int leftSize = middle-left+1; // rozmiar lewej podtablicy
   int rightSize = right-middle; // rozmiar prawej podtablicy
   int *leftTab = new int[leftSize]; // deklaracja lewej podtablicy o odpowiednim rozmiarze
   int *rightTab = new int[rightSize]; // deklaracja prawej podtablicy o odpowiednim rozmiarze
   for(i = 0; i<leftSize; i++)
    {
        leftTab[i] = Tab[left+i]; // wypelnienie lewej podtablicy odpowiednimi liczbami z tablicy
    };
   for(j = 0; j<rightSize; j++)
    {
        rightTab[j] = Tab[middle+1+j];  // wypelnienie prawej podtablicy odpowiednimi liczbami z tablicy
    };
   i = 0; j = 0; k = left; // przypisanie wartosci zmiennym iteracyjnym potrzebnym do petli "for"
   while(i < leftSize && j<rightSize)
    {
        if(leftTab[i] <= rightTab[j])
        {
            Tab[k] = leftTab[i];    // scalenie podtablic z tablica glowna
            i++;                    // inkrementacja zmiennej i
        }
        else
        {
            Tab[k] = rightTab[j];
            j++; // inkrementacja zmiennej j
        }
      k++; // inkrementacja zmiennej k
    };
   while(i<leftSize)
    {
        Tab[k] = leftTab[i];    // dodatkowy element z lewej podtablicy
        i++; k++;   // inkrementacja zmiennej k i zmiennej i
    }
   while(j<rightSize)
    {
        Tab[k] = rightTab[j];   //dodatkowy element z prawej podtablicy
        j++; k++; // inkrementacja zmiennej k i zmiennej j
    }
};

void mergeSort(int *Tab, int left, int right) // funkcja realizujaca sortowanie przez scalanie
{
   int middle; // zmienna przechowujaca srodek tablicy
   if(left < right)
    {
        middle = left+(right-left)/2; // wyznaczenie srodka tablicy, potrzebnego do podzialu na 2 tablice,
        mergeSort(Tab, left, middle); // sortowanie rekurencyjnie lewej czesci tablicy
        mergeSort(Tab, middle+1, right);    // sortowanie rekurencyjnie prawej czesci tablicy
        scalanie(Tab, left, middle, right); // scalanie lewej i prawej czesci tablicy w calosc
    }
};

void quickSort(int *Tab, int left, int right) // funkcja realizujaca sortowanie quickSort
{
    int x; // deklaracja zmiennej x
    int y; // deklaracja zmiennej y
    int pivot; // deklaracja zmiennej pivot, bedacej elementem podzialowym
  x = (left + right)/2; // przypisanie wartosci do zmiennej x
  pivot = Tab[x];   // przypisanie do zmiennej pivot wartosci zawartej w tablicy pod indeksem x
  Tab[x] = Tab[right]; // przypisanie do komorki tablicy pod indeksem x, wartosci zawartej pod indeksem right
    for(y=x=left; x < right; x++)
        {
        if(Tab[x] < pivot)
            {
                swap(Tab[x], Tab[y]); // zamiana miejscami wartosci tablicy zawartych pod indeksami x i y
                y++; // inkrementacja zmiennej y
            }
        };
  Tab[right] = Tab[y]; // przypisanie do komorki tablicy zawartej pod indeksem right, wartosci z komorki zawartej pod indeksem y
  Tab[y] = pivot;   // przypisanie do komorki tablicy pod indeksem y, wartosci zawartej pod indeksem pivot
    if(left < y - 1)
        {
            quickSort(Tab, left, y - 1); // rekurencyjne wywolanie algorytmu sortujacego "quickSort" dla lewej podtablicy
        };
    if(y + 1 < right)
        {
            quickSort(Tab, y + 1, right); // rekurencyjne wywolanie algorytmu sortujacego "quickSort" dla prawej podtablicy
        };
}

int main()
{

    cout<<"Witaj w programie!"<<endl; // przejrzyste menu programu, ulatwiajace korzystanie z niego
    cout<<"Mozliwe dzialania: "<<endl;
    cout<<"1. Wprowadzenie danych z klawiatury."<<endl<<"2. Wczytywanie danych z pliku."<<endl<<"3. Liczby pseudolosowe."<<endl<<"4. Generowanie ciagu do pliku losowe.txt"<<endl;
    cout<<"Wybierz numer dzialania: ";
    cin>>nr_dzialania; //
    if (!cin)
            {
                cout<<"Zle dokonales wyboru! :/"<<endl; // sprawdzenie czy wprowadzony znak jest wartoscia int, jesli nie wyswietlany jest komunikat
                cin.clear();
                cin.sync();
            }
    else
    {
    switch(nr_dzialania)    // funkcja "switch" zalezna od numeru dzialania ktory uzytkownik wybierze
    {
        case 1:
        {
            cout<<"Podaj rozmiar tablicy: ";
            cin>>R; // wczytanie rozmiaru tablicy
            if (!cin)
            {
                cout<<"Podany rozmiar tablicy nie jest liczba. Program zostal zakonczony."<<endl; // sprawdzenie czy wprowadzony znak jest wartoscia int, jesli nie wyswietlany jest komunikat
                cin.clear();
                cin.sync();
            }
            else
            {
            int *Tablica = new int[R]; // deklaracja tablicy dynamicznej o rozmiarze podanym przez uzytkownika
            int i=0;
                    for(i=0;i<R;i++) // petla for potrzebna do wypeleniena naszej tablicy liczbami
                    {
                        cout<<"Podaj "<<i+1<<" element tablicy: ";
                        cin>>Tablica[i]; // wczytanie podanego elementu do odpowiedniej komorki tablicy
                        if(!cin)
                        {
                            cout<<"Wprowadz liczbe!"<<endl; // jesli zostanie podany znak inny niz liczba program wyswietli komunikat
                            cin.clear ();
                            cin.sync ();
                            i--; // dekrementacja zmiennej i
                    }
                    else
                        continue;
                    }
            cout<<endl;
            cout<<"1. Sortowanie quickSort."<<endl<<"2. Sortowanie przez scalanie."<<endl;
            cout<<"Wybierz algorytm sortowania: "; // menu wyboru algorytmu, ktorym chcemy posortowac nasze liczby
            cin>>sposob;

            switch(sposob)  // funkcja "switch" zalezna od sposobu sortowania ktory uzytkownik wybierze
            {
                case 1:
                {
                    cout<<"Sortuje tablice, algorytmem quicksort. Prosze czekac!"<<endl<<endl;
                    start = clock(); // zapisanie liczby cykli procesora w momencie rozpoczecia algorytmu sortowania
                    quickSort(Tablica,0,R-1); // sortowanie metoda quickSort
                    stop = clock();     // zapisanie liczby cykli procesora w momencie zakonczenia algorytmu sortowania
                    czas = (double)(stop-start)/CLOCKS_PER_SEC;  // podzielenie liczby cykli przez stala "CLOCKS_PER_SEC" i zrzutowanie na typ double, aby otrzymac czas w sekundach
                    cout<<"Czas sortowania: "<<czas<<endl<<endl; // wyswietlenie czasu dzialania algorytmu sortowania
                    out.open("wynik.txt",ios::out); // otwarcie pliku "wynik.txt" do ktorego zostanie zapisany wynik dzialania programu
                    cout<<endl;
                    cout<<"Posortowana tablica: ";
                    for(int i=0;i<R;i++)
                    {
                        cout<<" | "<<Tablica[i];    // wyswietlenie posortowanej tablicy na ekranie
                        out<<" | "<<Tablica[i];     // wypisanie posortowanej tablicy do pliku
                    };
                    cout<<" | ";
                    out<<" | ";
                    out.close();    // zamkniecie strumienia wyjsciowego do pliku
                    cout<<endl<<endl;
                }break;
                case 2:
                {
                    cout<<"Sortuje tablice, algorytmem przez scalanie. Prosze czekac!"<<endl<<endl;
                    start = clock(); // zapisanie liczby cykli procesora w momencie rozpoczecia algorytmu sortowania
                    mergeSort(Tablica,0,R-1); // sortowanie metoda sortowania przez scalanie (mergeSort)
                    stop = clock(); // zapisanie liczby cykli procesora w momencie zakonczenia algorytmu sortowania
                    czas = (double)(stop-start)/CLOCKS_PER_SEC; // podzielenie liczby cykli przez stala "CLOCKS_PER_SEC" i zrzutowanie na typ double, aby otrzymac czas w sekundach
                    cout<<"Czas sortowania: "<<czas<<endl<<endl; // wyswietlenie czasu dzialania algorytmu sortowania
                    out.open("wynik.txt",ios::out); // otwarcie pliku "wynik.txt" do ktorego zostanie zapisany wynik dzialania programu
                    cout<<endl;
                    cout<<"Posortowana tablica: ";
                    for(int i=0;i<R;i++)
                    {
                        cout<<" | "<<Tablica[i]; // wyswietlenie posortowanej tablicy na ekranie
                        out<<" "<<Tablica[i]; // wypisanie posortowanej tablicy do pliku
                    };
                    cout<<" | ";
                    out<<" ";
                    out.close(); // zamkniecie strumienia wyjsciowego do pliku
                    cout<<endl<<endl;
                }
            }
            delete []Tablica;   // usuniecie tablicy dynamicznej z systemu (zwrocenie pamieci zajetej przez tablice do systemu)
            }
        }break;
        case 2:
        {
        string plik_wejsciowy;
        cout<<"Podaj sciezke pliku: ";
        cin>>plik_wejsciowy;
        in.open(plik_wejsciowy, ios::in); // otwarcie pliku zawierajacego dane wejsciowe
            if(in.good()==false) // jezeli wystapi jakis problem w czasie otwierania pliku program wyswietli komunikat "Nie mozna otworzyc pliku"
            {
                cout<<"Nie mozna otworzyc pliku"<<endl;
                exit(0);
            }
            else
            {
            int temp, ilosc = 0; // deklaracja licznika ilosci danych w pliku "ilosc" oraz zmienniej tymczasowej "temp"
               if(ifstream(plik_wejsciowy, ios::ate).tellg()) // jezeli plik nie bedzie zawieral danych(bedzie pusty) program wyswietli komunikat "Plik jest pusty"
                {
                while(!in.eof())// petla wykonuje sie dopoki dane w pliku wejsciowym sie nie skoncza
                {
                    in>>temp;      // przypisanie danych zawartych w pliku do zmiennej 'a' w celu policzenia ich ilosci
                    ilosc++;  // wskaznik ilosci danych zawartych w pliku, potrzebny do stworzenia tablicy
                }
                in.close();
                cout<<"Ilosc: "<<ilosc<<endl;

                int *T = new int[ilosc];    // deklaracja tablicy o wielkosci rownej ilosci elementow w pliku tekstowym
                int m=0; // zmienna iteracyjna
                in.open(plik_wejsciowy, ios::in);
                while(!in.eof()) // petla wykonuje sie dopoki dane w pliku wejsciowym sie nie skoncza
                {
                    in >> T[m];     // wpisywanie liczb zawartych w pliku do tablicy "T"
                    m++;    // inkrementacja zmiennej m
                }
                in.close(); // zamkniecie strumienia wejsciowego z pliku
                cout<<endl;
                /*for(int i=0;i<ilosc; i++)
                {
                    cout<<" | "<<T[i]; // opcjonalne wypisywanie liczb wczytanych z pliku na ekranie, wylaczone ze wzgledu na duza ilosc elementow
                };
                cout<<" | "<<endl;*/

                cout<<"1. Sortowanie quickSort."<<endl<<"2. Sortowanie przez scalanie."<<endl;
                cout<<"Wybierz algorytm sortowania: ";
                cin>>sposob;

                R = ilosc;
                switch(sposob)  // funkcja "switch" zalezna od sposobu sortowania ktory uzytkownik wybierze
                {
                    case 1:
                    {
                        cout<<"Sortuje tablice, algorytmem quicksort. Prosze czekac!"<<endl<<endl;
                        start = clock();    // zapisanie liczby cykli procesora w momencie rozpoczecia algorytmu sortowania
                        quickSort(T,0,R-1); // sortowanie metoda quickSort
                        stop = clock(); // zapisanie liczby cykli procesora w momencie zakonczenia algorytmu sortowania
                        czas = (double)(stop-start)/CLOCKS_PER_SEC; // podzielenie liczby cykli przez stala "CLOCKS_PER_SEC" i zrzutowanie na typ double, aby otrzymac czas w sekundach
                        cout<<"Czas sortowania: "<<czas<<endl<<endl;    // wyswietlenie czasu dzialania algorytmu sortowania
                        out.open("wynik.txt",ios::out); // otwarcie pliku "wynik.txt" do ktorego zostanie zapisany wynik dzialania programu
                        cout<<endl<<endl;
                        /*cout<<"Posortowana tablica: ";*/
                        for(int i=0;i<R;i++)
                        {
                            /*cout<<" | "<<T[i];*/  // opcjonalne wyswietlenie posortowanej tablicy na ekranie, wylaczone ze wzgledu na duza ilosc elementow
                            out<<" | "<<T[i]; // wypisanie posortowanej tablicy do pliku
                        };
                        /*cout<<" | ";*/
                        out<<" | ";
                        out.close();    // zamkniecie strumienia wyjsciowego do pliku
                        cout<<endl<<endl;
                    }break;
                    case 2:
                    {
                        cout<<"Sortuje tablice, algorytmem sortowania przez scalanie. Prosze czekac!"<<endl<<endl;
                        start = clock();    // zapisanie liczby cykli procesora w momencie rozpoczecia algorytmu sortowania
                        mergeSort(T,0,R-1); // sortowanie metoda sortowania przez scalanie (mergeSort)
                        stop = clock(); // zapisanie liczby cykli procesora w momencie zakonczenia algorytmu sortowania
                        czas = (double)(stop-start)/CLOCKS_PER_SEC; // podzielenie liczby cykli przez stala "CLOCKS_PER_SEC" i zrzutowanie na typ double, aby otrzymac czas w sekundach
                        cout<<"Czas sortowania: "<<czas<<endl<<endl;    // wyswietlenie czasu dzialania algorytmu sortowania

                        cout<<endl<<endl;
                        /*cout<<"Posortowana tablica: ";*/
                        out.open("wynik.txt",ios::out); // otwarcie pliku "wynik.txt" do ktorego zostanie zapisany wynik dzialania programu
                        for(int i=0;i<R-1;i++)
                        {
                            /*cout<<" | "<<T[i];*/  // opcjonalne wyswietlenie posortowanej tablicy na ekranie, wylaczone ze wzgledu na duza ilosc elementow
                            out<<T[i]<<" ";     // wypisanie posortowanej tablicy do pliku
                        };
                        /*cout<<T[R-1]<<" | ";*/
                        out<<T[R-1];
                        out.close();    // zamkniecie strumienia wyjsciowego do pliku
                        cout<<endl<<endl;
                    }
                }
            delete [] T;    // usuniecie tablicy dynamicznej z systemu (zwrocenie pamieci zajetej przez tablice do systemu)
            }
            else
            {
                cout<<"Plik jest pusty."<<endl;
            };
            }
        }break;
        case 3:
        {
            cout<<"Podaj rozmiar tablicy: ";
            cin>>R;
            if (!cin)
            {
                cout<<"Podany rozmiar tablicy nie jest liczba. Program zostal zakonczony."<<endl; // sprawdzenie czy wprowadzony znak jest wartoscia int, jesli nie wyswietlany jest komunikat
                cin.clear();
                cin.sync();
            }
            else
            {
            int *Tablica = new int[R];  // deklaracja tablicy o wielkosci podanej przez uzytkownika
            cout<<"Zakres losowania [ 0, N ], podaj N: ";
            cin>>N;
            generatorCiagow(Tablica,R,N); // wywolanie funkcji generujacej liczby calkowite z przedzialu od 0 do podanego N i zapisujacej je do pliku "losowe.txt"
            cout<<endl;
            for(int i=0;i<R;i++)
            {
                cout<<" | "<<Tablica[i];// wypisanie wylosowanych liczb na ekranie
            };
            cout<<" | "<<endl<<endl;
            in.open("losowe.txt", ios::in); // otwarcie pliku "losowe.txt" zawierajacego elementy wylosowane przez generator ciagow
            if(in.good()==false) // jezeli wystapi jakis problem w czasie otwierania pliku program wyswietli komunikat "Nie mozna otworzyc pliku"
            {
                cout<<"Nie mozna otworzyc pliku"<<endl;
                exit(0);
            }
            else
            {
            int j=0; // zmienna iteracyjna
            int *Tab = new int[R];  // deklaracja tablicy o wielkosci podanej przez uzytkownika
            while(!in.eof())// petla wykonuje sie dopoki dane w pliku wejsciowym sie nie skoncza
                {
                    in>>Tab[j]; // wczytanie liczb z pliku do tablicy
                    j++;    // inkrementacja zmiennej j
                }
            in.close();
            cout<<"1. Sortowanie quickSort."<<endl<<"2. Sortowanie przez scalanie."<<endl;
            cout<<"Wybierz algorytm sortowania: ";
            cin>>sposob;

            switch(sposob)  // funkcja "switch" zalezna od sposobu sortowania ktory uzytkownik wybierze
            {
                case 1:
                {
                    cout<<"Sortuje tablice, algorytmem quicksort. Prosze czekac!"<<endl<<endl;
                    start = clock();    // zapisanie liczby cykli procesora w momencie rozpoczecia algorytmu sortowania
                    quickSort(Tab,0,R-1);   // sortowanie metoda quickSort
                    stop = clock(); // zapisanie liczby cykli procesora w momencie zakonczenia algorytmu sortowania
                    czas = (double)(stop-start)/CLOCKS_PER_SEC; // podzielenie liczby cykli przez stala "CLOCKS_PER_SEC" i zrzutowanie na typ double, aby otrzymac czas w sekundach
                    cout<<"Czas sortowania: "<<czas<<endl<<endl;    // wyswietlenie czasu dzialania algorytmu sortowania
                    out.open("wynik.txt",ios::out); // otwarcie pliku "wynik.txt" do ktorego zostanie zapisany wynik dzialania programu
                    cout<<endl<<endl;
                    cout<<"Posortowana tablica: ";
                    for(int i=0;i<R;i++)
                    {
                        cout<<" | "<<Tab[i];    // wyswietlenie posortowanej tablicy na ekranie
                        out<<" | "<<Tab[i];     // wypisanie posortowanej tablicy do pliku
                    };
                    cout<<" | ";
                    out<<" | ";
                    out.close();    // zamkniecie strumienia wyjsciowego do pliku
                    cout<<endl<<endl;
                }break;
                case 2:
                {
                    cout<<"Sortuje tablice, algorytmem przez scalanie. Prosze czekac!"<<endl<<endl;
                    start = clock();    // zapisanie liczby cykli procesora w momencie rozpoczecia algorytmu sortowania
                    mergeSort(Tab,0,R-1);   // sortowanie metoda sortowania przez scalanie (mergeSort)
                    stop = clock(); // zapisanie liczby cykli procesora w momencie zakonczenia algorytmu sortowania
                    czas = (double)(stop-start)/CLOCKS_PER_SEC; // podzielenie liczby cykli przez stala "CLOCKS_PER_SEC" i zrzutowanie na typ double, aby otrzymac czas w sekundach
                    cout<<"Czas sortowania: "<<czas<<endl<<endl; // wyswietlenie czasu dzialania algorytmu sortowania
                    out.open("wynik.txt",ios::out); // otwarcie pliku "wynik.txt" do ktorego zostanie zapisany wynik dzialania programu
                    cout<<endl<<endl;
                    cout<<"Posortowana tablica: ";
                    for(int i=0;i<R;i++)
                    {
                        cout<<" | "<<Tab[i];    // wyswietlenie posortowanej tablicy na ekranie
                        out<<" "<<Tab[i];     // wypisanie posortowanej tablicy do pliku
                    };
                    cout<<" | ";
                    out<<" ";
                    out.close();    // zamkniecie strumienia wyjsciowego do pliku
                    cout<<endl<<endl;
                }break;
            }delete Tab;    // usuniecie tablicy dynamicznej z systemu (zwrocenie pamieci zajetej przez tablice do systemu)
            }
            delete Tablica; // usuniecie tablicy dynamicznej z systemu (zwrocenie pamieci zajetej przez tablice do systemu)
            }
        }break;
        case 4:
        {
          cout<<"Podaj rozmiar tablicy: ";
            cin>>R;
            if (!cin)
            {
                cout<<"Podany rozmiar tablicy nie jest liczba. Program zostal zakonczony."<<endl; // sprawdzenie czy wprowadzony znak jest wartoscia int, jesli nie wyswietlany jest komunikat
                cin.clear();
                cin.sync();
            }
            else
            {
            int *Tablica = new int[R]; // deklaracja tablicy o wielkosci podanej przez uzytkownika, do ktorej wylosowane zostana liczby
            cout<<"Zakres losowania [ 0, N ], podaj N: ";
            cin>>N;
            generatorCiagow(Tablica,R,N); // wywolanie funkcji generujacej liczby calkowite z przedzialu od 0 do podanego N i zapisujacej je do pliku "losowe.txt"
            cout<<endl;
            cout<<"Gotowe!"<<endl;
            delete [] Tablica; // usuniecie tablicy dynamicznej z systemu (zwrocenie pamieci zajetej przez tablice do systemu)
            }
        }
    };
    };
    getch();

    return 0;
}
