#include <iostream>
#include <string>

#include "file_util.hh"
#include "Node.hh"
#include "XmlElement.hh"
#include "TextElement.hh"

/* First version - file_util demo - write/read files before working with XML */

/* Temporary TODO Next: 
    - Add member functions to get child by name
    - Make an XML Document class, which can load and save XML Documents
*/

int main() {

    /* Demonstration code */

    /* First nodes */

    XmlElement rootEl;

    rootEl.setName("RootElement");
    rootEl.setAttribute("attr1", "first attribute");
    rootEl.setAttribute("attr2", "second attribute");
    
    XmlElement nestl("NestedElement1", false);
    XmlElement nest2("NestedElement2");
    rootEl.pushBackChild(nestl);
    rootEl.pushBackChild(nest2);

    /* Printing */
    std::cout << "1. The element is:" << std::endl << rootEl.print() << std::endl;

    /* Additional nodes */
    rootEl.getChild(0).setName("NestedElementZero");
    rootEl.getChild(1).setAttribute("internal_index", "1");
    XmlElement nest3("NestedElement3");
    static_cast<XmlElement &>(rootEl.getChild(1)).pushBackChild(nest3);

    /* Adding paragraphs */
    TextElement p1("p", "This is a text paragraph");
    static_cast<XmlElement &>(rootEl.getChild(1)).pushBackChild(p1);

    XmlElement p2("p", true);
    TextElement text1("text1", "This \"is\" a showcase of ", false, false);
    p2.pushBackChild(text1);
    TextElement text2("b", "HTML", true, false, false, true);
    p2.pushBackChild(text2);
    TextElement text3("text3", "-like paragraph capability (in addition to pure XML). <3", false, false);
    p2.pushBackChild(text3);

    static_cast<XmlElement &>(rootEl.getChild(1)).pushBackChild(p2);

    /* Printing again */
    std::cout << "2. The element is:" << std::endl << rootEl.print() << std::endl;

    return 0;
}