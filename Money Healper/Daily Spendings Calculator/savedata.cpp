#include <fstream>
#include <iostream>
#include <filesystem>

#include "savedata.h"

struct CurrentData {
    double Income;
};

bool Data::CheckData() {
    std::string SaveDataFolderPath = "C:\\ProgramData\\MoneyHelper";
    int Outcome = std::filesystem::create_directories(SaveDataFolderPath);

    if (Outcome == 1) {
        return true;
    }
    else {
        return false;
    }
}

bool Data::WriteData(auto DataToWrite, int LineNumber) {

}