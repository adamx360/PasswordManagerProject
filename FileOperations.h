#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include "ObjectOperations.h"

class FileOperations {
public:
    /**             Funkcja szyfrująca podany tekst
     *
     * @param text  -   Tekst do zaszyfrowania
     * @param pass  -   Hasło do pliku
     * @return          Zaszyfrowany tekst
     */
    static std::string cypher(const std::string &text, const std::string &pass);

    /**             Funkcja rozszyfrowująca podany tekst
     *
     * @param text  -   Tekst do rozszyfrowania
     * @param pass  -   Hasło do pliku
     * @param time  -   Godzina o której próbowano rozszyfrować text
     * @return          Rozszyfrowany tekst
     */
    static std::string decypher(const std::string &text, const std::string &pass,std::string time[]);

    /**             Funkcja zwracająca ścieżkę do pliku
     *
     * @return          Ścieżka do pliku
     */
    static std::string getPath();

    /**             Funkcja otwierająca plik i zapisująca jego zawartość do zwracanej zmiennej
     *
     * @param filePath  Ścieżka do pliku
     * @return          Zawartość pliku
     */
    static std::string fileOpen(std::string &filePath);

    /**             Funkcja zwraca hasło do pliku
     *
     * @return          Hasło do pliku
     */
    static std::string getPass();

    /**             Funkcja przekształcająca tekst na linie
     *
     * @param str       Tekst do przekształcenia na linie
     * @param lines     Zmienna zawierająca wszystkie linie
     */
    static void stringToLineArray(const std::string &str, std::vector<std::string> &lines);

    /**             Funkcja przekształcająca linie na hasła
     *
     * @param line      Linia tekstu do przekształcenia na hasła
     * @param cat       Zmienna zawierająca wszystkie kategorie
     * @param passwd    Zmienna zawierająca wszystkie hasła
     */
    static void lineToObject(const std::string &line, std::vector<Category> &cat, std::vector<Password> &passwd);

    /**             Funkcja zmieniająca hasła na tekst
     *
     * @param text      Tekst który ma zawierać wszystkie hasła
     * @param passwd    Zmienna zawierająca wszystkie hasła
     * @param filePass  Hasło do pliku
     * @param time      Godzina ostatniej próby rozszyfrowania pliku
     */
    static void objectToText(std::string &text, std::vector<Password> &passwd, std::string &filePass, std::string time[]);

    /**             Funkcja zapisująca tekst do pliku
     *
     * @param text      Tekst zapisywany do pliku
     * @param path      Ścieżka/Nazwa pliku
     */
    static void fileSave(const std::string &text, const std::string &path);

    /**             Funkcja usuwająca "timestampy"
     *
     * @param line      Linia tekstu
     */
    static void timeDelete(std::string &line);
};