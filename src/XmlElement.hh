/**
 * @file XmlElement.hh
 * @author Linux-Tech-Tips
 * @brief XML Element class declaration header
 *
 * The header declaring a Node representing an XML Element, including attributes and child elements
 */

#ifndef XML_ELEMENT_H
#define XML_ELEMENT_H

#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <regex>

#include "Node.hh"

/** 
 * @class XmlElement
 * @author Linux-Tech-Tips
 * @brief Standard XML Element class
 * 
 * A standard XML Element, wuth a name, attributes and nested child elements
*/
class XmlElement: public Node {

    protected:
        /** The nested child Nodes of the element */
        std::vector<Node *> children;
        /** Whether the XmlElement should occupy only one line, including all its directly nested elements */
        bool singleLine;
    
    public:
        /* Constructors */

        /** Simple constructor 
         *  @param name the name of the element
         *  @param singleLine whether the nested elements should be on the same line as the XmlElement's tag or on a separate line
         *  @param endLine whether the element should end the line it's on
         *  @param indent whether the element itself should be indented (if nested)
         *  @param checkName if true, check whether the specified name is XML compliant
        */
        XmlElement(std::string const & name = "_default_element", bool singleLine = false, bool endLine = true, bool indent = true, bool checkName = true);
        /** Constructor 
         *  @param name the name of the element
         *  @param attributes initialize with this map of attributes instead of an empty one
         *  @param children initialize with this vector of nested elements instead of an empty one
         *  @param singleLine whether the nested elements should be on the same line as the XmlElement's tag or on a separate line
         *  @param endLine whether the element should end the line it's on
         *  @param indent whether the element itself should be indented (if nested)
         *  @param checkName if true, check whether the specified name is XML compliant
        */
        XmlElement(std::string const & name, std::map<char const *, std::string> & attributes, std::vector<Node *> & children, bool singleLine = false, bool endLine = true, bool indent = true, bool checkName = true);


        /* Member functions */


        /* Child elements */

        /** Add a nested child element to the given position */
        void addChild(int pos, Node & value);
        /** Get a nested child element from the given position */
        Node & getChild(int index);
        /** Delete a nested child element from the given position */
        void delChild(int pos);
        /** Add a nested child element to the end of the list */
        void pushBackChild(Node & value);
        /** Remove a nested child element from the back of the list */
        void popBackChild(void);
        /** Get how many nested child elements are currently in this element */
        size_t getChildAmount(void);
        /** Get whether no children present (the list is empty) */
        bool childrenEmpty(void);


        /* Other */

        /** Set whether the whole element (including all nested Nodes) should be rendered on a single line */
        void setSingleLine(bool singleLine);
        /** Get whether the whole element (including all nested Elements) is rendered on a single line*/
        bool getSingleLine(void);
        /** Returns the processed XML using the specified settings and content */
        std::string print(int indentLevel = 0);

};



#endif /* XML_ELEMENT_H */