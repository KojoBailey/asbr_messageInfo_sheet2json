#include "functions.h"

void sendError (std::string message) {
    std::cout << "\033[31m" << "> ERROR: " << message << "\033[0m";
}

std::string getCellStr (std::istream& file, char delim) {
    std::string output = "";
    char p;

    if (file.peek() == delim) { file.ignore(); return "empty_string"; }

    while (file.peek() != delim && file.peek() != EOF) {
        file.get(p);
        output += p;
    }
    
    if (file.peek() != EOF) { file.ignore(); }
    return output;
}

int getCellInt (std::istream& file, char delim) {
    std::string output = "";
    char p;

    if (file.peek() == delim) { file.ignore(); return 0; }

    while (file.peek() != delim && file.peek() != EOF) {
        file.get(p);
        output += p;
    }

    if (file.peek() != EOF) { file.ignore(); }
    return stoi(output);
}