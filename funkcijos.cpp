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

void FailuGeneravimas(int studentuSk, int pazymiuSk) {
    auto startVisas = high_resolution_clock::now();
    ofstream out("studentai" + to_string(studentuSk) + ".txt");
    ostringstream buffer;

    buffer << left << setw(25) << "Vardas" << setw(25) << "Pavarde";
    for (int i = 1; i <= pazymiuSk; i++) {
        buffer << setw(10) << ("ND " + to_string(i));
    }
    buffer << setw(10) << "Egz." << endl;
    out << buffer.str();
    buffer.str(""); // isvalo bufferi

    auto startGeneravimas = high_resolution_clock::now();
    auto totalIrasymasDuration = milliseconds(0);

    // generuoja studentus su pazymiais
    for (int i = 1; i <= studentuSk; i++) {
        
        buffer << left << setw(25) << ("Vardas" + to_string(i)) << setw(25) << ("Pavarde" + to_string(i));
        for (int j = 0; j < pazymiuSk; j++) {
            buffer << setw(10) << (rand() % 10 + 1);
        }
        buffer << setw(10) << (rand() % 10 + 1) << endl;

        if (i % 100000 == 0) { // iraso i faila kas 100000 irasu
            auto startIrasymas = high_resolution_clock::now();
            out << buffer.str();
            buffer.str(""); // isvalo bufferi
            auto endIrasymas = high_resolution_clock::now();
            totalIrasymasDuration += duration_cast<milliseconds>(endIrasymas - startIrasymas);
        }
    }
    auto endGeneravimas = high_resolution_clock::now();
    auto durationGeneravimas = duration_cast<milliseconds>(endGeneravimas - startGeneravimas);

    auto startIrasymas = high_resolution_clock::now();
    // likusius irasom i faila
    out << buffer.str();
    out.close();
    auto endIrasymas = high_resolution_clock::now();
    totalIrasymasDuration += duration_cast<milliseconds>(endIrasymas - startIrasymas);
    
    auto endVisas = high_resolution_clock::now();
    auto durationVisas = duration_cast<milliseconds>(endVisas - startVisas);

    cout << "Studentu generavimas uztruko: " << (durationGeneravimas.count() - totalIrasymasDuration.count()) << " ms" << endl;
    cout << "Studentu irasymas i faila uztruko: " << totalIrasymasDuration.count() << " ms" << endl;
    cout << "Is viso uztruko: " << durationVisas.count() << " ms" << endl;
}
/*void StudentuAtskirimas() {

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

    auto start = high_resolution_clock::now();

    while (in >> vardas >> pavarde >> galutinis) {
        if (galutinis < 5) {
            bufferVargsiukai << left << setw(15) << vardas << setw(20) << pavarde << fixed << setprecision(2) << galutinis << endl;
        } else {
            bufferKieti << left << setw(15) << vardas << setw(20) << pavarde << fixed << setprecision(2) << galutinis << endl;
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
    in.close();
} 
*/
///////////////////////////////////////////////////////////////////////////
void Test1() {
    vector<int> studentuSkaiciai = {1000, 10000, 100000, 1000000, 10000000};
    int pazymiuSk = 10; // pazymiu skaicius
    
    for (int studentuSk : studentuSkaiciai) {
        cout << "Generuojami " << studentuSk << " studentu" << endl;
        
        FailuGeneravimas(studentuSk, pazymiuSk);
       
    }
}

void Test2() {
    vector<string> failai = {"studentai1000.txt", "studentai10000.txt", "studentai100000.txt", "studentai1000000.txt", "studentai10000000.txt"};

    
    for (string failas : failai) {
        cout << failas << endl;
        auto start = high_resolution_clock::now();
        ofstream out;
        
        out.open("rezultatai.txt", ios::trunc | ios::out | ios::binary);
          
        vector<Studentas> studentai;
        NuskaitytiStudentusIsFailo(failas, studentai);
        
        
        out << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;
        
        // loopina per kiekviena studenta studentu vektoriuje ir skaiciuoja galutini pazymi 
        for (auto& studentas : studentai) {
           
                studentas.setGalutinis(0.4 * Vidurkis(studentas.getPazymiai()) + 0.6 * studentas.getEgzaminas());
        }

        RikiuotiStudentus(studentai, 0);

        // irasoma dalimis, kad neuzimtu per daug atminties
        const size_t chunkSize = 100000; // daliu dydis
        size_t totalStudents = studentai.size();
        for (size_t i = 0; i < totalStudents; i += chunkSize) {
            size_t end = min(i + chunkSize, totalStudents);
            for (size_t j = i; j < end; ++j) {
          
                out << left << setw(15) << studentai[j].getVardas() << setw(20) << studentai[j].getPavarde() << fixed << setprecision(2) << studentai[j].getGalutinis() << endl;
               
            }
        }
        StudentuAtskirimas(studentai);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        cout << "Is viso uztruko: " << duration.count() << " ms" << endl;
        cout << endl;
    }

}

