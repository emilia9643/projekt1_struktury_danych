#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <iomanip>
#include <fstream>
#include "dynamic_array.h"
#include "linked_list.h"
#include "doubly_linked_list.h"

using namespace std;
using namespace std::chrono;

void runtest(){
    vector<int> sizes = {5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000}; 
    vector<int> seeds = {111, 222, 333, 444, 555, 666, 777, 888, 999, 1010}; // 10 unikalnych ziaren
    const int NUM_COPIES = 100; // Liczba powtórzeń dla pojedynczego pomiaru. tworze 100 takich samych kopii struktury bo pojedyńcza operacja trwa za krótko

    cout << "Rozpoczynam badania struktur danych...\n";

    for (int size : sizes) {
        cout << "\n========================================================================\n";
        cout << "               ROZMIAR STRUKTURY: " << size << "\n";
        cout << "========================================================================\n";

        // Tablice do sumowania czasów z 10 seedów, 0-dynamiczna, 1-1k, 2-2k. Przechowują łączny czas operacji z 10 seedów.
        long long t_search[3] = {0}, t_add_front[3] = {0}, t_rem_front[3] = {0};
        long long t_add_back[3] = {0}, t_rem_back[3] = {0}, t_add_rand[3] = {0}, t_rem_rand[3] = {0};

        // Wykonanie pomiarów dla każdego ziarna
        for (int seed : seeds) {
            srand(seed); 
            vector<int> randomNums;
            for(int i = 0; i < size; i++) {
                // losowanie wartości od -100000 do 100000
                randomNums.push_back((rand() % 200001) - 100000);
            }

            vector<DynamicArray> arr_copies(NUM_COPIES);
            vector<LinkedList> list1K_copies(NUM_COPIES);
            vector<DoublyLinkedList> list2K_copies(NUM_COPIES);
            
            // do każdej ze 100 kopii dodajemy liczby losowo
            for(int i = 0; i < NUM_COPIES; i++) {
                for(int num : randomNums) {
                    arr_copies[i].add_back(num);   
                    list1K_copies[i].addAtEnd(num);  
                    list2K_copies[i].addAtEnd(num);
                }
            }

            auto start = high_resolution_clock::now();
            auto end = high_resolution_clock::now();


            //SZUKANIE
            int val_to_find = (rand() % 200001) - 100000;
            // zaczynamy timer->na 100 tablicach wyszukujemy jeden element->
            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) arr_copies[i].search(val_to_find);
            end = high_resolution_clock::now();
            t_search[0] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;
            //konwertujemy czas na liczbę całkowitą reprezentującą nanosekundę
            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) list1K_copies[i].isInList(val_to_find);
            end = high_resolution_clock::now();
            t_search[1] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;

            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) list2K_copies[i].isInList(val_to_find);
            end = high_resolution_clock::now();
            t_search[2] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;

            // DODAWANIE NA POCZĄTEK- składnia jak wcześniej, 
            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) arr_copies[i].add_front(999);
            end = high_resolution_clock::now();
            t_add_front[0] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;

            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) list1K_copies[i].addToFront(999);
            end = high_resolution_clock::now();
            t_add_front[1] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;

            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) list2K_copies[i].addToFront(999);
            end = high_resolution_clock::now();
            t_add_front[2] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;

            //USUWANIE Z POCZATKU
            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) arr_copies[i].remove_front();
            end = high_resolution_clock::now();
            t_rem_front[0] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;

            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) list1K_copies[i].removeFromBegining();
            end = high_resolution_clock::now();
            t_rem_front[1] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;

            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) list2K_copies[i].removeFromBegining();
            end = high_resolution_clock::now();
            t_rem_front[2] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;

            //dodawanie na koniec
            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) arr_copies[i].add_back(999);
            end = high_resolution_clock::now();
            t_add_back[0] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;

            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) list1K_copies[i].addAtEnd(999);
            end = high_resolution_clock::now();
            t_add_back[1] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;

            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) list2K_copies[i].addAtEnd(999);
            end = high_resolution_clock::now();
            t_add_back[2] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;

            //usuwanie z konca
            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) arr_copies[i].remove_back();
            end = high_resolution_clock::now();
            t_rem_back[0] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;

            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) list1K_copies[i].removeFromEnd();
            end = high_resolution_clock::now();
            t_rem_back[1] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;

            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) list2K_copies[i].removeFromEnd();
            end = high_resolution_clock::now();
            t_rem_back[2] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;


            //dodawanie w losowe miejsce r_idx
            size_t r_idx = rand() % size;
            
            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) arr_copies[i].add_at(r_idx, 999);
            end = high_resolution_clock::now();
            t_add_rand[0] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;

            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) list1K_copies[i].addAtIndex(r_idx, 999);
            end = high_resolution_clock::now();
            t_add_rand[1] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;

            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) list2K_copies[i].addAtIndex(r_idx, 999);
            end = high_resolution_clock::now();
            t_add_rand[2] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;

            //usuwanie z losowego miejsca r_idx
            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) arr_copies[i].remove_at(r_idx);
            end = high_resolution_clock::now();
            t_rem_rand[0] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;

            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) list1K_copies[i].removeAtIndex(r_idx);
            end = high_resolution_clock::now();
            t_rem_rand[1] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;

            start = high_resolution_clock::now();
            for(int i = 0; i < NUM_COPIES; i++) list2K_copies[i].removeAtIndex(r_idx);
            end = high_resolution_clock::now();
            t_rem_rand[2] += duration_cast<nanoseconds>(end - start).count() / NUM_COPIES;
        }

        //dzielimy zsumowany czas przez ilosc seedow
        int S = seeds.size();
        
        cout << "--- Wyszukiwanie ---\n";
        cout << "Tablica:  " << setw(8) << t_search[0] / S << " ns | Lista 1K: " << setw(8) << t_search[1] / S << " ns | Lista 2K: " << setw(8) << t_search[2] / S << " ns\n\n";

        cout << "--- Dodawanie na poczatek ---\n";
        cout << "Tablica:  " << setw(8) << t_add_front[0] / S << " ns | Lista 1K: " << setw(8) << t_add_front[1] / S << " ns | Lista 2K: " << setw(8) << t_add_front[2] / S << " ns\n\n";

        cout << "--- Usuwanie z poczatku ---\n";
        cout << "Tablica:  " << setw(8) << t_rem_front[0] / S << " ns | Lista 1K: " << setw(8) << t_rem_front[1] / S << " ns | Lista 2K: " << setw(8) << t_rem_front[2] / S << " ns\n\n";

        cout << "--- Dodawanie na koniec ---\n";
        cout << "Tablica:  " << setw(8) << t_add_back[0] / S << " ns | Lista 1K: " << setw(8) << t_add_back[1] / S << " ns | Lista 2K: " << setw(8) << t_add_back[2] / S << " ns\n\n";

        cout << "--- Usuwanie z konca ---\n";
        cout << "Tablica:  " << setw(8) << t_rem_back[0] / S << " ns | Lista 1K: " << setw(8) << t_rem_back[1] / S << " ns | Lista 2K: " << setw(8) << t_rem_back[2] / S << " ns\n\n";

        cout << "--- Dodawanie w losowe miejsce ---\n";
        cout << "Tablica:  " << setw(8) << t_add_rand[0] / S << " ns | Lista 1K: " << setw(8) << t_add_rand[1] / S << " ns | Lista 2K: " << setw(8) << t_add_rand[2] / S << " ns\n\n";

        cout << "--- Usuwanie z losowego miejsca ---\n";
        cout << "Tablica:  " << setw(8) << t_rem_rand[0] / S << " ns | Lista 1K: " << setw(8) << t_rem_rand[1] / S << " ns | Lista 2K: " << setw(8) << t_rem_rand[2] / S << " ns\n";
    }
}

