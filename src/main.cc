#include <iostream>
#include <string>

#include "file_util.hh"

/* First version - file_util demo - write/read files before working with XML */

int main() {

    std::cout << file_readString("README.md") << std::endl;

    file_writeString("test.txt", "TEST FILE DATA\n");

    return 0;
}