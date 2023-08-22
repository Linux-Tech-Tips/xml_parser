/**
 * @file XmlPrologElement.hh
 * @author Linux-Tech-Tips
 * @brief XML Prolog element class declaration header
 *
 * The header declaring the class of an element containing the XML prolog
 */
#ifndef XML_PROLOG_H
#define XML_PROLOG_H

#include <string>
#include <string.h>

#include "Node.hh"

/** Define for the standalone setting 'yes', to make sure the argument is specified correctly */
#define STANDALONE_YES "yes"
/** Define for the standalone setting 'no', to make sure the argument is specified correctly */
#define STANDALONE_NO "no"
/** Define to unset the standalone setting, if set to this, the argument won't print */
#define STANDALONE_UNSET ""

/** 
 * @class XmlPrologElement
 * @author Linux-Tech-Tips
 * @brief XML Prolog Element class
 * 
 * The element containing an XML Prolog, including the valid attributes - version, encoding and standalone
*/
class XmlPrologElement : public Node {

    private:
        /** The version of the XML document, as defined in the prolog */
        float xmlVersion;
        /** The encoding of the XML document, as defined in the prolog */
        std::string encoding;
        /** The standalone option of the XML document, as defined in the prolog */
        char const * standalone;
        /** Whether to print additional user-defined attributes into the prolog */
        bool printUserAttributes;

    public:
        /** Constructor 
         *  @param name the name of the element, used for internal identification only (doesn't print)
         *  @param xmlVersion the version of the XML document to be specified in the prolog - mandatory
         *  @param encoding the encoding of the XML document to be specified in the prolog (leave blank to not print)
         *  @param standalone the standalone option of the XML document to be specified in the prolog (set using the defines, set to STANDALONE_UNSET to not print)
         *  @param endLine whether the element should end the line it's on
         *  @param indent whether the element should be indented if nested
         *  @param printUserAttributes whether user-defined additional attributes are printed - the recommended value is 'false'
        */
        XmlPrologElement(std::string const & name = "_default_prolog_element", float xmlVersion = 1.0f, std::string const & encoding = "", const char * standalone = STANDALONE_UNSET, bool endLine = true, bool indent = false, bool printUserAttributes = false);

        /* Default XML prolog parameter member function */

        /** Sets the XML version to be displayed in the prolog */
        void setXmlVersion(float xmlVersion);
        /** Gets the XML version displayed in the prolog */
        float getXmlVersion(void);

        /** Sets the encoding to be displayed in the XML prolog */
        void setEncoding(std::string const & encoding);
        /**  Gets the encoding displayed in the XML prolog */
        std::string getEncoding(void);

        /** Sets the standalone setting to be displayed in the XML prolog 
         *  @param standalone recommended to use the defines, set to STANDALONE_UNSET to not print
        */
        void setStandalone(char const * standalone);
        /** Gets the standalone setting displayed in the XML prolog */
        char const * getStandalone(void);

        /** Sets whether additional user-defined attributes should be printed in the XML prolog - recommended 'false' */
        void setUserAttributes(bool printUserAttributes);
        /** Gets whether additional user-defined attributes are printed in the XML prolog*/
        bool getUserAttributes(void);

        /* Other member functions */

        /** Returns the processed XML of the prolog with the specified settings */
        std::string print(int indentLevel = 0);

        /** Creates a dynamically allocated copy of itself
         * Used internally - if called by an end-user, make sure to delete the copy once not needed
        */
        Node * _copy(void) const;
};

#endif /* XML_PROLOG_H */