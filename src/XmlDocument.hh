/**
 * @file XmlDocument.hh
 * @author Linux-Tech-Tips
 * @brief The XML Document class header
 * 
 * The header file declaring the XML Document class
*/
#ifndef XML_DOC_H
#define XML_DOC_H

#include <string>
#include <vector>
#include <utility>

#include "Node.hh"
#include "Comment.hh"
#include "ProcessingInstruction.hh"
#include "TextElement.hh"
#include "XmlElement.hh"
#include "XmlProlog.hh"
#include "DTD/DTD.hh"
#include "DTD/AttributeDTD.hh"
#include "DTD/DoctypeDTD.hh"
#include "DTD/ElementDTD.hh"
#include "DTD/EntityDTD.hh"
#include "file_util.hh"

/** 
 * @class XmlDocument
 * @author Linux-Tech-Tips
 * @brief XML Document class
 * 
 * The XML Document class, containing an object-oriented representation of an XML document,
 * with the capability to process a text XML declaration into objects, and the objects back into an XML declaration.
 * Formatting is not guaranteed to be kept exactly.
*/
class XmlDocument {

    protected:
        
        /* XML Data */

        /** The path to the XML file */
        std::string filePath;
        /** All root-level XML Nodes contained within the document (nested Nodes are contained within the root-level nodes) */
        std::vector<Node *> nodes;

        /* Protected member functions */

        /* Protected static - auxiliary functions for XML parsing/processing */

        /** Internal auxiliary function to get the next part of an XML tag (content in a single <...>) in the content, starting at the tag opening character defined by i 
         *  @param content the text content to find the XML tag in
         *  @param i the position on which '<' is found; is incremented as the function progresses through the tag declaration and ends at the tag end
        */
        static std::string getNextTagPart(std::string const & content, size_t * i);

        /** Internal auxiliary function which returns the name of an XML tag based on the XML text declaration of the tag
         * - returns empty string if name either not found, or if node type doesn't display name in the tag
         * - special behavior: for Comment type, the name is the first word of the comment, if any found
         * @param endIndex optionally specify an integer pointer into which the index of the end of the name in the tag will be saved (std::string::npos is saved if name not found)
        */
        static std::string getTagName(std::string const & tag, int * endIndex = nullptr);

        /** Internal auxiliary function which saves any attributes specified in the given tag into the given Node object instance 
         * @param nameEndIndex the index of the last character of the tag name, which simplifies the use of the function if specified
        */
        static void saveAttributes(std::string const & tag, Node * nodeObject, int nameEndIndex = -1);

        /** Internal function, returns a Node * instance of an XML element, if the passed xmlNode and nodeType correspond to an XML Node (undefined behavior otherwise) */
        static Node * getXMLObject(std::string const & trimmedNode, std::string const & nodeName, NodeTypeName nodeType, bool endLine, bool indent);

        /** Internal function, returns a Node * instance of a DTD element, if the passed xmlNode and nodeType correspond to a DTD Node (undefined behavior otherwise) */
        static Node * getDTDObject(std::string const & trimmedNode, std::string const & nodeName, NodeTypeName nodeType, bool endLine, bool indent);

    public:

        /* Static member functions */

        /** Returns an std::vector containing pairs with parsed XML file content 
         * - each pair consists of an XML declaration of a root XML node and the assumed NodeTypeName of the node
         * - if the XML declaration consists of content surrounded by 2 tag parts (opening and closing), the character '\0' is inserted to differentiate the content
         */
        static std::vector<std::pair<std::string, NodeTypeName>> getNodes(std::string const & fileContent);

        /** Returns an allocated Node * instance of the given inheriting nodeType, based on the processed XML node declaration (must be deleted after usage)
         *  @param xmlNode the plaintext XML declaration of a node
         *  @param nodeType the expected type of the Node declared within xmlNode
        */
        static Node * getNodeObject(std::string const & xmlNode, NodeTypeName nodeType);


        /* Constructors */

        /** Constructor - loads an XML file into the XmlDocument instance
         *  @param filePath the path to an XML file on the device to load
        */
        XmlDocument(char const * filePath);

        /** Copy constructor (allocating new Node memory for a new copy) */
        XmlDocument(XmlDocument const & original);

        /** Empty constructor - creating an empty Xml Document */
        XmlDocument();

        ~XmlDocument(void);


        /* Get functions for internal nodes */

        /** Returns the pointer to the internally saved Node at the specified index */
        Node * getNode(int index);

        /** Returns the pointer to the first (or n-th) internally saved Node with the given name 
         *  @param name the name of the node to look for
         *  @param offset which node with the given name to find, if more exist (leave default or 0 to get the first found instance)
        */
        Node * getNode(char const * name, size_t offset = 0);

        /** Gets the amount of root-level child Nodes contained within the XML document */
        size_t getChildAmount(void) const;

        /** Gets the amount of root-level child Nodes with the given name in the XML document */
        size_t getChildAmount(char const * name) const;

        /** Returns whether the first (or n-th if defined by offset) child Node exists, and saves its index (if index not nullptr) */
        bool findChild(char const * name, int * index = nullptr, size_t offset = 0);

        /* Member functions modifying the base internal node vector */

        /** Adds a new node (copy of the passed constant reference) to the specified index */
        void addNode(Node const & node, int index = 0);

        /** Adds a new node (copy of the passed constant reference) to the end of the document */
        void pushBackNode(Node const & node);

        /** Removes an internally saved Node from the specified index */
        void delNode(int index);

        /** Removes the last Node in the document */
        void popBackNode(void);


        /* Document manipulation functions */

        /** Removes all content from the Document */
        void clear(void);

        /** Loads the XML document on the given path into this XmlDocument instance (replacing old content, if any) */
        void load(char const * filePath);

        /** Saves the current XmlDocument to the given path */
        void save(char const * filePath);

        /** Loads the given string into the XmlDocument instance.
         * Used internally to load the document from a file, but can be used when loading from a different source than a file as well
        */
        void loadFromString(std::string const & xml);

        /** Returns the complete XML string of the loaded document */
        std::string print(void);

};

#endif /* XML_DOC_H */