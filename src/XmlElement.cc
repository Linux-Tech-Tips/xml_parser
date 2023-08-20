#include "XmlElement.hh"


/* === Public member functions === */

/* Constructor */
XmlElement::XmlElement(std::string const & name, bool singleLine, bool endLine, bool indent, bool checkName) {
    this->setName(name, checkName);
    this->singleLine = singleLine;
    this->indent = indent;
    this->endLine = endLine;
}

/* Copy constructor */
XmlElement::XmlElement(XmlElement const & original) {
    /* Copying all statically allocated members */
    this->name = original.name;
    this->singleLine = original.singleLine;
    this->indent = original.indent;
    this->endLine = original.endLine;
    this->attributes = original.attributes;

    /* Copying dynamically allocated child Nodes */
    if(original.getChildAmount() > 0) {
        for(auto it : original.children) {
            this->pushBackChild(*it);
        }
    }
}

/* Destructor */
XmlElement::~XmlElement() {
    /* Deallocating any copies of child Nodes */
    if(this->getChildAmount() > 0) {
        for(auto it : this->children) {
            delete it;
        }
    }
}


/* Member functions */

/* Child elements */
void XmlElement::addChild(int pos, Node const & value) {
    this->children.insert(this->children.begin() + pos, value._copy());
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

void XmlElement::pushBackChild(Node const & value) {
    this->children.push_back(value._copy());
}

void XmlElement::popBackChild(void) {
    this->children.pop_back();
}

size_t XmlElement::getChildAmount(void) const {
    return this->children.size();
}

bool XmlElement::childrenEmpty(void) const {
    return this->children.empty();
}


/* Other */
void XmlElement::setSingleLine(bool singleLine) {
    this->singleLine = singleLine;
}

bool XmlElement::getSingleLine(void) const {
    return this->singleLine;
}

std::string XmlElement::print(int indentLevel) {
    /* Opening the element */
    std::string result;
    /* Indenting */
    if(indent && indentLevel > 0) {
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
            if(!this->singleLine)
                result += it->print(indentLevel + 1);
            else
                result += it->print();
        }

        /* Closing the element normally, with indents */
        if(indentLevel > 0 && !this->singleLine) {
            for(int i = 0; i < indentLevel; i++) {
                result += "\t";
            }
        }
        result += "</" + this->name + ">";
    
    /* Self-closing empty element */
    } else {
        result += " />";
    }

    if(this->endLine)
        result += "\n";

    return result;
}

Node * XmlElement::_copy() const {
    return new XmlElement(*this);
}