#include "XmlProlog.hh"

/* Constructor */
XmlProlog::XmlProlog(
    std::string const & name, float xmlVersion, std::string const & encoding, std::string const & standalone, 
    bool endLine, bool indent, bool printUserAttributes) {

        this->setName(name, false);
        this->nodeType = NodeTypeName::XmlProlog;
        this->setAttribute("xml_version", std::to_string(xmlVersion).substr(0, 3));
        this->setAttribute("encoding", encoding);
        this->setAttribute("standalone", standalone);
        this->endLine = endLine;
        this->indent = indent;
        this->printUserAttributes = printUserAttributes;
}

/* Public member functions */


/* Default XML prolog parameter member function */

void XmlProlog::setXmlVersion(float xmlVersion) {
    this->setAttribute("xml_version", std::to_string(xmlVersion).substr(0, 3));
}

float XmlProlog::getXmlVersion(void) const {
    return std::stof(this->getAttribute("xml_version"));
}


void XmlProlog::setEncoding(std::string const & encoding) {
    this->setAttribute("encoding", encoding);
}

std::string XmlProlog::getEncoding(void) const {
    return this->getAttribute("encoding");
}

void XmlProlog::unsetEncoding(void) {
    this->delAttribute("encoding");
}


void XmlProlog::setStandalone(std::string const & standalone) {
    this->setAttribute("standalone", standalone);
}

std::string XmlProlog::getStandalone(void) const {
    return this->getAttribute("standalone");
}

void XmlProlog::unsetStandalone(void) {
    this->delAttribute("standalone");
}


void XmlProlog::setUserAttributes(bool printUserAttributes) {
    this->printUserAttributes = printUserAttributes;
}

bool XmlProlog::getUserAttributes(void) const {
    return this->printUserAttributes;
}


/* Other member functions */

std::string XmlProlog::print(int indentLevel) {
    std::string result;

    if(this->indent && indentLevel > 0) {
        for(int i = 0; i < indentLevel; i++)
            result += "\t";
    }

    result += "<?xml";

    if(this->printUserAttributes) {
        for(auto it : this->attributes) {
            result += " " + it.first + "=\"" + it.second + "\"";
        }
    } else {

        if(!this->getAttribute("xml_version").empty()) {
            result += " version=\"" + this->getAttribute("xml_version") + "\"";
        } else {
            result += " version=\"1.0\"";
        }

        if(!this->getAttribute("encoding").empty()) {
            result += " encoding=\"" + this->getAttribute("encoding") + "\"";
        }

        if(!this->getAttribute("standalone").empty()) {
            result += " standalone=\"" + this->getAttribute("standalone") + "\"";
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