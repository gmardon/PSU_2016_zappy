#include "error.h"

Error::Error(const std::string &message, const std::string &indicator) noexcept : _message(message), _indicator(indicator)
{
}

const char *Error::what() const noexcept
{
    return (this->_message.c_str());
}

std::string const &Error::getIndicator() const noexcept
{
    return (this->_indicator);
}
