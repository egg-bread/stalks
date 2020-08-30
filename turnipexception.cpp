#include "turnipexception.h"

TurnipException::TurnipException(std::string err) : err{move(err)} {}

const std::string& TurnipException::what() const
{
    return err;
}
