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

int main() {
    bool vid; // ar naudoti vidurki ar mediana
    vector<Studentas> studentai;

    while (true) {
        Studentas studentas;
        cout << "Iveskite studento varda(norint baigti iveskite: q): ";
        cin >> studentas.vardas;
        if (studentas.vardas == "q") break;
        cout << "Iveskite studento pavarde: ";
        cin >> studentas.pavarde;
        cout << "Iveskite pazymius (iveskite -1 norint baigti): ";
        int pazymys;
        while (true) {
            cin >> pazymys;
            if (pazymys == -1) break;
            studentas.pazymiai.push_back(pazymys);
        }
        cout << "Iveskite studento egzamino pazymi: ";
        cin >> studentas.egzaminas;
        studentai.push_back(studentas);
    }

    // loopina per kiekviena studenta studentu vektoriuje ir skaiciuoja galutini pazymi 
    for (auto& studentas : studentai) {
        cout << "Iveskite 1 jei norite skaiciuoti vidurki, 0 jei norite skaiciuoti mediana: ";
        cin >> vid;
        if (vid) {
            studentas.galutinis = 0.4 * Vidurkis(studentas.pazymiai) + 0.6 * studentas.egzaminas;
        } else {
            studentas.galutinis = 0.4 * Mediana(studentas.pazymiai) + 0.6 * studentas.egzaminas;
        }
        cout << fixed << setprecision(2) << studentas.vardas << " " << studentas.pavarde << " " << studentas.galutinis << endl;
    }

    return 0;
}

float Vidurkis(vector<int> pazymiai) {
    float suma = 0;
    for (int pazymys : pazymiai) {
        suma += pazymys;
    }
    return suma / pazymiai.size();
}

float Mediana(vector<int> pazymiai) {
    sort(pazymiai.begin(), pazymiai.end());
    int pazSk = pazymiai.size();
    if (pazSk % 2 == 0) {
        return (pazymiai[pazSk / 2 - 1] + pazymiai[pazSk / 2]) / 2.0;
    } else {
        return pazymiai[pazSk / 2];
    }
}