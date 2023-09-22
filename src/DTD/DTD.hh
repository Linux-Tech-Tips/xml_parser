/**
 * @file DTD.hh
 * @author Linux-Tech-Tips
 * @brief XML DTD (Document Type Definition) element class declaration header
 *
 * The header declaring the class of the XML Document Type Definition
 */
#ifndef XML_DTD_H
#define XML_DTD_H

#include <string>

#include "../Node.hh"

/* DTD Type defines */

/** !DOCTYPE DTD */
#define DTD_DOCTYPE "DOCTYPE"
/** !ELEMENT DTD */
#define DTD_ELEMENT "ELEMENT"
/** !ATTLIST DTD - Attribute list */
#define DTD_ATTRIBUTES "ATTLIST"
/** !ENTITY DTD */
#define DTD_ENTITY "ENTITY"

/* DTD External content keyword defines */

/** SYSTEM external DTD identifier */
#define DTD_EXTERN_SYSTEM "SYSTEM"
/** PUBLIC external DTD identifier */
#define DTD_EXTERN_PUBLIC "PUBLIC"

/* DTD Element Content type keyword defines */

/** DTD PCDATA (Parsed character data) content type */
#define DTD_CONTENT_PCDATA "#PCDATA"
/** DTD EMPTY content type */
#define DTD_CONTENT_EMPTY "EMPTY"
/** DTD ANY content type */
#define DTD_CONTENT_ANY "ANY"

/* DTD Attribute keyword defines */

/** DTD CDATA (character data, string) attribute type */
#define DTD_ATTR_CDATA "CDATA"
/** DTD ID (unique identifier) attribute type */
#define DTD_ATTR_ID "ID"
/** DTD IDREF (reference to an id of another element) attribute type */
#define DTD_ATTR_IDREF "IDREF"
/** DTD IDREFS (list of ID references) attribute type */
#define DTD_ATTR_IDREFS "IDREFS"
/** DTD ENTITY attribute type */
#define DTD_ATTR_ENTITY "ENTITY"
/** DTD ENTITIES (list of entities) attribute type */
#define DTD_ATTR_ENTITIES "ENTITIES"
/** DTD NMTOKEN (valid XML name) attribute type */
#define DTD_ATTR_NMTOKEN "NMTOKEN"
/** DTD NMTOKENS (a list of valid XML names) attribute type */
#define DTD_ATTR_NMTOKENS "NMTOKENS"

/** DTD REQUIRED attribute value identifier */
#define DTD_ATTR_REQUIRED "#REQUIRED"
/** DTD IMPLIED (optional) attribute value identifier */
#define DTD_ATTR_IMPLIED "#IMPLIED"
/** DTD FIXED (must be the set value) attribute value identifier, to be followed by a string value (enclosed in double quotes) */
#define DTD_ATTR_FIXED "#FIXED"



/** 
 * @class DTD
 * @author Linux-Tech-Tips
 * @brief XML Document Type Definition element class
 * 
 * The base XML DTD (Document Type Definition) element class, containing the name of the root element. To be extended by specific DTD classes. 
 * The inherited name serves as a unique identifier and is not displayed.
 * Each inheriting DTD subclass uses attributes its way, for the purposes of the specific DTD. This usage is described for each class.
 * For the base class, the only recognised attribute is 'content', which is displayed in the element.
 * Content manipulation member functions are overloaded in inheriting classes, to get/set all the available content of the given DTD type.
*/
class DTD : public Node {

    protected:
        /** The type of the DTD, to be set using the defined constants */
        std::string type;

    public:
        /** Constructor 
         *  @param name the internal identifying name of the DTD (not displayed)
         *  @param type the type of the DTD, which is actually displayed
         *  @param indent whether the DTD should be indented if nested
         *  @param endLine whether the DTD should end the line it's on
        */
        DTD(std::string const & name = "_default_base_DTD", std::string const & type = DTD_DOCTYPE, std::string const & content = "", bool indent = true, bool endLine = true);

        /** Sets the 'content' attribute to the desired content */
        virtual void setContent(std::string const & content);

        /** Saves the current value of the 'content' attribute to the given parameter */
        virtual void getContent(std::string & content) const;

        /** Removes any content from this element */
        void delContent(void);

        /** Returns the processed XML of the DTD */
        std::string print(int indentLevel = 0);

        /** Creates a dynamically allocated copy of itself
         * Used internally - if called by an end-user, make sure to delete the copy once not needed
        */
        Node * _copy(void) const;

};

#endif /* XML_DTD_H */