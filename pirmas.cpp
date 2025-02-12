#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::fixed;
using std::setprecision;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> pazymiai;
    int egzaminas;
    float galutinis;
    int pazSk; // pazymiu skaicius
};

float Vidurkis(vector<int> pazymiai, int pazSk);


int main() {
    int n; // studentu skaicius
    
    cout << "Iveskite studentu skaiciu: ";
    cin >> n;
    vector<Studentas> studentas(n);

    //loopina per visus studentus ir iveda ju duomenis
    for (int i = 0; i < n; i++) {
        cout << "Iveskite studento varda: ";
        cin >> studentas[i].vardas;
        cout << "Iveskite studento pavarde: ";
        cin >> studentas[i].pavarde;
        cout << "Iveskite pazymiu skaiciu: ";
        cin >> studentas[i].pazSk;
        studentas[i].pazymiai.resize(studentas[i].pazSk); // pazymiu vektoriui priskiriam dydi
        cout << "Iveskite studento pazymius: ";
        for (int j = 0; j < studentas[i].pazSk; j++) {
            cin >> studentas[i].pazymiai[j];
        }
        cout << "Iveskite studento egzamino pazymi: ";
        cin >> studentas[i].egzaminas;
        
    }

    for (int i = 0; i < n; i++) {
        studentas[i].galutinis = 0.4 * Vidurkis(studentas[i].pazymiai, studentas[i].pazSk) + 0.6 * studentas[i].egzaminas;
        cout << fixed << setprecision(2) << studentas[i].vardas << " " << studentas[i].pavarde << " " << studentas[i].galutinis << endl;
    }

    return 0;
}

float Vidurkis(vector<int> pazymiai, int pazSk) {
    float suma = 0;
    for (int i = 0; i < pazSk; i++) {
        suma += pazymiai[i];
    }
    return suma / pazSk;
}