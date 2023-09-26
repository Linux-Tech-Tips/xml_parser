#include <iostream>
#include <string>

#include "file_util.hh"
#include "Node.hh"
#include "XmlElement.hh"
#include "TextElement.hh"
#include "XmlProlog.hh"
#include "Comment.hh"
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
    dynamic_cast<XmlElement *>(rootEl.getChild(1))->pushBackChild(Comment("NOTE:", "The following is a paragrahp", true));
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

    int nestedP = ((XmlElement *)rootEl.getChild("NestedElement2"))->getChildAmount("p");
    if(nestedP > 0) {
        std::cout << "Number of p elements in NestedElement2: " << nestedP << std::endl;
        XmlElement * n2 = ((XmlElement *)rootEl.getChild("NestedElement2"));
        XmlElement * np = ((XmlElement *)(n2->getChild("p", 1)));
        std::cout << "Last p element content is: " << np->print() << std::endl;
    }

    /* XML Document prolog */
    XmlProlog prlg("xml_prolog", 1.0f, "UTF-8", STANDALONE_YES);

    /* XML DTD Document type declaration */
    DoctypeDTD doctype("html");
    doctype.setExtLink("ext.dtd");
    doctype.setExtType(DTD_EXTERN_PUBLIC);
    doctype.pushBackChild(DTD("CUSTOM_DTD", "test"));
    doctype.pushBackChild(ElementDTD("element1", DTD_CONTENT_EMPTY));
    doctype.pushBackChild(ElementDTD("element2", DTD_CONTENT_ANY));
    doctype.pushBackChild(AttributeDTD("element1", "at", DTD_ATTR_CDATA, DTD_ATTR_FIXED " \"tribute\""));
    doctype.pushBackChild(AttributeDTD("element1", "not", DTD_ATTR_CDATA, "thing", true));
    doctype.pushBackChild(EntityDTD("EN", "TITY"));
    doctype.pushBackChild(EntityDTD("EXT", DTD_EXTERN_SYSTEM " \"https://www.w3schools.com/entities.dtd\"", false));

    std::string tmpName;
    std::string tmpValue;
    bool tmpIsString;
    ((EntityDTD *)doctype.getChild(6))->getContent(tmpName, tmpValue, tmpIsString);
    std::cout << "DEBUG: Values are " << tmpName << " " << tmpValue << " " << tmpIsString << std::endl;

    ElementDTD seqElement("element3");
    std::string content [5] = {"one", "two", "three", "four", "five"};
    seqElement.setElementContent(content, 5);
    seqElement.addElementContent("six");
    seqElement.addElementContent("(seven | eight)");

    doctype.pushBackChild(seqElement);

    if(doctype.findChild(DTD_ELEMENT))
        std::cout << "FOUND" << std::endl;

    int t;
    if(doctype.findChild("CUSTOM_DTD", &t))
        std::cout << "FOUND AT " << t << std::endl;

    std::cout << "Total: " << doctype.getChildAmount() << std::endl;

    if(doctype.findChild(DTD_ENTITY, &t, 0))
        std::cout << "FOUND AT " << t << std::endl;

    if(doctype.findChild(DTD_ENTITY, &t, 1)) {
        std::cout << "FOUND AT " << t << std::endl;
        std::cout << "Entity name: " << ((EntityDTD *)doctype.getChild(DTD_ENTITY, 1))->getEntityName() << std::endl;
    }
    
    std::string gotContent;
    ((DTD *)doctype.getChild(0))->getContent(gotContent);
    std::cout << "CONTENT: " << gotContent << std::endl;

    doctype.setContent("this is content");

    /* Printing again */
    std::cout << "2. The element is:" << std::endl << prlg.print() << doctype.print() << rootEl.print() << std::endl;

    return 0;
}