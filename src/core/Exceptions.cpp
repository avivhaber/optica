#include "Exceptions.h"

GeneralException::GeneralException(std::string msg) noexcept: msg(msg) {}

char const* GeneralException::what() const noexcept {
    return msg.c_str();
}
