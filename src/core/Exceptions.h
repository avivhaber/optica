#include <string>

struct GeneralException : public std::exception {
  std::string msg;
  GeneralException(std::string msg) noexcept : msg(msg) {}
  char const* what() const noexcept override { return msg.c_str(); }
};
