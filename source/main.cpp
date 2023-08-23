// g++ main.cpp json.cpp functions.cpp -o ../mI_C.exe

#include <filesystem> // C++17
#include <vector>

#include "json.h"
#include "functions.h"

namespace fs = std::filesystem;

void settingsPrompt(std::istream& file, std::string file_extension, char delimiter, bool compare_text) {
    std::cout << "> The following settings can be changed in 'settings.cfg' or with the \"" << "\033[1;33m" << "/settings" << "\033[0m" << "\" command:\n";
    std::cout << "\t> File extension is set to '" << "\033[1;33m" << file_extension << "\033[0m" << "'. Formatting must be character-separated data (e.g. CSV or TBV).\n";
    std::cout << "\t> Delimiter is set to '" << "\033[1;33m" << delimiter << "\033[0m" << "'. Note that only single chars are allowed (e.g. '@').\n";
    std::cout << "\t> Comparison for 2 columns of text is set to '" << "\033[1;33m" << compare_text << "\033[0m" << "'.\n";
    std::cout << std::endl;

    std::string command;
    std::cin >> command;
    if (command == "/settings") {
        std::cout << "> Set file extension - include period (e.g. .tsv):\n";
        std::cin >> file_extension;
        std::cout << "> Set delimiter - single char only (e.g. @):\n";
        std::cin >> delimiter;
        std::cout << "> Compare 2 columns of text - 1 or 0 (true or false):\n";
        std::cin >> compare_text;

        std::remove("settings.cfg");
        std::ofstream file("settings.cfg");
        file << "file_extension=" << file_extension << std::endl;
        file << "delimiter=" << delimiter << std::endl;
        file << "compare_text=" << compare_text << std::endl;

        std::cout << "\t> File extension has been changed to '" << "\033[1;33m" << file_extension << "\033[0m" << "'.\n";
        std::cout << "\t> Delimiter has been changed to '" << "\033[1;33m" << delimiter << "\033[0m" << "'. Note that only single chars are allowed (e.g. '@').\n";
        std::cout << "\t> Comparison for 2 columns of text has been set to '" << "\033[1;33m" << compare_text << "\033[0m" << "'.\n";
    }
}

int main(int argc, char* argv[]) {
    bool error = false;

    std::string file_extension;
    char delimiter;
    bool compare_text;

    std::ifstream cfg("settings.cfg");
    std::cout << "> Reading configuration settings...\n\n";

    std::string cfg_buffer;
    while (cfg.peek()!=EOF) {
        cfg_buffer = getCellStr(cfg, '=');
        if (cfg_buffer == "file_extension") {
            file_extension = getCellStr(cfg, '\n');
        } else if (cfg_buffer == "delimiter") {
            delimiter = getCellStr(cfg, '\n').at(0);
        } else if (cfg_buffer == "compare_text") {
            compare_text = getCellInt(cfg, '\n');
        }
    }

    if (argc == 1) {
        sendError("To input a file, simply drag it onto this application.\n\n");
        error = true;
        settingsPrompt(cfg, file_extension, delimiter, compare_text);
    } else if (argc != 2) {
        sendError("Too many files! Only 1 file is accepted.\n\n");
        error = true;
        settingsPrompt(cfg, file_extension, delimiter, compare_text);
    }

    fs::path filePath = argv[1];
    std::ifstream sheet(filePath);
    if (!error) {
        if (!sheet.is_open()) {
            sendError("File '" + filePath.filename().generic_string() + "' failed to open\n\n");
            error = true;
        } else if (filePath.extension() != file_extension) {
            sendError("'settings.cfg' specifies the input of a '" + file_extension + "' file.\n\n");
            error = true;
        }
    }

    if (!error) {
        struct JSON {
            std::string crc32_id;
            int char_id;
            int cue_id;
            std::string dialogue;
        };
        std::vector<JSON> item;

        std::string temp_crc32;
        int temp_char;
        int temp_cue;
        std::string temp_dialogue;

        std::cout << "> Converting to 'messageInfo.bin' JSON...\n";

        sheet.seekg(0, sheet.beg);
        while (sheet.peek()!=EOF) {
            temp_crc32 = getCellStr(sheet, delimiter);
            temp_char = getCellInt(sheet, delimiter);
            temp_cue = getCellInt(sheet, delimiter);
            if (compare_text == 1) {
                temp_dialogue = getCellStr(sheet, delimiter);
                if (temp_dialogue == "empty_string") {
                    temp_dialogue = getCellStr(sheet, '\n');
                } else { getCellStr(sheet, '\n'); }
            } else {
                temp_dialogue = getCellStr(sheet, '\n');
            }
            item.push_back({temp_crc32, temp_char, temp_cue, temp_dialogue});
        }

        sheet.close();

        std::ofstream output("output.json");

        std::string mainData = "";
        std::string loopData;

        for (int i = 0; i < item.size(); i++) {
            loopData = "";
            loopData += jsonLine("msg_id_crc32", item[i].crc32_id);         // crc32 ID
            loopData += jsonLine("unk1", 0);
            loopData += jsonLine("unk2", 0);
            loopData += jsonLine("unk3", 0);
            loopData += jsonLine("unk4", 0);
            loopData += jsonLine("unk5", 0);
            loopData += jsonLine("unk6", -1);
            loopData += jsonLine("unk7", item[i].char_id);                  // character ID
            loopData += jsonLine("cue_id", item[i].cue_id);                 // ACB/AWB cue ID
            loopData += jsonLine("unk9", -1);
            loopData += jsonLine("unk10", 0);
            loopData += jsonLine("string", item[i].dialogue, true);         // the message itself

            if (i == item.size() - 1) {
                mainData += jsonBrace(loopData, true);
            } else {
                mainData += jsonBrace(loopData);
            }
        }

        std::string finalOutput = jsonBrace("\"unk0\": 1001,\n\"unk1\": 8,\n\"entries\": " + jsonBox(mainData) + "\"big_endian\": false\n", true);

        output << finalOutput;
        std::cout << "\033[32m" << "> Conversion complete! File has been output as 'output.json'.\n\n" << "\033[0m";
    }

    settingsPrompt(cfg, file_extension, delimiter, compare_text);
    system("pause");
}