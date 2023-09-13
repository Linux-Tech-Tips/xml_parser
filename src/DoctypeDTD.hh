/**
 * @file DoctypeDTD.hh
 * @author Linux-Tech-Tips
 * @brief XML Doctype DTD element class declaration header
 *
 * The header declaring the class of the XML Doctype specific DTD header
 */
#ifndef XML_DOCTYPE_H
#define XML_DOCTYPE_H

#include <string>
#include <vector>

#include "DTD.hh"

/** 
 * @class DoctypeDTD
 * @author Linux-Tech-Tips
 * @brief XML Doctype DTD element class
 * 
 * The XML Doctype DTD element class, containing the DOCTYPE DTD directive and the root element name.
 * The inherited name serves as a unique identifier and is not displayed.
 * The class can hold multiple nested DTD elements, printed in square brackets. 
 * The recognized attributes for this class are: 
 *  - 'root_element' ... the root element of the XML Document
 *  - 'ext_type' ... the type of an external DTD file - DTD_SYSTEM / DTD_PUBLIC (only used when ext_link attribute also specified)
 *  - 'ext_link' ... the link to the external DTD file or catalog, displayed only if set (the type is specified as ext_type, or DTD_SYSTEM by default)
*/
class DoctypeDTD : public DTD {

    protected:
        /** Child DTD elements nested within the Doctype DTD element */
        std::vector<DTD *> children;
        /** Whether the nested child elements should be rendered on a single line */
        bool singleLine;

    public:
        /** Constructor
         *  @param name the internal identifying name of the element, not displayed
         *  @param rootElement the root element of the XML document, to be specified in the Doctype DTD
         *  @param singleLine whether the nested child DTD elements should be on the same line as the DTD or the following line
         *  @param endLine whether the DTD should end the line it's on
         *  @param indent whether the DTD should be indented if nested
        */
        DoctypeDTD(std::string const & name = "_default_doctype_dtd", std::string const & rootElement = "default_element", bool singleLine = false, bool endLine = true, bool indent = false);

        /** Copy constructor */
        DoctypeDTD(DoctypeDTD const & original);

        ~DoctypeDTD(void);


        /* Attribute Get/Set member functions */

        /** Sets the 'root_element' attribute to the specified value */
        void setRootElement(std::string const & rootElement);
        /** Gets the current value of the 'root_element' attribute */
        std::string getRootElement(void) const;

        /** Sets the 'ext_type' attribute to the specified value (recommended to use DTD_* constants) */
        void setExtType(std::string const & extType);
        /** Gets the current value of the 'ext_type' attribute */
        std::string getExtType(void) const;

        /** Sets the 'ext_link' attribute to the specified value (recommended to use DTD_* constants) */
        void setExtLink(std::string const & extLink);
        /** Gets the current value of the 'ext_link' attribute */
        std::string getExtLink(void) const;

        /** Unsets  the 'ext_link' and 'ext_type' attributes */
        void unsetExt(void);


        /* Child DTD management member functions */

        /** Adds a nested DTD child element to the given position */
        void addChild(int pos, DTD const & value);
        /** Deletes a nested DTD child element from the given position */
        void delChild(int pos);

        /** Adds a nested DTD child element to the end of the list */
        void pushBackChild(DTD const & value);
        /** Removes the last nested DTD element */
        void popBackChild(void);

        /** Returns a pointer to the internally stored nested DTD element at the given position (or null pointer if out of bounds) */
        Node * getChild(int pos);
        /** Returns a pointer to the internally stored nested DTD child element with the given name (or null pointer if no such child exists) */
        Node * getChild(std::string const & name);

        /** Returns the current amount of existing child DTD elements */
        size_t getChildAmount(void) const;
        /** Get whether the list of nested child DTD elements is empty */
        bool childrenEmpty(void) const;

        /** Returns whether a child DTD element with the given name exists, and if so, saves the index of the first match 
         *  @param index the saved index; if index < 0, the child was not found (pass nullptr to not save index)
        */
        bool findChild(char const * nameToFind, int * index = nullptr);


        /* Other */

        /** Returns the processed XML of the Doctype DTD element */
        std::string print(int indentLevel = 0);

        /** Creates a dynamically allocated copy of itself
         * Used internally - if called by an end-user, make sure to delete the copy once not needed
        */
        Node * _copy(void) const;

};

#endif /* XML_DOCTYPE_H */