#include "mano_lib.h"

struct Studentas {
    string vardas;
    string pavarde;
    int* pazymiai;
    int pazymiuSk;
    int egzaminas;
    float galutinis;
};

float Vidurkis(int* pazymiai, int pazymiuSk);
float Mediana(int* pazymiai, int pazymiuSk);

int main() {
    bool vid; // ar naudoti vidurki ar mediana

    Studentas* studentai = nullptr;
    int studentuSK = 0;

    while (true) {
        Studentas studentas; // laikinas studentas
        studentas.pazymiai = nullptr;
        studentas.pazymiuSk = 0;

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
            int* temp = new int[studentas.pazymiuSk + 1];
            for (int i = 0; i < studentas.pazymiuSk; i++) {
                temp[i] = studentas.pazymiai[i];
            }
            temp[studentas.pazymiuSk] = pazymys;
            delete[] studentas.pazymiai;
            studentas.pazymiai = temp;
            studentas.pazymiuSk++;
        }
        cout << "Iveskite studento egzamino pazymi: ";
        cin >> studentas.egzaminas;

        Studentas* tempStudentai = new Studentas[studentuSK + 1];
        for (int i = 0; i < studentuSK; i++) {
            tempStudentai[i] = studentai[i];
        }
        tempStudentai[studentuSK] = studentas;
        delete[] studentai;
        studentai = tempStudentai;
        studentuSK++;
    }

    // loopina per kiekviena studenta studentu vektoriuje ir skaiciuoja galutini pazymi 
    for (int i = 0; i < studentuSK; i++) {
        cout << "Iveskite 1 jei norite skaiciuoti vidurki, 0 jei norite skaiciuoti mediana: ";
        cin >> vid;
        if (vid) {
            studentai[i].galutinis = 0.4 * Vidurkis(studentai[i].pazymiai, studentai[i].pazymiuSk) + 0.6 * studentai[i].egzaminas;
        } else {
            studentai[i].galutinis = 0.4 * Mediana(studentai[i].pazymiai, studentai[i].pazymiuSk) + 0.6 * studentai[i].egzaminas;
        }
        cout << fixed << setprecision(2) << studentai[i].vardas << " " << studentai[i].pavarde << " " << studentai[i].galutinis << endl;
    }

    // isvalo dinamine atminti
    for (int i = 0; i < studentuSK; i++) {
        delete[] studentai[i].pazymiai;
    }
    delete[] studentai;

    return 0;
}

float Vidurkis(int* pazymiai, int pazymiuSk) {
    float suma = 0;
    for(int i = 0; i < pazymiuSk; i++){
        suma += pazymiai[i];
    }
    return suma / pazymiuSk;
}

float Mediana(int* pazymiai, int pazymiuSk) {
    sort(pazymiai, pazymiai + pazymiuSk);
    if(pazymiuSk % 2 == 0){
        return (pazymiai[pazymiuSk / 2 - 1] + pazymiai[pazymiuSk / 2]) / 2.0;
    } else {
        return pazymiai[pazymiuSk / 2];
    }
}