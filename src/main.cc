#include <iostream>
#include <string>

#include "file_util.hh"
#include "Node.hh"
#include "XmlElement.hh"
#include "TextElement.hh"

/* First version - file_util demo - write/read files before working with XML */

int main() {

    XmlElement testEl;

    testEl.setName("TestEl");
    testEl.setAttribute("lol", "thing");
    testEl.setAttribute("attr2", "thing2");
    
    XmlElement nestEl("NestEl", false);
    XmlElement el2("EllyMent");
    testEl.pushBackChild(nestEl);
    testEl.pushBackChild(el2);
    std::cout << "The element is:" << std::endl << testEl.print() << std::endl;

    std::cout << "Changing-" << std::endl;

    testEl.getChild(0).setName("ZerothElement");
    static_cast<XmlElement &>(testEl.getChild(1)).setAttribute("elly", "ment");
    XmlElement el3("Nestie");
    static_cast<XmlElement &>(testEl.getChild(1)).pushBackChild(el3);

    TextElement tEl1("p", "This is a text paragraph");
    static_cast<XmlElement &>(testEl.getChild(1)).pushBackChild(tEl1);

    XmlElement tEl2("p", true);
    TextElement tmpT1("tmp", "This \"is\" a pretty cursed ", false, false);
    tEl2.pushBackChild(tmpT1);
    TextElement tmpT2("b", "XML", true, false);
    tEl2.pushBackChild(tmpT2);
    TextElement tmpT3("tmp", " Document, tbh <3", false, false);
    tEl2.pushBackChild(tmpT3);

    static_cast<XmlElement &>(testEl.getChild(1)).pushBackChild(tEl2);

    std::cout << "The element is:" << std::endl << testEl.print() << std::endl;

    return 0;
}