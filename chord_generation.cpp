#include <iostream>
#include <string>

void rotate_right(std::string& notes);
void rotate_left(std::string& notes);

std::string generate_chord(const char note, const std::string& type);
std::string convert_notes(const std::string& notes);

// h - l are sharps
static std::string notes_dictionary = "ahbcidjefkgl";

int main() {
    char note = 'h';
    try {
        std::cout << convert_notes(generate_chord(note, "minor"));
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
        std::cout << "power chord" << std::endl;
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
        std::string chord = std::string(1, notes_dictionary[0]) + std::string(1, notes_dictionary[7]);
        return chord;
    }
    else if (type == "major") {
        std::cout << "major chord" << std::endl;
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
        std::string chord = std::string(1, notes_dictionary[0]) + std::string(1, notes_dictionary[4]) + std::string(1, notes_dictionary[7]);
        return chord;
    }
    else if (type == "minor") {
        std::cout << "minor chord" << std::endl;
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
        std::string chord = std::string(1, notes_dictionary[0]) + std::string(1, notes_dictionary[3]) + std::string(1, notes_dictionary[7]);
        return chord;
    }
    else if (type == "diminished") {
        std::cout << "diminished chord" << std::endl;
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
        std::string chord = std::string(1, notes_dictionary[0]) + std::string(1, notes_dictionary[3]) + std::string(1, notes_dictionary[6]);
        return chord;
    }
    else if (type == "augmented") {
        std::cout << "augmented chord" << std::endl;
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
        std::string chord = std::string(1, notes_dictionary[0]) + std::string(1, notes_dictionary[4]) + std::string(1, notes_dictionary[8]);
        return chord;
    }
    return std::string("filler");
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
low  e string starts at "position 0"  - "position 7"\
     a string starts at "position 3"  - "position 10"\
     d string starts at "position 6"  - "position 13"\
     g string starts at "position 9"  - "position 16" \
     b string starts at "position 11" - "position 18"\
high e string starts at "position 14" - "position 21" 
