#include "mano_lib.h"
#include "strukt_lib.h"

float Vidurkis(vector<int> pazymiai);
float Mediana(vector<int> pazymiai);
void GeneruotiPazymius(int pazymiuSk, vector<int>& pazymiai);
void GeneruotiStudentus(int studentuSk, vector<Studentas>& studentai);
void NuskaitytiStudentusIsFailo(string failas, vector<Studentas>& studentai);
void RikiuotiStudentus(vector<Studentas>& studentai, int pasirinkimas);
