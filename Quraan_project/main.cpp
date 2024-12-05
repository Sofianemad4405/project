#include <iostream>
#include <fstream>
#include <limits>
#include <windows.h>
#include <mmsystem.h>
#include <string>
#include "App.cpp"
//#include "playList.cpp"
#include <conio.h>

#define myline "====================================================\n"
using namespace std;

void showMenu() {
    cout << "=========================================================\n";
    cout << "               Quran Playlist Manager Menu               \n";
    cout << "=========================================================\n";
    cout << "1. Add a new playlist\n";
    cout << "2. Add Surah to an existing playlist\n";
    cout << "3. Remove Surah from an existing playlist\n";
    cout << "4. Update the order of an existing playlist\n";
    cout << "5. Display All Current Playlists\n";
    cout << "6. Display All Playlists Surah\n";
    cout << "7. Display Surah in a specific playlist\n";
    cout << "8. Play Surah from a specific playlist\n";
    cout << "9. Save an existing playlist to a file\n";
    cout << "10. Load an existing playlist from a file\n";
    cout << "11. Remove an existing playlist\n";
    cout << "12. Exit\n";
    cout << "=========================================================\n";
    cout << "*Any other option, app will terminate*\n";
    cout << "Your choice: ";
}

myApp myApp;

void addPlayList() {
    string shName;
    cout << "Enter the playlist name (Sheikh-Name): ";
    cin >> shName;
    playList pl(shName);
    myApp.addNewPlayList(pl);
    cout << "Sheikh added successfully ... !\n";
}

void removePlayList() {
    myApp.displayPlayLists();
    if (myApp.isEmpty()) {
        cout << "There are no playlists.\n";
        return;
    }
    int index;
    cout << "Enter id of playlist to remove: ";
    cin >> index;
    myApp.removePlaylistByIndex(index);
    cout << "\nPlaylist removed successfully... ! \n";
}
void addSurahToExistingPlaylist() {
    myApp.displayPlayLists();
    string sheikhName;
    cout << "Enter the name of the playlist to add a surah: ";

    cin>>sheikhName;


    int playlistIndex = myApp.searchInPlaylists(sheikhName);

    string suraName, suraType, suraPath;
    cout << "\nEnter surah name: ";
    cin >> suraName;
    cout << "Enter surah type: ";
    cin>>suraType;
    cout << "Enter surah path: ";
    cin>>suraPath;

    Surah newSurah(suraName, suraType, suraPath);

    playList playlist = myApp.getPlaylists().getAt(playlistIndex);

    playlist.addNewSurah(newSurah);

    cout << "Surah \"" << suraName << "\" added successfully to the playlist \"" << sheikhName << "\".\n";
}

bool findSurah(const string &playlistName, const string &surahName) {
    int playlistIndex = myApp.searchInPlaylists(playlistName);
    if (playlistIndex == -1) return false;

    playList pl = myApp.getPlaylists().getAt(playlistIndex);
    int surahIndex = pl.searchSura(surahName);
    return surahIndex != -1;
}

void removeSurahFromExistingPlaylist() {
    myApp.displayPlayLists();
    if (myApp.isEmpty()) {
        char option;
        cout << "You have not entered any playlists \nDo you want to add a playlist (y/n): ";
        cin >> option;
        if (option == 'y') {
            playList pl;
            myApp.addNewPlayList(pl);
        } else if (option == 'n') {
            return;
        }
    }
    string playlistName, surahName;
    cout << "Enter the name of the playlist to remove a Surah from: ";
    cin >> playlistName;

    cout << "\nEnter the name of the Surah to remove: ";
    cin >> surahName;

    if (findSurah(playlistName, surahName)) {
        playList pl = myApp.getPlaylists().getAt(myApp.searchInPlaylists(playlistName));
        int surahIndex = pl.searchSura(surahName);
        pl.removeSurah(surahIndex);
        cout << "Surah \"" << surahName << "\" removed from playlist \"" << playlistName << "\" successfully.\n";
    } else {
        cout << "Failed to remove Surah. Either playlist or Surah was not found.\n";
    }
}

void updateOrderOfPlaylist() {
    string playlistName;
    int newPos;
    myApp.displayPlayLists();
    cout << "Enter the name of playlist: ";
    cin >> playlistName;
    cout << "\nEnter the new position of the playlist: ";
    cin >> newPos;

    int plIndex = myApp.searchInPlaylists(playlistName);
    if (plIndex == -1) {
        cout << "There is no such playlist named " << playlistName << " ,Try again ... !\n";
        return;
    }
    if (newPos < 0 || newPos >= myApp.getPlaylists().getSize()) {
        cout << "Invalid position. Try again...\n";
        return;
    }
    playList pl = myApp.getPlaylists().getAt(plIndex);
    myApp.updatePlaylists(pl, plIndex, newPos);
}

