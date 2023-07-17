#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Node{

public:
    T data;
    Node* next = NULL;

    Node(T data){
        this->data = data;
    }
    
};


template <typename T>
class LinkedList{

private:
    int len = 0;
    Node<T>* head = NULL;

public:
    LinkedList(){

    }

    void add(T data, int idx){
        if(idx > len){
            throw "Invalid index. ";
        }
        Node<T>* cur = head;
        Node<T>* temp = NULL;
        if(idx == 0 && len == 0){
            head = new Node<T>(data);
        }
        else if(idx == 0){
            temp = head;
            head = new Node<T>(data);
            head->next = temp;
        }
        else{
            for(int i = 0 ; i < idx-1 ; i++){
                cur = cur->next;
            }
            temp = cur->next;
            cur->next = new Node<T>(data);
            cur->next->next = temp;
        }
        len++;
    }

    void update(T data, int idx){
        if(idx >= len){
            throw "Invalid index. ";
        }
        Node<T>* cur = head;
        Node<T>* temp = NULL;
        if(idx == 0){
            temp = head->next;
            head = new Node<T>(data);
            head->next = temp;
        }
        else{
            for(int i = 0 ; i < idx-1 ; i++){
                cur = cur->next;
            }
            temp = cur->next->next;
            cur->next = new Node<T>(data);
            cur->next->next = temp;
        }
    }

    void remove(int idx){
        if(idx >= len){
            throw "Invalid index. ";
        }
        Node<T>* cur = head;
        Node<T>* temp = NULL;
        if(idx == 0){
            temp = head->next;
            free(head);
            head = temp;
        }
        else{
            for(int i = 0 ; i < idx-1 ; i++){
                cur = cur->next;
            }
            temp = cur->next->next;
            free(cur->next);
            cur->next = temp;
        }
        len--;
    }

    int find(T data){
        Node<T>* cur = head;
        int cnt = 0;
        while(cur != NULL){
            if(cur->data == data){
                break;
            }
            cur = cur->next;
            cnt++;
        }
        if(cur == NULL){
            return -1;
        }
        else{
            return cnt;
        }
    }

    T get(int idx){
        if(idx >= len){
            throw "Invalid index. ";
        }
        Node<T>* cur = head;
        for(int i = 0 ; i < idx ; i++){
            cur = cur->next;
        }
        return cur->data;
    }

    void print(){
        Node<T>* cur = head;
        while(cur != NULL){
            cur->data.print();
            cur = cur->next;
        }
    }

    void clear(){
        head = NULL;
        len = 0;
    }
};


class Song{

private:
    string name;
    string singer;

public:
    Song(){

    }

    Song(string name, string singer){
        this->name = name;
        this->singer = singer;
    }

    string getName(){
        return name;
    }

    string getSinger(){
        return singer;
    }

    void setName(string name){
        this->name = name;
    }

    void getSinger(string singer){
        this->singer = singer;
    }

    bool operator==(Song other){
        return (name == other.name) && (singer == other.singer);
    }

    void print(){
        cout<<"("<<name<<", "<<singer<<")"<<endl;
    }
};


// string functions

bool isValid(char chr){
    return ('0' <= chr && chr <= '9') || ('A' <= chr && chr <= 'z');
}

bool isNumeric(string cmd){
    int length = cmd.length();
    for(int i = 0 ; i < length ; i++){
        if(!('0' <= cmd[i] && cmd[i] <= '9')){
            return false;
        }
    }
    return true;
}

bool isTrash(string cmd){
    int length = cmd.length();
    for(int i = 0 ; i < length ; i++){
        if(isValid(cmd[i])){
            return false;
        }
    }
    return true;
}

string cutSpace(string &cmd){

    if(isTrash(cmd)){
        throw "Invalid command. ";
    }

    int length = cmd.length();
    int first = 0;
    while(!isValid(cmd[first])) first++;
    int start = first, end = length;
    for(int i = first ; i < length ; i++){
        if(!isValid(cmd[i])){
            start = i;
            break;
        }
    }
    if(start ==  first && isValid(cmd[first]) && isValid(cmd[length-1])){
        start = length;
    }
    for(int i = start ; i < length ; i++){
        if(isValid(cmd[i])){
            end = i;
            break;
        }
    }
    string front = cmd.substr(first, start-first);
    string rest = cmd.substr(end, length-end);
    cmd = rest;
    return front;
}


