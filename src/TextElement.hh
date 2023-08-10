/**
 * @file TextElement.hh
 * @author Linux-Tech-Tips
 * @brief XML Text XmlElement class
 *
 * A node representing a single-line, text-only element. 
 * The text can be enclosed in an XML tag with attributes, if the text within the element should contain no further elements
 * The node can also represent pure, unenclosed text, to be inserted among other nodes into a parent node
 */

#include <string>
#include <map>

#include "Node.hh"

class TextElement: public Node {

    private:
        std::string escapeContent(std::string content);

    protected:
        bool showTag;
        bool escapeSpecial;
        bool endLine;
        std::string textContent;
    
    public:
        /* Constructors */
        TextElement(void);
        TextElement(std::string name);
        TextElement(std::string name, std::string content);
        TextElement(std::string name, std::string content, bool showTag);
        TextElement(std::string name, std::string content, bool showTag, bool endLine);
        TextElement(std::string name, std::string content, bool showTag, bool endLine, bool escapeSpecial);
        TextElement(std::string name, std::string content, bool showTag, bool endLine, bool escapeSpecial, std::map<char const *, std::string> & attributes);

        /* Member functions */

        /* Text content */
        void setContent(std::string content);
        std::string getContent(void);

        /* Other */
        void setShowTag(bool showTag);
        bool getShowTag(void);
        std::string print(int indentLevel = 0);

};