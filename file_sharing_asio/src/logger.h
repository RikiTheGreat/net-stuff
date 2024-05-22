#ifndef LOGGER_H
#define LOGGER_H

#include <source_location>
#include <string_view>
#include <iostream>

inline void log(const std::string_view message,
         const std::source_location location =
               std::source_location::current())
{
    std::clog << "file: "
              << location.file_name() << '('
              << location.line() << ':'
              << location.column() << ") `"
              << location.function_name() << "`: "
              << message << '\n';
}

#endif //LOGGER_H
