#include <iostream>

using namespace std;
template <typename T>
class SongList
{
private:
    Song* head;
    Song* tail;
    int n;
public:
    SongList() {
        this->head = NULL;
        this->tail = NULL;
        this->n = 0;
    }

    void addSong(T song) {
        Song *temp = new Song song;
        tail->next = temp;
        tail = temp;
        n++;
    }

    void deleteSong() {
        tail = tail->prep;
        tail->next = NULL;
        n--;
    }

    void showList() {
        Song *temp = head;
        for (int i = 0; i < n; i++)
        {
            temp.Show();
            temp = temp->next;
        }
        
    }

};

class Song 
{
private:
    string singer;
    string title;
    Song* next;
    Song* prep;
public:
    Song(string singer, string title) {
        this->singer = singer;
        this->title = title;
    }
    string Show() {
        cout << "Title: " + this->title + "\n" + "Singer: " + this->singer << endl;
    }
};

void delay() {
    char y;
    while(1) {
        cout << "back menu?(y) : " << endl;
        cin >> y;
        if (y == 'y') {
            break;
        }
    }
}

int main() {
    SongList SL = SongList();
    while(1) {
        int n;
        cout << "Playlist" << endl;
        cout << "1. add Song" << endl;
        cout << "2. delete Last Song" << endl;
        cout << "3. print Playlist" << endl;
        cin >> n;
        if (n == 1) {
            string title, singer;
            cout << "title?: " << endl;
            getline(cin,title);
            cout << "singer?: " << endl;
            getline(cin,singer);
            Song s = Song(singer, title);
            SL.addSong(s);
        } else if (n == 2) {
            SL.deleteSong();
        } else if (n == 3) {
            SL.showList();
        } else {
            cout << "wrong number" << endl;
        }
    }
    return 0;
}