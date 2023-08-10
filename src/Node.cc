#include "Node.hh"

/* Private member functions */

bool Node::checkName(std::string name, bool xmlReserved) {
    return std::regex_match(name, std::regex("(_|[a-zA-Z])[\\w-.]*")) && (!xmlReserved || name != "xml");
}

/* Constructors */

Node::Node() {
    this->setName("_default_node");
}

Node::Node(std::string const & name) {
    this->setName(name);
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

size_t Node::getAttributeNumber(void) {
    return this->attributes.size();
}

bool Node::isAttributeEmpty(void) {
    return this->attributes.empty();
}


/* Other*/

std::string Node::print(int indentLevel) {
    return "";
}