void Test3() {
    //vector<string> failai = {"studentai1000.txt", "studentai10000.txt", "studentai100000.txt", "studentai1000000.txt", "studentai10000000.txt"};
    vector <string> failai = {"studentai100000.txt", "studentai1000000.txt"};
    for (string failas : failai) {
        cout << failas << endl;
        auto start = high_resolution_clock::now();
        ofstream out;
        
        out.open("rezultatai.txt", ios::trunc | ios::out | ios::binary);
          
        vector<Studentas> studentai;
        //deque<Studentas> studentai;
        //list<Studentas> studentai;
        NuskaitytiStudentusIsFailo(failas, studentai);
        
        
        out << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;
        
        // loopina per kiekviena studenta studentu vektoriuje ir skaiciuoja galutini pazymi 
        for (auto& studentas : studentai) {
           
                studentas.setGalutinis ( 0.4 * Vidurkis(studentas.getPazymiai()) + 0.6 * studentas.getEgzaminas());
        }

        RikiuotiStudentus(studentai, 3);

        // rasoma dalimis, kad neuzimtu per daug atminties
        const size_t chunkSize = 100000; // daliu dydis
        size_t totalStudents = studentai.size();
        auto it = studentai.begin(); // Initialize an iterator for the list
        
        for (size_t i = 0; i < totalStudents; i += chunkSize) {
            size_t end = min(i + chunkSize, totalStudents);
            for (size_t j = i; j < end; ++j, ++it) { // Increment the iterator directly
                out << left << setw(15) << it->getVardas() << setw(20) << it->getPavarde() << fixed << setprecision(2) << it->getGalutinis() << endl;
            }
        }
        //StudentuAtskirimas(studentai);
        SkaidytiStudentus3Strategija(studentai);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        cout << "Is viso uztruko: " << duration.count() << " ms" << endl;
        cout << endl;
    }

}

void TestStudentas() {
    // Test default constructor
    Studentas s1;
    assert(s1.getVardas().empty());
    assert(s1.getPavarde().empty());
    assert(s1.getPazymiai().empty());
    assert(s1.getEgzaminas() == 0);
    assert(s1.getGalutinis() == 0.0f);

    // Test parameterized constructor
    vector<int> pazymiai = {8, 9, 10};
    Studentas s2("Jonas", "Jonaitis", pazymiai, 9);
    assert(s2.getVardas() == "Jonas");
    assert(s2.getPavarde() == "Jonaitis");
    assert(s2.getPazymiai() == pazymiai);
    assert(s2.getEgzaminas() == 9);

    // Test copy constructor
    Studentas s3(s2);
    assert(s3.getVardas() == "Jonas");
    assert(s3.getPavarde() == "Jonaitis");
    assert(s3.getPazymiai() == pazymiai);
    assert(s3.getEgzaminas() == 9);

    // Test move constructor
    Studentas s4(std::move(s3));
    assert(s4.getVardas() == "Jonas");
    assert(s4.getPavarde() == "Jonaitis");
    assert(s4.getPazymiai() == pazymiai);
    assert(s4.getEgzaminas() == 9);
    assert(s3.getVardas().empty()); // s3 should be empty after move

    // Test copy assignment operator
    Studentas s5;
    s5 = s2;
    assert(s5.getVardas() == "Jonas");
    assert(s5.getPavarde() == "Jonaitis");
    assert(s5.getPazymiai() == pazymiai);
    assert(s5.getEgzaminas() == 9);

    // Test move assignment operator
    Studentas s6;
    s6 = std::move(s5);
    assert(s6.getVardas() == "Jonas");
    assert(s6.getPavarde() == "Jonaitis");
    assert(s6.getPazymiai() == pazymiai);
    assert(s6.getEgzaminas() == 9);
    assert(s5.getVardas().empty()); // s5 should be empty after move

    // Test setters
    s1.setVardas("Petras");
    s1.setPavarde("Petraitis");
    s1.setPazymiai({7, 8, 9});
    s1.setEgzaminas(10);
    s1.setGalutinis(8.5f);
    assert(s1.getVardas() == "Petras");
    assert(s1.getPavarde() == "Petraitis");
    assert(s1.getPazymiai() == vector<int>({7, 8, 9}));
    assert(s1.getEgzaminas() == 10);
    assert(s1.getGalutinis() == 8.5f);

    // Test input operator
    std::istringstream input("Antanas Antanaitis 7 8 9 10");
    Studentas s7;
    input >> s7;
    assert(s7.getVardas() == "Antanas");
    assert(s7.getPavarde() == "Antanaitis");
    assert(s7.getPazymiai() == vector<int>({7, 8, 9}));
    assert(s7.getEgzaminas() == 10);

    // Test output operator
    std::ostringstream output;
    output << s7;
    std::string expectedOutput = "Antanas        Antanaitis          7         8         9         10        0.00";
    assert(output.str().find("Antanas") != std::string::npos); // Check if output contains expected data

    std::cout << "Viskas veikia" << std::endl;
}
