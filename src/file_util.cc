#include "file_util.hh"

void file_writeString(char const * fileName, std::string const * fileData) {
    /* Writing to output file stream */
    std::ofstream f(fileName);
    f.write(fileData->c_str(), fileData->length());
    f.close();
}

std::string file_readString(char const * fileName) {
    /* Reading from input file stream into intermediary buffer */
    std::ifstream f(fileName);
    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}