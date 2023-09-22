#include "AttributeDTD.hh"

AttributeDTD::AttributeDTD(
    std::string const & name, std::string const & element, std::string const & attribute, std::string const & type, std::string const & value, 
    bool stringValue, bool indent, bool endLine) {

        this->setName(name, false);
        this->type = DTD_ATTRIBUTES;
        this->setElementName(element);
        this->setAttr(attribute, type, value);
        this->stringValue = stringValue;
        this->indent = indent;
        this->endLine = endLine;
}


/* Get/Set functions for the internal attributes */

void AttributeDTD::setElementName(std::string const & elementName) {
    this->setAttribute("element_name", elementName);
}

std::string AttributeDTD::getElementName(void) const {
    return this->getAttribute("element_name");
}

void AttributeDTD::setAttrName(std::string const & attrName) {
    this->setAttribute("attr_name", attrName);
}

std::string AttributeDTD::getAttrName(void) const {
    return this->getAttribute("attr_name");
}

void AttributeDTD::setAttrType(std::string const & attrType) {
    this->setAttribute("attr_type", attrType);
}

std::string AttributeDTD::getAttrType(void) const {
    return this->getAttribute("attr_type");
}

void AttributeDTD::setAttrValue(std::string const & attrValue, bool isString) {
    this->setAttribute("attr_value", attrValue);
    this->stringValue = isString;
}

std::string AttributeDTD::getAttrValue(void) const {
    return this->getAttribute("attr_value");
}

void AttributeDTD::setStringValue(bool isString) {
    this->stringValue = isString;
}

bool AttributeDTD::getStringValue(void) const {
    return this->stringValue;
}


/* General attribute get/set */

void AttributeDTD::setAttr(std::string const & attrName, std::string const & attrType, std::string const & attrValue, bool isString) {
    this->setAttrName(attrName);
    this->setAttrType(attrType);
    this->setAttrValue(attrValue);
    this->stringValue = isString;
}

void AttributeDTD::getAttr(std::string & attrName, std::string & attrType, std::string & attrValue, bool & isString) const {
    attrName = this->getAttrName();
    attrType = this->getAttrType();
    attrValue = this->getAttrValue();
    isString = this->stringValue;
}


/* General content get/set */

void AttributeDTD::setContent(std::string const & elementName, std::string const & attrName, std::string const & attrType, std::string const & attrValue, bool isString) {
    this->setElementName(elementName);
    this->setAttr(attrName, attrType, attrValue, isString);
}

void AttributeDTD::getContent(std::string & elementName, std::string & attrName, std::string & attrType, std::string & attrValue, bool & isString) const {
    elementName = this->getElementName();
    this->getAttr(attrName, attrType, attrValue, isString);
}

void AttributeDTD::delContent(void) {
    this->delAttribute("element_name");
    this->delAttribute("attr_name");
    this->delAttribute("attr_type");
    this->delAttribute("attr_value");
}


/* Other functions */

std::string AttributeDTD::print(int indentLevel) {
    std::string result;

    /* Starting with indent if desired */
    if(this->indent && indentLevel > 0) {
        for(int i = 0; i < indentLevel; i++) {
            result += "\t";
        }
    }

    result += "<!" + this->type + " " + this->getElementName() + " " + this->getAttrName() + " " + this->getAttrType() + " ";

    if(this->stringValue)
        result += "\"" + this->getAttrValue() + "\"";
    else
        result += this->getAttrValue();
    
    result += ">";

    if(this->endLine)
        result += "\n";

    return result;
}

Node * AttributeDTD::_copy(void) const {
    return new AttributeDTD(*this);
}