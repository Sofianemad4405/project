#include <iostream>
#include "surah.cpp"
#include "doublyLinkedList.cpp"
#include <windows.h>
#include <mmsystem.h>


using namespace std;

class playList {
private:
    string sheikhName;
    DoublyLinkedList<Surah> Suras;

    struct Node {
        Surah data;
        Node *next;
        Node *prev;

        Node() : next(nullptr), prev(nullptr) {}
    };

    Node *head;
    Node *tail;
    int surahsCount = 0;

public:
    playList() : sheikhName(""), Suras() {}

    playList(string name) : sheikhName(name), Suras() {}

    void addNewSurah(Surah s) {
        Suras.addLast(s);
        surahsCount++;
    }


    void removeSurah(int index) {
        try {
            Suras.removeAt(index);
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
        }
        surahsCount--;
    }

    Surah getSurahAt(int index) const {
        if (index < 0 || index >= surahsCount) {
            cout << "Error: Invalid index." << endl;
            return Surah();
        }

        Node *current = head;
        int currentIndex = 0;

        while (current != nullptr && currentIndex < index) {
            current = current->next;
            currentIndex++;
        }
        if (current != nullptr) {
            return current->data;
        }
        cout << "Error: Something went wrong." << endl;
        return Surah();
    }


    Surah searchSurah(string &surahName) {
        int index = Suras.search(surahName);
        if (index != -1) {
            return Suras.getAt(index);
        }
        throw runtime_error("Surah not found");
    }

    int searchSura(string surahName) {
        Node *temp = head;
        int ctr = 0;
        while (temp) {
            if (temp->data.getSurahName() == surahName) {
                return ctr;
            }
            ctr++;
            temp = temp->next;
        }
        return -1;
    }

    void setSheikhName(string name) {
        sheikhName = name;
    }

    string getSheikhName() const {
        return sheikhName;
    }


    void displaySurahs() {
        cout << "======================================" << endl;
        cout << " Playlist: " << sheikhName << endl;
        cout << "======================================" << endl;

        if (Suras.isEmpty()) {
            cout << "No Surahs in this playlist." << endl;
            cout << "======================================" << endl;
            return;
        }
        cout<< "ID"<<"          "<<"Surah name"<<"          "<<"Surah type"<<"          "<<"Surah path\n";
        for (int i = 0; i < Suras.getSize(); ++i) {
            Surah s = Suras.getAt(i);
            cout << i + 1 << ".         " << s.getSurahName() << "           (" << s.getSurahType() << ")" <<"          \n";
        }
        cout << "======================================" << endl << endl;
    }
    int getSurahsCount() const{
        return surahsCount;
    }


    void start() {
       Surah s= Suras.getAt(0);
       s.play();
    }
};
