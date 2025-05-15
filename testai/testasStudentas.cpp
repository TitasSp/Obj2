#include "catch.hpp"
#include "../funkcijos.h"

// Pagal 5 taisyklių patikrinimą: kopijavimas, perkėlimas, destruktorius

TEST_CASE("Student - Copy constructor creates identical object", "[5-rule]") {
    Studentas original("Jonas", "Jonaitis", {8, 9}, 9);
    Studentas copy = original;

    REQUIRE(copy.getVardas() == "Jonas");
    REQUIRE(copy.getPavarde() == "Jonaitis");
    REQUIRE(copy.getEgzaminas() == 9);
    REQUIRE(copy.getPazymiai().size() == 2);
    REQUIRE(copy.getPazymiai()[0] == 8);
}

TEST_CASE("Student - Copy assignment operator", "[5-rule]") {
    Studentas a("Jonas", "Jonaitis", {5, 6}, 8);
    Studentas b;
    b = a;

    REQUIRE(b.getVardas() == a.getVardas());
    REQUIRE(b.getEgzaminas() == a.getEgzaminas());
}

TEST_CASE("Student - Move constructor", "[5-rule]") {
    Studentas temp("Tomas", "Tomaitis", {10}, 10);
    Studentas moved = std::move(temp);

    REQUIRE(moved.getVardas() == "Tomas");
    REQUIRE(moved.getEgzaminas() == 10);
}

TEST_CASE("Student - Move assignment operator", "[5-rule]") {
    Studentas a("Ona", "Onaitytė", {7, 7}, 8);
    Studentas b;
    b = std::move(a);

    REQUIRE(b.getPavarde() == "Onaitytė");
    REQUIRE(b.getPazymiai().size() == 2);
}

TEST_CASE("Student - Destructor doesn't leak", "[5-rule]") {
    Studentas* ptr = new Studentas("A", "B", {1, 2}, 3);
    delete ptr;

    SUCCEED("Destructor ran without crash");
}
