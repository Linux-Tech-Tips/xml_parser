#include "ElementDTD.hh"

/* Constructor */

ElementDTD::ElementDTD(std::string const & elementName, std::string const & content, bool indent, bool endLine) {
    this->setName(DTD_ELEMENT, false);
    this->nodeType = NodeTypeName::ElementDTD;
    this->setAttribute("element_name", elementName);
    this->setAttribute("element_content", content);
    this->endLine = endLine;
    this->indent = indent;
}


/* Specific content manipulation member functions */

void ElementDTD::setElementContent(std::string const * const contentValues, size_t amount, bool mixedContent) {
    if(amount > 0) {
        std::string tmpContent;

        /* Iterating through all but last and adding separator */
        int i;
        for(i = 0; i < ((int)amount - 1); i++) {
            tmpContent += contentValues[i] + (mixedContent ? " | " : ", ");
        }
        /* Adding last content value */
        tmpContent += contentValues[i];

        /* Setting the content attribute */
        this->setAttribute("element_content", tmpContent);
    }
}

void ElementDTD::setElementContent(std::string const & content) {
    this->setAttribute("element_content", content);
}

void ElementDTD::addElementContent(std::string const & contentValue, bool mixedContent) {
    /* Appending content to existing, with the desired separator */
    this->setAttribute("element_content", this->getAttribute("element_content") + (mixedContent ? " | " : ", ") + contentValue);
}

std::string ElementDTD::getElementContent(void) const {
    return this->getAttribute("element_content");
}

void ElementDTD::setElementName(std::string const & elementName) {
    this->setAttribute("element_name", elementName);
}

std::string ElementDTD::getElementName(void) const {
    return this->getAttribute("element_name");
}


/* General content manipulation member functions */

void ElementDTD::setContent(std::string const & elementName, std::string const * const contentValues, size_t amount, bool mixedContent) {
    this->setElementName(elementName);
    this->setElementContent(contentValues, amount, mixedContent);
}

/** Sets all the available content fields of the Element DTD, with a directly specified Element content string */
void ElementDTD::setContent(std::string const & elementName, std::string const & elementContent) {
    this->setElementName(elementName);
    this->setElementContent(elementContent);
}

/** Saves all the available content fields of the Element DTD to the given parameters */
void ElementDTD::getContent(std::string & elementName, std::string & elementContent) const {
    elementName = this->getElementName();
    elementContent = this->getElementContent();
}

/** Removes all the recognized content fields from the DTD */
void ElementDTD::delContent(void) {
    this->delAttribute("element_name");
    this->delAttribute("element_content");
}


/* Other functions */

std::string ElementDTD::print(int indentLevel) {
    std::string result;

    /* Starting with indent if desired */
    if(this->indent && indentLevel > 0) {
        for(int i = 0; i < indentLevel; i++) {
            result += "\t";
        }
    }
    result += "<!" + this->name + " ";

    result += this->getAttribute("element_name") + " ";

    if(this->getAttribute("element_content").compare(DTD_CONTENT_EMPTY) == 0 || this->getAttribute("element_content").compare(DTD_CONTENT_ANY) == 0) {
        result += this->getAttribute("element_content");
    } else {
        result += "(" + this->getAttribute("element_content") + ")";
    }

    /* End, with linebreak if desired */
    result += ">";
    if(this->endLine)
        result += "\n";

    return result;
}


Node * ElementDTD::_copy(void) const {
    return new ElementDTD(*this);
}