// ui and linkedlist
LinkedList<Song> list;

void add(string cmd){
    string index = cutSpace(cmd);
    string songname = cutSpace(cmd);
    string songsinger = cutSpace(cmd);
    if(!isTrash(cmd) || !isNumeric(index)){
        throw "Invalid command. ";
    }

    int idx = stoi(index);
    Song song(songname, songsinger);
    list.add(song, idx);
    cout<<"Song added. "<<endl;
}

void update(string cmd){
    string index = cutSpace(cmd);
    string songname = cutSpace(cmd);
    string songsinger = cutSpace(cmd);
    if(!isTrash(cmd) || !isNumeric(index)){
        throw "Invalid command. ";
    }

    int idx = stoi(index);
    Song song(songname, songsinger);
    list.update(song, idx);
    cout<<"Song updated. "<<endl;
}

void remove(string cmd){
    string index = cutSpace(cmd);
    if(!isTrash(cmd) || !isNumeric(index)){
        throw "Invalid command. ";
    }

    int idx = stoi(index);
    list.remove(idx);
    cout<<"Song removed. "<<endl;
}

void get(string cmd){
    string index = cutSpace(cmd);
    if(!isTrash(cmd) || !isNumeric(index)){
        throw "Invalid command. ";
    }
    int idx = stoi(index);
    Song song = list.get(idx);
    song.print();
}

void find(string cmd){
    string songname = cutSpace(cmd);
    string songsinger = cutSpace(cmd);
    if(!isTrash(cmd)){
        throw "Invalid command. ";
    }
    Song song(songname, songsinger);
    int idx = list.find(song);
    if(idx == -1){
        cout<<"No song found. ";
    }else{
        cout<<"Index : "<<idx<<endl;
    }
}

void print(string cmd){
    if(!isTrash(cmd)){
        throw "Invalid command. ";
    }
    list.print();
    cout<<endl;
}

void clear(string cmd){
    if(!isTrash(cmd)){
        throw "Invalid command. ";
    }
    list.clear();
    system("cls");
    cout<<"Successfully cleared."<<endl;
}

void help(string cmd){
    if(!isTrash(cmd)){
        throw "Invalid command. ";
    }
    cout<<"\tadd (index) (songname) (songsinger) : add the song to the linkedlist. "<<endl;
    cout<<"\tupdate (index) (songname) (songsinger) : update the song in the given index. "<<endl;
    cout<<"\tremove (index) : remove the song in the given index. "<<endl;
    cout<<endl;
    cout<<"\tget (index) : show the song in the given index. "<<endl;
    cout<<"\tfind (songname) (songsinger) : find the index of the song with the given name and singer. "<<endl;
    cout<<endl;
    cout<<"\tprint : print the whole linkedlist. "<<endl;
    cout<<"\tclear : clear the linkedlist and the history. "<<endl;
    cout<<"\thelp : show available commands. "<<endl;
    cout<<endl;
    cout<<"\tquit : quit program. "<<endl;
    cout<<endl;
}

void quit(string cmd){
    if(!isTrash(cmd)){
        throw "Invalid command. ";
    }
    exit(0);
}

int main(){
    string cmd;
    string subcmd;
    list = LinkedList<Song>();

    cout<<"insert \'help\' to view available commands"<<endl;
    while(true){
        cout<<">>";
        getline(cin, cmd);
        subcmd = cutSpace(cmd);
        try{
            if(subcmd == "add"){
                add(cmd);
            }
            else if(subcmd == "update"){
                update(cmd);
            }
            else if(subcmd == "remove"){
                remove(cmd);
            }
            else if(subcmd == "get"){
                get(cmd);
            }
            else if(subcmd == "find"){
                find(cmd);
            }
            else if(subcmd == "print"){
                print(cmd);
            }
            else if(subcmd == "clear"){
                clear(cmd);
            }
            else if(subcmd == "help"){
                help(cmd);
            }
            else if(subcmd == "quit"){
                quit(cmd);
            }
            else{
                cout<<"Invalid command."<<endl;
            }
        }catch(const char* str){
            cout<<str<<endl;
        }
    }
}
