/**
 * @file Node.hh
 * @author Linux-Tech-Tips
 * @brief XML Text XmlElement class
 *
 * The base XML Node class, containing a name and attributes, and a virtual print function
 * 
 */
#ifndef NODE_H
#define NODE_H

#include <string>
#include <stdexcept>
#include <regex>

class Node {

    protected:
        std::string name;
        std::map<char const *, std::string> attributes;

        bool checkName(std::string name, bool xmlReserved = true);

    public:
        /* Constructors */
        Node(void);
        Node(std::string const & name);

        /* Destructor */
        virtual ~Node() = default;

        /* Member functions */

        /* Name */
        virtual void setName(std::string name, bool checkName = true);
        virtual std::string getName(void);

        /* Attribute */
        virtual void setAttribute(char const * name, std::string const & value);
        virtual std::string getAttribute(char const * name);
        virtual size_t getAttributeNumber(void);
        virtual bool isAttributeEmpty(void);

        /* Other */
        virtual std::string print(int indentLevel = 0);

};

#endif /* NODE_H */