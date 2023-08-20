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
    
    rootEl.pushBackChild(XmlElement("NestedElement1", false));
    rootEl.pushBackChild(XmlElement("NestedElement2"));

    /* Printing */
    std::cout << "1. The element is:" << std::endl << rootEl.print() << std::endl;

    /* Additional nodes */
    rootEl.getChild(0).setName("NestedElementZero");
    rootEl.getChild(1).setAttribute("internal_index", "1");
    XmlElement & test = static_cast<XmlElement &>(rootEl.getChild(1));
    test.pushBackChild(XmlElement("NestedElement3"));

    /* Adding paragraphs */
    static_cast<XmlElement &>(rootEl.getChild(1)).pushBackChild(TextElement("p", "This is a text paragraph"));

    XmlElement paragraph("p", true);
    paragraph.pushBackChild(TextElement("text1", "This \"is\" a showcase of ", false, false));
    paragraph.pushBackChild(TextElement("b", "HTML", true, false, false, true));
    paragraph.pushBackChild(TextElement("text3", "-like paragraph capability (in addition to pure XML). <3", false, false));

    static_cast<XmlElement &>(rootEl.getChild(1)).pushBackChild(paragraph);

    /* Printing again */
    std::cout << "2. The element is:" << std::endl << rootEl.print() << std::endl;

    return 0;
}