int main() {
    DynamicArray arr;
    LinkedList list1K;
    DoublyLinkedList list2K;

    int glownyWybor = -1;

    // GŁÓWNA PĘTLA - MENU POZIOM 1
    while (glownyWybor != 0) {
        cout << "\n-------------------------------------\n";
        cout << "               MENU GLOWNE               \n";
        cout << "-------------------------------------\n";
        cout << "Wybierz strukture do testowania:\n";
        cout << "1. Tablica Dynamiczna\n";
        cout << "2. Lista Jednokierunkowa\n";
        cout << "3. Lista Dwukierunkowa\n";
        cout << "4. Uruchom testy\n";
        cout << "0. Wyjscie z programu\n";
        cout << "Twoj wybor: ";
        cin >> glownyWybor;

        if (glownyWybor == 0) {
            cout << "Zamykanie programu...\n";
            break;
        } else if (glownyWybor == 4) {
            runtest();
            continue;
        } else if (glownyWybor < 1 || glownyWybor > 3) {
            cout << "Niepoprawny wybor! Sprobuj ponownie.\n";
            continue;
        }

        int opcja = -1;

        // MENU POZIOM 2
        while (opcja != 0) {
            cout << "\n--- MENU STRUKTURY (Typ: " << glownyWybor << ") ---\n";
            cout << "1. Zbuduj z pliku\n";
            cout << "2. Usun element(index)\n";
            cout << "3. Dodaj element(koniec)\n";
            cout << "4. Znajdz element(wartosc)\n";
            cout << "5. Utworz losowo\n";
            cout << "6. Wyswietl strukture\n";
            cout << "7. Dodaj element index\n";
            cout << "0. Powrot do Menu Glownego\n";
            cout << "Twoja opcja: ";
            cin >> opcja;

            int wartosc, indeks, wielkosc;
            string nazwaPliku;
            ifstream plik;

            switch (opcja) {
                case 0:
                    break;

                case 1:
                    cout << "Podaj nazwe pliku (np. dane.txt): ";
                    cin >> nazwaPliku;
                    
                    // Czyszczenie przed wczytaniem nowych danych
                    if (glownyWybor == 1) arr.clear();
                    else if (glownyWybor == 2) list1K.clear();
                    else if (glownyWybor == 3) list2K.clear();
                    
                    plik.open(nazwaPliku);
                    if (plik.is_open()) {
                        while (plik >> wartosc) {
                            if (glownyWybor == 1) arr.add_back(wartosc);
                            else if (glownyWybor == 2) list1K.addAtEnd(wartosc);
                            else if (glownyWybor == 3) list2K.addAtEnd(wartosc);
                        }
                        plik.close();
                        cout << "Wczytano dane z pliku.\n";
                    } else {
                        cout << "Nie udalo sie otworzyc pliku!\n";
                    }
                    break;

                case 2:
                    cout << "Podaj INDEKS elementu do usuniecia: ";
                    cin >> indeks;
                    
                    try {
                        if (glownyWybor == 1) { 
                            arr.remove_at(indeks); 
                            cout << "Usunieto element z indeksu " << indeks << " w tablicy.\n"; 
                        }
                        else if (glownyWybor == 2) { 
                            list1K.removeAtIndex(indeks); 
                            cout << "Usunieto element z indeksu " << indeks << " w liscie 1K.\n"; 
                        }
                        else if (glownyWybor == 3) { 
                            list2K.removeAtIndex(indeks); 
                            cout << "Usunieto element z indeksu " << indeks << " w liscie 2K.\n"; 
                        }
                    } catch (const std::out_of_range& e) {
                        cout << "Blad: " << e.what() << "\n";
                    }
                    break;

                case 3:
                    cout << "Podaj wartosc do dodania na koniec: ";
                    cin >> wartosc;
                    if (glownyWybor == 1) { arr.add_back(wartosc); cout << "Dodano do tablicy.\n"; }
                    else if (glownyWybor == 2) { list1K.addAtEnd(wartosc); cout << "Dodano do listy 1K.\n"; }
                    else if (glownyWybor == 3) { list2K.addAtEnd(wartosc); cout << "Dodano do listy 2K.\n"; }
                    break;

                case 4:
                    cout << "Podaj wartosc do znalezienia: ";
                    cin >> wartosc;
                    bool znaleziono;
                    znaleziono = false; // Inicjalizacja zabezpieczająca
                    
                    if (glownyWybor == 1) znaleziono = arr.search(wartosc);
                    else if (glownyWybor == 2) znaleziono = list1K.isInList(wartosc);
                    else if (glownyWybor == 3) znaleziono = list2K.isInList(wartosc);
                    
                    if (znaleziono) cout << "Element znajduje sie w strukturze.\n";
                    else cout << "Brak elementu w strukturze.\n";
                    break;

                case 5:
                    cout << "Podaj wielkosc struktury do wygenerowania: ";
                    cin >> wielkosc;
                    
                    // Czyszczenie struktury przed wylosowaniem nowych wartości
                    if (glownyWybor == 1) arr.clear();
                    else if (glownyWybor == 2) list1K.clear();
                    else if (glownyWybor == 3) list2K.clear();

                    for (int i = 0; i < wielkosc; i++) {
                        wartosc = (rand() % 200001) - 100000;
                        if (glownyWybor == 1) arr.add_back(wartosc);
                        else if (glownyWybor == 2) list1K.addAtEnd(wartosc);
                        else if (glownyWybor == 3) list2K.addAtEnd(wartosc);
                    }
                    cout << "Wygenerowano losowo " << wielkosc << " elementow.\n";
                    break;

                case 6:
                    cout << "Zawartosc struktury:\n";
                    if (glownyWybor == 1) { 
                        for(size_t i = 0; i < arr.getSize(); i++) {
                            cout << arr.getElement(i) << " ";
                        }
                        cout << "\n";
                    }
                    else if (glownyWybor == 2) { list1K.display(); }
                    else if (glownyWybor == 3) { list2K.display(); }
                    break;
                case 7: // Dodaj pod wskazany indeks
                    cout << "Podaj indeks: ";
                    cin >> indeks;
                    cout << "Podaj wartosc do dodania: ";
                    cin >> wartosc;
                    
                    try {
                        if (glownyWybor == 1) { 
                            arr.add_at(indeks, wartosc); 
                            cout << "Dodano do tablicy pod indeks " << indeks << ".\n"; 
                        }
                        else if (glownyWybor == 2) { 
                            list1K.addAtIndex(indeks, wartosc); 
                            cout << "Dodano do listy 1K pod indeks " << indeks << ".\n"; 
                        }
                        else if (glownyWybor == 3) { 
                            list2K.addAtIndex(indeks, wartosc); 
                            cout << "Dodano do listy 2K pod indeks " << indeks << ".\n"; 
                        }
                    } catch (const std::out_of_range& e) {
                        cout << "Blad dodawania: " << e.what() << "\n";
                    }
                    break;
                default:
                    cout << "zła opcja.\n";
                    break;
            }
        }
    }

    return 0;
}