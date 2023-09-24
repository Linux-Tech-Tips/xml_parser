/**
 * @file DTD.hh
 * @author Linux-Tech-Tips
 * @brief XML DTD (Document Type Definition) element class declaration header
 *
 * The header declaring the class of the XML Document Type Definition
 */
#ifndef XML_ELEMENT_DTD_H
#define XML_ELEMENT_DTD_H

#include <string>

#include "DTD.hh"

/** 
 * @class ElementDTD
 * @author Linux-Tech-Tips
 * @brief XML Element DTD (describing an XML element) class
 * 
 * The XML Element DTD class, describing an XML element
 * The recognized attributes for this class are:
 *  - 'element_name' ... the name of the element which this DTD describes
 *  - 'element_content' ... the content of the element description
*/
class ElementDTD : public DTD {

    public:
        /** Constructor
         *  @param elementName the name of the element which the DTD describes
         *  @param content the content of the element description (rendered in parentheses)
         *  @param indent whether the DTD should be indented if nested
         *  @param endLine whether the DTD should end the line it's on
        */
        ElementDTD(std::string const & elementName = "default_element", std::string const & elementContent = "", bool indent = true, bool endLine = true);


        /* Specific content manipulation member functions */

        /** Sets the content of the element to a list of the specified values. 
         * To specify a nested XOR within a comma-separated sequence, specify the whole bracket-enclosed item as a single string
         *  @param contentValues a static array of the content values describing the element
         *  @param amount the size of the static 'contentValues' array
         *  @param mixedContent if true, the list is saved as mixed content, separated by pipe characters ('|'). Otherwise saved as a comma-separated sequence
        */
        void setElementContent(std::string const * const contentValues, size_t amount, bool mixedContent = false);

        /** Sets the content of the element directly to the specified string */
        void setElementContent(std::string const & elementContent);

        /** Adds the specified value to the current content variable 
         *  @param contentValue the value of the content describing the XML Element
         *  @param mixedContent if true, the value is added as mixed content, separated by a pipe character ('|'). Otherwise separated by a comma
        */
        void addElementContent(std::string const & contentValue, bool mixedContent = false);

        /** Returns the specified Element content, as a single string */
        std::string getElementContent(void) const;

        /** Sets the name of the described XML element */
        void setElementName(std::string const & elementName);

        /** Gets the set name of the XML element to be described */
        std::string getElementName(void) const;


        /* General content manipulation member functions */

        /** Sets all the available content fields of the Element DTD, with the specific Element content defined using a list of values. 
         *  @param mixedContent if true, the list is saved as mixed content, separated by pipe characters ('|'). Otherwise saved as a comma-separated sequence
        */
        void setContent(std::string const & elementName, std::string const * const contentValues, size_t amount, bool mixedContent = false);

        /** Sets all the available content fields of the Element DTD, with a directly specified Element content string */
        void setContent(std::string const & elementName, std::string const & elementContent);

        /** Saves all the available content fields of the Element DTD to the given parameters */
        void getContent(std::string & elementName, std::string & elementContent) const;

        /** Removes all the recognized content fields from the DTD */
        void delContent(void);


        /* Other functions */

        /** Returns the processed XML of the Element DTD, with the specified content enclosed in brackets, if applicable */
        std::string print(int indentLevel = 0);

        /** Creates a dynamically allocated copy of itself
         * Used internally - if called by an end-user, make sure to delete the copy once not needed
        */
        Node * _copy(void) const;

};

#endif /* XML_ELEMENT_DTD_H */