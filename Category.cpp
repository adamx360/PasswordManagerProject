#include "Category.h"

Category::Category(std::string category) {
    this->name=std::move(category);
}

bool Category::operator==(const Category &rhs) const {
    return name == rhs.name;
}

bool Category::operator!=(const Category &rhs) const {
    return !(rhs == *this);
}

bool Category::operator<(const Category &rhs) const {
    return name < rhs.name;
}

bool Category::operator>(const Category &rhs) const {
    return rhs < *this;
}

bool Category::operator<=(const Category &rhs) const {
    return !(rhs < *this);
}

bool Category::operator>=(const Category &rhs) const {
    return !(*this < rhs);
}

Category::Category() = default;

std::ostream &operator<<(std::ostream &os, const Category &category) {
    os << category.name;
    return os;
}