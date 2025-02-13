#include "mano_lib.h"

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> pazymiai;
    int egzaminas;
    float galutinis;
    int pazSk; // pazymiu skaicius
};

float Vidurkis(vector<int> pazymiai, int pazSk);
float Mediana(vector<int> pazymiai, int pazSk);

int main() {
    bool vid; // ar naudoti vidurki ar mediana
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

    // loopina per visus studentus ir skaiciuoja galutini pazymi 
    for (int i = 0; i < n; i++) {
        cout << "Iveskite 1 jei norite skaiciuoti vidurki, 0 jei norite skaiciuoti mediana: ";
        cin >> vid;
        if (vid) {
            studentas[i].galutinis = 0.4 * Vidurkis(studentas[i].pazymiai, studentas[i].pazSk) + 0.6 * studentas[i].egzaminas;
        } else {
            studentas[i].galutinis = 0.4 * Mediana(studentas[i].pazymiai, studentas[i].pazSk) + 0.6 * studentas[i].egzaminas;
        }
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

float Mediana(vector<int> pazymiai, int pazSk) {
    sort(pazymiai.begin(), pazymiai.end());
    if (pazSk % 2 == 0) {
        return (pazymiai[pazSk / 2 - 1] + pazymiai[pazSk / 2]) / 2;
    } else {
        return pazymiai[pazSk / 2];
    }
}