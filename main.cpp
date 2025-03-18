#include "mano_lib.h"
#include "funkcijos.h"

// Function template to handle the main program logic for different container types
template <typename Container>
void VykdytiPrograma(Container& studentai) {
    try {
        auto start = std::chrono::high_resolution_clock::now(); // Start timer
        std::chrono::duration<double> inputWaitDuration(0); // Input waiting time

        srand(time(0)); // Initialize random seed
        int vid; // Whether to use average or median
        int iFaila; // Whether to output to a file
        int pasirinkimas;
        int pazymiuSk;
        string failas;

        while (true) {
            auto inputStart = std::chrono::high_resolution_clock::now(); // Start input waiting time
            cout << "Pasirinkite veiksma:\n";
            cout << "1 - Ivesti viska ranka\n";
            cout << "2 - Generuoti pazymius\n";
            cout << "3 - Generuoti ir pazymius ir studentu vardus, pavardes\n";
            cout << "4 - Nuskaityti studentus is failo\n";
            cout << "5 - Baigti darba\n";
            cin >> pasirinkimas;
            inputWaitDuration += std::chrono::high_resolution_clock::now() - inputStart; // Add input waiting time

            // Validate input
            if (cin.fail() || pasirinkimas < 1 || pasirinkimas > 5) {
                cerr << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (pasirinkimas == 5) break;

            if (pasirinkimas == 1 || pasirinkimas == 2) {
                Studentas<typename Container::value_type> studentas;
                cout << "Iveskite studento varda: ";
                cin >> studentas.vardas;
                cout << "Iveskite studento pavarde: ";
                cin >> studentas.pavarde;

                if (pasirinkimas == 1) {
                    int pazymys;
                    while (true) {
                        cout << "Iveskite pazymi (iveskite -1 norint baigti): ";
                        cin >> pazymys;

                        if (cin.fail() || pazymys < -1 || pazymys > 10) {
                            cerr << "Netinkama ivestis. Bandykite dar karta." << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                        if (pazymys == -1) break;

                        studentas.pazymiai.push_back(pazymys);
                    }
                } else {
                    cout << "Iveskite pazymiu skaiciu: ";
                    cin >> pazymiuSk;

                    if (cin.fail() || pazymiuSk <= 0) {
                        cerr << "Netinkama ivestis. Bandykite dar karta." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    GeneruotiPazymius(pazymiuSk, studentas.pazymiai);
                }

                cout << "Iveskite studento egzamino pazymi: ";
                cin >> studentas.egzaminas;

                if (cin.fail() || studentas.egzaminas < 0 || studentas.egzaminas > 10) {
                    cerr << "Netinkama ivestis. Bandykite dar karta." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                studentai.push_back(studentas);
            } else if (pasirinkimas == 3) {
                cout << "Iveskite studentu skaiciu: ";
                int studentuSk;
                cin >> studentuSk;

                if (cin.fail() || studentuSk <= 0) {
                    cerr << "Netinkama ivestis. Bandykite dar karta." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                cout << "Iveskite pazymiu skaiciu: ";
                cin >> pazymiuSk;

                if (cin.fail() || pazymiuSk <= 0) {
                    cerr << "Netinkama ivestis. Bandykite dar karta." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                GeneruotiStudentus(studentuSk, pazymiuSk, studentai);
            } else if (pasirinkimas == 4) {
                cout << "Iveskite failo pavadinima: ";
                cin >> failas;

                ifstream in(failas);
                if (!in.is_open()) {
                    cerr << "Nepavyko atidaryti failo." << endl;
                    continue;
                }
                in.close();

                NuskaitytiStudentusIsFailo(failas, studentai);
            }
        }

        cout << "Iveskite 1 jei norite skaiciuoti vidurki, 0 jei norite skaiciuoti mediana: ";
        cin >> vid;

        if (cin.fail() || vid < 0 || vid > 1) {
            cerr << "Netinkama ivestis. Programa baigiama." << endl;
            return;
        }

        cout << "Isvesti atsakymus i faila? (1 - taip, 0 - ne): ";
        cin >> iFaila;

        if (cin.fail() || iFaila < 0 || iFaila > 1) {
            cerr << "Netinkama ivestis. Programa baigiama." << endl;
            return;
        }

        ofstream out;
        if (iFaila) {
            out.open("rezultatai.txt", ios::trunc | ios::out);
            if (!out) {
                cerr << "Nepavyko atidaryti failo rasymui." << endl;
                return;
            }
        }

        for (auto& studentas : studentai) {
            if (vid) {
                studentas.galutinis = 0.4 * Vidurkis(studentas.pazymiai) + 0.6 * studentas.egzaminas;
            } else {
                studentas.galutinis = 0.4 * Mediana(studentas.pazymiai) + 0.6 * studentas.egzaminas;
            }
        }

        if (iFaila) {
            for (const auto& studentas : studentai) {
                out << studentas.vardas << " " << studentas.pavarde << " " << studentas.galutinis << endl;
            }
            out.close();
        } else {
            for (const auto& studentas : studentai) {
                cout << studentas.vardas << " " << studentas.pavarde << " " << studentas.galutinis << endl;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start - inputWaitDuration;
        cout << "Programos vykdymo trukme (be input laukimo): " << duration.count() << " sekundes" << endl;

    } catch (const exception& e) {
        cerr << "Ivyko klaida: " << e.what() << endl;
    }
}

int main() {
    int konteinerioPasirinkimas;
    cout << "Pasirinkite konteinerio tipa:\n";
    cout << "1 - vector\n";
    cout << "2 - deque\n";
    cout << "3 - list\n";
    cin >> konteinerioPasirinkimas;

    if (cin.fail() || konteinerioPasirinkimas < 1 || konteinerioPasirinkimas > 3) {
        cerr << "Neteisingas konteinerio pasirinkimas. Programa baigiama." << endl;
        return 1;
    }

    if (konteinerioPasirinkimas == 1) {
        vector<Studentas<vector<int>>> studentai;
        VykdytiPrograma(studentai);
    } else if (konteinerioPasirinkimas == 2) {
        deque<Studentas<deque<int>>> studentai;
        VykdytiPrograma(studentai);
    } else if (konteinerioPasirinkimas == 3) {
        list<Studentas<list<int>>> studentai;
        VykdytiPrograma(studentai);
    }

    return 0;
}