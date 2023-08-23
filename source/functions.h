#include <string>
#include <iostream>
#include <fstream>

void sendError (std::string message);
std::string getCellStr (std::istream& file, char delim);
int getCellInt (std::istream& file, char delim);