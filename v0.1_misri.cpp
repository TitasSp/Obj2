#include "mano_lib.h"

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> pazymiai;
    int egzaminas;
    float galutinis;
    int pazymiuSk;
};

float Vidurkis(vector<int> pazymiai);
float Mediana(vector<int> pazymiai);
void GeneruotiPazymius(int pazymiuSk, vector<int>& pazymiai);
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
                    studentas.pazymiai.push_back(pazymys);
                    studentas.pazymiuSk++;
                }
            } else {
                cout << "Iveskite pazymiu skaiciu: ";
                int pazymiuSk;
                cin >> pazymiuSk;
                GeneruotiPazymius(pazymiuSk, studentas.pazymiai);
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
            studentai[i].galutinis = 0.4 * Vidurkis(studentai[i].pazymiai) + 0.6 * studentai[i].egzaminas;
        } else {
            studentai[i].galutinis = 0.4 * Mediana(studentai[i].pazymiai) + 0.6 * studentai[i].egzaminas;
        }
        cout << fixed << setprecision(2) << studentai[i].vardas << " " << studentai[i].pavarde << " " << studentai[i].galutinis << endl;
    }

    for (int i = 0; i < studentuSK; i++) {
        studentai[i].pazymiai.clear();
    }
    delete[] studentai;

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

void GeneruotiPazymius(int pazymiuSk, vector<int>& pazymiai) {
    for(int i = 0; i < pazymiuSk; i++){
        pazymiai.push_back(rand() % 10 + 1);
        cout << pazymiai[i] << " ";
    }
    cout << endl;
}

void GeneruotiStudentus(int studentuSk, Studentas*& studentai, int& studentuSkOut) {
    vector<string> vardai = {"Jonas", "Petras", "Antanas", "Tomas", "Marius"};
    vector<string> pavardes = {"Jonaitis", "Petraitis", "Antanaitis", "Tomaitis", "Maraitis"};

    Studentas* tempStudentai = new Studentas[studentuSkOut + studentuSk];
    for (int i = 0; i < studentuSkOut; i++) {
        tempStudentai[i] = studentai[i];
    }

    for (int i = 0; i < studentuSk; i++) {
        Studentas studentas;
        studentas.vardas = vardai[rand() % vardai.size()];
        studentas.pavarde = pavardes[rand() % pavardes.size()];
        GeneruotiPazymius(rand() % 10 + 1, studentas.pazymiai);
        studentas.egzaminas = rand() % 10 + 1;
        tempStudentai[studentuSkOut + i] = studentas;
    }

    delete[] studentai;
    studentai = tempStudentai;
    studentuSkOut += studentuSk;
}