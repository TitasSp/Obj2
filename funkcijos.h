#pragma once
#include "mano_lib.h"


template <typename Container>
struct Studentas {
    string vardas;
    string pavarde;
    Container pazymiai;
    int egzaminas;
    float galutinis;
};

template <typename Container>
float Vidurkis(const Container& pazymiai) {
    if (pazymiai.empty()) return 0.0f;
    return std::accumulate(pazymiai.begin(), pazymiai.end(), 0.0f) / pazymiai.size();
}


template <typename Container>
float Mediana(Container pazymiai) { // Pass by value to allow sorting
    if (pazymiai.empty()) return 0.0f;

    if constexpr (std::is_same<Container, std::list<typename Container::value_type>>::value) {
        pazymiai.sort(); // Use list's sort method
    } else {
        std::sort(pazymiai.begin(), pazymiai.end()); // Use std::sort for vector and deque
    }

    size_t size = pazymiai.size();
    auto it = pazymiai.begin();
    std::advance(it, size / 2);

    if (size % 2 == 0) {
        auto it_prev = it;
        std::advance(it_prev, -1);
        return (*it + *it_prev) / 2.0f;
    } else {
        return *it;
    }
}

template <typename Container>
void GeneruotiPazymius(int pazymiuSk, Container& pazymiai) {
    for (int i = 0; i < pazymiuSk; ++i) {
        pazymiai.push_back(rand() % 10 + 1); // Generate random grades between 1 and 10
    }
}

template <typename Container>
void GeneruotiStudentus(int studentuSk, int pazymiuSk, Container& studentai) {
    if (studentuSk <= 0 || pazymiuSk <= 0) {
        throw invalid_argument("Studentu ir pazymiu skaicius turi buti teigiami");
    }
    vector<string> vardai = {"Jonas", "Petras", "Antanas", "Tomas", "Marius"};
    vector<string> pavardes = {"Jonaitis", "Petraitis", "Antanaitis", "Tomaitis", "Maraitis"};

    for (int i = 0; i < studentuSk; i++) {
        typename Container::value_type studentas; // Correctly instantiate Studentas
        studentas.vardas = vardai[rand() % vardai.size()];
        studentas.pavarde = pavardes[rand() % pavardes.size()];
        GeneruotiPazymius(pazymiuSk, studentas.pazymiai); 
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
    getline(in, line); // Skip the first line

    while (getline(in, line)) {
        istringstream iss(line);
        typename Container::value_type studentas; // Correctly instantiate Studentas
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

        studentai.push_back(move(studentas));
    }

    // Use shrink_to_fit only for vector and deque
    if constexpr (std::is_same<Container, std::vector<typename Container::value_type>>::value ||
                  std::is_same<Container, std::deque<typename Container::value_type>>::value) {
        studentai.shrink_to_fit();
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
            // Do not sort
            break;
        case 1:
            if constexpr (std::is_same<Container, std::list<typename Container::value_type>>::value) {
                studentai.sort([](const auto& a, const auto& b) { return a.vardas < b.vardas; });
            } else {
                std::sort(studentai.begin(), studentai.end(), [](const auto& a, const auto& b) { return a.vardas < b.vardas; });
            }
            break;
        case 2:
            if constexpr (std::is_same<Container, std::list<typename Container::value_type>>::value) {
                studentai.sort([](const auto& a, const auto& b) { return a.pavarde < b.pavarde; });
            } else {
                std::sort(studentai.begin(), studentai.end(), [](const auto& a, const auto& b) { return a.pavarde < b.pavarde; });
            }
            break;
        case 3:
            if constexpr (std::is_same<Container, std::list<typename Container::value_type>>::value) {
                studentai.sort([](const auto& a, const auto& b) { return a.galutinis < b.galutinis; });
            } else {
                std::sort(studentai.begin(), studentai.end(), [](const auto& a, const auto& b) { return a.galutinis < b.galutinis; });
            }
            break;
        case 4:
            if constexpr (std::is_same<Container, std::list<typename Container::value_type>>::value) {
                studentai.sort([](const auto& a, const auto& b) { return a.galutinis > b.galutinis; });
            } else {
                std::sort(studentai.begin(), studentai.end(), [](const auto& a, const auto& b) { return a.galutinis > b.galutinis; });
            }
            break;
        default:
            throw invalid_argument("Neteisingas rikiavimo pasirinkimas");
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Studentu rikiavimas uztruko: " << duration.count() << " ms" << endl;
}
/*
template <typename Container>
void VykdytiPrograma(Container& studentai);
template <typename Container>
float Vidurkis(const Container& pazymiai);
template <typename Container>
float Mediana(Container pazymiai);
template <typename Container>
void GeneruotiPazymius(int pazymiuSk, Container& pazymiai);
template <typename Container>
void GeneruotiStudentus(int studentuSk, int pazymiuSk, Container& studentai);
template <typename Container>
void NuskaitytiStudentusIsFailo(string failas, Container& studentai);
template <typename Container>
void RikiuotiStudentus(Container& studentai, int pasirinkimas);
*/
void FailuGeneravimas(int studentuSk, int pazymiuSk);
void StudentuAtskirimas();
void Test1();
template <typename Container>
void Test2();
