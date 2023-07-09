//
// Created by 김령교 on 7/9/23.
//

#ifndef CPPAI_PROGRAM_H
#define CPPAI_PROGRAM_H

#include <iostream>
#include <string>

#define RESET   "\033[0m"
#define BLUE    "\033[34m"

class Program;

class Scene {
public:
    virtual void body(Program* program) = 0;
};

class Program {
public:
    std::string name;
    Scene* nowPlaying;
    Program(std::string program_name, Scene* first_scene) : name(program_name), nowPlaying(first_scene) {
    }

    bool working = true;
    void play(){
        clear();
        while (working){
            cout << BLUE << name << RESET << endl;
            nowPlaying->body(this);
            clear();
        }
    }

    void clear() {
        system("clear");
    }
};

#endif //CPPAI_PROGRAM_H
