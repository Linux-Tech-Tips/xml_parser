#include "ProcessingInstruction.hh"

ProcessingInstruction::ProcessingInstruction(std::string const & name, bool endLine, bool indent) {
    this->setName(name, false);
    this->endLine = endLine;
    this->indent = indent;
}


std::string ProcessingInstruction::print(int indentLevel) {
    std::string result;

    /* Indenting if desired */
    if(this->indent && indentLevel > 0) {
        for(int i = 0; i < indentLevel; i++) {
            result += "\t";
        }
    }

    result += "<?" + this->name;

    /* Adding any user-defined attributes */
    for(auto it : this->attributes) {
        result += " ";
        result += it.first;
        result += "=\"" + it.second + "\"";
    }

    result += "?>";

    if(this->endLine)
        result += "\n";

    return result;
}


Node * ProcessingInstruction::_copy(void) const {
    return new ProcessingInstruction(*this);
}