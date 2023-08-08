/**
 * @file file_util.hh
 * @author Linux-Tech-Tips
 * @brief Very simple utility functions for easier file saving and loading
 *
 * Contains functions which simplify the process of saving and loading @ref std::string variables to and from files.
 */

#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/** Writes a string into a file */
void file_writeString(char const * fileName, std::string const & fileData);

/** Returns a string read from a file */
std::string file_readString(char const * fileName);

#endif /* FILE_UTIL_H */