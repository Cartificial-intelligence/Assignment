#include <bits/stdc++.h>
using namespace std;
#include <windows.h>
template <class T>
class Node{
public:
    T data;
    Node *next;
    Node(){
        next = nullptr;
    }
    Node(T data_){
        data = data_;
        next = nullptr;
    }

};
template <class T>
class LinkedList{
private:
    Node<T> *head;
public:
    LinkedList(){
        head = new Node<T>();
    }
    Node<T>* get(int index){
        Node<T> *cur = head;
        while(cur != nullptr && index>0){
            cur = cur->next;
            index--;
        }
        if(cur == nullptr) return nullptr;
        if(index==0) return cur;
    }
    void append(T newData){
        Node<T> *cur = head;
        while((cur->next) != nullptr){
            cur = cur->next;
        }
        cur->next = new Node<T>(newData);
    }
    void findNode(string name, string artist){
        Node<T> *cur = head->next;
        int i=0;
        while(cur != nullptr){
            i++;
            if(artist=="" || cur->data.artist == artist){
                if(name =="" || cur->data.name == name){
                    printf("%d: ",i);
                    cur->data.print();
                    cout<<endl;
                }
            }
            cur = cur->next;
        }
    }
    void deleteNode(int index){
        index--;
        Node<T> *cur = head;
        while(cur != nullptr && index>0){
            cur = cur->next;
            index--;
        }
        if(cur == nullptr) return;
        cur->next = cur->next->next;
    }
    void print(){
        Node<T>* cur = head->next;
        int i = 0;
        while(cur!=nullptr){
            i++;
            printf("%d: ",i);
            cur->data.print();
            printf("\n");
            cur = cur->next;
        }
        if(i==0){
            printf("No Songs in Playlist\n");
        }
    }

};

class Song{
public:
    string name;
    string artist;
    int listenCount = 0;
    Song(){

    }
    Song(string name_, string artist_){
        name = name_;
        artist = artist_;
    }
    string getName(){
        return name;
    }
    string getArtist(){
        return artist;
    }
    int getListenCount(){
        return listenCount;
    }
    void print(){
        cout<<name<<" by "<<artist;
    }
};
LinkedList<Song>* myPlaylist = new LinkedList<Song>();
void seePlaylist();
void addSong();
void deleteSong();
void searchSong();
void editSong();
void startPage(){
    system("cls");
    printf("My Playlist\nPress 0 to exit\nPress 1 to see the playlist\nPress 2 to add a song\nPress 3 to delete a song\nPress 4 to search for a song\n");
    int input = 0;
    bool run = true;
    while(run){
        scanf("%d", &input);
        run = false;
        if(input == 0){
            return;
        }
        else if(input == 1){
            seePlaylist();
        }
        else if(input == 2){
            addSong();
        }
        else if(input == 3){
            deleteSong();
        }
        else if(input == 4){
            searchSong();
        }
        else{
            startPage();
        }
    }
}
void seePlaylist(){
    system("cls");
    (*myPlaylist).print();
    printf("Enter 1 to go back\nEnter 2 to edit song\n");
    int input = 0;
    bool run = true;
    while(run){
        scanf("%d", &input);
        run = false;
        if(input == 1){
            startPage();
        }
        else if(input == 2){
            editSong();
        }
        else{
            seePlaylist();
        }
    }
}
void addSong(){
    system("cls");
    string title;
    string artist;
    cin.ignore(10000,'\n');
    printf("Enter song title:");
    getline(cin, title);
    printf("Enter artist name:");
    getline(cin, artist);
    Song *newSong = new Song(title,artist);
    myPlaylist->append(*newSong);
    int input = 0;
    printf("Song successfully added!\n");
    Sleep(100);
    startPage();
}
void deleteSong(){
    system("cls");
    myPlaylist->print();
    printf("Enter the song number:");
    int index;
    scanf("%d",&index);
    myPlaylist->deleteNode(index);
    printf("Song successfully deleted!\n");
    Sleep(100);
    startPage();
}
void searchSong(){
    system("cls");
    string title;
    string artist;
    cin.ignore(10000,'\n');
    printf("Searching for songs\n");
    printf("Enter song title(leave blank if not needed):");
    getline(cin, title);
    printf("Enter artist name(leave blank if not needed):");
    getline(cin, artist);
    system("cls");
    printf("Songs found:\n");
    myPlaylist->findNode(title, artist);
    printf("Enter any key to go back\n");
    string input;
    cin>>input;
    startPage();
}
void editSong(){
    system("cls");
    myPlaylist->print();
    printf("Enter the song number:");
    int index;
    scanf("%d", &index);
    string title;
    string artist;
    cin.ignore(10000,'\n');
    printf("Enter song title(leave blank for no change):");
    getline(cin, title);
    printf("Enter artist name:(leave blank for no change):");
    getline(cin, artist);
    Node<Song> *cur = myPlaylist->get(index);
    if(title!=""){
        cur->data.name = title;
    }
    if(artist!=""){
        cur->data.artist = artist;
    }
    printf("Song successfully edited!\n");
    Sleep(100);
    startPage();
}
int main(){
    startPage();
}
