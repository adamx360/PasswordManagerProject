#include <string>
#include <ostream>
#include <utility>
#include "Category.h"

class Password {
public:
    std::string label;          //Nazwa
    std::string password;       //Hasło
    Category category;          //Kategoria
    std::string website;        //Strona internetowa
    std::string login;          //Login

    Password(std::string label, std::string password, const Category &category, std::string website, std::string login);

    friend std::ostream &operator<<(std::ostream &os, const Password &password);
};