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

/* TODO Print behavior:
    - if content DTD_EMPTY or DTD_ANY print without parentheses
    - otherwise print with parentheses
*/

/** 
 * @class ElementDTD
 * @author Linux-Tech-Tips
 * @brief XML Element DTD (describing an XML element) class
 * 
 * The XML Element DTD class, describing an XML element
 * The recognized attributes for this class are:
 *  - 'element_name' ... the name of the element which this DTD describes
 *  - 'content' ... the content of the element description
*/
class ElementDTD : public DTD {

    public:
        /** Constructor
         *  @param name the internal identifying name of the element, not displayed
         *  @param elementName the name of the element which the DTD describes
         *  @param content the content of the element description (rendered in parentheses)
         *  @param indent whether the DTD should be indented if nested
         *  @param endLine whether the DTD should end the line it's on
        */
        ElementDTD(std::string const & name = "_default_element_dtd", std::string const & elementName = "default_element", std::string const & content = "", bool indent = true, bool endLine = true);

        /** Sets the content of the element to a list of the specified values. 
         * To specify a nested XOR within a comma-separated sequence, specify the whole bracket-enclosed item as a single string
         *  @param contentValues a static array of the content values describing the element
         *  @param amount the size of the static 'contentValues' array
         *  @param mixedContent if true, the list is saved as mixed content, separated by pipe characters ('|'). Otherwise saved as a comma-separated sequence
        */
        void setContent(std::string const * const contentValues, size_t amount, bool mixedContent = false);

        /** Sets the content of the element directly to the specified string */
        void setContent(std::string const & content);

        /** Adds the specified value to the current content variable 
         *  @param contentValue the value of the content describing the XML Element
         *  @param mixedContent if true, the value is added as mixed content, separated by a pipe character ('|'). Otherwise separated by a comma
        */
        void addContentValue(std::string const & contentValue, bool mixedContent = false);

        /** Returns the processed XML of the Element DTD, with the specified content enclosed in brackets, if applicable */
        std::string print(int indentLevel = 0);

        /** Creates a dynamically allocated copy of itself
         * Used internally - if called by an end-user, make sure to delete the copy once not needed
        */
        Node * _copy(void) const;

};

#endif /* XML_ELEMENT_DTD_H */