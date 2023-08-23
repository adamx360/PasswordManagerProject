#include <vector>
#include <string>
#include "FileOperations.h"

int main() {
    std::string path = FileOperations::getPath();           //Ścieżka do pliku
    std::string text = FileOperations::fileOpen(path);  //Zawartość pliku
    std::string passToFile=FileOperations::getPass();       //Hasło do pliku
    std::string timeStr[3];                 //Godzina ostatniej próby rozszyfrowania pliku
    text = FileOperations::decypher(text, passToFile, timeStr);
    std::vector<std::string> lines;         //Zmienna zawierająca wszystkie linie z pliku
    std::vector<Password> passwd;           //Zmienna zawierająca wszystkie hasła
    std::vector<Category> cat;              //Zmienna zawierająca wszystkie kategorie
    FileOperations::stringToLineArray(text, lines);
    int index=0;
    for (std::string& s:lines) {
        if(index<3) {
            FileOperations::timeDelete(s);
        }
        index++;
        FileOperations::lineToObject(s,cat,passwd);
    }
    ObjectOperations::chooseFunction(passwd, cat);
    FileOperations::objectToText(text,passwd,passToFile, timeStr);
    FileOperations::fileSave(text,path);
}