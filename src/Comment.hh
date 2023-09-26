/**
 * @file Comment.hh
 * @author Linux-Tech-Tips
 * @brief An XML Comment Element class
 *
 * The header declaring the XML Comment Element class
 * 
 */
#ifndef XML_COMMENT_H
#define XML_COMMENT_H

#include <string>

#include "Node.hh"

/** 
 * @class Node
 * @author Linux-Tech-Tips
 * @brief Base XML Node class
 * 
 * The base XML Node class, containing a name, attributes, general XML Node settings and a virtual print function. 
 * Is expected to be inherited from by extending classes, defining specific nodes with special behavior. 
*/
class Comment : public Node {

    protected:
        /** The inner content of the comment, can be any string */
        std::string content;
        /** Whether the name of the comment should be shown before the content */
        bool showName;
    
    public:
        /** Constructor
         *  @param name the name of the Comment, displayed if desired, otherwise for internal usage
         *  @param content the internal string content of the Comment
         *  @param showName whether the name of the Comment node should be rendered in the XML
         *  @param endLine whether the Node should end the line it's on
         *  @param indent whether the Node should be indented if nested
        */
        Comment(std::string const & name = "_default_comment", std::string const & content = "default comment content", bool showName = false, bool endLine = true, bool indent = true);


        /* Internal content get/set functions */

        /** Sets the content of the Comment to the desired string value */
        void setContent(std::string const & content);

        /** Returns the current content of the Comment */
        std::string getContent(void) const;

        /** Sets whether the name of the Comment is to be shown before content in the XML */
        void setShowName(bool showName);

        /** Gets whether the name of the Comment is shown before content in the XML */
        bool getShowName(void) const;


        /* Other functions */

        /** Returns the processed XML of the Comment */
        virtual std::string print(int indentLevel = 0);

        /** Creates a dynamically allocated copy of itself
         * Used internally - if called by an end-user, make sure to delete the copy once not needed
        */
        virtual Node * _copy(void) const;

};

#endif /* XML_COMMENT_H */