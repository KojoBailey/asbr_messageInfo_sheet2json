#include <iostream>

#include "json.h"

std::string jsonBrace (std::string contents, bool end) {
    std::string output = "{\n";
    char buffer;

    for (int i = 0; i < contents.size(); i++) {
        if ( i == 0 ) { output += "\t"; }
        buffer = contents.at(i);
        output += buffer;
        if (buffer == '\n' && i != contents.size() - 1) { output += "\t"; }
    }

    output += "}";
    if (!end) { output += ","; }
    output += "\n";
    return output;
}

std::string jsonBox (std::string contents) {
    std::string output = "[\n";
    char buffer;

    for (int i = 0; i < contents.size(); i++) {
        if ( i == 0 ) { output += "\t"; }
        buffer = contents.at(i);
        output += buffer;
        if (buffer == '\n' && i != contents.size() - 1) { output += "\t"; }
    }

    output += "],\n";
    return output;
}

std::string jsonLine (std::string name, std::string contents, bool end) {
    std::string output = "\"" + name + "\": \"" + contents + "\"";

    if (!end) { output += ","; }
    output += "\n";
    return output;
}

std::string jsonLine (std::string name, int contents, bool end) {
    std::string output = "\"" + name + "\": " + std::to_string(contents);

    if (!end) { output += ","; }
    output += "\n";
    return output;
}