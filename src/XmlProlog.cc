#include "XmlProlog.hh"

/* Constructor */
XmlProlog::XmlProlog(
    std::string const & name, float xmlVersion, std::string const & encoding, const char * standalone, 
    bool endLine, bool indent, bool printUserAttributes) {

        this->setName(name, false);
        this->nodeType = NodeTypeName::XmlProlog;
        this->xmlVersion = xmlVersion;
        this->encoding = encoding;
        this->standalone = standalone;
        this->endLine = endLine;
        this->indent = indent;
        this->printUserAttributes = printUserAttributes;
}

/* Public member functions */


/* Default XML prolog parameter member function */

void XmlProlog::setXmlVersion(float xmlVersion) {
    this->xmlVersion = xmlVersion;
}

float XmlProlog::getXmlVersion(void) {
    return this->xmlVersion;
}


void XmlProlog::setEncoding(std::string const & encoding) {
    this->encoding = encoding;
}

std::string XmlProlog::getEncoding(void) {
    return this->encoding;
}


void XmlProlog::setStandalone(char const * standalone) {
    this->standalone = standalone;
}

char const * XmlProlog::getStandalone(void) {
    return this->standalone;
}


void XmlProlog::setUserAttributes(bool printUserAttributes) {
    this->printUserAttributes = printUserAttributes;
}

bool XmlProlog::getUserAttributes(void) {
    return this->printUserAttributes;
}


/* Other member functions */

std::string XmlProlog::print(int indentLevel) {
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


Node * XmlProlog::_copy(void) const {
    return new XmlProlog(*this);
}