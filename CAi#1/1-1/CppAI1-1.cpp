//
// Created by 김령교 on 7/8/23.
//

#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <ncurses.h>

void waitForInput() {
    // 키 입력 처리
    struct termios oldSettings, newSettings;
    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);

    char key;
    read(STDIN_FILENO, &key, 1);  // 아무 키나 입력받음

    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
}


#include "LinkedList.h"
#include "program.h"

// ANSI 이스케이프 시퀀스를 사용하여 텍스트 색상 변경
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

using namespace std;

// Song 클래스 정의
class Song {
public:
    string title, artist;

    Song(string title, string artist)
    {
        this -> title = title;
        this -> artist = artist;
    }

    bool operator==(const string& keyword) const {
        return title == keyword || artist == keyword;
    }

    bool operator==(const Song& other) const {
        return this->title == other.title && this->artist == other.artist;
    }

    bool operator!=(const Song& other) const {
        return !(*this == other);
    }

    void displayInfo() const {
        cout << "Title: " << title << ", Artist: " << artist << endl;
    }
};

// 플레이리스트 클래스 정의
class Playlist : LinkedList<Song>{
public:

    void addSong(Song song) {
        add(song);
    }

    LinkedList<Song>* searchSong(string keyword) {
        return search(keyword);
    }

    bool updateSong(Song item, Song updatedSong) {
        return update(item, updatedSong);
    }

    bool removeSong(Song item) {
        return remove(item);
    }

    LinkedList<Song>* LinkedList(){
        return (::LinkedList<Song>*) this;
    }
};


class MusicPlayer;

class MainView: public Scene{
public:
    static int state;
    /*화살표 컨트롤
    static int selected;
    string option[3];
    MainView(){
        option[0] = "[1] 전체 목록";
        option[1] = "[2] 음악 추가";
        option[2] = "[3] 검색";
    }*/

    void body(Program* program) override;
};

class ListView: public Scene{
public:
    static int state;
    string name;
    LinkedList<Song>* data;
    ListView(string listName, LinkedList<Song>* listData){
        name = listName;
        data = listData;
    }
    void body(Program* program) override;
};

class ItemView: public Scene{
public:
    static int state;
    Song data;
    ItemView(Song song): data(song){}
    void body(Program* program) override;
};

class ModifyView: public Scene{
public:
    static int state;
    Song data;
    ModifyView(Song song): data(song){}
    void body(Program* program) override;
};

class RemoveView: public Scene{
public:
    static int state;
    Song data;
    RemoveView(Song song): data(song){}
    void body(Program* program) override;
};

//class AllListView: public Scene{
//public:
//    static int state;
//    void body(Program* program) override;
//};

class AddSongView: public Scene{
public:
    void body(Program* program) override;
};

class SearchView: public Scene{
public:
    void body(Program* program) override;
};

class MusicPlayer: public Program{
public:
    Playlist playlist;
    MusicPlayer(): Program("Music Player 1.0", new MainView()){};
};

int MainView::state = 0;
/*화살표 컨트롤 int MainView::selected = 0;*/
void MainView::body(Program* program) {
    MusicPlayer* musicPlayer = (MusicPlayer*) program;

    cout << "[1] 전체 목록" << endl;
    cout << "[2] 음악 추가" << endl;
    cout << "[3] 검색" << endl;

    if (state == 1){
        cout << YELLOW << "잘못 입력하셨습니다. 다시 입력해주세요." << RESET << endl;
    }
    cout << "실행할 항목의 번호 : ";
    int select;
    cin >> select;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    switch (select) {
        case 1:
            state = 0;
            program->nowPlaying = new ListView("전체 목록", musicPlayer->playlist.LinkedList());
            break;
        case 2:
            state = 0;
            program->nowPlaying = new AddSongView();
            break;
        case 3:
            state = 0;
            program->nowPlaying = new SearchView();
            break;
        default:
            state = 1;
            break;
    }

    /* 화살표 컨트롤
    for (int i = 0; i < 3; i++){
        if (i == selected){
            cout << YELLOW << option[i] << RESET;
        } else {
            cout << option[i];
        }
        if (i < 2){
            cout << endl;
        }
    }

    cout << endl;

    // 키 입력 대기
    int ch = getch();

    // 화살표 키 확인
    if (ch == KEY_UP) {
        // 위쪽 화살표 키 눌렸을 때의 동작
        selected += 2;
        selected %= 3;
    } else if (ch == KEY_DOWN) {
        // 아래쪽 화살표 키 눌렸을 때의 동작
        ++selected %= 3;
    } else if (ch == 10){
        switch (selected+1) {
            case 1:
                state = 0;
                program->nowPlaying = new AllListView();
                break;
            case 2:
                state = 0;
                program->nowPlaying = new AddSongView();
                break;
            case 3:
                state = 0;
                break;
            default:
                state = 1;
                break;
        }
    }*/
}

