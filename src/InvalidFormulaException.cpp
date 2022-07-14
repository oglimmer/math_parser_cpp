
#include "InvalidFormulaException.hpp"

InvalidFormulaException::InvalidFormulaException(const std::string &message) : message_(message) {
}

const char *InvalidFormulaException::what() const noexcept {
    return message_.c_str();
}

std::ostream &InvalidFormulaException::operator<<(std::ostream &os) const {
    os << message_;
    return os;
}

