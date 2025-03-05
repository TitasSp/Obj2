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
    ofstream out("studentai" + to_string(studentuSk) + ".txt");
    ostringstream buffer;

    buffer << left << setw(25) << "Vardas" << setw(25) << "Pavarde";
    for (int i = 1; i <= pazymiuSk; i++) {
        buffer << setw(10) << ("ND " + to_string(i));
    }
    buffer << setw(10) << "Egz." << endl;
    out << buffer.str();
    buffer.str(""); // isvalo bufferi

    // generuoja studentus su pazymiais
    for (int i = 1; i <= studentuSk; i++) {
        buffer << left << setw(25) << ("Vardas" + to_string(i)) << setw(25) << ("Pavarde" + to_string(i));
        for (int j = 0; j < pazymiuSk; j++) {
            buffer << setw(10) << (rand() % 10 + 1);
        }
        buffer << setw(10) << (rand() % 10 + 1) << endl;

        if (i % 10000 == 0) { // iraso i faila kas 10000 irasu
            out << buffer.str();
            buffer.str(""); // isvalo bufferi
        }
    }

    // likusius irasa irasom i faila
    out << buffer.str();
    out.close();
}

void StudentuFaileRusiavimas(string failas) {
    vector<Studentas> studentai;
    NuskaitytiStudentusIsFailo(failas, studentai);

    ofstream out("protingi.txt", ios::trunc);
    ofstream out2("nelaimingi.txt", ios::trunc);
    out << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;
    out2 << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;

    for (auto& studentas : studentai) {
        studentas.galutinis = 0.4 * Vidurkis(studentas.pazymiai) + 0.6 * studentas.egzaminas;
        if (studentas.galutinis >= 5.0) {
            out << left << setw(15) << studentas.vardas << setw(20) << studentas.pavarde << fixed << setprecision(2) << studentas.galutinis << endl;
        } else {
            out2 << left << setw(15) << studentas.vardas << setw(20) << studentas.pavarde << fixed << setprecision(2) << studentas.galutinis << endl;
        }
    }
    out.close();
    out2.close();
}