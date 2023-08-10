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

#include "Node.hh"

class XmlElement: public Node {

    protected:
        std::vector<Node *> children;
        bool singleLine;
        bool increment;
    
    public:
        /* Constructors */
        XmlElement(void);
        XmlElement(std::string const & name);
        XmlElement(std::string const & name, bool singleLine);
        XmlElement(std::string const & name, std::map<char const *, std::string> & attributes, std::vector<Node *> & children, bool singleLine, bool increment);
        XmlElement(std::string const & name, std::map<char const *, std::string> & attributes, std::vector<Node *> & children, bool singleLine, bool increment, bool checkName);

        /* Member functions */

        /* Child elements */
        void addChild(int pos, Node & value);
        Node & getChild(int index);
        void delChild(int pos);
        void pushBackChild(Node & value);
        void popBackChild(void);
        size_t getChildAmount(void);
        bool childrenEmpty(void);

        /* Other */
        void setSingleLine(bool singleLine);
        bool getSingleLine(void);
        void setIncrement(bool increment);
        bool getIncrement(void);
        std::string print(int indentLevel = 0);

};



#endif /* ELEMENT_H */