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
void GeneruotiPazymius(int pazymiuSk, int*& pazymiai, int& pazymiuSkOut);
void GeneruotiStudentus(int studentuSk, Studentas*& studentai, int& studentuSkOut);

int main() {
    srand(time(0)); // inicializuoja random seeda
    bool vid; // ar naudoti vidurki ar mediana

    Studentas* studentai = nullptr;
    int studentuSK = 0;
    int pasirinkimas;

    while (true) {
        cout << "Pasirinkite veiksma:\n";
        cout << "1 - Ivesti viska ranka\n";
        cout << "2 - Generuoti pazymius\n";
        cout << "3 - Generuoti ir pazymius ir studentu vardus, pavardes\n";
        cout << "4 - Baigti darba\n";
        cin >> pasirinkimas;

        if (pasirinkimas == 4) break;

        if (pasirinkimas == 1 || pasirinkimas == 2) {
            Studentas studentas; // laikinas studentas
            studentas.pazymiai = nullptr;
            studentas.pazymiuSk = 0;

            cout << "Iveskite studento varda: ";
            cin >> studentas.vardas;
            cout << "Iveskite studento pavarde: ";
            cin >> studentas.pavarde;

            if (pasirinkimas == 1) {
                cout << "Iveskite pazymius (iveskite -1 norint baigti): ";
                int pazymys;
                while (true) {
                    cin >> pazymys;
                    if (pazymys == -1) break;
                    int* temp = new int[studentas.pazymiuSk + 1]; // laikinas masyvas pazymiams
                    for (int i = 0; i < studentas.pazymiuSk; i++) {
                        temp[i] = studentas.pazymiai[i]; // nukopijuoja pazymius i laikina masyva
                    }
                    temp[studentas.pazymiuSk] = pazymys; // prideda nauja pazymi
                    delete[] studentas.pazymiai; 
                    studentas.pazymiai = temp;
                    studentas.pazymiuSk++;
                }
            } else {
                cout << "Iveskite pazymiu skaiciu: ";
                int pazymiuSk;
                cin >> pazymiuSk;
                GeneruotiPazymius(pazymiuSk, studentas.pazymiai, studentas.pazymiuSk);
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
        } else if (pasirinkimas == 3) {
            int studentuSk;
            cout << "Iveskite studentu skaiciu: ";
            cin >> studentuSk;
            GeneruotiStudentus(studentuSk, studentai, studentuSK);
        }
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

void GeneruotiPazymius(int pazymiuSk, int*& pazymiai, int& pazymiuSkOut) {
    pazymiai = new int[pazymiuSk];
    for(int i = 0; i < pazymiuSk; i++){
        pazymiai[i] = rand() % 10 + 1;
        cout << pazymiai[i] << " ";
    }
    cout << endl;
    pazymiuSkOut = pazymiuSk;
}

void GeneruotiStudentus(int studentuSk, Studentas*& studentai, int& studentuSkOut) {
    string vardai[] = {"Jonas", "Petras", "Antanas", "Tomas", "Marius"};
    string pavardes[] = {"Jonaitis", "Petraitis", "Antanaitis", "Tomaitis", "Maraitis"};

    Studentas* tempStudentai = new Studentas[studentuSkOut + studentuSk];
    for (int i = 0; i < studentuSkOut; i++) {
        tempStudentai[i] = studentai[i];
    }

    for (int i = 0; i < studentuSk; i++) {
        Studentas studentas;
        studentas.vardas = vardai[rand() % 5];
        studentas.pavarde = pavardes[rand() % 5];
        GeneruotiPazymius(rand() % 10 + 1, studentas.pazymiai, studentas.pazymiuSk);
        studentas.egzaminas = rand() % 10 + 1;
        tempStudentai[studentuSkOut + i] = studentas;
    }

    delete[] studentai;
    studentai = tempStudentai;
    studentuSkOut += studentuSk;
}