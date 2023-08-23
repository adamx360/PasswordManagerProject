#include "FileOperations.h"
#include <ctime>

void FileOperations::timeDelete(std::string &line){
    std::string newLine;
    int index=0;
    for (char c:line) {
        if(index>1){
            newLine+=c;
        }
        index++;
    }
    line=newLine;
}

std::string FileOperations::cypher(const std::string &text, const std::string &pass) {
    int passValue = 0;
    std::string cypheredText;
    const std::string WHITESPACE = " \n\r\t\f\v";
    for (char c: pass) {
        passValue += c;
    }
    for (char c: text) {
        if(WHITESPACE.find(c)==std::string::npos)
            c += passValue % 5 + 1;
        cypheredText += c;
    }
    return cypheredText;
}

std::string FileOperations::decypher(const std::string &text, const std::string &pass, std::string timeStr[]) {
    int passValue = 0;
    time_t t = time(nullptr);
    tm *now = localtime(&t);
    timeStr[0] = std::to_string(now->tm_hour);
    timeStr[1] = std::to_string(now->tm_min);
    timeStr[2] = std::to_string(now->tm_sec);
    const std::string WHITESPACE = " \n\r\t\f\v";
    std::string decypheredText;
    for (char c: pass) {
        passValue += c;
    }
    for (char c: text) {
        if(WHITESPACE.find(c)==std::string::npos)
            c -= passValue % 5 + 1;
        decypheredText += c;
    }
    std::cout << decypheredText << std::endl;
    return decypheredText;
}

std::string FileOperations::getPath() {
    std::string fileName;
    std::cout << "Wybierz sposób wyszukania pliku\n"
                 "1. Podaj nazwę pliku z folderu\n"
                 "2. Podaj ścieżkę do pliku\n";
    int tmp;
    ObjectOperations::getValue(tmp, 1, 2);
    switch (tmp) {
        case 1:
            std::cout << "Podaj nazwę\n";
            std::cin >> fileName;
            fileName = "../" + fileName + ".txt";
            return fileName;
        case 2:
            std::cout << "Podaj ścieżkę\n";
            std::cin >> fileName;
            if (fileName.find(".txt") == std::string::npos) {
                fileName += ".txt";
            }
            return fileName;
        default:
            break;
    }
    return fileName;
}

std::string FileOperations::fileOpen(std::string &filePath) {
    std::fstream file;
    file.open(filePath);
    while (!file.is_open()) {
        std::cout << "Podany plik nie istnieje.\n"
                     "1.Utwórz plik\n"
                     "2.Wyszukaj plik ponownie\n";
        int tmp;
        ObjectOperations::getValue(tmp, 1, 2);
        switch (tmp) {
            case 1:
                file.open(filePath, std::fstream::out);
                std::cout << "Plik utworzony" << std::endl;
                file.open(filePath);
                break;
            case 2:
                filePath = getPath();
                file.open(filePath);
                break;
            default:
                break;
        }
    }

    std::string text;
    std::string line;
    while (getline(file, line)) {
        text += line + "\n";
    }
    file.close();
    return text;
}

std::string FileOperations::getPass() {
    std::string pass;
    std::cout << "Podaj hasło" << std::endl;
    std::cin >> pass;
    return pass;
}

void FileOperations::stringToLineArray(std::string const &str, std::vector<std::string> &lines) {
    std::stringstream s(str);
    std::string s2;
    while (getline(s, s2)) {
        lines.push_back(s2);
    }
}

void FileOperations::lineToObject(const std::string &line, std::vector<Category> &cat, std::vector<Password> &passwd) {
    std::vector<std::string> parameters;
    std::stringstream s(line);
    std::string s2;
    while (getline(s, s2, '|')) {
        parameters.push_back(s2);
    }
    std::string pass[5];
    int index = 0;
    for (const std::string &st: parameters) {
        pass[index] = st;
        index++;
    }
    Category category(pass[2]);
    Password password(pass[0], pass[1], category, pass[3], pass[4]);
    cat.push_back(category);
    passwd.push_back(password);
}

void FileOperations::objectToText(std::string &text, std::vector<Password> &passwd, std::string &filePass,
                                  std::string time[]) {
    text = "";
    std::string line;
    int index = 0;
    for (const Password &pass: passwd) {
        line = pass.label + "|" + pass.password + "|" + pass.category.name + "|" + pass.website + "|" + pass.login;
        line = cypher(line, filePass);
        index++;
        switch (index) {
            case 1:
                line = ((time[0].length()>1) ? time[0]+line : std::to_string(0)+time[0]+line);
                break;
            case 2:
                line = ((time[1].length()>1) ? time[1]+line : std::to_string(0)+time[1]+line);
                break;
            case 3:
                line = ((time[2].length()>1) ? time[2]+line : std::to_string(0)+time[2]+line);
                break;
            default:
                break;
        }
        text += line + "\n";
    }
}

void FileOperations::fileSave(const std::string &text, const std::string &path) {
    std::fstream fileOut;
    fileOut.open(path, std::ios::out);
    if (fileOut.is_open()) {
        fileOut << text;
        fileOut.close();
    }
}