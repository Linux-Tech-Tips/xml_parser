#include "Node.hh"

/* Private member functions */

bool Node::checkName(std::string name, bool xmlReserved) {
    return std::regex_match(name, std::regex("(_|[a-zA-Z])[\\w\\-\\.]*")) && (!xmlReserved || name != "xml");
}

/* Constructor */

Node::Node(std::string const & name, bool endLine, bool indent) {
    this->setName(name);
    this->nodeType = NodeTypeName::Node;
    this->endLine = endLine;
    this->indent = indent;
}

/* Public member functions */

/* Name */

void Node::setName(std::string const & name, bool checkName) {
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

std::string Node::getName(void) const {
    return this->name;
}

/* Type */

NodeTypeName Node::getNodeType(void) const {
    return this->nodeType;
}


/* Attribute */

void Node::setAttribute(std::string const & name, std::string const & value) {
    this->attributes[name] = value;
}

std::string Node::getAttribute(std::string const & name) const {
    if(this->attributes.find(name) != this->attributes.end())
        return this->attributes.at(name);
    else
        return "";
}

void Node::delAttribute(std::string const & name) {
    if(this->attributes.find(name) != this->attributes.end())
        this->attributes.erase(name);
}

size_t Node::getAttributeNumber(void) const {
    return this->attributes.size();
}

bool Node::isAttributeEmpty(void) const {
    return this->attributes.empty();
}


/* Other*/

void Node::setEndLine(bool endLine) {
    this->endLine = endLine;
}

bool Node::getEndLine(void) const {
    return this->endLine;
}

void Node::setIndent(bool indent) {
    this->indent = indent;
}

bool Node::getIndent(void) const {
    return this->indent;
}

std::string Node::print(int indentLevel) {
    std::string result;
    
    /* Indent if desired */
    if(this->indent && indentLevel > 0) {
        for(int i = 0; i < indentLevel; i++)
            result += "\t";    
    }

    result += "<" + this->name;

    /* Attributes if any */
    for(auto it : this->attributes) {
        result += " ";
        result += it.first;
        result += "=\"" + it.second + "\"";
    }

    result += " />";

    /* Line break if not single line */
    if(this->endLine)
        result += "\n";

    return result;
}

Node * Node::_copy(void) const {
    return new Node(*this);
}
