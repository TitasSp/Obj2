#include "mano_lib.h"
#include "funkcijos.h"

int main() {
    try {
        srand(time(0)); // inicializuoja random seeda
        int vid; // ar naudoti vidurki ar mediana
        int iFaila; // ar isvesti i faila
        vector<Studentas> studentai;
        int pasirinkimas;
        int pazymiuSk;
        string failas;
        stringstream buffer;

        while (true) {
            cout << "Pasirinkite veiksma:\n";
            cout << "1 - Ivesti viska ranka\n";
            cout << "2 - Generuoti pazymius\n";
            cout << "3 - Generuoti ir pazymius ir studentu vardus, pavardes\n";
            cout << "4 - Nuskaityti studentus is failo\n";
            cout << "5 - Baigti darba\n";
            cin >> pasirinkimas;

            // patikrina ar ivestas skaicius ir ar jis yra tarp 1 ir 5
            try {
                if (cin.fail() || pasirinkimas < 1 || pasirinkimas > 5) {
                    throw invalid_argument("Neteisingas pasirinkimas");
                }
            } catch (invalid_argument& e) {
                cerr << "Ivyko klaida: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (pasirinkimas == 5) break;

            if (pasirinkimas == 1 || pasirinkimas == 2) {
                Studentas studentas;
                cout << "Iveskite studento varda: ";
                cin >> studentas.vardas;
                cout << "Iveskite studento pavarde: ";
                cin >> studentas.pavarde;

                if (pasirinkimas == 1) {
                    int pazymys;
                    while (true) {
                        cout << "Iveskite pazymi (iveskite -1 norint baigti): ";
                        cin >> pazymys;
                        //tikrinam ar ivestas skaicius ir ar jis yra tarp -1 ir 10
                        if (cin.fail() || pazymys < -1 || pazymys > 10) {
                            cout << "Ivyko klaida: netinkama ivestis " << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                        if (pazymys == -1) break;

                        studentas.pazymiai.push_back(pazymys);
                    }
                } else {
                    while (true) {
                        try {
                            cout << "Iveskite pazymiu skaiciu: ";
                            cin >> pazymiuSk;
                            if (cin.fail() || pazymiuSk <= 0) {
                                throw invalid_argument("Neteisinga ivestis");
                            }
                            GeneruotiPazymius(pazymiuSk, studentas.pazymiai);
                            break;
                        } catch (const invalid_argument& e) {
                            cerr << "Ivyko klaida: " << e.what() << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                    }
                }

                while (true) {
                    try {
                        cout << "Iveskite studento egzamino pazymi: ";
                        cin >> studentas.egzaminas;
                        if (cin.fail() || studentas.egzaminas < 0 || studentas.egzaminas > 10) {
                            throw invalid_argument("Neteisinga ivestis");
                        }
                        studentai.push_back(studentas);
                        break;
                    } catch (const invalid_argument& e) {
                        cerr << "Ivyko klaida: " << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                }

            } else if (pasirinkimas == 3) {
                while (true) {
                    try {
                        cout << "Generuoti studentus i faila? (1 - taip, 0 - ne): ";
                        int iFaila;
                        cin >> iFaila;
                        if (cin.fail() || iFaila < 0 || iFaila > 1) {
                            throw invalid_argument("Neteisinga ivestis");
                        }
                        cout << "Iveskite studentu skaiciu: ";
                        int studentuSk;
                        cin >> studentuSk;
                        if (cin.fail() || studentuSk <= 0) {
                            throw invalid_argument("Neteisinga ivestis");
                        }

                        if (iFaila) {
                            cout << "Iveskite pazymiu skaiciu: ";
                            cin >> pazymiuSk;
                            if (cin.fail() || pazymiuSk <= 0) {
                                throw invalid_argument("Neteisinga ivestis");
                            }
                            FailuGeneravimas(studentuSk, pazymiuSk);
                        } else {
                            GeneruotiStudentus(studentuSk, studentai);
                        }
                        break;
                    } catch (const invalid_argument& e) {
                        cerr << "Ivyko klaida: " << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
            } else if (pasirinkimas == 4) {
                while (true) {
                    cout << "Failai: " << endl;
                    system("dir \b *.txt");
                    cout << endl;
                    cout << "Iveskite failo pavadinima: ";
                    cin >> failas;
                    ifstream in(failas);
                    if (!in.is_open()) {
                        cerr << "Nepavyko atidaryti failo" << endl;
                        continue;
                    }
                    in.close();
                    break;
                }

                auto startRead = high_resolution_clock::now(); // pradeda skaiciuoti laika
                NuskaitytiStudentusIsFailo(failas, studentai);
                auto endRead = high_resolution_clock::now();
                auto durationRead = duration_cast<seconds>(endRead - startRead);
                cout << "Failo nuskaitymas uztruko: " << durationRead.count() << " s" << endl;
            }
        }

        while (true) {
            cout << "Iveskite 1 jei norite skaiciuoti vidurki, 0 jei norite skaiciuoti mediana: ";
            cin >> vid;
            if (cin.fail() || vid < 0 || vid > 1) {
                cout << "Ivyko klaida: netinkama ivestis " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            break;
        }

        while (true) {
            cout << "Isvesti atsakymus i faila? (1 - taip, 0 - ne): ";
            cin >> iFaila;
            if (cin.fail() || iFaila < 0 || iFaila > 1) {
                cout << "Ivyko klaida: netinkama ivestis " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            break;
        }

        ofstream out;
        if (iFaila) {
            out.open("rezultatai.txt", ios::trunc | ios::out | ios::binary);
            if (!out) {
                cerr << "Nepavyko atidaryti failo rasymui" << endl;
                return 1;
            }
        }

        int rikiavimoPasirinkimas;
        while (true) {
            try {
                cout << "Pasirinkite rikiavimo buda:\n";
                cout << "0 - Nerikiuoti\n";
                cout << "1 - Pagal varda\n";
                cout << "2 - Pagal pavarde\n";
                cout << "3 - Pagal galutini pazymi didejancia tvarka\n";
                cout << "4 - Pagal galutini pazymi mazejancia tvarka\n";
                cin >> rikiavimoPasirinkimas;
                if (cin.fail() || rikiavimoPasirinkimas < 0 || rikiavimoPasirinkimas > 4) {
                    throw invalid_argument("Neteisinga ivestis");
                }
                break;
            } catch (const invalid_argument& e) {
                cerr << "Ivyko klaida: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
        }

        if (iFaila) {
            out << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;
        } else {
            cout << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;
        }

        bool suskirstyti;
        cout << "Suskirtyti studentus i dvi grupes, pagal pazymius?(1  - taip, 0 - ne) ";
        cin >> suskirstyti;

        // loopina per kiekviena studenta studentu vektoriuje ir skaiciuoja galutini pazymi 
        for (auto& studentas : studentai) {
            if (vid) {
                studentas.galutinis = 0.4 * Vidurkis(studentas.pazymiai) + 0.6 * studentas.egzaminas;
            } else {
                studentas.galutinis = 0.4 * Mediana(studentas.pazymiai) + 0.6 * studentas.egzaminas;
            }
        }

        RikiuotiStudentus(studentai, rikiavimoPasirinkimas);

        // irasoma dalimis, kad neuzimtu per daug atminties
        const size_t chunkSize = 100000; // daliu dydis
        size_t totalStudents = studentai.size();
        for (size_t i = 0; i < totalStudents; i += chunkSize) {
            size_t end = min(i + chunkSize, totalStudents);
            for (size_t j = i; j < end; ++j) {
                if (iFaila) {
                    out << left << setw(15) << studentai[j].vardas << setw(20) << studentai[j].pavarde << fixed << setprecision(2) << studentai[j].galutinis << endl;
                } else {
                    cout << left << setw(15) << studentai[j].vardas << setw(20) << studentai[j].pavarde << fixed << setprecision(2) << studentai[j].galutinis << endl;
                }
            }
        }

        if (iFaila) {
            out.close();
            if (suskirstyti) {
                StudentuAtskirimas(failas);
            }
            system("notepad rezultatai.txt");
        }
    // pagauna klaida
    } catch (const exception& e) {
        cerr << "Ivyko klaida: " << e.what() << endl;
    }
    return 0;
}