#include <iostream>
#include <string>

#include "file_util.hh"
#include "Node.hh"
#include "XmlElement.hh"
#include "TextElement.hh"
#include "XmlProlog.hh"
#include "DTD.hh"
#include "DoctypeDTD.hh"

/* First version - file_util demo - write/read files before working with XML */

/* Temporary TODO Next: 
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
    static_cast<XmlElement &>(rootEl.getChild(1)).pushBackChild(XmlElement("NestedElement3"));

    /* Adding paragraphs */
    static_cast<XmlElement &>(rootEl.getChild(1)).pushBackChild(TextElement("p", "This is a text paragraph"));

    XmlElement paragraph("p", true);
    paragraph.pushBackChild(TextElement("text1", "This \"is\" a showcase of ", false, false));
    paragraph.pushBackChild(TextElement("b", "HTML", true, false, false, true));
    paragraph.pushBackChild(TextElement("text3", "-like paragraph capability (in addition to pure XML). <3", false, false));

    static_cast<XmlElement &>(rootEl.getChild(1)).pushBackChild(paragraph);

    if(rootEl.findChild("NestedElementZero")) {
        XmlElement & zero = static_cast<XmlElement &>(rootEl.getChild("NestedElementZero"));
        zero.setAttribute("zeroth", "true");
        zero.pushBackChild(TextElement("p", "this is the zero-th element, nice"));
    }

    /* XML Document prolog */
    XmlProlog prlg("xml_prolog", 1.0f, "UTF-8", STANDALONE_YES);

    /* XML DTD Document type declaration */
    DoctypeDTD doctype("doctype", "html");
    doctype.setExtLink("ext.dtd");
    doctype.setExtType(DTD_PUBLIC);
    doctype.pushBackChild(DTD("_dtd_1", DTD_ENTITY, "test"));
    doctype.pushBackChild(DTD("_dtd_1", DTD_ATTRIBUTES, "another test"));
    doctype.pushBackChild(DTD("_dtd_1", DTD_ATTRIBUTES, "another test (test1, test2)"));

    /* Printing again */
    std::cout << "2. The element is:" << std::endl << prlg.print() << doctype.print() << rootEl.print() << std::endl;

    return 0;
}