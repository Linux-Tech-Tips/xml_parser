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
         *  @param rootElement the root element of the XML document, to be specified in the Doctype DTD
         *  @param singleLine whether the nested child DTD elements should be on the same line as the DTD or the following line
         *  @param indent whether the DTD should be indented if nested
         *  @param endLine whether the DTD should end the line it's on
        */
        DoctypeDTD(std::string const & rootElement = "default_element", bool singleLine = false, bool indent = false, bool endLine = true);

        /** Copy constructor */
        DoctypeDTD(DoctypeDTD const & original);

        ~DoctypeDTD(void);


        /* Attribute Get/Set member functions */

        /** Sets the 'root_element' attribute to the specified value */
        void setRootElement(std::string const & rootElement);
        /** Gets the current value of the 'root_element' attribute */
        std::string getRootElement(void) const;

        /** Sets the 'ext_type' attribute to the specified value (recommended to use DTD_EXTERN_* constants) */
        void setExtType(std::string const & extType);
        /** Gets the current value of the 'ext_type' attribute */
        std::string getExtType(void) const;

        /** Sets the 'ext_link' attribute (the link to the external DTD) to the specified value. If an empty string is specified, the attribute is unset */
        void setExtLink(std::string const & extLink);
        /** Gets the current value of the 'ext_link' attribute */
        std::string getExtLink(void) const;

        /** Unsets  the 'ext_link' and 'ext_type' attributes */
        void unsetExt(void);


        /* Content management member functions */

        /** Sets all the available content fields to the given values (if empty string specified for extLink, the attribute is unset) */
        void setContent(std::string const & rootElement, std::string const & extType = "", std::string const & extLink = "");

        /** Saves all the available content fields to the given variables (if empty string saved, the content is unset) */
        void getContent(std::string & rootElement, std::string & extType, std::string & extLink) const;

        /** Removes all the supported content fields */
        void delContent(void);


        /* Child DTD management member functions */

        /** Adds a nested DTD child element to the given position */
        void addChild(int pos, DTD const & value);
        /** Deletes a nested DTD child element from the given position */
        void delChild(int pos);

        /** Adds a nested DTD child element to the end of the list */
        void pushBackChild(DTD const & value);
        /** Removes the last nested DTD element */
        void popBackChild(void);

        /** Returns a pointer to the internally stored nested DTD element at the given position (or null pointer if out of bounds). 
         * The function exposes the pointer to the nested DTD directly, and therefore the returned pointer should not be deleted after use.
        */
        Node * getChild(int pos);
        /** Returns a pointer to the n-th internally stored nested DTD child element with the given name (or null pointer if no such child exists). 
         * The function exposes the pointer to the nested DTD directly, and therefore the returned pointer should not be deleted after use.
         *  @param offset which found element to get (leave default or 0 for the first element; the amount of found named children specified by the offset is skipped)
        */
        Node * getChild(char const * name, size_t offset = 0);

        /** Returns the current amount of existing child DTD elements */
        size_t getChildAmount(void) const;
        /** Returns the current amount of existing child DTD elements with the given name */
        size_t getChildAmount(char const * name) const;
        /** Get whether the list of nested child DTD elements is empty */
        bool childrenEmpty(void) const;

        /** Returns whether a child DTD element with the given name exists, and if so, saves the index of the first match 
         *  @param index the saved index; if index < 0, the child was not found (pass nullptr to not save index)
         *  @param offset which found element index to save (leave default or 0 for the first element; the amount of found named children specified by the offset is skipped)
        */
        bool findChild(char const * nameToFind, int * index = nullptr, size_t offset = 0);


        /* Other */

        /** Returns the processed XML of the Doctype DTD element */
        std::string print(int indentLevel = 0);

        /** Creates a dynamically allocated copy of itself
         * Used internally - if called by an end-user, make sure to delete the copy once not needed
        */
        Node * _copy(void) const;

};

#endif /* XML_DOCTYPE_H */