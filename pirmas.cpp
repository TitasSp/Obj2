#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

struct Studentas {
    string vardas = "titas";
    string pavarde = "spegis";
    vector<int> pazymiai = {10, 9, 8, 7, 6};
    int egzaminas = 8;
    float galutinis;
};

int main() {
    Studentas studentas;

    float suma = 0;
    for (int i = 0; i < 5; i++) {
        suma += studentas.pazymiai[i];
    }
    float vidurkis = suma / 5;
    studentas.galutinis = 0.4 * vidurkis + 0.6 * studentas.egzaminas;
    cout << studentas.vardas << " " << studentas.pavarde << " " << studentas.galutinis << endl;

    return 0;
}
