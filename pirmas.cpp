#include "mano_lib.h"
#include "funkcijos.h"

int main() {
    srand(time(0)); // inicializuoja random seeda
    bool vid; // ar naudoti vidurki ar mediana
    vector<Studentas> studentai;
    int pasirinkimas;
    
    while (true) {
        cout << "Pasirinkite veiksma:\n";
        cout << "1 - Ivesti viska ranka\n";
        cout << "2 - Generuoti pazymius\n";
        cout << "3 - Generuoti ir pazymius ir studentu vardus, pavardes\n";
        cout << "4 - Nuskaityti studentus is failo\n";
        cout << "5 - Baigti darba\n";
        cin >> pasirinkimas;

        if (pasirinkimas == 5) break;

        if (pasirinkimas == 1 || pasirinkimas == 2) {
            Studentas studentas;
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
                }
            } else {
                cout << "Iveskite pazymiu skaiciu: ";
                int pazymiuSk;
                cin >> pazymiuSk;
                GeneruotiPazymius(pazymiuSk, studentas.pazymiai);
            }

            cout << "Iveskite studento egzamino pazymi: ";
            cin >> studentas.egzaminas;
            studentai.push_back(studentas);
        } else if (pasirinkimas == 3) {
            int studentuSk;
            cout << "Iveskite studentu skaiciu: ";
            cin >> studentuSk;
            GeneruotiStudentus(studentuSk, studentai);
        }
        else if (pasirinkimas == 4) {
            string failas;
            cout << "Iveskite failo pavadinima: ";
            cin >> failas;

            auto startRead = high_resolution_clock::now();
            NuskaitytiStudentusIsFailo(failas, studentai);
            auto endRead = high_resolution_clock::now();
            auto durationRead = duration_cast<milliseconds>(endRead - startRead);
            cout << "Failo nuskaitymas uztruko: " << durationRead.count() << " ms" << endl;
        }
    }

    cout << "Iveskite 1 jei norite skaiciuoti vidurki, 0 jei norite skaiciuoti mediana: ";
    cin >> vid;
    cout << "Isvesti atsakymus i faila? (1 - taip, 0 - ne): ";
    bool iFaila;
    cin >> iFaila;
    
    ofstream out;
    if (iFaila) {
        out.open("rezultatai.txt", ios::trunc);
    }
    int rikiavimoPasirinkimas;
    cout << "Pasirinkite rikiavimo buda:\n";
    cout << "0 - Nerikiuoti\n";
    cout << "1 - Pagal varda\n";
    cout << "2 - Pagal pavarde\n";
    cout << "3 - Pagal galutini pazymi didejancia tvarka\n";
    cout << "4 - Pagal galutini pazymi mazejancia tvarka\n";
    cin >> rikiavimoPasirinkimas;

    if (iFaila) {
        out << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;
    }
    else{
        cout << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;
    }

    // loopina per kiekviena studenta studentu vektoriuje ir skaiciuoja galutini pazymi 
    for (auto& studentas : studentai) {
        if (vid) {
            studentas.galutinis = 0.4 * Vidurkis(studentas.pazymiai) + 0.6 * studentas.egzaminas;
        } else {
            studentas.galutinis = 0.4 * Mediana(studentas.pazymiai) + 0.6 * studentas.egzaminas;
        }
        
        RikiuotiStudentus(studentai, rikiavimoPasirinkimas);
        
        if (iFaila) {
            out << left << setw(15) << studentas.vardas << setw(20) << studentas.pavarde << fixed << setprecision(2) << studentas.galutinis << endl;
        } else {
            cout << left << setw(15) << studentas.vardas << setw(20) << studentas.pavarde << fixed << setprecision(2) << studentas.galutinis << endl;
        }
    }

    if (iFaila) {
        out.close();
    }


    return 0;
}
