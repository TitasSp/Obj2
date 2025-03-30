# ObjPirmaUzduotis

Projekto naudojimo instrukcija:
Atidarykite projekto aplankala ir paleiskite program.exe

Arba 

1) Atidarykite terminala projekto direktorijoje (cd C:\"projekto direktorija")
2) Sukurkite build direktorija 
(mkdir build

cd build)
3) Paleiskite CMake, norint sugeneruoti build failus (cmake ..)
4) Kompiliuokite projekta (cmake --build .)
5) Paleiskite faila (.\ObjCppProject.exe)
---------------------------------------------------------------------------------------------
Testavimo sistemos parametrai:
Processor	12th Gen Intel(R) Core(TM) i5-1235U, 1300 Mhz, 10 Core(s), 12 Logical Processor(s)

Installed Physical Memory (RAM)	16.0 GB

SSD	512 GB NVMe Micron_2400_MTFDKBA512QFM
---------------------------------------------------------------------------------------------
Testų rezultatų apibendrinimas:
Testai buvo atlikti naudojant skirtingus konteinerius (deque, list, vector) ir skirtingus studentų failų dydžius (nuo 1000 iki 10 000 000 įrašų). Rezultatai parodo kiekvieno konteinerio našumą atliekant šias operacijas: nuskaitymą, rikiavimą, suskirstymą ir įrašymą į failus.

Maži failai (iki 100 000 įrašų): Visi konteineriai veikia efektyviai, tačiau list ir vector turi nedidelį pranašumą dėl greitesnio nuskaitymo ir rikiavimo.
Vidutiniai failai (iki 1 000 000 įrašų): deque ir vector yra panašūs našumo atžvilgiu, tačiau list išlieka konkurencingas dėl greito rikiavimo.
Dideli failai (10 000 000 įrašų): list yra efektyviausias pasirinkimas, nes apdorojimo laikas yra trumpesnis nei deque ar vector.
---------------------------------------------------------------------------------------------
Testai:
deque:
Test 1
studentai1000.txt
Studentu nuskaitymas is failo uztruko: 42 ms
Studentu rikiavimas uztruko: 2 ms
Studentu suskirstymas uztruko: 11 ms
Studentu irasymas i failus uztruko: 1 ms
Is viso uztruko: 100 ms

studentai10000.txt
Studentu nuskaitymas is failo uztruko: 382 ms
Studentu rikiavimas uztruko: 19 ms
Studentu suskirstymas uztruko: 111 ms
Studentu irasymas i failus uztruko: 22 ms
Is viso uztruko: 763 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 3372 ms
Studentu rikiavimas uztruko: 172 ms
Studentu suskirstymas uztruko: 833 ms
Studentu irasymas i failus uztruko: 34 ms
Is viso uztruko: 5735 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 25666 ms
Studentu rikiavimas uztruko: 1806 ms
Studentu suskirstymas uztruko: 9933 ms
Studentu irasymas i failus uztruko: 325 ms
Is viso uztruko: 53138 ms

studentai10000000.txt
Studentu nuskaitymas is failo uztruko: 354322 ms
Studentu rikiavimas uztruko: 20018 ms
Studentu suskirstymas uztruko: 68148 ms
Studentu irasymas i failus uztruko: 1092 ms
Is viso uztruko: 581463 ms

Test 2
studentai1000.txt
Studentu nuskaitymas is failo uztruko: 32 ms
Studentu rikiavimas uztruko: 1 ms
Studentu suskirstymas uztruko: 8 ms
Studentu irasymas i failus uztruko: 1 ms
Is viso uztruko: 161 ms

studentai10000.txt
Studentu nuskaitymas is failo uztruko: 327 ms
Studentu rikiavimas uztruko: 18 ms
Studentu suskirstymas uztruko: 73 ms
Studentu irasymas i failus uztruko: 4 ms
Is viso uztruko: 652 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 3406 ms
Studentu rikiavimas uztruko: 180 ms
Studentu suskirstymas uztruko: 881 ms
Studentu irasymas i failus uztruko: 24 ms
Is viso uztruko: 5757 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 18839 ms
Studentu rikiavimas uztruko: 1004 ms
Studentu suskirstymas uztruko: 4399 ms
Studentu irasymas i failus uztruko: 218 ms
Is viso uztruko: 32099 ms

