#include "ElementDTD.hh"

/* Constructor */

ElementDTD::ElementDTD(std::string const & name, std::string const & elementName, std::string const & content, bool endLine, bool indent) {
    this->setName(name, false);
    this->type = DTD_ELEMENT;
    this->setAttribute("element_name", elementName);
    this->setAttribute("content", content);
    this->endLine = endLine;
    this->indent = indent;
}


/* Other functions */

void ElementDTD::setContent(std::string const * const contentValues, size_t amount, bool mixedContent) {
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
        this->setAttribute("content", tmpContent);
    }
}

void ElementDTD::setContent(std::string const & content) {
    this->setAttribute("content", content);
}

void ElementDTD::addContentValue(std::string const & contentValue, bool mixedContent) {
    /* Appending content to existing, with the desired separator */
    this->setAttribute("content", this->getAttribute("content") + (mixedContent ? " | " : ", ") + contentValue);
}

std::string ElementDTD::print(int indentLevel) {
    std::string result;

    /* Starting with indent if desired */
    if(this->indent && indentLevel > 0) {
        for(int i = 0; i < indentLevel; i++) {
            result += "\t";
        }
    }
    result += "<!" + this->type + " ";

    result += this->getAttribute("element_name") + " ";

    if(this->getAttribute("content").compare(DTD_EMPTY) == 0 || this->getAttribute("content").compare(DTD_ANY) == 0) {
        result += this->getAttribute("content");
    } else {
        result += "(" + this->getAttribute("content") + ")";
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