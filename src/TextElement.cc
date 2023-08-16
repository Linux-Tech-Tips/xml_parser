#include "TextElement.hh"

/* Private member functions */
std::string TextElement::escapeContent(std::string content) {
    std::string result;
    for(char & it : content) {
        switch(it) {
            case '"':
                result += "&quot;";
                break;
            case '\'':
                result += "&apos;";
                break;
            case '<':
                result += "&lt;";
                break;
            case '>':
                result += "&gt;";
                break;
            case '&':
                result += "&amp";
                break;
            default:
                result += it;
        }
    }
    return result;
}

/* Constructors */
TextElement::TextElement(
        std::string name, std::string content, 
        bool showTag, bool indent, bool escapeSpecial
    ) : TextElement(name, content, showTag, indent, showTag, escapeSpecial) {}

TextElement::TextElement(std::string name, std::string content, bool showTag, bool indent, bool endLine, bool escapeSpecial) {
    this->setName(name);
    this->textContent = content;
    this->showTag = showTag;
    this->indent= indent;
    this->escapeSpecial = escapeSpecial;
    this->endLine = endLine;
}

TextElement::TextElement(
        std::string name, std::string content, 
        bool showTag, bool indent, bool endLine, bool escapeSpecial, 
        std::map<char const *, std::string> & attributes
    ) : TextElement(name, content, showTag, indent, endLine, escapeSpecial) {
        
    this->attributes = attributes;
}

/* Member functions */

/* Text content */
void TextElement::setContent(std::string content) {
    this->textContent = content;
}

std::string TextElement::getContent(void) {
    return this->textContent;
}


/* Other */
void TextElement::setShowTag(bool showTag) {
    this->showTag = showTag;
}

bool TextElement::getShowTag(void) {
    return this->showTag;
}

void TextElement::setEscapeSpecial(bool escapeSpecial) {
    this->escapeSpecial = escapeSpecial;
}

bool TextElement::getEscapeSpecial(void) {
    return this->escapeSpecial;
}

std::string TextElement::print(int indentLevel) {
    std::string result;
    /* Indent at the start */
    if(indent && indentLevel > 0) {
        for(int i = 0; i < indentLevel; i++) {
            result += "\t";
        }
    }
    /* Printing tag start if desired */
    if(this->showTag) {
        result += "<" + this->name;
        for(auto it : this->attributes) {
            result += " ";
            result += it.first;
            result += "=\"" + it.second + "\"";
        }
        result += ">";
    }

    /* Printing formatted text content */
    if(this->escapeSpecial) {
        result += this->escapeContent(this->textContent);
    } else {
        result += this->textContent;
    }

    /* Printing tag end if desired */
    if(this->showTag)
        result += "</" + this->name + ">";
    if(this->endLine)
        result += "\n";
    
    return result;
}

