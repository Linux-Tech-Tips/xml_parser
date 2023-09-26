#include "Comment.hh"

Comment::Comment(std::string const & name, std::string const & content, bool showName, bool endLine, bool indent) {
    this->setName(name, false);
    this->content = content;
    this->showName = showName;
    this->endLine = endLine;
    this->indent = indent;
}


/* Internal content get/set functions */

void Comment::setContent(std::string const & content) {
    this->content = content;
}

std::string Comment::getContent(void) const {
    return this->content;
}

void Comment::setShowName(bool showName) {
    this->showName = showName;
}

bool Comment::getShowName(void) const {
    return this->showName;
}


/* Other functions */

std::string Comment::print(int indentLevel) {
    std::string result;
    
    /* Indent if desired */
    if(this->indent && indentLevel > 0) {
        for(int i = 0; i < indentLevel; i++)
            result += "\t";    
    }

    result += "<!-- ";

    if(this->showName) {
        result += this->name + " ";
    }

    result += this->content + " -->";

    if(this->endLine)
        result += "\n";

    return result;
}

Node * Comment::_copy(void) const {
    return new Comment(*this);
}