#include "DTD.hh"

/* Constructor */

DTD::DTD(std::string const & name, std::string const & type, std::string const & content, bool indent, bool endLine) {
    this->setName(name, false);
    this->type = type;
    if(content.length() > 0)
        this->setAttribute("content", content);
    this->indent = indent;
    this->endLine = endLine;
}

/* Other functions */

void DTD::setContent(std::string const & content) {
    this->setAttribute("content", content);
}

std::string DTD::getContent(void) {
    return this->getAttribute("content");
}

void DTD::delContent(void) {
    this->delAttribute("content");
}

std::string DTD::print(int indentLevel) {
    std::string result;

    /* Beginning with indent */
    if(this->indent && indentLevel > 0) {
        for(int i = 0; i < indentLevel; i++) {
            result += "\t";
        }
    }
    result += "<!" + this->type + " ";

    /* Internally, an empty string is returned if the attribute doesn't exist */
    result += this->getAttribute("content");

    /* End with linebreak */
    result += ">";
    if(this->endLine)
        result += "\n";

    return result;
}

Node * DTD::_copy(void) const {
    return new Node(*this);
}