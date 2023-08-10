#include "XmlElement.hh"

/* === Public member functions === */

/* Constructors */
XmlElement::XmlElement() {
    this->setName("_default_element");
    this->singleLine = false;
    this->increment = true;
}

XmlElement::XmlElement(std::string const & name) {
    this->setName(name);
    this->singleLine = false;
    this->increment = true;
}

XmlElement::XmlElement(std::string const & name, bool singleLine) {
    this->setName(name);
    this->singleLine = singleLine;
    this->increment = !singleLine;
}

XmlElement::XmlElement(std::string const & name, std::map<char const *, std::string> & attributes, std::vector<Node *> & children, bool singleLine, bool increment) {
    this->setName(name);
    this->attributes = attributes;
    this->children = children;
    this->singleLine = singleLine;
    this->increment = increment;
}

XmlElement::XmlElement(std::string const & name, std::map<char const *, std::string> & attributes, std::vector<Node *> & children, bool singleLine, bool increment, bool checkName) {
    this->setName(name, checkName);
    this->attributes = attributes;
    this->children = children;
    this->singleLine = singleLine;
    this->increment = increment;
}


/* Member functions */

/* Child elements */
void XmlElement::addChild(int pos, Node & value) {
    this->children.insert(this->children.begin() + pos, &value);
}

Node & XmlElement::getChild(int index) {
    if(index < this->children.size())
        return *this->children[index];
    else
        throw std::invalid_argument("Error: Element index out of bounds");
}

void XmlElement::delChild(int pos) {
    if(pos < this->children.size())
        this->children.erase(this->children.begin() + pos);
    else
        throw std::invalid_argument("Error: Can't erase at out-of-bounds index");
}

void XmlElement::pushBackChild(Node & value) {
    this->children.push_back(&value);
}

void XmlElement::popBackChild(void) {
    this->children.pop_back();
}

size_t XmlElement::getChildAmount(void) {
    return this->children.size();
}

bool XmlElement::childrenEmpty(void) {
    return this->children.empty();
}


/* Other */
void XmlElement::setSingleLine(bool singleLine) {
    this->singleLine = singleLine;
}

bool XmlElement::getSingleLine(void) {
    return this->singleLine;
}

void XmlElement::setIncrement(bool increment) {
    this->increment = increment;
}

bool XmlElement::getIncrement(void) {
    return this->increment;
}

std::string XmlElement::print(int indentLevel) {
    /* Opening the element */
    std::string result;
    /* Indenting */
    if(indentLevel > 0) {
        for(int i = 0; i < indentLevel; i++) {
            result += "\t";
        }
    }
    result += "<" + this->name;
    for(auto it : this->attributes) {
        result += " ";
        result += it.first;
        result += "=\"" + it.second + "\"";
    }
    /* Closing normally, adding content if not empty */
    if(this->children.size() > 0) {
        result += ">";
        if(!this->singleLine)
            result += "\n";
        
        /* Adding child elements */
        for(auto it : this->children) {
            if(!this->singleLine && this->increment)
                result += (*it).print(indentLevel + 1);
            else
                result += (*it).print();
        }

        /* Closing the element normally, with indents */
        if(indentLevel > 0 && !this->singleLine) {
            for(int i = 0; i < indentLevel; i++) {
                result += "\t";
            }
        }
        result += "</" + this->name + ">\n";
    
    /* Self-closing empty element */
    } else {
        result += " />\n";
    }

    return result;
}