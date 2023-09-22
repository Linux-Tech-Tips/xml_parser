/**
 * @file AttributeDTD.hh
 * @author Linux-Tech-Tips
 * @brief XML DTD (Document Type Definition) element class declaration header
 *
 * The header declaring the class of the XML Document Type Definition
 */
#ifndef XML_ATTRIBUTE_DTD_H
#define XML_ATTRIBUTE_DTD_H

#include <string>

#include "DTD.hh"

/** 
 * @class DTD
 * @author Linux-Tech-Tips
 * @brief XML Document Type Definition element class
 * 
 * The Attribute DTD, describing the properties of a specific attribute of a specific element.
 * The recognized internal attributes for this class are:
 *  - 'element_name' ... the name of the element of which an attribute is described
 *  - 'attr_name' ... the name of the described attribute
 *  - 'attr_type' ... the type of the described attribute (recommended to use DTD_ATTR_* constants)
 *  - 'attr_value' ... the value of the attribute (either a literal value, or DTD_ATTR_* constants can be used, or a mix of both for FIXED values)
*/
class AttributeDTD : public DTD {

    protected:
        /** If true, the value of the attribute is treated as a string and surrounded by double quotes */
        bool stringValue;

    public:
        /** Constructor 
         *  @param name the internal identifying name of the DTD (not displayed)
         *  @param element the name of the element of which an attribute is described
         *  @param attribute the name of the described attribute
         *  @param type the type of the described attribute
         *  @param value the value of the described attribute
         *  @param indent whether the DTD should be indented if nested
         *  @param endLine whether the DTD should end the line it's on
        */
        AttributeDTD(
            std::string const & name = "_default_attribute_DTD", std::string const & element = "default_element", 
            std::string const & attribute = "default_attribute", std::string const & type = DTD_ATTR_CDATA, std::string const & value = DTD_ATTR_IMPLIED,
            bool stringValue = false, bool indent = true, bool endLine = true);
        

        /* Get/Set functions for the internal attributes */

        /** Sets the 'element_name' property */
        void setElementName(std::string const & elementName);

        /** Returns the current value of the 'element_name' property */
        std::string getElementName(void) const;

        /** Sets the 'attr_name' property */
        void setAttrName(std::string const & attrName);

        /** Returns the current value of the 'attr_name' property */
        std::string getAttrName(void) const;

        /** Sets the 'attr_type' property */
        void setAttrType(std::string const & attrType);

        /** Returns the current value of the 'attr_type' property */
        std::string getAttrType(void) const;

        /** Sets the 'attr_value' property 
         *  @param isString if true, the attribute value is treated as a string and is surrounded with double quotes in the XML
        */
        void setAttrValue(std::string const & attrValue, bool isString = false);

        /** Returns the current value of the 'attr_value' property */
        std::string getAttrValue(void) const;

        /** Sets whether the attribute value should be treated as a string (and surrounded by double quotes in the XML) */
        void setStringValue(bool isString);

        /** Gets whether the attribute value is treated as a string (surrounded by double quotes in the XML) */
        bool getStringValue(void) const;


        /* General attribute get/set */

        /** Sets the XML Attribute properties to the given values
         *  @param isString if true, the attribute value is treated as a string and is surrounded with double quotes in the XML
        */
        void setAttr(std::string const & attrName, std::string const & attrType, std::string const & attrValue, bool isString = false);

        /** Saves the XML Attribute properties to the given parameters */
        void getAttr(std::string & attrName, std::string & attrType, std::string & attrValue, bool & isString) const;


        /* General content get/set */

        /** Sets all available content fields of the DTD to the given values */
        void setContent(std::string const & elementName, std::string const & attrName, std::string const & attrType, std::string const & attrValue, bool isString = false);

        /** Saves all available content fields of the DTD to the given parameters */
        void getContent(std::string & elementName, std::string & attrName, std::string & attrType, std::string & attrValue, bool & isString) const;

        /** Unsets all available content fields */
        void delContent(void);


        /* Other functions */

        /** Returns the processed XML content of the Attribute DTD */
        std::string print(int indentLevel = 0);

        /** Creates a dynamically allocated copy of itself
         * Used internally - if called by an end-user, make sure to delete the copy once not needed
        */
        Node * _copy(void) const;

};

#endif /* XML_ATTRIBUTE_DTD_H */