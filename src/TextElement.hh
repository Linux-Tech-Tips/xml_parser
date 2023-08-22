/**
 * @file TextElement.hh
 * @author Linux-Tech-Tips
 * @brief XML Text-only Element class declaration header
 *
 * The header declaring a node representing a single-line, text-only element. 
 * The text can be enclosed in an XML tag with attributes, if the text within the element should contain no further elements
 * The node can also represent pure, unenclosed text, to be inserted among other nodes into a parent node
 */
#ifndef TEXT_ELEMENT_H
#define TEXT_ELEMENT_H

#include <string>
#include <map>

#include "Node.hh"

/** 
 * @class TextElement
 * @author Linux-Tech-Tips
 * @brief XML Text-only element
 * 
 * A node representing a text-only element, without child elements but with text content.
 * Can either print only text (to be used as a child element for HTML-like purposes of nested elements within text) 
 * or print the text content enclosed within an XML node of the specified name, with optional attributes.
*/
class TextElement: public Node {

    private:
        /** Escapes any XML special characters in the element's content */
        std::string escapeContent(void);

    protected:
        /** Whether the XML tag with the name and attributes should be shown */
        bool showTag;
        /** Whether special characters are escaped upon rendering */
        bool escapeSpecial;
        /** The actual text content of the element */
        std::string textContent;
    
    public:
        /* Constructors */

        /** Simple constructor
         * By default, if the tag is shown, a line break is added; if the tag is hidden, the element doesn't end the line it's on
         *  @param name the name of the element
         *  @param content the text content of the element
         *  @param showTag whether the XML tag with the name and optionally attributes is shown
         *  @param indent whether the element should be indented if nested
         *  @param escapeSpecial whether XML special characters should be escaped
        */
        TextElement(std::string const & name = "_default_text_element", std::string const & content = "", bool showTag = true, bool indent = true, bool escapeSpecial = true);
        /** Constructor
         *  @param name the name of the element
         *  @param content the text content of the element
         *  @param showTag whether the XML tag with the name and optionally attributes is shown
         *  @param indent whether the element should be indented if nested
         *  @param endLine whether the element should end the line it's on
         *  @param escapeSpecial whether XML special characters should be escaped
        */
        TextElement(std::string const & name, std::string const & content, bool showTag, bool indent, bool endLine, bool escapeSpecial);


        /* Member functions */


        /* Text content */

        /** Sets the text content of the element */
        void setContent(std::string const & content);
        /** Returns the current text content of the element */
        std::string getContent(void);


        /* Other */

        /** Sets whether the XML tag with the name and attributes should be shown */
        void setShowTag(bool showTag);
        /** Get whether the XML tag with the name and attributes is shown */
        bool getShowTag(void) const;
        /** Sets whether XML special characters should be escaped */
        void setEscapeSpecial(bool escapeSpecial);
        /** Gets whether XML special characters are to be escaped */
        bool getEscapeSpecial(void) const;
        /** Returns the processed XML with the text content using the specified settings */
        std::string print(int indentLevel = 0);

        /** Creates a dynamically allocated copy of itself
         * Used internally - if called by an end-user, make sure to delete the copy once not needed
        */
        Node * _copy(void) const;

};

#endif /* TEXT_ELEMENT_H */