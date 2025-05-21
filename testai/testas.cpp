#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../funkcijos.h"
#include "../mano_lib.h"

TEST_CASE("Galutinio pazymio skaiciavimas (vidurkis)", "[galutinis]") {
    
    Studentas s("A", "B", {10, 8, 9}, 9);
    s.setGalutinis(0.4f * Vidurkis(s.getPazymiai()) + 0.6f * s.getEgzaminas());
    REQUIRE(s.getGalutinis() == Approx(9)); // tikriname su vidurkiu
}

TEST_CASE("Galutinio pazymio skaiciavimas (mediana)", "[galutinis]") {
    
    Studentas s("A", "B", {10, 8, 9}, 9);
    s.setGalutinis(0.4f * Mediana(s.getPazymiai()) + 0.6f * s.getEgzaminas());
    REQUIRE(s.getGalutinis() == Approx(9)); // tikriname su mediana
}

TEST_CASE("Pazymiu generavimas", "[generavimas]") {
    vector<int> pazymiai;
    GeneruotiPazymius(3, pazymiai);
    REQUIRE(pazymiai.size() == 3); // tikriname ar sugeneruoti 3 pazymiai
    for (int pazymys : pazymiai) {
        REQUIRE(pazymys >= 1); // tikriname ar visi pazymiai yra teigiami
        REQUIRE(pazymys <= 10); // tikriname ar visi pazymiai yra ne didesni uz 10
    }
}

TEST_CASE("Studentu rikiavimas pagal varda", "[rikiavimas]") {
    vector<Studentas> studentai;
    studentai.push_back(Studentas("Jonas", "Jonaitis", {8, 9}, 9));
    studentai.push_back(Studentas("Petras", "Petraitis", {7, 8}, 8));
    studentai.push_back(Studentas("Antanas", "Antanaitis", {10, 9}, 10));

    RikiuotiStudentus(studentai, 1); // rikiuojame pagal varda

    REQUIRE(studentai[0].getVardas() == "Antanas");
    REQUIRE(studentai[1].getVardas() == "Jonas");
    REQUIRE(studentai[2].getVardas() == "Petras");
}

TEST_CASE("Studentu rikiavimas pagal pavarde", "[rikiavimas]") {
    vector<Studentas> studentai;
    studentai.push_back(Studentas("Jonas", "Jonaitis", {8, 9}, 9));
    studentai.push_back(Studentas("Petras", "Petraitis", {7, 8}, 8));
    studentai.push_back(Studentas("Antanas", "Antanaitis", {10, 9}, 10));

    RikiuotiStudentus(studentai, 2); // rikiuojame pagal pavarde

    REQUIRE(studentai[0].getPavarde() == "Antanaitis");
    REQUIRE(studentai[1].getPavarde() == "Jonaitis");
    REQUIRE(studentai[2].getPavarde() == "Petraitis");
}
