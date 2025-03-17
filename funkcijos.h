#include "mano_lib.h"

template <typename Container>
struct Studentas {
    string vardas;
    string pavarde;
    Container pazymiai;
    int egzaminas;
    float galutinis;
};

float Vidurkis(vector<int> pazymiai);
float Mediana(vector<int> pazymiai);
void GeneruotiPazymius(int pazymiuSk, vector<int>& pazymiai);
template <typename Container>
void GeneruotiStudentus(int studentuSk, Container& studentai);
template <typename Container>
void NuskaitytiStudentusIsFailo(string failas, const Container& studentai);
template <typename Container>
void RikiuotiStudentus(Container& studentai, int pasirinkimas);
void FailuGeneravimas(int studentuSk, int pazymiuSk);
void StudentuAtskirimas();
void Test1();
template <typename Container>
void Test2();