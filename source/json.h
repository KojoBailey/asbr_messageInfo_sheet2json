#include <string>

std::string jsonBrace (std::string contents, bool end = 0);
std::string jsonBox (std::string contents);
std::string jsonLine (std::string name, std::string contents, bool end = 0);
std::string jsonLine (std::string name, int contents, bool end = 0);