#include "mano_lib.h"

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> pazymiai;
    int egzaminas;
    float galutinis;
};

float Vidurkis(vector<int> pazymiai);
float Mediana(vector<int> pazymiai);
void GeneruotiPazymius(int pazymiuSk, vector<int>& pazymiai);
void GeneruotiStudentus(int studentuSk, vector<Studentas>& studentai);
void NuskaitytiStudentusIsFailo(string failas, vector<Studentas>& studentai);
void RikiuotiStudentus(vector<Studentas>& studentai, int pasirinkimas);
void FailuGeneravimas(int studentuSk, int pazymiuSk);