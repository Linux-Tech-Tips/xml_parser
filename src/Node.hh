/**
 * @file Node.hh
 * @author Linux-Tech-Tips
 * @brief Base XML Node class declaration header
 *
 * The header declaring the base XML Node class, containing a name and attributes, and a virtual print function
 * 
 */
#ifndef NODE_H
#define NODE_H

#include <string>
#include <stdexcept>
#include <regex>

/** 
 * @class Node
 * @author Linux-Tech-Tips
 * @brief Base XML Node class
 * 
 * The base XML Node class, containing a name, attributes, general XML Node settings and a virtual print function. 
 * Is expected to be inherited from by extending classes, defining specific nodes with special behavior. 
*/
class Node {

    protected:
        /** The name of the node, serves as an identifier and is printed in XML */
        std::string name;
        /** Whether the element ends the line it's on */
        bool endLine;
        /** Whether the element should take the indent level into consideration */
        bool indent;
        /** The attributes of the node in key-value pairs, both keys and values printed in XML */
        std::map<char const *, std::string> attributes;

        /** Internal function to check whether a given name is XML-compliant */
        bool checkName(std::string name, bool xmlReserved = true);

    public:
        /* Constructors */
        /** Simple constructor 
         *  @param name the name of the Node
         *  @param endLine whether the Node should end the line it's on
         *  @param indent whether the Node should be indented if nested
        */
        Node(std::string const & name = "_default_node", bool endLine = true, bool indent = true);

        /* Destructor */
        virtual ~Node(void) = default;


        /* Member functions */

        /* Name */

        /** Sets the name of the node
         *  @param checkName if true, checks whether given name XML-compliant
         */
        virtual void setName(std::string const & name, bool checkName = true);
        /** Returns the current name of the node */
        virtual std::string getName(void);


        /* Attribute */

        /** Sets the attribute of the given key to the given value. 
         * If the attribute doesn't exist, it is created with the value.
         */
        virtual void setAttribute(char const * name, std::string const & value);
        /** Returns the current value of the attribute with the given name */
        virtual std::string getAttribute(char const * name);
        /** Deletes the attribute with the specified name */
        virtual void delAttribute(char const * name);
        /** Returns the current amount of existing attributes */
        virtual size_t getAttributeNumber(void) const;
        /** Returns whether the attributes map is empty */
        virtual bool isAttributeEmpty(void) const;


        /* Other */

        /** Sets whether the element should end the line */
        virtual void setEndLine(bool EndLine);
        /** Gets whether the element ends the line */
        virtual bool getEndLine(void) const;
        /** Sets whether the element should be indented */
        virtual void setIndent(bool indent);
        /** Gets whether the element is indented */
        virtual bool getIndent(void) const;
        /** Returns the processed XML of the current node's name and attributes in XML angle brackets */
        virtual std::string print(int indentLevel = 0);

        /** Creates a dynamically allocated copy of itself
         * Used internally - if called by an end-user, make sure to delete the copy once not needed
        */
        virtual Node * _copy(void) const;

};

#endif /* NODE_H */