studentai10000000.txt
Studentu nuskaitymas is failo uztruko: 345754 ms
Studentu rikiavimas uztruko: 20087 ms
Studentu suskirstymas uztruko: 65062 ms
Studentu irasymas i failus uztruko: 1668 ms
Is viso uztruko: 570368 ms

Test 3
studentai1000.txt
Studentu nuskaitymas is failo uztruko: 23 ms
Studentu rikiavimas uztruko: 1 ms
Studentu suskirstymas uztruko: 5 ms
Studentu irasymas i failus uztruko: 1 ms
Is viso uztruko: 139 ms

studentai10000.txt
Studentu nuskaitymas is failo uztruko: 214 ms
Studentu rikiavimas uztruko: 9 ms
Studentu suskirstymas uztruko: 43 ms
Studentu irasymas i failus uztruko: 2 ms
Is viso uztruko: 362 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 1785 ms
Studentu rikiavimas uztruko: 100 ms
Studentu suskirstymas uztruko: 413 ms
Studentu irasymas i failus uztruko: 13 ms
Is viso uztruko: 3120 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 10759 ms
Studentu rikiavimas uztruko: 579 ms
Studentu suskirstymas uztruko: 2440 ms
Studentu irasymas i failus uztruko: 92 ms
Is viso uztruko: 18378 ms

studentai10000000.txt
Studentu nuskaitymas is failo uztruko: 325531 ms
Studentu rikiavimas uztruko: 18626 ms
Studentu suskirstymas uztruko: 35234 ms
Studentu irasymas i failus uztruko: 862 ms
Is viso uztruko: 464580 ms

List:
studentai1000.txt
Studentu nuskaitymas is failo uztruko: 21 ms
Studentu rikiavimas uztruko: 0 ms
Studentu suskirstymas uztruko: 6 ms
Studentu irasymas i failus uztruko: 1 ms
Is viso uztruko: 52 ms

studentai10000.txt
Studentu nuskaitymas is failo uztruko: 194 ms
Studentu rikiavimas uztruko: 1 ms
Studentu suskirstymas uztruko: 41 ms
Studentu irasymas i failus uztruko: 2 ms
Is viso uztruko: 331 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 1869 ms
Studentu rikiavimas uztruko: 19 ms
Studentu suskirstymas uztruko: 427 ms
Studentu irasymas i failus uztruko: 15 ms
Is viso uztruko: 3135 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 11225 ms
Studentu rikiavimas uztruko: 218 ms
Studentu suskirstymas uztruko: 2560 ms
Studentu irasymas i failus uztruko: 90 ms
Is viso uztruko: 18625 ms

studentai10000000.txt
Studentu nuskaitymas is failo uztruko: 185826 ms
Studentu rikiavimas uztruko: 6983 ms
Studentu suskirstymas uztruko: 38115 ms
Studentu irasymas i failus uztruko: 894 ms
Is viso uztruko: 305952 ms

studentai1000.txt
Studentu nuskaitymas is failo uztruko: 20 ms
Studentu rikiavimas uztruko: 0 ms
Studentu suskirstymas uztruko: 4 ms
Studentu irasymas i failus uztruko: 1 ms
Is viso uztruko: 115 ms

studentai10000.txt
Studentu nuskaitymas is failo uztruko: 198 ms
Studentu rikiavimas uztruko: 0 ms
Studentu suskirstymas uztruko: 44 ms
Studentu irasymas i failus uztruko: 1 ms
Is viso uztruko: 338 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 1855 ms
Studentu rikiavimas uztruko: 18 ms
Studentu suskirstymas uztruko: 450 ms
Studentu irasymas i failus uztruko: 25 ms
Is viso uztruko: 3102 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 11417 ms
Studentu rikiavimas uztruko: 222 ms
Studentu suskirstymas uztruko: 2519 ms
Studentu irasymas i failus uztruko: 92 ms
Is viso uztruko: 18732 ms

studentai10000000.txt
Studentu nuskaitymas is failo uztruko: 273554 ms
Studentu rikiavimas uztruko: 7129 ms
Studentu suskirstymas uztruko: 38076 ms
Studentu irasymas i failus uztruko: 803 ms
Is viso uztruko: 393938 ms

