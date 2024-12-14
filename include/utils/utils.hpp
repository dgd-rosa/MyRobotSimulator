#include <sstream>

#ifndef UTILS_HPP
#define UTILS_HPP

class Utils
{
    public:
        template <typename T>
        static std::string to_string_with_precision(const T a_value, const int n)
        {
            std::ostringstream out;
            out.precision(n);
            out << std::fixed << a_value;
            return std::move(out).str();
        }

    Utils() = delete;
};

#endif