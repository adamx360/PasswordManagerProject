#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include "Password.h"

class ObjectOperations {
public:
    /**             Funkcja generująca hasło
     *
     * @param password  Zmienna która ma zawierać hasło
     * @param size      Długość hasła
     * @param upper     Czy mają być wielkie litery
     * @param spec      Czy mają być znaki specjalne
     */
    static void generatePassword(std::string &password, int size, int upper, int spec);

    /**             Funkcja pobierająca cyfre w podanym zakresie od użytkownika
     *
     * @param val       Zmienna która ma być cyfrą
     * @param min       Minimalna cyfra
     * @param max       Maksymalna cyfra
     */
    static void getValue(int &val,int min, int max);

    /**             Funkcja wyboru funkcji operujących na hasłach
     *
     * @param passwd    Zmienna zawierająca wszystkie hasła
     * @param cat       Zmienna zawierająca wszystkie kategorie
     */
    static void chooseFunction(std::vector<Password> &passwd,std::vector<Category> &cat);

    /**             Funkcja wyszukująca hasła
     *
     * @param passwd    Zmienna zawierająca wszystkie hasła
     */
    static void wyszukajHasla(std::vector<Password> &passwd);

    /**             Funkcja sortująca hasła
     *
     * @param passwd    Zmienna zawierająca wszystkie hasła
     */
    static void posortujHasla(std::vector<Password> &passwd);

    /**             Funkcja dodająca nowe hasło
     *
     * @param passwd    Zmienna zawierająca wszystkie hasła
     * @param cat       Zmienna zawierająca wszystkie kategorie
     */
    static void dodajHaslo(std::vector<Password> &passwd,std::vector<Category> &cat);

    /**             Funkcja edytująca istniejące hasło
     *
     * @param passwd    Zmienna zawierająca wszystkie hasła
     * @param cat       Zmienna zawierająca wszystkie kategorie
     */
    static void edytujHaslo(std::vector<Password> &passwd,std::vector<Category> &cat);

    /**             Funkcja usuwająca hasło
     *
     * @param passwd    Zmienna zawierająca wszystkie hasła
     */
    static void usunHaslo(std::vector<Password> &passwd);

    /**             Funkcja dodająca nową kategorie
     *
     * @param cat       Zmienna zawierająca wszystkie kategorie
     */
    static void dodajKategorie(std::vector<Category> &cat);

    /**             Funkcja usuwająca kategorie
     *
     * @param cat       Zmienna zawierająca wszystkie kategorie
     * @param passwd    Zmienna zawierająca wszystkie hasła
     */
    static void usunKategorie(std::vector<Category> &cat,std::vector<Password> &passwd);
};