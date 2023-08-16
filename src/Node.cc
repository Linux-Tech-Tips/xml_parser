#include "Node.hh"

/* Private member functions */

bool Node::checkName(std::string name, bool xmlReserved) {
    return std::regex_match(name, std::regex("(_|[a-zA-Z])[\\w\\-\\.]*")) && (!xmlReserved || name != "xml");
}

/* Constructors */

/* TODO Refactor - pointless to pass address when the function called takes copy anyway */
Node::Node(std::string const & name, bool endLine, bool indent) {
    this->setName(name);
    this->endLine = endLine;
    this->indent = indent;
}

/* Public member functions */

/* Name */

void Node::setName(std::string name, bool checkName) {
    if(checkName) {
        if(this->checkName(name)) {
            this->name = name;
        } else {
            throw std::invalid_argument("Error: Element name doesn't match XML standard");
        }
    } else {
        this->name = name;
    }
}

std::string Node::getName(void) {
    return this->name;
}


/* Attribute */
void Node::setAttribute(char const * name, std::string const & value) {
    this->attributes[name] = value;
}

std::string Node::getAttribute(char const * name) {
    if(this->attributes.find(name) != this->attributes.end())
        return this->attributes[name];
    else
        return "";
}

void Node::delAttribute(char const * name) {
    if(this->attributes.find(name) != this->attributes.end())
        this->attributes.erase(name);
}

size_t Node::getAttributeNumber(void) {
    return this->attributes.size();
}

bool Node::isAttributeEmpty(void) {
    return this->attributes.empty();
}


/* Other*/

void Node::setEndLine(bool endLine) {
    this->endLine = endLine;
}

bool Node::getEndLine(void) {
    return this->endLine;
}

void Node::setIndent(bool indent) {
    this->indent = indent;
}

bool Node::getIndent(void) {
    return this->indent;
}

std::string Node::print(int indentLevel) {
    std::string result;
    
    /* Indent if desired */
    if(indent && indentLevel > 0) {
        for(int i = 0; i < indentLevel; i++)
            result += "\t";    
    }

    result += "<" + this->name;

    /* Attributes if any */
    for(auto it : this->attributes) {
        result += " ";
        result += *it.first;
        result += "=\"" + it.second + "\"";
    }

    result += " />";

    /* Line break if not single line */
    if(this->endLine)
        result += "\n";

    return result;
}
