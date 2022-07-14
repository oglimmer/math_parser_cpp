
#pragma once

#include <exception>
#include <string>

class InvalidFormulaException : public std::exception {
private:
    std::string message_;
public:
    explicit InvalidFormulaException(const std::string &message);

    const char *what() const noexcept override;

    std::ostream &operator<<(std::ostream &os) const;
};

