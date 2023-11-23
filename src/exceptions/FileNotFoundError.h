#ifndef MB_TOG_PROGRAMMING_LANGUAGE_FILENOTFOUNDERROR_H
#define MB_TOG_PROGRAMMING_LANGUAGE_FILENOTFOUNDERROR_H

#include <iostream>

class FileNotFoundError : public std::runtime_error {
public:
    explicit FileNotFoundError(const std::string &filename)
    : std::runtime_error("Unable to find file with filename: " + filename)
    {}

};

#endif //MB_TOG_PROGRAMMING_LANGUAGE_FILENOTFOUNDERROR_H