int ListView::state = 0;
void ListView::body(Program* program) {
    cout << name << endl;

    int count = (*data).size();
    if (count == 0){
        cout << "플레이리스트가 비었습니다." << endl;
    } else {
        int index = 0;
        for (Song song : *data){
            cout << "[" << ++index << "] ";
            song.displayInfo();
        }
    }

    if (state == 1){
        cout << YELLOW << "잘못 입력하셨습니다. 다시 입력해주세요." << RESET << endl;
    }
    cout << "선택할 항목의 번호(종료: 0) : ";
    int select;
    cin >> select;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (select == 0){
        state = 0;
        program->nowPlaying = new MainView();
    } else if (select <= count){
        state = 0;
        program->nowPlaying = new ItemView(data->get(select - 1));
    } else{
        state = 1;
    }
}

int ItemView::state = 0;
void ItemView::body(Program* program) {
    MusicPlayer* musicPlayer = (MusicPlayer*) program;
    data.displayInfo();

    cout << "[1] 수정" << endl;
    cout << RED << "[2] 삭제" << RESET << endl;

    if (state == 1){
        cout << YELLOW << "잘못 입력하셨습니다. 다시 입력해주세요." << RESET << endl;
    }
    cout << "실행할 항목의 번호 : ";
    int select;
    cin >> select;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    switch (select) {
        case 1:
            state = 0;
            program->nowPlaying = new ModifyView(data);
            break;
        case 2:
            state = 0;
            program->nowPlaying = new RemoveView(data);
            break;
        default:
            state = 1;
            break;
    }

    /* 화살표 컨트롤
    for (int i = 0; i < 3; i++){
        if (i == selected){
            cout << YELLOW << option[i] << RESET;
        } else {
            cout << option[i];
        }
        if (i < 2){
            cout << endl;
        }
    }

    cout << endl;

    // 키 입력 대기
    int ch = getch();

    // 화살표 키 확인
    if (ch == KEY_UP) {
        // 위쪽 화살표 키 눌렸을 때의 동작
        selected += 2;
        selected %= 3;
    } else if (ch == KEY_DOWN) {
        // 아래쪽 화살표 키 눌렸을 때의 동작
        ++selected %= 3;
    } else if (ch == 10){
        switch (selected+1) {
            case 1:
                state = 0;
                program->nowPlaying = new AllListView();
                break;
            case 2:
                state = 0;
                program->nowPlaying = new AddSongView();
                break;
            case 3:
                state = 0;
                break;
            default:
                state = 1;
                break;
        }
    }*/
}

void ModifyView::body(Program* program) {
    cout << "음악 수정" << endl;

    string title, artist;
    cout << "title(" << data.title << ") : ";
    getline(cin, title);
    cout << "artist(" << data.artist << ") : ";
    getline(cin, artist);

    MusicPlayer* musicPlayer = (MusicPlayer*) program;
    musicPlayer->playlist.updateSong(data, Song(title, artist));

    cout << "음악이 수정되었습니다." << endl;
    cout << "아무키나 눌러 메인메뉴로" << endl;
    waitForInput();// 아무 키 입력 대기

    program->nowPlaying = new MainView();
}

void RemoveView::body(Program* program) {
    data.displayInfo();
    cout << RED << "진짜 삭제하시겠습니까?" << RESET << endl;
    cout << "(" << RED << "예: Y" << RESET << "/" << GREEN << "아니요: Y외의 키"<< RESET << ") : "<< endl;
    string select;
    cin >> select;

    if (select == "Y" || select == "y"){
        MusicPlayer* musicPlayer = (MusicPlayer*) program;
        if (musicPlayer->playlist.removeSong(data)) {
            cout << "삭제되었습니다." << endl;
        } else {
            cout << "삭제 실패했습니다." << endl;
        }
    } else {
        cout << "취소되었습니다." << endl;
    }

    cout << "아무키나 눌러 메인메뉴로" << endl;
    waitForInput();// 아무 키 입력 대기

    program->nowPlaying = new MainView();
}

void AddSongView::body(Program* program) {
    cout << "음악 추가" << endl;

    string title, artist;
    cout << "title : ";
    getline(cin, title);
    cout << "artist : ";
    getline(cin, artist);

    MusicPlayer* musicPlayer = (MusicPlayer*) program;
    musicPlayer->playlist.addSong(Song(title, artist));

    cout << "음악이 추가되었습니다." << endl;
    cout << "아무키나 눌러 메인메뉴로" << endl;
    waitForInput();// 아무 키 입력 대기

    program->nowPlaying = new MainView();
}

void SearchView::body(Program* program) {
    string keyword;
    cout << "검색어를 입력하세요 : ";
    getline(cin, keyword);

    MusicPlayer* musicPlayer = (MusicPlayer*) program;
    program->nowPlaying = new ListView("검색어 : " + keyword, musicPlayer->playlist.searchSong(keyword));
}

int main() {
    /* 화살표 컨트롤
    // ncurses 초기화
    initscr();
    keypad(stdscr, true); // 화살표 입력을 활성화
    */
    MusicPlayer().play();
    /* 화살표 컨트롤
    // ncurses 종료
    endwin();
    */
    return 0;
}
