#include <iostream>
#include <string>

#include "file_util.hh"
#include "XmlElement.hh"

/* First version - file_util demo - write/read files before working with XML */

int main() {

    XmlElement testEl;

    testEl.setName("TestEl");
    testEl.setAttribute("lol", "thing");
    testEl.setAttribute("attr2", "thing2");
    
    testEl.pushBackChild((XmlElement){"NestEl", true});
    testEl.pushBackChild((XmlElement){"EllyMent"});
    std::cout << "The element is:" << std::endl << testEl.print() << std::endl;

    std::cout << "Changing-" << std::endl;

    testEl.getChild(0).setName("ZerothElement");
    testEl.getChild(1).setAttribute("elly", "ment");
    testEl.getChild(1).pushBackChild((XmlElement){"Nestie"});

    std::cout << "The element is:" << std::endl << testEl.print() << std::endl;

    return 0;
}