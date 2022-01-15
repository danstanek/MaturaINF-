#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const char* WEJSCIE_NAZWA = "dane.txt";
const char* WYJSCIE_NAZWA = "zad_5.txt";
const char* SLOWA_WYJSCIE_NAZWA = "slowa.txt";

struct Para
{
    string a;
    string b;
};

vector<Para> dane;

void WczytajDane();

bool CzyPalindrom(const string& wartosc);
bool CzyBJestWA(const Para& para);
int PrefiksDlugosc(const Para& para);
int SufiksDlugosc(const Para& para);
string BudujC(const Para& para);

int ZadanieA();
int ZadanieB();
int ZadanieC();
void ZadanieD();

int main()
{
    WczytajDane();

    fstream plikWyjsciowy(WYJSCIE_NAZWA, fstream::out);

    plikWyjsciowy << "a) " << ZadanieA() << endl;
    plikWyjsciowy << "b) " << ZadanieB() << endl;
    plikWyjsciowy << "c) " << ZadanieC() << endl;

    plikWyjsciowy.close();

    ZadanieD();

    return 0;
}

void WczytajDane()
{
    fstream plik(WEJSCIE_NAZWA);

    string tmp;
    while (plik >> tmp)
    {
        Para p;
        p.a = tmp;
        plik >> p.b;
        dane.push_back(p);
    }

    plik.close();
}

bool CzyPalindrom(const string& wartosc)
{
    for (int i = 0; i < wartosc.length(); i++)
    {
        int j = wartosc.length() - i - 1;
        if (wartosc[i] != wartosc[j]) return false;
    }

    return true;
}
bool CzyBJestWA(const Para& para)
{
    for (int i = 0; i < para.a.length(); i++)
    {
        bool jest = true;
        for (int j = 0; j < para.b.length(); j++)
        {
            if (i + j >= para.a.length())
            {
                jest = false;
                break;
            }

            if (para.a[i + j] != para.b[j])
            {
                jest = false;
                break;
            }
        }

        if (jest) return true;
    }

    return false;
}
int PrefiksDlugosc(const Para& para)
{
    int dlugosc = 0;

    for (int i = 0; i < para.b.length(); i++)
    {
        int doSprawdzenia = para.b.length() - i;

        bool ok = true;

        for (int j = 0; j < doSprawdzenia; j++)
        {
            if (para.a[j] != para.b[i + j])
            {
                ok = false;
                break;
            }
        }

        if (ok && doSprawdzenia > dlugosc) dlugosc = doSprawdzenia;
    }

    return dlugosc;
}
int SufiksDlugosc(const Para& para)
{
    int dlugosc = 0;

    for (int i = para.b.length(); i > 0; i--)
    {
        int startA = para.a.length() - i;

        bool ok = true;

        for (int j = 0; j < i; j++)
        {
            if (para.a[j + startA] != para.b[j])
            {
                ok = false;
                break;
            }
        }

        if (ok && i > dlugosc) dlugosc = i;
    }

    return dlugosc;
}
string BudujC(const Para& para)
{
    int prefiks = PrefiksDlugosc(para);
    int sufiks = SufiksDlugosc(para);

    if (CzyBJestWA(para))
    {
        return para.a;
    }
    else if (prefiks > sufiks)
    {
        return para.b + para.a.substr(prefiks, para.a.length() - prefiks);
    }
    else if (sufiks > prefiks)
    {
        return para.a + para.b.substr(sufiks, para.b.length() - sufiks);
    }

    return para.a + para.b;
}

int ZadanieA()
{
    int ilosc = 0;

    for(vector<Para>::const_iterator i = dane.begin(); i != dane.end(); i++)
    {
        if (CzyPalindrom(i->a)) ilosc++;
        if (CzyPalindrom(i->b)) ilosc++;
    }

    return ilosc;
}
int ZadanieB()
{
    int ilosc = 0;

    for(vector<Para>::const_iterator i = dane.begin(); i != dane.end(); i++)
    {
        if (CzyBJestWA(*i)) ilosc++;
    }

    return ilosc;
}
int ZadanieC()
{
    int ilosc = 0;

    for(vector<Para>::const_iterator i = dane.begin(); i != dane.end(); i++)
    {
        if (PrefiksDlugosc(*i) == 0 && SufiksDlugosc(*i) == 0 && !CzyBJestWA(*i)) ilosc++;
    }

    return ilosc;
}
void ZadanieD()
{
    fstream plikSlowa(SLOWA_WYJSCIE_NAZWA, fstream::out);

    for (vector<Para>::const_iterator i = dane.begin(); i != dane.end(); i++)
    {
        plikSlowa << BudujC(*i) << endl;
    }

    plikSlowa.close();
}
