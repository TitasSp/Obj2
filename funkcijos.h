#include "mano_lib.h"

template <typename Container>
struct Studentas {
    string vardas;
    string pavarde;
    Container pazymiai;
    int egzaminas;
    float galutinis;
};

template <typename Container>
float Vidurkis(const Container& pazymiai);
template <typename Container>
float Mediana(Container pazymiai);
template <typename Container>
void GeneruotiPazymius(int pazymiuSk, Container& pazymiai);
template <typename Container>
void GeneruotiStudentus(int studentuSk, Container& studentai);
template <typename Container>
void NuskaitytiStudentusIsFailo(string failas, Container& studentai);
template <typename Container>
void RikiuotiStudentus(Container& studentai, int pasirinkimas);
void FailuGeneravimas(int studentuSk, int pazymiuSk);
void StudentuAtskirimas();
void Test1();
template <typename Container>
void Test2();