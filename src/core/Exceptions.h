#include <string>

struct GeneralException : std::exception {
    std::string msg;
    GeneralException(std::string msg) noexcept;
    char const* what() const noexcept override;
};
