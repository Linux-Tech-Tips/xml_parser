#include "DoctypeDTD.hh"

/* Constructor/Destructor */
DoctypeDTD::DoctypeDTD(std::string const & name, std::string const & rootElement, bool singleLine, bool endLine, bool indent) {
    this->setName(name, false);
    this->type = DTD_DOCTYPE;
    this->setAttribute("root_element", rootElement);
    this->singleLine = singleLine;
    this->indent = indent;
    this->endLine = endLine;
}

DoctypeDTD::DoctypeDTD(DoctypeDTD const & original) {
    this->name = original.name;
    this->type = original.type;
    this->attributes = original.attributes;
    this->indent = indent;
    this->endLine = endLine;

    /* Copy nested children, if any */
    if(original.getChildAmount() > 0) {
        for(auto it : original.children) {
            this->pushBackChild(*it);
        }
    }
}

DoctypeDTD::~DoctypeDTD(void) {
    /* Deleting any dynamically allocated children */
    if(this->getChildAmount() > 0) {
        for(auto it : this->children) {
            delete it;
        }
    }
}


/* Attribute Get/Set member functions */

void DoctypeDTD::setRootElement(std::string const & rootElement) {
    this->setAttribute("root_element", rootElement);
}

std::string DoctypeDTD::getRootElement(void) const {
    return this->getAttribute("root_element");
}

void DoctypeDTD::setExtType(std::string const & extType) {
    this->setAttribute("ext_type", extType);
}

std::string DoctypeDTD::getExtType(void) const {
    return this->getAttribute("ext_type");
}

void DoctypeDTD::setExtLink(std::string const & extLink) {
    this->setAttribute("ext_link", extLink);
}

std::string DoctypeDTD::getExtLink(void) const {
    return this->getAttribute("ext_link");
}

void DoctypeDTD::unsetExt(void) {
    this->delAttribute("ext_type");
    this->delAttribute("ext_link");
}


/* Child DTD management member functions */

void DoctypeDTD::addChild(int pos, DTD const & value) {
    this->children.insert(this->children.begin() + pos, dynamic_cast<DTD *>(value._copy()));
}

void DoctypeDTD::delChild(int pos) {
    this->children.erase(this->children.begin() + pos);
}

void DoctypeDTD::pushBackChild(DTD const & value) {
    this->children.push_back(dynamic_cast<DTD *>(value._copy()));
}

void DoctypeDTD::popBackChild(void) {
    this->children.pop_back();
}

Node * DoctypeDTD::getChild(int pos) {
    if((size_t)pos < this->getChildAmount())
        return this->children.at((size_t)pos);
    else
        return nullptr;
}

Node * DoctypeDTD::getChild(std::string const & name) {
    int index;
    if(this->findChild(name.c_str(), &index))
        return this->children.at(index);
    else
        return nullptr;
}

size_t DoctypeDTD::getChildAmount(void) const {
    return this->children.size();
}

bool DoctypeDTD::childrenEmpty(void) const {
    return this->children.empty();
}

bool DoctypeDTD::findChild(char const * nameToFind, int * index) {
    /* Check all child elements */
    for(size_t i = 0; i < this->getChildAmount(); i++) {
        if(this->children.at(i)->getName().compare(nameToFind) == 0) {
            *index = i;
            return true;
        }
    }
    /* Return false if none found */
    *index = -1;
    return false;
}


/* Other */

std::string DoctypeDTD::print(int indentLevel) {
    std::string result;

    /* Indenting if desired */
    if(this->indent && indentLevel > 0) {
        for(int i = 0; i < indentLevel; i++)
            result += "\t";
    }

    result += "<!" + this->type + " " + this->getRootElement();

    /* Adding link to external DTD if specified */
    if(this->attributes.find("ext_link") != this->attributes.end()) {
        /* Defaulting ext_type to DTD_SYSTEM if unspecified */
        if(this->attributes.find("ext_type") != this->attributes.end())
            result += " " + this->getExtType();
        else
            result += " " DTD_SYSTEM;
        
        /* Adding specified link */
        result += " \"" + this->getExtLink() + "\"";
    }

    if(this->getChildAmount() > 0) {
        /* Printing the child element section start*/
        result += " [";
        if(!this->singleLine)
            result += "\n";
        
        /* Printing all the child elements */
        for(auto it : this->children) {
            if(this->singleLine)
                result += it->print();
            else
                result += it->print(indentLevel + 1);
        }

        /* Closing child element section (with indents if desired) */
        if(this->indent && indentLevel > 0) {
            for(int i = 0; i < indentLevel; i++)
                result += "\t";
        }
        result += "]";
    }

    /* Closing DTD element */
    result += ">";

    if(this->endLine)
        result += "\n";

    return result;
}

Node * DoctypeDTD::_copy(void) const {
    return new DoctypeDTD(*this);
}