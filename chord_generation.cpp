#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <random>

void rotate_right(std::string& notes);
void rotate_left(std::string& notes);

std::string generate_chord(const char note, const std::string& type);
std::string convert_notes(const std::string& notes);

void generate_staff(std::string& notes, int position);

// h - l are sharps
static std::string notes_dictionary = "ahbcidjefkgl";

int main() {
    srand(time(0));
    std::string notes = "";
    try {
        for (int i = 0 ; i < 4; i++) {
            std::string type = "";
            if (rand() % 5 == 0) {
                type = "power";
            }
            else if (rand() % 5 == 1) {
                type = "major";
            }
            else if (rand() % 5 == 2) {
                type = "minor";
            }
            else if (rand() % 5 == 3) {
                type = "augmented";
            }
            else if (rand() % 5 == 3) {
                type = "diminished";
            }
            char note = 'a' + (rand() % 12);
            notes += generate_chord(note, "minor");
        }
        generate_staff(notes, rand() % 6);
    }
    catch (std::string error) {
        std::cout << error << std::endl;
    }

    return 0;
}
// Generate an array of size 12 number numerically from 0-11\
posiiton in array is equvilient to distance from root\
chose arbitrary note to be the root, rotate the array left or right until the note is at index 0\
this index is referenced like a dictionary to create chords.
void rotate_right(std::string& notes) {
    if (notes.size() == 0) {
        throw std::string("rotate_right: notes has no values");
    }
    else {
    std::string new_notes = "";
        int k = 0;
        for (int i = 1; i < notes.size() + 1; i++) {
            new_notes.push_back(notes[i % notes.size()]);
            k++;
        }
        notes = new_notes;
    }
}
void rotate_left(std::string& notes) {
    if (notes.size() == 0) {
        throw std::string("rotate_left: notes has no values");
    }
    else {
    std::string new_notes = "";
        int k = 0;
        for (int i = notes.size() - 1; i < notes.size() + (notes.size() - 1); i++) {
            new_notes.push_back(notes[i % notes.size()]);
            k++;
        }
        notes = new_notes;
    }
}

std::string generate_chord(const char note, const std::string& type) {
    if (type != "power" && type != "major" && type != "minor" && type != "augmented" && type != "diminished") {
        throw std::string("generate_chord: Invalid type");
    }
    else if (type == "power") { // index 0 and index 7
        // make dictionary first note = first note
        int i = 0;
        while(note != notes_dictionary[0]) {
            if (i == 12) {
                throw std::string("generate_chord: invalid note");
                break;
            }
            rotate_right(notes_dictionary);
            i++;
        }
        std::string chord = std::string(1, notes_dictionary[0]) + std::string(1, notes_dictionary[7]) + std::string(1, notes_dictionary[0]) + std::string(1, notes_dictionary[7]);
        return chord;
    }
    else if (type == "major") {
        // make dictionary first note = first note
        int i = 0;
        while(note != notes_dictionary[0]) {
            if (i == 12) {
                throw std::string("generate_chord: invalid note");
                break;
            }
            rotate_right(notes_dictionary);
            i++;
        }
        std::string chord = std::string(1, notes_dictionary[0]) + std::string(1, notes_dictionary[4]) + std::string(1, notes_dictionary[7]) + std::string(1, notes_dictionary[11]);
        return chord;
    }
    else if (type == "minor") {
        // make dictionary first note = first note
        int i = 0;
        while(note != notes_dictionary[0]) {
            if (i == 12) {
                throw std::string("generate_chord: invalid note");
                break;
            }
            rotate_right(notes_dictionary);
            i++;
        }
        std::string chord = std::string(1, notes_dictionary[0]) + std::string(1, notes_dictionary[3]) + std::string(1, notes_dictionary[7]) + std::string(1, notes_dictionary[10]);
        return chord;
    }
    else if (type == "diminished") {
        // make dictionary first note = first note
        int i = 0;
        while(note != notes_dictionary[0]) {
            if (i == 12) {
                throw std::string("generate_chord: invalid note");
                break;
            }
            rotate_right(notes_dictionary);
            i++;
        }
        std::string chord = std::string(1, notes_dictionary[0]) + std::string(1, notes_dictionary[3]) + std::string(1, notes_dictionary[6]) + std::string(1, notes_dictionary[10]);
        return chord;
    }
    else if (type == "augmented") {
        // make dictionary first note = first note
        int i = 0;
        while(note != notes_dictionary[0]) {
            if (i == 12) {
                throw std::string("generate_chord: invalid note");
                break;
            }
            rotate_right(notes_dictionary);
            i++;
        }
        std::string chord = std::string(1, notes_dictionary[0]) + std::string(1, notes_dictionary[4]) + std::string(1, notes_dictionary[8]) + std::string(1, notes_dictionary[11]);
        return chord;
    }
    return std::string("gl");
}
std::string convert_notes(const std::string& notes) {
    std::string new_notes = "";
    for (int i = 0; i < notes.size(); i++) {
        switch(notes[i]) {
            case('h'):
                new_notes = new_notes + std::string("a#");
            break;
            case('i'):
                new_notes = new_notes + std::string("c#");
            break;
            case('j'):
                new_notes = new_notes + std::string("d#");
            break;
            case('k'):
                new_notes = new_notes + std::string("f#");
            break;
            case('l'):
                new_notes = new_notes + std::string("g#");
            break;
            default:
                new_notes = new_notes + notes[i];
            break;
        }
    }
    return new_notes;
}
// localize a staff to focus on a single string for guitar\
each string takes up 8 notes from octave to octave\
low  e string starts at "position 0"  - "position 7"  0\
     a string starts at "position 3"  - "position 10" 1\
     d string starts at "position 6"  - "position 13" 2\
     g string starts at "position 9"  - "position 16" 3\
     b string starts at "position 11" - "position 18" 4\
