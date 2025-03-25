#include "mano_lib.h"

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> pazymiai;
    int egzaminas;
    float galutinis;
};


template <typename Container>
void GeneruotiStudentus(int studentuSk, Container& studentai) {
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
template <typename Container>
void NuskaitytiStudentusIsFailo(string failas, Container& studentai) {
    auto start = high_resolution_clock::now();

    ifstream in(failas);
    if (!in.is_open()) {
        throw runtime_error("Nepavyko atidaryti failo");
    }

    string line;
    getline(in, line); // Skip the header line

    if constexpr (is_same<Container, vector<Studentas>>::value) {
        studentai.reserve(10000000); // Reserve memory for vector or deque
    }

    while (getline(in, line)) {
        istringstream iss(line);
        Studentas studentas;
        iss >> studentas.vardas >> studentas.pavarde;

        int pazymys;
        studentas.pazymiai.clear();
        while (iss >> pazymys) {
            studentas.pazymiai.push_back(pazymys);
        }

        if (!studentas.pazymiai.empty()) {
            studentas.egzaminas = studentas.pazymiai.back();
            studentas.pazymiai.pop_back();
        }

        studentai.push_back(studentas); // Avoid move for list
    }

    in.close();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Studentu nuskaitymas is failo uztruko: " << duration.count() << " ms" << endl;
}
template <typename Container>
void RikiuotiStudentus(Container& studentai, int pasirinkimas) {
    auto start = high_resolution_clock::now();

    switch (pasirinkimas) {
        case 0:
            // nerikiuoti
            break;
        case 1:
            if constexpr (is_same<Container, list<Studentas>>::value) {
                studentai.sort([](const Studentas& a, const Studentas& b) {
                    return a.vardas < b.vardas;
                });
            } else {
                sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                    return a.vardas < b.vardas;
                });
            }
            break;
        case 2:
            if constexpr (is_same<Container, list<Studentas>>::value) {
                studentai.sort([](const Studentas& a, const Studentas& b) {
                    return a.pavarde < b.pavarde;
                });
            } else {
                sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                    return a.pavarde < b.pavarde;
                });
            }
            break;
        case 3:
            if constexpr (is_same<Container, list<Studentas>>::value) {
                studentai.sort([](const Studentas& a, const Studentas& b) {
                    return a.galutinis < b.galutinis;
                });
            } else {
                sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                    return a.galutinis < b.galutinis;
                });
            }
            break;
        case 4:
            if constexpr (is_same<Container, list<Studentas>>::value) {
                studentai.sort([](const Studentas& a, const Studentas& b) {
                    return a.galutinis > b.galutinis;
                });
            } else {
                sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                    return a.galutinis > b.galutinis;
                });
            }
            break;
        default:
            throw invalid_argument("Neteisingas rikiavimo pasirinkimas");
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Studentu rikiavimas uztruko: " << duration.count() << " ms" << endl;
}

template <typename Container>
void SkaiciuotiGalutini(Container& studentai, bool vid) {
    for (auto& studentas : studentai) {
        if(vid){
            studentas.galutinis = 0.4 * Vidurkis(studentas.pazymiai) + 0.6 * studentas.egzaminas;
        } else {
            studentas.galutinis = 0.4 * Mediana(studentas.pazymiai) + 0.6 * studentas.egzaminas;
        }
    }
}

template <typename Container>
void StudentuAtskirimas(Container& studentai) {
    ofstream outVargsiukai("stud_b.txt");
    ofstream outKieti("stud_g.txt");

    ostringstream bufferVargsiukai;
    ostringstream bufferKieti;

    bufferVargsiukai << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;
    bufferKieti << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;

    auto start = high_resolution_clock::now();

    for (const auto& studentas : studentai) {
        if (studentas.galutinis < 5) {
            bufferVargsiukai << left << setw(15) << studentas.vardas << setw(20) << studentas.pavarde<< fixed << setprecision(2) << studentas.galutinis << endl;
        } else {
            bufferKieti << left << setw(15) << studentas.vardas << setw(20) << studentas.pavarde<< fixed << setprecision(2) << studentas.galutinis << endl;
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Studentu suskirstymas uztruko: " << duration.count() << " ms" << endl;

    auto start2 = high_resolution_clock::now();

    outVargsiukai << bufferVargsiukai.str();
    outKieti << bufferKieti.str();

    auto end2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(end2 - start2);
    cout << "Studentu irasymas i failus uztruko: " << duration2.count() << " ms" << endl;

    outVargsiukai.close();
    outKieti.close();
}

float Vidurkis(vector<int> pazymiai);
float Mediana(vector<int> pazymiai);
void GeneruotiPazymius(int pazymiuSk, vector<int>& pazymiai);
//template <typename Container>
//void GeneruotiStudentus(int studentuSk, Container& studentai);
//template <typename Container>
//void NuskaitytiStudentusIsFailo(string failas, Container& studentai);
//template <typename Container>
//void RikiuotiStudentus(Container& studentai, int pasirinkimas);
void FailuGeneravimas(int studentuSk, int pazymiuSk);
//void StudentuAtskirimas();
void Test1();
void Test2();
void Test3();