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

/* Add/delete */
void XmlElement::addChild(int pos, Node const & value) {
    this->children.insert(this->children.begin() + pos, value._copy());
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

/* Get a specific node */
Node & XmlElement::getChild(int index) {
    if(index < this->children.size())
        return *this->children[index];
    else
        throw std::invalid_argument("Error: Element index out of bounds");
}

Node & XmlElement::getChild(char const * childName) {
    int index;
    if(this->findChild(childName, &index))
        return *this->children[index];
    else
        throw std::invalid_argument("Error: Element not found");
}

/* Get general information about nested nodes in this element */
size_t XmlElement::getChildAmount(void) const {
    return this->children.size();
}

bool XmlElement::childrenEmpty(void) const {
    return this->children.empty();
}

bool XmlElement::findChild(char const * nameToFind, int * index) {
    /* Checks all child elements */
    for(int i = 0; i < this->getChildAmount(); i++) {
        if(this->children[i]->getName().compare(nameToFind) == 0) {
            /* Returns and saves the index of the first instance found*/
            *index = i;
            return true;
        }
    }
    /* Returns false and saves -1 if for loop finishes without finding any */
    *index = -1;
    return false;
}

bool XmlElement::findChild(char const * nameToFind) {
    /* Checks all child elements, returns true on first match */
    for(int i = 0; i < this->getChildAmount(); i++) {
        if(this->children[i]->getName().compare(nameToFind) == 0)
            return true;
    }
    /* Returns false if none found */
    return false;
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