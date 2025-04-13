#include "mano_lib.h"

void GeneruotiPazymius(int pazymiuSk, vector<int>& pazymiai);
float Vidurkis(vector<int> pazymiai);
float Mediana(vector<int> pazymiai);

class Studentas {
    private:
        string vardas;
        string pavarde;
        vector<int> pazymiai;
        int egzaminas;
        float galutinis;
    
    public:
        // Constructors
        Studentas() : egzaminas(0), galutinis(0.0f) {}
        Studentas(const string& vardas, const string& pavarde, const vector<int>& pazymiai, int egzaminas)
            : vardas(vardas), pavarde(pavarde), pazymiai(pazymiai), egzaminas(egzaminas), galutinis(0.0f) {}
    

        // Destructor
        ~Studentas() {
            // cleaner kodas
        }
        // Getters
        string getVardas() const { return vardas; }
        string getPavarde() const { return pavarde; }
        vector<int> getPazymiai() const { return pazymiai; }
        vector<int>& getPazymiaiRef() { return pazymiai; }
        int getEgzaminas() const { return egzaminas; }
        float getGalutinis() const { return galutinis; }
    
        // Setters
        void setVardas(const string& v) { vardas = v; }
        void setPavarde(const string& p) { pavarde = p; }
        void setPazymiai(const vector<int>& p) { pazymiai = p; }
        void setEgzaminas(int e) { egzaminas = e; }
        void setGalutinis(float g) { galutinis = g; }
    
        void addPazymys(int pazymys) {
            pazymiai.push_back(pazymys);
        }
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
            studentas.setVardas(vardai[rand() % vardai.size()]);
            studentas.setPavarde(pavardes[rand() % pavardes.size()]);
            
            vector<int> pazymiai;
            GeneruotiPazymius(rand() % 10 + 1, pazymiai);
            studentas.setPazymiai(pazymiai);
            
            studentas.setEgzaminas(rand() % 10 + 1);
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
            string vardas, pavarde;
            iss >> vardas >> pavarde;
            studentas.setVardas(vardas);
            studentas.setPavarde(pavarde);
    
            vector<int> pazymiai;
            int pazymys;
            while (iss >> pazymys) {
                pazymiai.push_back(pazymys);
            }
    
            if (!pazymiai.empty()) {
                studentas.setEgzaminas(pazymiai.back());
                pazymiai.pop_back();
            }
            studentas.setPazymiai(pazymiai);
    
            studentai.push_back(studentas);
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
                    return a.getVardas() < b.getVardas();
                });
            } else {
                sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                    return a.getVardas() < b.getVardas();
                });
            }
            break;
        case 2:
            if constexpr (is_same<Container, list<Studentas>>::value) {
                studentai.sort([](const Studentas& a, const Studentas& b) {
                    return a.getPavarde() < b.getPavarde();
                });
            } else {
                sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                    return a.getPavarde() < b.getPavarde();
                });
            }
            break;
        case 3:
            if constexpr (is_same<Container, list<Studentas>>::value) {
                studentai.sort([](const Studentas& a, const Studentas& b) {
                    return a.getGalutinis() < b.getGalutinis();
                });
            } else {
                sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                    return a.getGalutinis() < b.getGalutinis();
                });
            }
            break;
        case 4:
            if constexpr (is_same<Container, list<Studentas>>::value) {
                studentai.sort([](const Studentas& a, const Studentas& b) {
                    return a.getGalutinis() > b.getGalutinis();
                });
            } else {
                sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                    return a.getGalutinis() > b.getGalutinis();
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
        if (vid) {
            studentas.setGalutinis(0.4 * Vidurkis(studentas.getPazymiai()) + 0.6 * studentas.getEgzaminas());
        } else {
            studentas.setGalutinis(0.4 * Mediana(studentas.getPazymiai()) + 0.6 * studentas.getEgzaminas());
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
        if (studentas.getGalutinis() < 5) {
            bufferVargsiukai << left << setw(15) << studentas.getVardas() << setw(20) << studentas.getPavarde()
                             << fixed << setprecision(2) << studentas.getGalutinis() << endl;
        } else {
            bufferKieti << left << setw(15) << studentas.getVardas() << setw(20) << studentas.getPavarde()
                        << fixed << setprecision(2) << studentas.getGalutinis() << endl;
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

template <typename Container>
void SkaidytiStudentus3Strategija(Container& studentai) {
    auto start = high_resolution_clock::now();
    Container vargsiukai;
    // Naudojame std::partition, kad "vargšiukai" būtų konteinerio gale
    auto it = std::partition(studentai.begin(), studentai.end(), [](const Studentas& studentas) {
        return studentas.getGalutinis() >= 5; // Use getter
    });

    // Kopijuojame "vargšiukus" į naują konteinerį
    vargsiukai.insert(vargsiukai.end(), it, studentai.end());

    // Pašaliname "vargšiukus" iš pradinio konteinerio
    studentai.erase(it, studentai.end());

    // Įrašome "vargšiukus" į failą
    ofstream outVargsiukai("stud_b.txt");
    if (!outVargsiukai.is_open()) {
        throw runtime_error("Nepavyko atidaryti failo");
    }
    outVargsiukai << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;
    for (const auto& studentas : vargsiukai) {
        outVargsiukai << left << setw(15) << studentas.getVardas() << setw(20) << studentas.getPavarde()
                      << fixed << setprecision(2) << studentas.getGalutinis() << endl;
    }
    outVargsiukai.close();

    // Įrašome "kietiakus" į failą
    ofstream outKietiakai("stud_g.txt");
    if (!outKietiakai.is_open()) {
        throw runtime_error("Nepavyko atidaryti failo");
    }
    outKietiakai << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;
    for (const auto& studentas : studentai) {
        outKietiakai << left << setw(15) << studentas.getVardas() << setw(20) << studentas.getPavarde()
                     << fixed << setprecision(2) << studentas.getGalutinis() << endl;
    }
    outKietiakai.close();

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Studentu skaidymas ir irasymas i failus uztruko: " << duration.count() << " ms" << endl;
}

//float Vidurkis(vector<int> pazymiai);
//float Mediana(vector<int> pazymiai);
//void GeneruotiPazymius(int pazymiuSk, vector<int>& pazymiai);
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