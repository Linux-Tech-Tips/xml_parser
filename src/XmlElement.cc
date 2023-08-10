#include "XmlElement.hh"

/* === Private member functions === */

bool XmlElement::checkName(std::string name, bool xmlReserved) {
    return std::regex_match(name, std::regex("(_|[a-zA-Z])[\\w-.]*")) && (!xmlReserved || name != "xml");
}

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

XmlElement::XmlElement(std::string const & name, std::map<char const *, std::string> attributes, std::vector<XmlElement> childEl, bool singleLine, bool increment) {
    this->setName(name);
    this->attributes = attributes;
    this->childEl = childEl;
    this->singleLine = singleLine;
    this->increment = increment;
}

XmlElement::XmlElement(std::string const & name, std::map<char const *, std::string> attributes, std::vector<XmlElement> childEl, bool singleLine, bool increment, bool checkName) {
    this->setName(name, checkName);
    this->attributes = attributes;
    this->childEl = childEl;
    this->singleLine = singleLine;
    this->increment = increment;
}


/* Member functions */

/* Name */
void XmlElement::setName(std::string name, bool checkName) {
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

std::string XmlElement::getName(void) {
    return this->name;
}

/* Attribute */
void XmlElement::setAttribute(char const * name, std::string const & value) {
    this->attributes[name] = value;
}

std::string XmlElement::getAttribute(char const * name) {
    if(this->attributes.find(name) != this->attributes.end())
        return this->attributes[name];
    else
        return "";
}

size_t XmlElement::getAttributeNumber(void) {
    return this->attributes.size();
}

bool XmlElement::isAttributeEmpty(void) {
    return this->attributes.empty();
}

/* Child elements */
void XmlElement::addChild(int pos, XmlElement const & value) {
    this->childEl.insert(this->childEl.begin() + pos, value);
}

XmlElement & XmlElement::getChild(int index) {
    if(index < this->childEl.size())
        return this->childEl[index];
    else
        throw std::invalid_argument("Error: Element index out of bounds");
}

void XmlElement::delChild(int pos) {
    if(pos < this->childEl.size())
        this->childEl.erase(this->childEl.begin() + pos);
    else
        throw std::invalid_argument("Error: Can't erase at out-of-bounds index");
}

void XmlElement::pushBackChild(XmlElement const & value) {
    this->childEl.push_back(value);
}

void XmlElement::popBackChild(void) {
    this->childEl.pop_back();
}

size_t XmlElement::getChildNumber(void) {
    return this->childEl.size();
}

bool XmlElement::isChildEmpty(void) {
    return this->childEl.empty();
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

std::string XmlElement::print(int nestLevel) {
    /* Opening the element */
    std::string result;
    /* Indenting */
    if(nestLevel > 0) {
        for(int i = 0; i < nestLevel; i++) {
            result += "\t";
        }
    }
    result += "<" + this->name + "";
    for(std::map<char const *, std::string>::iterator it = this->attributes.begin(); it != this->attributes.end(); it++) {
        result += " ";
        result += it->first;
        result += "=\"" + it->second + "\"";
    }
    /* Closing normally, adding content if not empty */
    if(this->childEl.size() > 0) {
        result += ">";
        if(!this->singleLine)
            result += "\n";
        
        /* Adding child elements */
        for(std::vector<XmlElement>::iterator it = this->childEl.begin(); it != this->childEl.end(); it++) {
            if(!this->singleLine && this->increment)
                result += it->print(nestLevel + 1);
            else
                result += it->print();
        }

        /* Closing the element normally, with indents */
        if(nestLevel > 0) {
            for(int i = 0; i < nestLevel; i++) {
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