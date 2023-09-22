#include "EntityDTD.hh"

EntityDTD::EntityDTD(std::string const & name, std::string const & entityName, std::string const & entityValue, bool stringValue, bool indent, bool endLine) {
    this->setName(name, false);
    this->type = DTD_ENTITY;
    this->setEntityName(entityName);
    this->setEntityValue(entityValue);
    this->stringValue = stringValue;
    this->indent = indent;
    this->endLine = endLine;
}

void EntityDTD::setEntityName(std::string const & name) {
    this->setAttribute("entity_name", name);
}

std::string EntityDTD::getEntityName(void) const {
    return this->getAttribute("entity_name");
}

void EntityDTD::setEntityValue(std::string const & value, bool isString) {
    this->setAttribute("entity_value", value);
    this->stringValue = isString;
}

std::string EntityDTD::getEntityValue(void) const {
    return this->getAttribute("entity_value");
}

void EntityDTD::setStringValue(bool isString) {
    this->stringValue = isString;
}

bool EntityDTD::getStringValue(void) const {
    return  this->stringValue;
}

void EntityDTD::setContent(std::string const & entityName, std::string const & entityValue, bool isString) {
    this->setEntityName(entityName);
    this->setEntityValue(entityValue, isString);
}

void EntityDTD::getContent(std::string & entityName, std::string & entityValue, bool & isString) const {
    entityName = this->getEntityName();
    entityValue = this->getEntityValue();
    isString = this->stringValue;
}

void EntityDTD::delContent(void) {
    this->delAttribute("entity_name");
    this->delAttribute("entity_value");
}


/* Other functions */

std::string EntityDTD::print(int indentLevel) {
    std::string result;

    /* Indent if desired */
    if(this->indent && indentLevel > 0) {
        for(int i = 0; i < indentLevel; i++) {
            result += "\t";
        }
    }

    result += "<!" + this->type + " " + this->getEntityName() + " ";
    
    if(this->stringValue) 
        result += "\"" + this->getEntityValue() + "\"";
    else
        result += this->getEntityValue();
    
    result += ">";

    if(this->endLine)
        result += "\n";

    return result;
}

Node * EntityDTD::_copy(void) const {
    return new EntityDTD(*this);
}