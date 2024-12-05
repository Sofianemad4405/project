#include<iostream>
//#include "doublyLinkedList.cpp"
#include "playList.cpp"
#include <windows.h>
#include <mmsystem.h>


using namespace std;

class myApp {
    DoublyLinkedList<playList> playlists;
    int size = 0;
public:
    void addNewPlayList(playList pl) {
        playlists.addLast(pl);
        size++;
    }

    int getSize() {
        return size;
    }

    void addNewPlayListAt(playList pl, int index) {
        playlists.addAt(pl, index);
    }

    void removePlaylistByIndex(int index) {
        playlists.removeAt(index);
        size--;
    }


    DoublyLinkedList<playList> getPlaylists() {
        cout<<"hello";
        return playlists;
    }

    playList getPlaylistAt(int index) {
        return playlists.getAt(index);
    }


    bool isEmpty() {
        return size == 0;
    }

    void displayPlayLists() {
        cout << "====================================================" << endl;
        cout << "            Current Quran Playlists                 " << endl;
        cout << "====================================================" << endl;

        if (isEmpty()) {
            cout << "No playlists available. Add a playlist to get started!" << endl;
            cout << "====================================================" << endl;
            return;
        }

        int i = 1;
        for (int j = 0; j < size; j++) {
            playList pl = playlists.getAt(j);
            cout << i++ << " - " << "Sheikh " << pl.getSheikhName() << endl;
        }
        cout << "====================================================" << endl;
    }


    int searchInPlaylists(const string &sheikhName) {
        for (int i = 0; i < size; ++i) {
            playList pl = playlists.getAt(i);
            if (pl.getSheikhName() == sheikhName) {
                return i;
            }
        }
        return -1;
    }

    void removePlaylistByName(const string &sheikhName) {
        int index = searchInPlaylists(sheikhName);
        if (index != -1) {
            removePlaylistByIndex(index);
            return;
        }
        cout << "There is no playlist named " << sheikhName << " try again ... !\n";
    }


    void displayPLayListComponents(playList pl) {
        cout << "=============================================\n";
        cout << "               " << pl.getSheikhName() << endl;
        cout << "=============================================\n";
        pl.displaySurahs();
    }

    void updatePlaylists(const playList &pl, int index, int newPosition) {
        if (index < 0 || index >= this->playlists.getSize()) {
            cout << "Invalid index. Cannot update playlist order.\n";
            return;
        }
        this->removePlaylistByIndex(index);
        this->addNewPlayListAt(pl, newPosition);
    }

    void updatePlaylistByName(const playList &pl, string playListName, int newPosition) {
        int index = searchInPlaylists(playListName);
        updatePlaylists(pl, index, newPosition);
    }


    void displayPlaylistsSurah(myApp playlists) const {
        if (playlists.isEmpty()) {
            cout << "No myApp available.\n";
            return;
        }

        for (int i = 0; i < playlists.getSize(); i++) {
            playList pl = playlists.getPlaylistAt(i);
            cout << "=======================================\n";
            cout << "        " << pl.getSheikhName() << endl;
            cout << "=======================================\n";
            pl.displaySurahs();
        }
    }

    void runPlaylist() {

        displayPlayLists();
        string playlistName ;
        cout << "Select a playlist to run : ";
        cin>>playlistName;
        int index = searchInPlaylists(playlistName);
        if (index != -1) {
            playList pl = playlists.getAt(index);
            pl.start();
        } else {
            cout << "No playlist found .\n";
        }
    }
};