studentai1000.txt
Studentu nuskaitymas is failo uztruko: 21 ms
Studentu rikiavimas uztruko: 0 ms
Studentu suskirstymas uztruko: 4 ms
Studentu irasymas i failus uztruko: 1 ms
Is viso uztruko: 124 ms

studentai10000.txt
Studentu nuskaitymas is failo uztruko: 202 ms
Studentu rikiavimas uztruko: 1 ms
Studentu suskirstymas uztruko: 42 ms
Studentu irasymas i failus uztruko: 2 ms
Is viso uztruko: 337 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 1859 ms
Studentu rikiavimas uztruko: 17 ms
Studentu suskirstymas uztruko: 466 ms
Studentu irasymas i failus uztruko: 14 ms
Is viso uztruko: 3107 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 11351 ms
Studentu rikiavimas uztruko: 201 ms
Studentu suskirstymas uztruko: 2521 ms
Studentu irasymas i failus uztruko: 94 ms
Is viso uztruko: 18627 ms

studentai10000000.txt
Studentu nuskaitymas is failo uztruko: 188116 ms
Studentu rikiavimas uztruko: 7034 ms
Studentu suskirstymas uztruko: 37654 ms
Studentu irasymas i failus uztruko: 780 ms
Is viso uztruko: 307527 ms

vectors:

studentai1000.txt
Studentu nuskaitymas is failo uztruko: 32 ms
Studentu rikiavimas uztruko: 1 ms
Studentu suskirstymas uztruko: 8 ms
Studentu irasymas i failus uztruko: 1 ms
Is viso uztruko: 152 ms

studentai10000.txt
Studentu nuskaitymas is failo uztruko: 197 ms
Studentu rikiavimas uztruko: 7 ms
Studentu suskirstymas uztruko: 43 ms
Studentu irasymas i failus uztruko: 1 ms
Is viso uztruko: 341 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 1838 ms
Studentu rikiavimas uztruko: 80 ms
Studentu suskirstymas uztruko: 446 ms
Studentu irasymas i failus uztruko: 14 ms
Is viso uztruko: 3191 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 11005 ms
Studentu rikiavimas uztruko: 445 ms
Studentu suskirstymas uztruko: 2539 ms
Studentu irasymas i failus uztruko: 102 ms
Is viso uztruko: 18518 ms

studentai10000000.txt
Studentu nuskaitymas is failo uztruko: 185815 ms
Studentu rikiavimas uztruko: 8487 ms
Studentu suskirstymas uztruko: 203151 ms
Studentu irasymas i failus uztruko: 865 ms
Is viso uztruko: 471429 ms

studentai1000.txt
Studentu nuskaitymas is failo uztruko: 27 ms
Studentu rikiavimas uztruko: 1 ms
Studentu suskirstymas uztruko: 4 ms
Studentu irasymas i failus uztruko: 1 ms
Is viso uztruko: 124 ms

studentai10000.txt
Studentu nuskaitymas is failo uztruko: 194 ms
Studentu rikiavimas uztruko: 8 ms
Studentu suskirstymas uztruko: 41 ms
Studentu irasymas i failus uztruko: 2 ms
Is viso uztruko: 336 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 1820 ms
Studentu rikiavimas uztruko: 77 ms
Studentu suskirstymas uztruko: 428 ms
Studentu irasymas i failus uztruko: 13 ms
Is viso uztruko: 3069 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 11084 ms
Studentu rikiavimas uztruko: 442 ms
Studentu suskirstymas uztruko: 2515 ms
Studentu irasymas i failus uztruko: 83 ms
Is viso uztruko: 18446 ms

studentai10000000.txt
Studentu nuskaitymas is failo uztruko: 184478 ms
Studentu rikiavimas uztruko: 9001 ms
Studentu suskirstymas uztruko: 38999 ms
Studentu irasymas i failus uztruko: 851 ms
Is viso uztruko: 305534 ms

studentai1000.txt
Studentu nuskaitymas is failo uztruko: 22 ms
Studentu rikiavimas uztruko: 1 ms
Studentu suskirstymas uztruko: 7 ms
Studentu irasymas i failus uztruko: 1 ms
Is viso uztruko: 121 ms

