#include <string>
#include <ostream>
#include <utility>

class Category {
public:
    std::string name;       //Nazwa kategorii

    explicit Category(std::string category);

    Category();

    bool operator<(const Category &rhs) const;

    bool operator>(const Category &rhs) const;

    bool operator<=(const Category &rhs) const;

    bool operator>=(const Category &rhs) const;

    bool operator==(const Category &rhs) const;

    bool operator!=(const Category &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Category &category);

};