#include "funkcijos.h"

float Vidurkis(vector<int> pazymiai) {
    if (pazymiai.empty()) {
        throw invalid_argument("Pazymiu sarasas yra tuscias");
    }
    float suma = 0;
    for (int pazymys : pazymiai) {
        suma += pazymys;
    }
    return suma / pazymiai.size();
}

float Mediana(vector<int> pazymiai) {
    if (pazymiai.empty()) {
        throw invalid_argument("Pazymiu sarasas yra tuscias");
    }
    sort(pazymiai.begin(), pazymiai.end());
    int pazSk = pazymiai.size();
    if (pazSk % 2 == 0) {
        return (pazymiai[pazSk / 2 - 1] + pazymiai[pazSk / 2]) / 2.0;
    } else {
        return pazymiai[pazSk / 2];
    }
}

void GeneruotiPazymius(int pazymiuSk, vector<int>& pazymiai) {
    if (pazymiuSk <= 0) {
        throw invalid_argument("Pazymiu skaicius turi buti teigiamas");
    }
    for(int i = 0; i < pazymiuSk; i++){
        pazymiai.push_back(rand() % 10 + 1);
        cout << pazymiai[i] << " ";
    }
    cout << endl;
}

void GeneruotiStudentus(int studentuSk, vector<Studentas>& studentai) {
    if (studentuSk <= 0) {
        throw invalid_argument("Studentu skaicius turi buti teigiamas");
    }
    vector<string> vardai = {"Jonas", "Petras", "Antanas", "Tomas", "Marius"};
    vector<string> pavardes = {"Jonaitis", "Petraitis", "Antanaitis", "Tomaitis", "Maraitis"};

    for (int i = 0; i < studentuSk; i++) {
        Studentas studentas;
        studentas.vardas = vardai[rand() % vardai.size()];
        studentas.pavarde = pavardes[rand() % pavardes.size()];
        GeneruotiPazymius(rand() % 10 + 1, studentas.pazymiai);
        studentas.egzaminas = rand() % 10 + 1;
        studentai.push_back(studentas);
    }
}

void NuskaitytiStudentusIsFailo(string failas, vector<Studentas>& studentai) {
    ifstream in(failas);
    if (!in.is_open()) {
        throw runtime_error("Nepavyko atidaryti failo");
    }
    string vardas, pavarde;
    int pazymys;

    // praleidzia pirma eilute
    string pirmaEilute;
    getline(in, pirmaEilute);

    while (in >> vardas >> pavarde) {
        Studentas studentas;
        studentas.vardas = vardas;
        studentas.pavarde = pavarde;
        studentas.pazymiai.clear();
        
        // nuskaito pazymius iki egzamino pazymio
        while (in >> pazymys) {
            if (in.peek() == '\n' || in.peek() == EOF) {
                studentas.egzaminas = pazymys;
                break;
            }
        studentas.pazymiai.push_back(pazymys);
        }
        studentai.push_back(studentas);
    }
    in.close();
}

void RikiuotiStudentus(vector<Studentas>& studentai, int pasirinkimas) {
    switch (pasirinkimas) {
        case 0:
            // nerikiuoti
            break;
        case 1:
            sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                return a.vardas < b.vardas;
            });
            break;
        case 2:
            sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                return a.pavarde < b.pavarde;
            });
            break;
        case 3:
            sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                return a.galutinis < b.galutinis;
            });
            break;
        case 4:
            sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                return a.galutinis > b.galutinis;
            });
            break;
        default:
            throw invalid_argument("Neteisingas rikiavimo pasirinkimas");
    }
}

void FailuGeneravimas(int studentuSk, int pazymiuSk) {
    vector<Studentas> studentai;
    for (int i = 1; i <= studentuSk; i++) {
        Studentas studentas;
        studentas.vardas = "vardas" + to_string(i);
        studentas.pavarde = "pavarde" + to_string(i);
        for (int j = 0; j < pazymiuSk; j++) {
            studentas.pazymiai.push_back(rand() % 10 + 1);
        }
        studentas.egzaminas = rand() % 10 + 1;
        studentai.push_back(studentas);
    }
    ofstream out("studentai" + to_string(studentuSk) + ".txt");
    out << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Pazymiai" << "Egzaminas" << endl;
    for (auto& studentas : studentai) {
        out << left << setw(15) << studentas.vardas << setw(20) << studentas.pavarde;
        for (int pazymys : studentas.pazymiai) {
            out << pazymys << " ";
        }
        out << studentas.egzaminas << endl;
    }
    out.close();
}