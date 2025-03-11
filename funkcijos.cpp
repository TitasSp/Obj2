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

    string line;
    studentai.reserve(10000000); // rezervuoja atminti

    // praleidzia pirma eilute
    getline(in, line);

    while (getline(in, line)) {
        istringstream iss(line);
        Studentas studentas;
        iss >> studentas.vardas >> studentas.pavarde;

        int pazymys;
        studentas.pazymiai.clear();
        while (iss >> pazymys) {
            studentas.pazymiai.push_back(pazymys);
        }

        // paskutinis skaicius yra egzaminas
        if (!studentas.pazymiai.empty()) {
            studentas.egzaminas = studentas.pazymiai.back();
            studentas.pazymiai.pop_back();
        }

        studentai.push_back(move(studentas)); // naudoja move, kad nereiketu kopijuoti
           
    }
    studentai.shrink_to_fit();
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
    auto start = high_resolution_clock::now();
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

    // likusius irasom i faila
    out << buffer.str();
    out.close();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Failo nuskaitymas uztruko: " << duration.count() << " ms" << endl;
}

void StudentuAtskirimas() {
    ifstream in("rezultatai.txt");
    if (!in.is_open()) {
        throw runtime_error("Nepavyko atidaryti failo");
    }

    ofstream outVargsiukai("stud_b.txt");
    ofstream outKieti("stud_g.txt");

    ostringstream bufferVargsiukai;
    ostringstream bufferKieti;

    bufferVargsiukai.str(""); // isvalo bufferi
    bufferKieti.str(""); // isvalo bufferi

    bufferVargsiukai << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;
    bufferKieti << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;

    string vardas, pavarde;
    float galutinis;

    // praleidzia pirma eilute
    string pirmaEilute;
    getline(in, pirmaEilute);

    while (in >> vardas >> pavarde >> galutinis) {
        if (galutinis < 5) {
            bufferVargsiukai << left << setw(15) << vardas << setw(20) << pavarde << fixed << setprecision(2) << galutinis << endl;
        } else {
            bufferKieti << left << setw(15) << vardas << setw(20) << pavarde << fixed << setprecision(2) << galutinis << endl;
        }
    }

    outVargsiukai << bufferVargsiukai.str();
    outKieti << bufferKieti.str();
    outVargsiukai.close();
    outKieti.close();
    in.close();
} 