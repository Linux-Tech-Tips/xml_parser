#include "XmlPrologElement.hh"

/* Constructor */
XmlPrologElement::XmlPrologElement(
    std::string const & name, float xmlVersion, std::string const & encoding, const char * standalone, 
    bool endLine, bool indent, bool printUserAttributes) {

        this->setName(name, false);
        this->xmlVersion = xmlVersion;
        this->encoding = encoding;
        this->standalone = standalone;
        this->endLine = endLine;
        this->indent = indent;
        this->printUserAttributes = printUserAttributes;
}

/* Public member functions */


/* Default XML prolog parameter member function */

void XmlPrologElement::setXmlVersion(float xmlVersion) {
    this->xmlVersion = xmlVersion;
}

float XmlPrologElement::getXmlVersion(void) {
    return this->xmlVersion;
}


void XmlPrologElement::setEncoding(std::string const & encoding) {
    this->encoding = encoding;
}

std::string XmlPrologElement::getEncoding(void) {
    return this->encoding;
}


void XmlPrologElement::setStandalone(char const * standalone) {
    this->standalone = standalone;
}

char const * XmlPrologElement::getStandalone(void) {
    return this->standalone;
}


void XmlPrologElement::setUserAttributes(bool printUserAttributes) {
    this->printUserAttributes = printUserAttributes;
}

bool XmlPrologElement::getUserAttributes(void) {
    return this->printUserAttributes;
}


/* Other member functions */

std::string XmlPrologElement::print(int indentLevel) {
    std::string result;

    if(this->indent && indentLevel > 0) {
        for(int i = 0; i < indentLevel; i++)
            result += "\t";
    }

    result += "<?xml version=\"" + std::to_string(this->xmlVersion).substr(0, 3) + "\"";

    if(!this->encoding.empty()) {
        result += " encoding=\"" + this->encoding + "\"";
    }

    if(strcmp(this->standalone, STANDALONE_UNSET)) {
        result += " standalone=\"";
        result += this->standalone; 
        result += "\"";
    }

    if(this->printUserAttributes && !this->isAttributeEmpty()) {
        for(auto it : this->attributes) {
            result += " ";
            result += it.first;
            result += "=\"" + it.second + "\"";
        }
    }

    result += "?>";

    if(this->endLine)
        result += "\n";

    return result;
}


Node * XmlPrologElement::_copy(void) const {
    return new XmlPrologElement(*this);
}