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
TextElement::TextElement(void) {
    this->setName("_default_text_element");
    this->showTag = true;
    this->escapeSpecial = true;
    this->endLine = true;
}

TextElement::TextElement(std::string name) {
    this->setName(name);
    this->showTag = true;
    this->escapeSpecial = true;
    this->endLine = true;
}

TextElement::TextElement(std::string name, std::string content) {
    this->setName(name);
    this->textContent = content;
    this->showTag = true;
    this->escapeSpecial = true;
    this->endLine = true;
}

TextElement::TextElement(std::string name, std::string content, bool showTag) {
    this->setName(name);
    this->textContent = content;
    this->showTag = showTag;
    this->escapeSpecial = true;
    this->endLine = showTag;
}

TextElement::TextElement(std::string name, std::string content, bool showTag, bool endLine) {
    this->setName(name);
    this->textContent = content;
    this->showTag = showTag;
    this->escapeSpecial = true;
    this->endLine = endLine;
}

TextElement::TextElement(std::string name, std::string content, bool showTag, bool endLine, bool escapeSpecial) {
    this->setName(name);
    this->textContent = content;
    this->showTag = showTag;
    this->escapeSpecial = escapeSpecial;
    this->endLine = endLine;
}

TextElement::TextElement(std::string name, std::string content, bool showTag, bool endLine, bool escapeSpecial, std::map<char const *, std::string> & attributes) {
    this->setName(name);
    this->textContent = content;
    this->showTag = showTag;
    this->attributes = attributes;
    this->escapeSpecial = escapeSpecial;
    this->endLine = endLine;
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

std::string TextElement::print(int indentLevel) {
    std::string result;
    /* Indent at the start */
    if(indentLevel > 0) {
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

