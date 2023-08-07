#include <iostream>
#include <string>

#include "file_util.hh"

/* First version - file_util demo - write/read files before working with XML */

int main() {

    std::cout << file_readString("README.md") << std::endl;

    std::string fileData = "TEST FILE DATA\n";
    file_writeString("test.txt", &fileData);

    return 0;
}