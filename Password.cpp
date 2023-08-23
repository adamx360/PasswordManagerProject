#include "Password.h"

Password::Password(std::string label, std::string password, const Category &category, std::string website, std::string login) {
    this->label = std::move(label);
    this->password = std::move(password);
    this->category = category;
    this->website = std::move(website);
    this->login = std::move(login);
}

std::ostream &operator<<(std::ostream &os, const Password &password) {
    os << "Nazwa: " << password.label << " Hasło: " << password.password << " Kategoria: " << password.category
       << " Strona: " << password.website << " Login: " << password.login;
    return os;
}