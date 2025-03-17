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
void GeneruotiStudentus(int studentuSk, const Container& studentai);
void NuskaitytiStudentusIsFailo(string failas, const Container& studentai);
void RikiuotiStudentus(const Container& studentai, int pasirinkimas);
void FailuGeneravimas(int studentuSk, int pazymiuSk);
void StudentuAtskirimas();
void Test1();
void Test2();