#pragma once
#include "mano_lib.h"
#include "funkcijos.h"
#include <string>
#include <vector>

class Studentas {
private:
    std::string vardas;
    std::string pavarde;
    std::vector<int> pazymiai;
    int egzaminas;

public:
    // Constructors
    Studentas() : vardas(""), pavarde(""), egzaminas(0) {}
    Studentas(const std::string& vardas, const std::string& pavarde, const std::vector<int>& pazymiai, int egzaminas)
        : vardas(vardas), pavarde(pavarde), pazymiai(pazymiai), egzaminas(egzaminas) {}

    // Getters
    std::string getVardas() const { return vardas; }
    std::string getPavarde() const { return pavarde; }
    std::vector<int> getPazymiai() const { return pazymiai; }
    int getEgzaminas() const { return egzaminas; }

    // Setters
    void setVardas(const std::string& vardas) { this->vardas = vardas; }
    void setPavarde(const std::string& pavarde) { this->pavarde = pavarde; }
    void setPazymiai(const std::vector<int>& pazymiai) { this->pazymiai = pazymiai; }
    void setEgzaminas(int egzaminas) { this->egzaminas = egzaminas; }

    // Utility methods
    double calculateGalutinis() const {
        double vidurkis = 0.0;
        if (!pazymiai.empty()) {
            for (int paz : pazymiai) {
                vidurkis += paz;
            }
            vidurkis /= pazymiai.size();
        }
        return 0.4 * vidurkis + 0.6 * egzaminas;
    }
};