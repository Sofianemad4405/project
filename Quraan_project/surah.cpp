#include <iostream>
#include <windows.h>
#include <mmsystem.h> // For PlaySound
#pragma comment(lib, "winmm.lib")

using namespace std;

class Surah {
private:
    string surahName;
    string surahType;
    string surahPath;

public:
    // Constructor with member initializer list
    Surah(const string& surahName, const string& surahType, const string& surahPath)
            : surahName(surahName), surahType(surahType), surahPath(surahPath) {}

    // Default constructor
    Surah() : surahName(""), surahType(""), surahPath("") {}

    Surah(const Surah& b){
        this->surahName = b.surahName;
        this->surahType = b.surahType;
        this->surahPath = b.surahPath;
    }

    // Equality operator
    bool operator==(const string& otherName) const {
        return surahName == otherName;
    }

    // Display Surah details
    void displaySurahDetails() const {
        cout << "Surah Name: " << surahName << endl;
        cout << "Surah Type: " << surahType << endl;
        cout << "Surah Path: " << surahPath << endl;
    }

    // Accessor methods
    string getSurahName() const { return surahName; }
    string getSurahPath() const { return surahPath; }
    string getSurahType() const { return surahType; }

    // Validation
    bool isValid() const {
        return !surahName.empty() && !surahPath.empty();
    }

    // Assignment operator
    Surah& operator=(const Surah& other) {
        if (this != &other) { // Check for self-assignment
            surahName = other.surahName;
            surahPath = other.surahPath;
            surahType = other.surahType;
        }
        return *this;
    }

    void setSurahName(const string &surahName) {
        Surah::surahName = surahName;
    }

    void setSurahPath(const string &surahPath) {
        Surah::surahPath = surahPath;
    }

    void setSurahType(const string &surahType) {
        Surah::surahType = surahType;
    }

    // Play Surah audio
    void play() const {
        if (!isValid()) {
            cout << "Invalid Surah: Missing name or path." << endl;
            return;
        }
        if (PlaySound(surahPath.c_str(), NULL, SND_FILENAME | SND_ASYNC)) {
            cout << "Now playing: " << surahName << endl;
        } else {
            cout << "Failed to play Surah: " << surahName << endl;
        }
    }

    // Stop Surah audio
    void stop() const {
        PlaySound(NULL, NULL, 0);
        cout << "Playback stopped." << endl;
    }

    // Friend function for output
    friend ostream& operator<<(ostream& os, const Surah& surah) {
        os << "Surah Name: " << surah.surahName << ", Type: " << surah.surahType;
        return os;
    }
};
