#include "ObjectOperations.h"

void ObjectOperations::generatePassword(std::string &password, int size, int upper, int spec) {
    std::string allCharacters;
    srand(time(nullptr));
    for (char i = 'a'; i <= 'z'; i++) {
        allCharacters += i;
    }
    if (upper == 1) {
        for (char i = 'A'; i <= 'Z'; i++) {
            allCharacters += i;
        }
    }
    if (spec == 1) {
        allCharacters += "1234567890!@#$%^&*()_-+={[}]:;|\\<,>.?/~`'\"";
    }
    for (int i = 0; i < size; i++) {
        password += allCharacters.at(rand() % allCharacters.length());
    }
}

void ObjectOperations::getValue(int &val, int min, int max) {
    std::cout << "Wybierz liczbę: ";
    while (!(std::cin >> val) || !(val >= min && val <= max)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Podana wartość nie jest prawidłowa. Wybierz liczbę pomiędzy " << min << "-" << max << ": " << std::endl;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void ObjectOperations::chooseFunction(std::vector<Password> &passwd, std::vector<Category> &cat) {
    int selectNum = -1;
    while (selectNum != 0) {
        std::cout << "\n1.Wyszukaj hasła;"
                "\n2.Posortuj hasła;"
                "\n3.Dodaj hasło;"
                "\n4.Edytuj hasło;"
                "\n5.Usuń hasło;"
                "\n6.Dodaj kategorię;"
                "\n7.Usuń kategorię."
                "\n0.Zamknij program;" << std::endl;
        getValue(selectNum, 0, 7);
        switch (selectNum) {
            case 1:
                ObjectOperations::wyszukajHasla(passwd);
                break;
            case 2:
                ObjectOperations::posortujHasla(passwd);
                break;
            case 3:
                ObjectOperations::dodajHaslo(passwd, cat);
                break;
            case 4:
                ObjectOperations::edytujHaslo(passwd, cat);
                break;
            case 5:
                ObjectOperations::usunHaslo(passwd);
                break;
            case 6:
                ObjectOperations::dodajKategorie(cat);
                break;
            case 7:
                ObjectOperations::usunKategorie(cat, passwd);
                break;
            default:
                break;
        }
    }
}

void ObjectOperations::wyszukajHasla(std::vector<Password> &passwd) {
    std::cout << "\nWyszukaj według:"
            "\n1.Nazwy;"
            "\n2.Hasła;"
            "\n3.Kategorii;"
            "\n4.Strony internetowej;"
            "\n5.Loginu;"
            "\n0.Anuluj" << std::endl;
    int parChoice = -1;
    getValue(parChoice, 0, 5);
    if (parChoice == 0) {
        return;
    }
    std::vector<Password> found;
    std::string search;
    std::cout << "Wyszukaj:" << std::endl;
    getline(std::cin, search);
    switch (parChoice) {
        case 1:
            for (Password &pass: passwd) {
                if (pass.label.find(search) != std::string::npos) {
                    found.push_back(pass);
                }
            }
            break;
        case 2:
            for (Password &pass: passwd) {
                if (pass.password.find(search) != std::string::npos) {
                    found.push_back(pass);
                }
            }
            break;
        case 3:
            for (Password &pass: passwd) {
                if (pass.category.name.find(search) != std::string::npos) {
                    found.push_back(pass);
                }
            }
            break;
        case 4:
            for (Password &pass: passwd) {
                if (pass.website.find(search) != std::string::npos) {
                    found.push_back(pass);
                }
            }
            break;
        case 5:
            for (Password &pass: passwd) {
                if (pass.login.find(search) != std::string::npos) {
                    found.push_back(pass);
                }
            }
            break;
        default:
            return;
    }
    if (found.empty() && parChoice != 0) {
        std::cout << "Nie znaleziono hasła z podanym argumentem" << std::endl;
    } else {
        for (const Password &pass: found) {
            std::cout << pass << std::endl;
        }
    }
}

void ObjectOperations::posortujHasla(std::vector<Password> &passwd) {
    std::string parameters;
    std::string options[] = {"Nazwy;", "Hasła;", "Kategorii;", "Strony internetowej;", "Loginu;",};
    while (parameters.find('6') == std::string::npos) {
        std::cout << "\nSortuj według:" << std::endl;
        for (int i = 0; i < size(options); i++) {
            if (parameters.find(std::to_string(i + 1)) == std::string::npos)
                std::cout << i + 1 << ". " << options[i] << std::endl;
        }
        std::cout << "6.Zatwierdź"
                "\n0.Anuluj" << std::endl;
        int par = -1;
        getValue(par, 0, 6);
        bool longEnough = (parameters.length() >= 2);
        if (parameters.find(std::to_string(par))==std::string::npos && par != 6) {
            parameters.append(std::to_string(par));
        }
        if (par == 6 && !longEnough) {
            std::cout << "Wybierz conajmniej 2 kategorie" << std::endl;
        }
        if (par == 6 && longEnough) {
            parameters.append(std::to_string(par));
            break;
        }
        if (par == 0) {
            return;
        }
    }
    sort(passwd.begin(), passwd.end(), [&parameters](const Password &x, const Password &y) {
        bool check[] = {(x.label < y.label), (x.password < y.password), (x.category < y.category),
                        (x.website < y.website), (x.login < y.login)};
        bool equal[] = {(x.label == y.label), (x.password == y.password), (x.category == y.category),
                        (x.website == y.website), (x.login == y.login)};
        for (char c: parameters) {
            int index = c - '1';
            if (!equal[index])
                return check[index];
        }
        return false;
    });

    for (const Password &pass: passwd) {
        std::cout << pass << std::endl;
    }
}

void ObjectOperations::dodajHaslo(std::vector<Password> &passwd, std::vector<Category> &cat) {
    std::string label;
    std::cout << "Podaj nazwę: " << std::endl;
    getline(std::cin,label);

    std::string password;
    std::cout << "1.Podaj hasło\n"
            "2.Generuj hasło automatycznie" << std::endl;
    int generateChoice;
    int size;
    int upper;
    int spec;
    int acceptChoice = 0;
    getValue(generateChoice, 1, 2);
    switch (generateChoice) {
        case 1:
            std::cin >> password;
        case 2:
            std::cout << "1.Podaj ilość znaków z których ma składać się hasło:" << std::endl;
            std::cin >> size;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "2.Czy hasło ma zawierać wielkie i małe litery?\n"
                    "     1. Tak\n"
                    "     2. Nie" << std::endl;
            getValue(upper, 1, 2);
            std::cout << "3.Czy hasło ma zawierać znaki specjalne?\n"
                    "     1.Tak\n"
                    "     2.Nie" << std::endl;
            getValue(spec, 1, 2);
            while (acceptChoice != 1) {
                generatePassword(password, size, upper, spec);
                std::cout << "Wygenerowane hasło to: " << password << std::endl << "1. Zatwierdź hasło\n"
                                                                         "2. Wygeneruj nowe" << std::endl;
                getValue(acceptChoice, 1, 2);
            }
        default:
            break;
    }

    Category category;
    std::cout << "Wybierz kategorie: " << std::endl;
    int i = 1;
    for (const Category &category1: cat) {
        std::cout << i << ": " << category1 << std::endl;
        i++;
    }
    int j;
    getValue(j, 1, (int) cat.size());
    for (const Category &category1: cat) {
        if (i == j) {
            category = category1;
        }
        i++;
    }

    std::string website;
    std::cout << "Podaj link do strony(opcjonalne): " << std::endl;
    getline(std::cin, website);

    std::string login;
    std::cout << "Podaj login(opcjonalne): " << std::endl;
    getline(std::cin, login);

    Password password1(label, password, category, website, login);
    passwd.push_back(password1);

}

void ObjectOperations::edytujHaslo(std::vector<Password> &passwd, std::vector<Category> &cat) {
    std::cout << "Wybierz hasło do edycji: " << std::endl;
    int passIndex = 1;
    for (const Password &password: passwd) {
        std::cout << passIndex << ": " << password << std::endl;
        passIndex++;
    }
    int passChoice;
    getValue(passChoice, 1, (int) passwd.size());
    passIndex = 1;
    for (Password &password: passwd) {
        if (passIndex == passChoice) {
            std::cout << "Wybierz co chcesz edytować: "
                    "\n1.Nazwę;"
                    "\n2.Hasło;"
                    "\n3.Kategorię"
                    "\n4.Stronę internetową"
                    "\n5.Login;"
                    "\n0.Anuluj" << std::endl;
            int parChoice;
            int catIndex = 1;
            int catChoice = 1;
            getValue(parChoice, 0, 5);
            switch (parChoice) {
                case 1:
                    std::cout << "Podaj nową nazwę: " << std::endl;
                    getline(std::cin, password.label);
                    break;
                case 2:
                    std::cout << "Podaj nowe hasło: " << std::endl;
                    getline(std::cin, password.password);
                    break;
                case 3:
                    std::cout << "Wybierz kategorie: " << std::endl;
                    for (const Category &category1: cat) {
                        std::cout << catIndex << ": " << category1 << std::endl;
                        catIndex++;
                    }
                    catIndex = 1;
                    getValue(catChoice, 1, (int) cat.size());
                    for (const Category &category1: cat) {
                        if (catIndex == catChoice) {
                            password.category = category1;
                        }
                        catIndex++;
                    }
                    break;
                case 4:
                    std::cout << "Podaj nowy link do strony: " << std::endl;
                    getline(std::cin, password.website);
                    break;
                case 5:
                    std::cout << "Podaj nowy login: " << std::endl;
                    getline(std::cin, password.login);
                    break;
                default:
                    break;
            }
        }
        passIndex++;
    }
}

void ObjectOperations::usunHaslo(std::vector<Password> &passwd) {
    std::cout << "Wybierz hasło do usunięcia: " << std::endl;
    int index = 1;
    for (const Password &password: passwd) {
        std::cout << index << ": " << password << std::endl;
        index++;
    }
    int choice;
    getValue(choice, 1, (int) passwd.size());
    index = 1;
    for (auto it = passwd.begin(); it != passwd.end();) {
        if (index == choice) {
            passwd.erase(it);
        } else it++;
        index++;
    }
}

void ObjectOperations::dodajKategorie(std::vector<Category> &cat) {
    bool unique = true;
    std::string categoryName;
    std::cout << "Podaj nazwę kategorii:" << std::endl;
    std::cin >> categoryName;
    for (const Category &category: cat) {
        if (categoryName == category.name) {
            unique = false;
            std::cout << "Podana kategoria istnieje." << std::endl;
        }
    }
    while (!unique) {
        std::cout << "Podaj nazwę kategorii:" << std::endl;
        std::cin >> categoryName;
        for (const Category &category: cat) {
            if (categoryName == category.name) {
                unique = false;
                std::cout << "Podana kategoria istnieje." << std::endl;
            }
        }
    }
    Category category(categoryName);
    cat.push_back(category);
}

void ObjectOperations::usunKategorie(std::vector<Category> &cat, std::vector<Password> &passwd) {
    std::cout << "Wybierz kategorie do usunięcia: " << std::endl;
    int index = 1;
    for (const Category &category: cat) {
        std::cout << index << ": " << category << std::endl;
        index++;
    }
    int choice;
    getValue(choice, 1, (int) cat.size());
    index = 1;
    for (auto kategoria = cat.begin(); kategoria != cat.end();) {
        if (index == choice) {
            for (auto haslo = passwd.begin(); haslo != passwd.end();) {
                if (kategoria->name == haslo->category.name) {
                    passwd.erase(haslo);
                } else haslo++;
            }
            cat.erase(kategoria);
        } else kategoria++;
        index++;
    }
}