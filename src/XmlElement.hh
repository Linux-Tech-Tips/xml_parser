/**
 * @file XmlElement.hh
 * @author Linux-Tech-Tips
 * @brief XML Element class
 *
 * A Node representing an XML Element, including attributes and child elements
 */

#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <regex>

class XmlElement {

    private:
        std::string name;
        std::map<char const *, std::string> attributes;
        std::vector<XmlElement> childEl;
        bool singleLine;
        bool increment;

        bool checkName(std::string name, bool xmlReserved = true);
    
    public:
        /* Constructors */
        XmlElement(void);
        XmlElement(std::string const & name);
        XmlElement(std::string const & name, bool singleLine);
        XmlElement(std::string const & name, std::map<char const *, std::string> attributes, std::vector<XmlElement> childEl, bool singleLine, bool increment);
        XmlElement(std::string const & name, std::map<char const *, std::string> attributes, std::vector<XmlElement> childEl, bool singleLine, bool increment, bool checkName);

        /* Member functions */

        /* Name */
        void setName(std::string name, bool checkName = true);
        std::string getName(void);

        /* Attribute */
        void setAttribute(char const * name, std::string const & value);
        std::string getAttribute(char const * name);
        size_t getAttributeNumber(void);
        bool isAttributeEmpty(void);

        /* Child elements */
        void addChild(int pos, XmlElement const & value);
        XmlElement & getChild(int index);
        void delChild(int pos);
        void pushBackChild(XmlElement const & value);
        void popBackChild(void);
        size_t getChildNumber(void);
        bool isChildEmpty(void);

        /* Other */
        void setSingleLine(bool singleLine);
        bool getSingleLine(void);
        void setIncrement(bool increment);
        bool getIncrement(void);
        std::string print(int nestLevel = 0);

};



#endif /* ELEMENT_H */