high e string starts at "position 14" - "position 21" 5
void generate_staff(std::string& notes, int position) {
    int *note_location = new int[notes.size()];
    int *sharp_location = new int[notes.size()];
    for (int i = 0; i < notes.size(); i++) {
        switch(notes[i]) {
            case('a'):
                switch(position) {
                    case(0):
                        note_location[i] = 4;
                        sharp_location[i] = -1;
                    break;
                    case(1):
                        if (rand() % 2 == 0) {
                            note_location[i] = 4;
                        }
                        else {
                            note_location[i] = 11;
                        }
                        sharp_location[i] = -1;
                    break;
                    case(2):
                        note_location[i] = 11;
                        sharp_location[i] = -1;
                    break;
                    case(3):
                        note_location[i] = 11;
                        sharp_location[i] = -1;
                    break;
                    case(4):
                        note_location[i] = 18;
                        sharp_location[i] = -1;
                    break;
                    case(5):
                        note_location[i] = 18;
                        sharp_location[i] = -1;
                    break;
                    default:
                        throw std::string("generate_staff: wrong position");
                    break;
                }
            break;
            case('h'): // a#/Bb
                switch(position) {
                    case(0):
                        note_location[i] = 4;
                        sharp_location[i] = 4;
                    break;
                    case(1):
                        if (rand() % 2 == 0) {
                            note_location[i] = 4;
                            sharp_location[i] = 4;
                        }
                        else {
                            note_location[i] = 11;
                            sharp_location[i] = 11;
                        }
                    break;
                    case(2):
                        note_location[i] = 11;
                        sharp_location[i] = 11;
                    break;
                    case(3):
                        note_location[i] = 11;
                        sharp_location[i] = 11;
                    break;
                    case(4):
                        note_location[i] = 18;
                        sharp_location[i] = 18;
                    break;
                    case(5):
                        note_location[i] = 18;
                        sharp_location[i] = 18;
                    break;
                    default:
                        throw std::string("generate_staff: wrong position");
                    break;
                }
            break;
            case('b'):
                switch(position) {
                    case(0):
                        note_location[i] = 5;
                        sharp_location[i] = -1;
                    break;
                    case(1):
                        note_location[i] = 5;
                        sharp_location[i] = -1;
                    break;
                    case(2):
                        note_location[i] = 12;
                        sharp_location[i] = -1;
                    break;
                    case(3):
                        note_location[i] = 12;
                        sharp_location[i] = -1;
                    break;
                    case(4):
                        if (rand() % 2 == 0) {
                            note_location[i] = 12;
                        }
                        else {
                            note_location[i] = 19;
                        }
                        sharp_location[i] = -1;
                    break;
                    case(5):
                        note_location[i] = 19;
                        sharp_location[i] = -1;
                    break;
                    default:
                        throw std::string("generate_staff: wrong position");
                    break;
                }
            break;
            case('c'):
                switch(position) {
                    case(0):
                        note_location[i] = 6;
                        sharp_location[i] = -1;
                    break;
                    case(1):
                        note_location[i] = 6;
                        sharp_location[i] = -1;
                    break;
                    case(2):
                        note_location[i] = 13;
                        sharp_location[i] = -1;
                    break;
                    case(3):
                        note_location[i] = 13;
                        sharp_location[i] = -1;
                    break;
                    case(4):
                        note_location[i] = 13;
                        sharp_location[i] = -1;
                    break;
                    case(5):
                        note_location[i] = 20;
                        sharp_location[i] = -1;
                    break;
                    default:
                        throw std::string("generate_staff: wrong position");
                    break;
                }
            break;
            case('i'): // c#/Db
                switch(position) {
                    case(0):
                        note_location[i] = 6;
                        sharp_location[i] = 6;
                    break;
                    case(1):
                        note_location[i] = 6;
                        sharp_location[i] = 6;
                    break;
                    case(2):
                        note_location[i] = 13;
                        sharp_location[i] = 13;
                    break;
                    case(3):
                        note_location[i] = 13;
                        sharp_location[i] = 13;
                    break;
                    case(4):
                        note_location[i] = 13;
                        sharp_location[i] = 13;
                    break;
                    case(5):
                        note_location[i] = 20;
                        sharp_location[i] = 20;
                    break;
                    default:
                        throw std::string("generate_staff: wrong position");
                    break;
                }
            break;
            case('d'):
                switch(position) {
                    case(0):
                        note_location[i] = 7;
                        sharp_location[i] = -1;
                    break;
                    case(1):
                        note_location[i] = 7;
                        sharp_location[i] = -1;
                    break;
                    case(2):
                        if (rand() % 2 == 0) {
                            note_location[i] = 7;
                        }
                        else {
                            note_location[i] = 14;
                        }
                        sharp_location[i] = -1;
                    break;
                    case(3):
                        note_location[i] = 14;
                        sharp_location[i] = -1;
                    break;
                    case(4):
                        note_location[i] = 14;
                        sharp_location[i] = -1;
                    break;
                    case(5):
                        note_location[i] = 21;
                        sharp_location[i] = -1;
                    break;
                    default:
                        throw std::string("generate_staff: wrong position");
                    break;
                }
            break;
            case('j'): // d#/Eb
                switch(position) {
                    case(0):
                        note_location[i] = 7;
                        sharp_location[i] = 7;
                    break;
                    case(1):
                        note_location[i] = 7;
                        sharp_location[i] = 7;
                    break;
                    case(2):
                        if (rand() % 2 == 0) {
                            note_location[i] = 7;
                            sharp_location[i] = 7;
                        }
                        else {
                            note_location[i] = 14;
                            sharp_location[i] = 14;
                        }
                    break;
                    case(3):
                        note_location[i] = 14;
                        sharp_location[i] = 14;
                    break;
                    case(4):
                        note_location[i] = 14;
                        sharp_location[i] = 14;
                    break;
                    case(5):
                        note_location[i] = 21;
                        sharp_location[i] = 21;
                    break;
                    default:
                        throw std::string("generate_staff: wrong position");
                    break;
                }
            break;
            case('e'):
                switch(position) {
                    case(0):
                        if (rand() % 2 == 0) {
                            note_location[i] = 8;
                        }
                        else {
                            note_location[i] = 1;
                        }
                        sharp_location[i] = -1;
                    break;
                    case(1):
                        note_location[i] = 8;
                        sharp_location[i] = -1;
                    break;
                    case(2):
                        note_location[i] = 8;
                        sharp_location[i] = -1;
                    break;
                    case(3):
                        note_location[i] = 15;
                        sharp_location[i] = -1;
                    break;
                    case(4):
                        note_location[i] = 15;
                        sharp_location[i] = -1;
                    break;
                    case(5):
                        if (rand() % 2 == 0) {
                            note_location[i] = 15;
                        }
                        else {
                            note_location[i] = 22;
                        }
                        sharp_location[i] = -1;
                    break;
                    default:
                        throw std::string("generate_staff: wrong position");
                    break;
                }
            break;
            case('f'):
                switch(position) {
                    case(0):
                        note_location[i] = 2;
                        sharp_location[i] = -1;
                    break;
                    case(1):
                        note_location[i] = 9;
                        sharp_location[i] = -1;
                    break;
                    case(2):
                        note_location[i] = 9;
                        sharp_location[i] = -1;
                    break;
                    case(3):
                        note_location[i] = 16;
                        sharp_location[i] = -1;
                    break;
                    case(4):
                        note_location[i] = 16;
                        sharp_location[i] = -1;
                    break;
                    case(5):
                        note_location[i] = 16;
                        sharp_location[i] = -1;
                    break;
                    default:
                        throw std::string("generate_staff: wrong position");
                    break;
                }
            break;
            case('k'): // f#/Gb
                switch(position) {
                    case(0):
                        note_location[i] = 2;
                        sharp_location[i] = 2;
                    break;
                    case(1):
                        note_location[i] = 9;
                        sharp_location[i] = 9;
                    break;
                    case(2):
                        note_location[i] = 9;
                        sharp_location[i] = 9;
                    break;
                    case(3):
                        note_location[i] = 16;
                        sharp_location[i] = 16;
                    break;
                    case(4):
                        note_location[i] = 16;
                        sharp_location[i] = 16;
                    break;
                    case(5):
                        note_location[i] = 16;
                        sharp_location[i] = 16;
                    break;
                    default:
                        throw std::string("generate_staff: wrong position");
                    break;
                }
            break;
            case('g'):
                switch(position) {
                    case(0):
                        note_location[i] = 3;
                        sharp_location[i] = -1;
                    break;
                    case(1):
                        note_location[i] = 10;
                        sharp_location[i] = -1;
                    break;
                    case(2):
                        note_location[i] = 10;
                        sharp_location[i] = -1;
                    break;
                    case(3):
                        if (rand() % 2 == 0) {
                            note_location[i] = 10;
                        }
                        else {
                            note_location[i] = 17;
                        }
                        sharp_location[i] = -1;
                    break;
                    case(4):
                        note_location[i] = 17;
                        sharp_location[i] = -1;
                    break;
                    case(5):
                        note_location[i] = 17;
                        sharp_location[i] = -1;
                    break;
                    default:
                        throw std::string("generate_staff: wrong position");
                    break;
                }
            break;
            case('l'): // g#/Ab
                switch(position) {
                    case(0):
                        note_location[i] = 3;
                        sharp_location[i] = 3;
                    break;
                    case(1):
                        note_location[i] = 10;
                        sharp_location[i] = 10;
                    break;
                    case(2):
                        note_location[i] = 10;
                        sharp_location[i] = 10;
                    break;
                    case(3):
                        if (rand() % 2 == 0) {
                            note_location[i] = 10;
                            sharp_location[i] = 10;
                        }
                        else {
                            note_location[i] = 17;
                            sharp_location[i] = 17;
                        }
                    break;
                    case(4):
                        note_location[i] = 17;
                        sharp_location[i] = 17;
                    break;
                    case(5):
                        note_location[i] = 17;
                        sharp_location[i] = 17;
                    break;
                    default:
                        throw std::string("generate_staff: wrong position");
                    break;
                }
            break;
            default:
                throw std::string("generate_staff: invalid note");
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
            else if (level == note_location[j] && sharp_location[j] == note_location[j] && level % 2 == 0 && level >= 8 && level <= 16) {
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
            else if (level == note_location[j] && level % 2 == 0 && level >= 8 && level <= 16){
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

