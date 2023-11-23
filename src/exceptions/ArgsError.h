#ifndef MB_TOG_PROGRAMMING_LANGUAGE_ARGSERROR_H
#define MB_TOG_PROGRAMMING_LANGUAGE_ARGSERROR_H

#include <iostream>

class ArgsError : public std::runtime_error {
    public:
    explicit ArgsError(int expected, int got)
    : std::runtime_error("Expected " + std::to_string(expected) + " input args but got " + std::to_string(got))
    {}

};


#endif //MB_TOG_PROGRAMMING_LANGUAGE_ARGSERROR_H
