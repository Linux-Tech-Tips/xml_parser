# C++ XML Parser

A simple XML Parser for C++, with XML file saving/loading.

Mostly created as a project to practice C++ on. Also first bigger C++ project, so I'm still learning as I go basically. 
Please excuse some possibly inadequate code in the past commits. If anyone asks, it's called *Agile Development*.

The directory structure is as follows:
 - src         ... main source files directory
   - parser    ... the whole XML parser
     - XML     ... only the XML object structure
       - DTD   ... only the DTD portion of the XML object structure

Along with the parser, the folder 'src' also contains main.cc, which includes a compilable demonstration program. 
This serves mostly as a demonstration of the capabilities of the XML parser. 
It is basically a very bare-bones version of a command-line tool through which a user can edit XML files interactively 
(without a text editor).

A finished version of the program, consisting of the command-line demo tool making use of the parser, can be compiled using 'make all' or 'make run'.

Documentation is written using doxygen, and can be generated using 'make doc'.

The Makefile is a preset (also written by me), which can be found on [this page](https://github.com/Linux-Tech-Tips/Makefile_preset.git).
