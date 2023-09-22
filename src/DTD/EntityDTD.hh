/**
 * @file EntityDTD.hh
 * @author Linux-Tech-Tips
 * @brief XML Entity DTD element class declaration header
 *
 * The header declaring the XML Entity DTD class (defining a named shortcut to a value in XML)
 */
#ifndef XML_ENTITY_DTD_H
#define XML_ENTITY_DTD_H

#include <string>

#include "DTD.hh"

/** 
 * @class EntityDTD
 * @author Linux-Tech-Tips
 * @brief XML Entity DTD class
 * 
 * The Entity DTD, defining a named shortcut to a specified value in the XML document.
 * The recognized internal attributes for this class are:
 *  - 'entity_name' ... the name of the XML Entity
 *  - 'entity_value' ... the value of the XML Entity
*/
class EntityDTD : public DTD {

    protected:
        /** If true, the value of the Entity is treated as a string (and is enclosed in quotes) */
        bool stringValue;

    public:
        /** Constructor 
         *  @param name the internal identifying name of the DTD (not displayed)
         *  @param entityName the name of the defined XML Entity
         *  @param entityValue the value of the defined XML Entity
         *  @param stringValue if true, the value is treated as a string and is enclosed in quotes (set to false for fully custom value, e.g. for external entities)
         *  @param indent whether the DTD should be indented if nested
         *  @param endLine whether the DTD should end the line it's on
        */
        EntityDTD(std::string const & name = "_default_entity_DTD", std::string const & entityName = "_default_entity", std::string const & entityValue = "_default_entity_value", bool stringValue = true, bool indent = true, bool endLine = true);

        /** Sets the 'entity_name' attribute of the XML Entity */
        void setEntityName(std::string const & name);

        /** Gets the current value of the 'entity_name' attribute of the XML Entity */
        std::string getEntityName(void) const;

        /** Sets the 'entity_value' attribute of the XML Entity */
        void setEntityValue(std::string const & value, bool isString = true);

        /** Gets the current value of the 'entity_value' attribute of the XML Entity */
        std::string getEntityValue(void) const;

        /** Sets whether the Entity value should be treated as a string (rendered enclosed in quotes) */
        void setStringValue(bool isString);

        /** Gets whether the Entity value is internally considered a string (and rendered in quotes) */
        bool getStringValue(void) const;

        /** Sets all available content fields of the XML Entity */
        void setContent(std::string const & entityName, std::string const & entityValue, bool isString);

        /** Saves all available content fields of the XML Entity into the passed reference arguments */
        void getContent(std::string & entityName, std::string & entityValue, bool & isString) const;

        /** Removes content from all available attributes of this element */
        void delContent(void);


        /* Other functions */

        /** Returns the processed XML of the Entity DTD */
        std::string print(int indentLevel = 0);

        /** Creates a dynamically allocated copy of itself
         * Used internally - if called by an end-user, make sure to delete the copy once not needed
        */
        Node * _copy(void) const;

};

#endif /* XML_ENTITY_DTD_H */