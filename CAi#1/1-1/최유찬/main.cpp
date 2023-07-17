#include <iostream>
#include<string>
using namespace std;

template<typename T>
class Node{
private:
    T val;
public :
    Node<T>* prev , *next;
    Node()
    {
        prev = NULL;
        next = NULL;
    }
    Node(T val)
    {
        this->val = val;
        next = NULL;
        prev = NULL;
    }

    T getVal()
    {
        return val;
    }
    void setVal(T val)
    {
        this->val = val;
    }
};

template<typename T>
class LinkedList{
private:
    Node<T> *head, *tail;
    int num ;
public:
    LinkedList()
    {
        head = new Node<T>();
        tail = new Node<T>();
        head->next = tail;
        tail->prev = head;
        num =0 ;
    }
    void push(T val)
    {
        Node<T> *temp = new Node<T>(val);
        tail->prev->next = temp;
        temp->prev = tail->prev;
        tail->prev = temp;
        temp->next = tail;

        num++;
    }
    T pop()
    {
        if(num>0)
        {
            Node<T> *temp = tail ->prev;
            temp->prev->next = tail;
            tail->prev = temp->prev;
            num--;
            T ret = temp->getVal();
            delete temp;

            return ret;
        }
        else{
            throw -1;
        }
    }

    Node<T>* getNode(int i)
    {
        if(i>=num)
        {
            throw -1;
        }
        Node<T> *temp = head;

        while(i-- >=0)
        {
            temp = temp->next;
        }
        return temp;
    }

    T get(int i)
    {
        return getNode(i)->getVal();
    }

    void set(int i, T val)
    {
        getNode(i)->setVal(val);
    }

    void pop(int i)
    {
        Node<T> *temp = getNode(i);
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        num--;
    }

    int size()
    {
        return num;
    }
};

class Song{
private:
    string name, singer;
public:
    Song()
    {

    }
    Song(string n, string s="None")
    {
        name = n;
        singer = s;
    }

    void print()
    {
        cout<<name<<"("<<singer<<")"<<endl;
    }

    string getName()
    {
        return name;
    }

    string getSinger()
    {
        return singer;
    }
};

void printLine(){
    cout<<"===================================="<<endl;
}

class PlayList{
private:
    LinkedList<Song> lst = LinkedList<Song>();
public:
    void printSongs()
    {
        int num = lst.size();
        printLine();
        for(int i=0; i<num; i++)
        {
            cout<<(i+1)<<".";
            lst.get(i).print();
        }
        cout<<"Total Song : "<<num<<endl;
        printLine();
    }

    void printSongs(string name)
    {
        int num = lst.size();
        int cnt = 0;
        printLine();
        for(int i=0; i<num; i++)
        {
            if(lst.get(i).getName() == name)
            {
                cout<<(i+1)<<".";
                lst.get(i).print();
                cnt+=1;
            }
        }
        cout<<"Total Song : "<<cnt<<endl;
        printLine();
    }

    void setSongs(int i, string name, string singer)
    {
        Song temp = lst.get(i);
        if(name=="" || name=="-") name = temp.getName();
        if(singer=="" || singer=="-") singer = temp.getSinger();
        Song *n = new Song(name, singer);
        lst.set(i, *n);
    }

    void pushSongs(string name, string singer="None")
    {
        Song *n = new Song(name, singer);
        lst.push(*n);
    }

    void popSongs(int i)
    {
        lst.pop(i);
    }

    void popSongs()
    {
        lst.pop();
    }
};

class Menu
{
private:
    PlayList p = PlayList();

    int printMenu()
    {
        system("cls");
        printLine();
        cout<<"0.exit"<<endl;
        cout<<"1.add song"<<endl;
        cout<<"2.show playlist"<<endl;
        cout<<"3.find song"<<endl;
        printLine();

        cout<<"process num : ";
        int num;
        cin>>num;
        cin.ignore(10000,'\n');

        switch(num)
        {
        case 0:
            return -1;
        case 1:
            addSong();
            return 0;
        case 2:
            showPlaylist();
            return 1;
        case 3:
            findSongs();
            return 1;
        }
    }

    void printEditMenu()
    {
        printLine();
        cout<<"0.exit"<<endl;
        cout<<"1.edit song"<<endl;
        cout<<"2.delete song"<<endl;
        printLine();

        cout<<"process num : ";
        int num;
        cin>>num;
        cin.ignore(10000,'\n');

        switch(num)
        {
        case 0:
            break;
        case 1:
            editSong();
            break;
        case 2:
            delSong();
            break;
        }
    }

    void addSong()
    {
        string n, s;
        cout<<"name:";
        getline(cin, n);
        cout<<"singer:";
        getline(cin, s);
        p.pushSongs(n, s);
    }

    void showPlaylist()
    {
        system("cls");
        p.printSongs();
    }

    void findSongs()
    {
        system("cls");
        string n;
        cout<<"name:";
        getline(cin, n);
        p.printSongs(n);
    }

    void delSong()
    {
        int num;
        cout<<"id:";
        cin>>num;
        p.popSongs(num-1);
    }

    void editSong()
    {
        int num;
        cout<<"id:";
        cin>>num;
        cin.ignore(10000,'\n');

        string n, s;
        printLine();
        cout<<"blank or - : no change"<<endl;
        cout<<"name:";
        getline(cin, n);

        cout<<"singer:";
        getline(cin, s);

        p.setSongs(num-1, n, s);
    }
public:
    void process()
    {
        int cnt = 1;
        while(cnt>=0)
        {
            cnt = printMenu();
            if(cnt == 1)
                printEditMenu();
        }
    }
};

int main()
{
    Menu m = Menu();
    m.process();
    return 0;
}