studentai10000.txt
Studentu nuskaitymas is failo uztruko: 202 ms
Studentu rikiavimas uztruko: 8 ms
Studentu suskirstymas uztruko: 48 ms
Studentu irasymas i failus uztruko: 2 ms
Is viso uztruko: 351 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 1877 ms
Studentu rikiavimas uztruko: 80 ms
Studentu suskirstymas uztruko: 433 ms
Studentu irasymas i failus uztruko: 14 ms
Is viso uztruko: 3156 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 11423 ms
Studentu rikiavimas uztruko: 453 ms
Studentu suskirstymas uztruko: 2791 ms
Studentu irasymas i failus uztruko: 96 ms
Is viso uztruko: 19411 ms

studentai10000000.txt
Studentu nuskaitymas is failo uztruko: 186095 ms
Studentu rikiavimas uztruko: 8599 ms
Studentu suskirstymas uztruko: 39956 ms
Studentu irasymas i failus uztruko: 867 ms
Is viso uztruko: 308230 ms


//////////////////////
vector konteinerio testas naudojant pertition skaidant studentus i dvi grupes:
studentai1000.txt
Studentu nuskaitymas is failo uztruko: 37 ms
Studentu rikiavimas uztruko: 1 ms
Studentu skaidymas ir irasymas i failus uztruko: 24 ms
Is viso uztruko: 82 ms

studentai10000.txt
Studentu nuskaitymas is failo uztruko: 345 ms
Studentu rikiavimas uztruko: 15 ms
Studentu skaidymas ir irasymas i failus uztruko: 135 ms
Is viso uztruko: 633 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 3392 ms
Studentu rikiavimas uztruko: 159 ms
Studentu skaidymas ir irasymas i failus uztruko: 1433 ms
Is viso uztruko: 6611 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 19578 ms
Studentu rikiavimas uztruko: 783 ms
Studentu skaidymas ir irasymas i failus uztruko: 8246 ms
Is viso uztruko: 36521 ms

studentai10000000.txt
Studentu nuskaitymas is failo uztruko: 347105 ms
Studentu rikiavimas uztruko: 15300 ms
Studentu skaidymas ir irasymas i failus uztruko: 152613 ms
Is viso uztruko: 650938 ms

studentai1000.txt
Studentu nuskaitymas is failo uztruko: 52 ms
Studentu rikiavimas uztruko: 2 ms
Studentu skaidymas ir irasymas i failus uztruko: 166 ms
Is viso uztruko: 347 ms

studentai10000.txt
Studentu nuskaitymas is failo uztruko: 442 ms
Studentu rikiavimas uztruko: 13 ms
Studentu skaidymas ir irasymas i failus uztruko: 147 ms
Is viso uztruko: 747 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 3958 ms
Studentu rikiavimas uztruko: 194 ms
Studentu skaidymas ir irasymas i failus uztruko: 1645 ms
Is viso uztruko: 7404 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 20860 ms
Studentu rikiavimas uztruko: 768 ms
Studentu skaidymas ir irasymas i failus uztruko: 8065 ms
Is viso uztruko: 37336 ms

studentai10000000.txt
Studentu nuskaitymas is failo uztruko: 351012 ms
Studentu rikiavimas uztruko: 15665 ms
Studentu skaidymas ir irasymas i failus uztruko: 147176 ms
Is viso uztruko: 653552 ms

studentai1000.txt
Studentu nuskaitymas is failo uztruko: 38 ms
Studentu rikiavimas uztruko: 1 ms
Studentu skaidymas ir irasymas i failus uztruko: 108 ms
Is viso uztruko: 254 ms

studentai10000.txt
Studentu nuskaitymas is failo uztruko: 339 ms
Studentu rikiavimas uztruko: 14 ms
Studentu skaidymas ir irasymas i failus uztruko: 142 ms
Is viso uztruko: 636 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 3283 ms
Studentu rikiavimas uztruko: 133 ms
Studentu skaidymas ir irasymas i failus uztruko: 1328 ms
Is viso uztruko: 6050 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 20787 ms
Studentu rikiavimas uztruko: 938 ms
Studentu skaidymas ir irasymas i failus uztruko: 8911 ms
Is viso uztruko: 38931 ms

studentai10000000.txt
Studentu nuskaitymas is failo uztruko: 352201 ms
Studentu rikiavimas uztruko: 16260 ms
Studentu skaidymas ir irasymas i failus uztruko: 212642 ms
Is viso uztruko: 720394 ms
