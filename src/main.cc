#include <iostream>
#include <string>

#include "file_util.hh"
#include "Node.hh"
#include "XmlElement.hh"
#include "TextElement.hh"
#include "XmlProlog.hh"
#include "DTD/DTD.hh"
#include "DTD/DoctypeDTD.hh"
#include "DTD/ElementDTD.hh"
#include "DTD/AttributeDTD.hh"
#include "DTD/EntityDTD.hh"

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
    rootEl.getChild(0)->setName("NestedElementZero");
    rootEl.getChild(1)->setAttribute("internal_index", "1");
    dynamic_cast<XmlElement *>(rootEl.getChild(1))->pushBackChild(XmlElement("NestedElement3"));

    /* Adding paragraphs */
    dynamic_cast<XmlElement *>(rootEl.getChild(1))->pushBackChild(TextElement("p", "This is a text paragraph"));

    XmlElement paragraph("p", true);
    paragraph.pushBackChild(TextElement("text1", "This \"is\" a showcase of ", false, false));
    paragraph.pushBackChild(TextElement("b", "HTML", true, false, false, true));
    paragraph.pushBackChild(TextElement("text3", "-like paragraph capability (in addition to pure XML). <3", false, false));

    dynamic_cast<XmlElement *>(rootEl.getChild(1))->pushBackChild(paragraph);

    if(rootEl.findChild("NestedElementZero")) {
        XmlElement * zero = dynamic_cast<XmlElement *>(rootEl.getChild("NestedElementZero"));
        zero->setAttribute("zeroth", "true");
        zero->pushBackChild(TextElement("p", "this is the zero-th element, nice"));
    }

    /* XML Document prolog */
    XmlProlog prlg("xml_prolog", 1.0f, "UTF-8", STANDALONE_YES);

    /* XML DTD Document type declaration */
    DoctypeDTD doctype("doctype", "html");
    doctype.setExtLink("ext.dtd");
    doctype.setExtType(DTD_EXTERN_PUBLIC);
    doctype.pushBackChild(DTD("_dtd_1", "CUSTOM_DTD", "test"));
    doctype.pushBackChild(ElementDTD("_dtd_2", "element1", DTD_CONTENT_EMPTY));
    doctype.pushBackChild(ElementDTD("_dtd_3", "element2", DTD_CONTENT_ANY));
    doctype.pushBackChild(AttributeDTD("_dtd_4", "element1", "at", DTD_ATTR_CDATA, DTD_ATTR_FIXED " \"tribute\""));
    doctype.pushBackChild(AttributeDTD("_dtd_5", "element1", "not", DTD_ATTR_CDATA, "thing", true));
    doctype.pushBackChild(EntityDTD("_dtd_6", "EN", "TITY"));
    doctype.pushBackChild(EntityDTD("_dtd_7", "EXT", DTD_EXTERN_SYSTEM " \"https://www.w3schools.com/entities.dtd\"", false));

    std::string tmpName;
    std::string tmpValue;
    bool tmpIsString;
    ((EntityDTD *)doctype.getChild("_dtd_7"))->getContent(tmpName, tmpValue, tmpIsString);
    std::cout << "DEBUG: Values are " << tmpName << " " << tmpValue << " " << tmpIsString << std::endl;

    ElementDTD seqElement("_dtd_4", "element3");
    std::string content [5] = {"one", "two", "three", "four", "five"};
    seqElement.setElementContent(content, 5);
    seqElement.addElementContent("six");
    seqElement.addElementContent("(seven | eight)");

    doctype.pushBackChild(seqElement);

    if(doctype.findChild("_dtd_1"))
        std::cout << "FOUND" << std::endl;

    int t;
    if(doctype.findChild("_dtd_2", &t))
        std::cout << "FOUND AT " << t << std::endl;
    
    std::string gotContent;
    ((DTD *)doctype.getChild(0))->getContent(gotContent);
    std::cout << "CONTENT: " << gotContent << std::endl;

    doctype.setContent("this is content");

    /* Printing again */
    std::cout << "2. The element is:" << std::endl << prlg.print() << doctype.print() << rootEl.print() << std::endl;

    return 0;
}