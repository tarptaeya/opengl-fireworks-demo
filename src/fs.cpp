#include "fs.h"

namespace fs
{
    std::string read(const std::string &path)
    {
        std::ifstream file(path);
        std::stringstream stream;
        stream << file.rdbuf();
        return stream.str();
    }
}