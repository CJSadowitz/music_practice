#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <random>

void generate_staff(const std::string notes);
std::string generate_random_notes(int number);

int main() {
    srand(time(0));
    generate_staff(generate_random_notes(20));
    return 0;
}

void generate_staff(const std::string notes) {

    int *note_location = new int[notes.size()];
    int *sharp_location = new int[notes.size()];

    // Generate locations for low E string
    for (int i = 0; i < notes.size(); i++) {
        char c = notes[i];
        switch (c) {
            case 'e': // either high or low E
                if (rand() % 2 == 0) {
                    note_location[i] = 1;
                }
                else {
                    note_location[i] = 8;
                }
                sharp_location[i] = -1;
                break;
            case 'f':
                note_location[i]  = 2;
                sharp_location[i] = -1;
                break;
            case 'g':
                note_location[i]  = 3;
                sharp_location[i] = -1;
                break;
            case 'a':
                note_location[i]  = 4;
                sharp_location[i] = -1;
                break;
            case 'b':
                note_location[i]  = 5;
                sharp_location[i] = -1;
                break;
            case 'c':
                note_location[i]  = 6;
                sharp_location[i] = -1;
                break;
            case 'd':
                note_location[i]  = 7;
                sharp_location[i] = -1;
                break;
            case 'h':
                // A#
                note_location[i]  = 4;
                sharp_location[i] = 4;
                break;
            case 'i':
                // C#
                note_location[i]  = 6;
                sharp_location[i] = 6;
                break;
            case 'j':
                // D#
                note_location[i]  = 7;
                sharp_location[i] = 7;
                break;
            case 'k':
                // F#
                note_location[i]  = 2;
                sharp_location[i] = 2;
                break;
            case 'l':
                // G#
                note_location[i]  = 3;
                sharp_location[i] = 3;
                break;
        }
    }
    
    int level = 21;
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < notes.size(); j++) {
            if (j % 4 == 0 && level) {
                std::cout << "||";
            }
            if (level % 2 == 0 && note_location[j] < level && level >=  8 && level <= 16) {
                std::cout << "===";
            }
            else if (level % 2 == 1 && note_location[j] < level && level >= 8){
                std::cout << "   ";
            }
            else if (level == note_location[j] && sharp_location[j] == note_location[j] && level % 2 == 1) {
                if (notes[j] == 'k') {
                    std::cout << "f# ";
                }
                else if (notes[j] == 'h') {
                    std::cout << "a# ";
                }
                else if (notes[j] == 'l') {
                    std::cout << "g# ";
                }
                else if (notes[j] == 'i') {
                    std::cout << "c# ";
                }
                else if (notes[j] == 'j') {
                    std::cout << "d# ";
                }
            }
            else if (level == note_location[j] && sharp_location[j] == note_location[j] && level % 2 == 0 && level >= 8) {
                if (notes[j] == 'k') {
                    std::cout << "f#=";
                }
                else if (notes[j] == 'h') {
                    std::cout << "a#=";
                }
                else if (notes[j] == 'l') {
                    std::cout << "g#=";
                }
                else if (notes[j] == 'i') {
                    std::cout << "c#=";
                }
                else if (notes[j] == 'j') {
                    std::cout << "d#=";
                }
            }
            else if (level == note_location[j] && sharp_location[j] == note_location[j] && level % 2 == 0) {
                if (notes[j] == 'k') {
                    std::cout << "f#-";
                }
                else if (notes[j] == 'h') {
                    std::cout << "a#-";
                }
                else if (notes[j] == 'l') {
                    std::cout << "g#-";
                }
                else if (notes[j] == 'i') {
                    std::cout << "c#-";
                }
                else if (notes[j] == 'j') {
                    std::cout << "d#-";
                }
            }
            else if (level == note_location[j] && level % 2 == 1){
                std::cout << notes[j] << "  ";
            }
            else if (level == note_location[j] && level % 2 == 0 && level >= 8){
                std::cout << notes[j] << "==";
            }
            else if (level == note_location[j] && level % 2 == 0){
                std::cout << notes[j] << "--";
            }
            else if (level % 2 == 0 && level >= 8 && level <= 16)  {
                std::cout << "===";
            }
            else if (level % 2 == 0) {
                std::cout << "---";
            }
            else {
                std::cout << "   ";
            }
        }
        level--;
        std::cout << std::endl;
    }
    delete [] note_location;
    delete [] sharp_location;
}

std::string generate_random_notes(int number) {
    std::string output = "";
    for (int i = 0; i < number; i++) {
        int num = rand() % 12;
        output.push_back((char) num + 97);
    }
    return output;
}