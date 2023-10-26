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
        /* Constructors (and destructor) */

        /** Simple constructor 
         *  @param name the name of the element
         *  @param singleLine whether the nested elements should be on the same line as the XmlElement's tag or on a separate line
         *  @param endLine whether the element should end the line it's on
         *  @param indent whether the element itself should be indented (if nested)
         *  @param checkName if true, check whether the specified name is XML compliant
        */
        XmlElement(std::string const & name = "_default_element", bool singleLine = false, bool endLine = true, bool indent = true, bool checkName = true);

        /** Copy constructor - copies the XmlElement, along with all its child elements */
        XmlElement(XmlElement const & original);

        ~XmlElement(void);


        /* Member functions */


        /* Child elements */

        /** Add a nested child element to the given position */
        void addChild(int pos, Node const & value);
        /** Delete a nested child element from the given position */
        void delChild(int pos);
        
        /** Add a nested child element to the end of the list */
        void pushBackChild(Node const & value);
        /** Remove a nested child element from the back of the list */
        void popBackChild(void);

        /** Get a pointer to the nested child element from the given position (or null pointer if out of bounds). 
         * The function exposes the pointer to the inner child Node directly, and therefore the returned pointer should not be deleted after use.
        */
        Node * getChild(int index);
        /** Get a pointer to the n-th nested child element with the given name (or null pointer if not found or offset out of range). 
         * The function exposes the pointer to the inner child Node directly, and therefore the returned pointer should not be deleted after use.
         *  @param offset which found named child to get (leave default or 0 for the first child; the amount of found named children specified by offset is skipped)
        */
        Node * getChild(char const * childName, size_t offset = 0);
        
        /** Get how many nested child elements are currently in this element */
        size_t getChildAmount(void) const;
        /** Get how many nested child elements with the specified name are currently in this element */
        size_t getChildAmount(char const * childName) const;
        /** Get whether no children present (the list is empty) */
        bool childrenEmpty(void) const;

        /** Returns whether an n-th child element with the given name exists and saves the index of the n-th match
         * @param index the saved index; if index < 0, element was not found (pass nullptr to not save index)
         * @param offset which named child to look for (leave default or 0 for the first child; the amount of found named children specified by offset is skipped)
        */
        bool findChild(char const * nameToFind, int * index = nullptr, size_t offset = 0);


        /* Other */

        /** Set whether the whole element (including all nested Nodes) should be rendered on a single line */
        void setSingleLine(bool singleLine);
        /** Get whether the whole element (including all nested Elements) is rendered on a single line*/
        bool getSingleLine(void) const;
        /** Returns the processed XML using the specified settings and content */
        std::string print(int indentLevel = 0);

        /** Creates a dynamically allocated copy of itself
         * Used internally - if called by an end-user, make sure to delete the copy once not needed
        */
        Node * _copy(void) const;

};



#endif /* XML_ELEMENT_H */