void displayAllCurrentPlaylists() {
    myApp.displayPlayLists();
}

void displayPlayListsSurah() {
    for (int i = 0; i < myApp.getSize(); ++i) {
        playList pl = myApp.getPlaylistAt(i);
        myApp.displayPLayListComponents(pl);
    }
}

void displaySurahInSpecificPlayList() {
    string surahName;
    string playlistName;
    myApp.displayPlayLists();

    cout << "Enter the playlist to search in : ";
    cin >> playlistName;
    int plIndex = myApp.searchInPlaylists(playlistName);
    if (plIndex == -1) {
        cout << "There is no such playlist named " << playlistName << " , try again .... !" << endl;
        return;
    }
    playList pl = myApp.getPlaylistAt(plIndex);
    cout << "\nEnter the surah name: ";
    cin >> surahName;

    Surah surah = pl.searchSurah(surahName);
    if (!surah.isValid()) {
        cout << "The surah \"" << surahName << "\" was not found in playlist \"" << playlistName << "\"." << endl;
        return;
    }
    surah.displaySurahDetails();
}

void playPLayList() {
    myApp.runPlaylist();
}

//playList& playlist, const string& fileName
void savePlaylistToFile() {
    string fileName;
    cout << "Enter the filename to save the playlist: ";
    cin >> fileName;
    ofstream outFile(fileName);
    if (!outFile) {
        cout << "Error: Could not open file " << fileName << " for writing." << endl;
        return;
    }
    cout << "Enter the name of the playlist to save: ";
    string playlistName;
    cin >> playlistName;
    int playlistIndex = myApp.searchInPlaylists(playlistName);
    if (playlistIndex == -1) {
        cout << "There is no playlist named " << playlistName << " ,try again.. !\n";
        return;
    }
    playList playlist = myApp.getPlaylists().getAt(playlistIndex);

    outFile << playlist.getSheikhName() << endl;

    for (int i = 0; i < playlist.getSurahsCount(); ++i) {
        Surah surah = playlist.getSurahAt(i);
        outFile << surah.getSurahName() << endl;
        outFile << surah.getSurahType() << endl;
        outFile << surah.getSurahPath() << endl;
    }

    outFile.close();
    cout << "Playlist saved successfully to " << fileName << endl;
}

void loadPlaylistFromFile(const string& fileName) {
    ifstream inFile(fileName);
    if (!inFile) {
        cout << "Error: Could not open file " << fileName << " for reading." << endl;
        return;
    }

    string line;
    string playlistName;
    getline(inFile, playlistName);
    playList newPlaylist(playlistName);

    while (getline(inFile, line)) {
        string surahName = line;
        string surahType;
        getline(inFile, surahType);
        string surahPath;
        getline(inFile, surahPath);

        Surah newSurah(surahName, surahType, surahPath);
        newPlaylist.addNewSurah(newSurah);
    }

    myApp.addNewPlayList(newPlaylist);
    inFile.close();
    cout << "Playlist loaded successfully from " << fileName << endl;
}

int main() {
    showMenu();
    int option;
    do {
        cin >> option;

        switch (option) {
            case 1:
                addPlayList();
                break;
            case 2:
                addSurahToExistingPlaylist();
                break;
            case 3:
                removeSurahFromExistingPlaylist();
                break;
            case 4:
                updateOrderOfPlaylist();
                break;
            case 5:
                displayAllCurrentPlaylists();
                break;
            case 6:
                displayPlayListsSurah();
                break;
            case 7:
                displaySurahInSpecificPlayList();
                break;
            case 8:
                playPLayList();
                break;
            case 9: {
                savePlaylistToFile();
                break;
            }
            case 10: {
                string filename;
                cout << "Enter the filename to load the playlist: ";
                cin >> filename;
                loadPlaylistFromFile(filename);
                break;
            }
            case 11:
                removePlayList();
                break;
            case 12:
                cout << "Exiting application...\n";
                break;
            default:
                cout << "Invalid option. Exiting application...\n";
                break;
        }

        if (option != 12) {
            showMenu();
        }
    } while (option != 12);

    return 0;
}
