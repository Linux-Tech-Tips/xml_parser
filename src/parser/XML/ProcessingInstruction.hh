/**
 * @file ProcessingInstruction.hh
 * @author Linux-Tech-Tips
 * @brief XML Processing Instruction element class declaration header
 *
 * The header declaring the class of an XML processing instruction
 */
#ifndef PROCESSING_INSTRUCTION_H
#define PROCESSING_INSTRUCTION_H

#include <string>

#include "Node.hh"

/** 
 * @class ProcessingInstruction
 * @author Linux-Tech-Tips
 * @brief XML Processing Instruction Element class
 * 
 * The element containing an XML Processing Instruction (PI), with an overloaded print member function
*/
class ProcessingInstruction : public Node {

    public:
        /** Constructor 
         *  @param name the name/target of the processing instruction - shows up first when printed
         *  @param endLine whether the element should end the line it's on
         *  @param indent whether the element should be indented if nested
        */
        ProcessingInstruction(std::string const & name = "_default_processing_instruction", bool endLine = true, bool indent = false);

        /** Returns the processed XML of the current Processing Instruction, including the target and any attributes */
        std::string print(int indentLevel = 0);

        /** Creates a dynamically allocated copy of itself
         * Used internally - if called by an end-user, make sure to delete the copy once not needed
        */
        Node * _copy(void) const;

};

#endif /* PROCESSING_INSTRUCTION_H */