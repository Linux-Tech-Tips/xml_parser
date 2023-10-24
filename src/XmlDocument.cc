#include "XmlDocument.hh"

/* Protected member functions */

/* Protected static - auxiliary functions for XML parsing/processing */

std::string XmlDocument::getNextTagPart(std::string const & content, size_t * i) {
    std::string result;

    /* If incorrect parameters passed, empty string returned */
    if((*i) >= content.length()) {
        return result;
    }

    /* Saving first character, initializing the tag counter to keep track of '<>' and processing content */
    result += content[*i];
    (*i)++;
    int tagCounter = 1;
    /* inQuotes - what type of quote the parser is in, or 0 if not in quotes */
    char inQuotes = 0;

    for(; (tagCounter > 0) && ((*i) < content.length()); (*i)++) {
        /* Adding next character to the result */
        result += content[*i];

        /* If the parser is within quoted (double or single) text, only look for the quote */
        if(inQuotes) {
            if(content[*i] == inQuotes && content[(*i)-1] != '\\') {
                inQuotes = 0;
            }
        /* If the parser is not in quoted text, look for '<>' and increment or decrement the tag counter (+check quotes) */
        } else {
            if(content[*i] == '"' || content[*i] == '\'') {
                inQuotes = content[*i];
            } else if(content[*i] == '<') {
                tagCounter++;
            } else if(content[*i] == '>') {
                tagCounter--;
            }
        }
    }

    return result;
}

std::string XmlDocument::getTagName(std::string const & tag, int * endIndex) {
    std::string name;

    /* Testing whether a complete tag found, otherwise name is empty */
    if(tag.find('<') != std::string::npos && tag.find('>') != std::string::npos) {
        
        /* The index on which the tag starts */
        int startIdx = tag.find('<');
        int nameEnd = -1;

        /* Comment case (starts with <-- ; process first word ) */
        if(tag.substr(startIdx, 4).compare("<!--") == 0) {
            int nameStart = tag.find(' ', startIdx) + 1;
            nameEnd = tag.find_first_of(" >", nameStart);
            name = tag.substr(nameStart, (nameEnd - nameStart));

        /* ProcessingInstruction or DTD case */
        } else if(tag[startIdx+1] == '!' || tag[startIdx+1] == '?') {
            nameEnd = tag.find_first_of(" >", startIdx+1);
            name = tag.substr(startIdx+2, (nameEnd - (startIdx+2)));

        /* Else, any other XML Node */
        } else {
            nameEnd = tag.find_first_of(" />", startIdx+1);
            name = tag.substr(startIdx+1, (nameEnd - (startIdx+1)));

        }

        if(endIndex != nullptr) {
            *endIndex = nameEnd;
        }
    }

    return name;
}

void XmlDocument::saveAttributes(std::string const & tag, Node * nodeObject, int nameEndIndex) {

    /* Getting the index of the end of the tag name, if not specified */
    if(nameEndIndex < 0) {
        XmlDocument::getTagName(tag, &nameEndIndex);
    }

    /* Going through the rest of the tag */

    /* Attribute parser state - 0 .. reading key; 1 .. reading value; 2 (or anything else; default) .. searching */
    int state = 2;
    /* Which character is used as quotation marks (most commonly ' or ", defaulted to ") */
    char quoteChar = '"';
    /* The key-value pair currently in use */
    std::string pair [2] = {"", ""};
    /* Control variable to make sure the for loop is breakable from within */
    bool finished = false;
    
    for(size_t i = nameEndIndex; (i < tag.length() && !finished); i++) {
        /* Selecting appropriate parser behavior based on state */
        switch(state) {
            /* Reading key */
            case 0:
                /* Checking for equals, otherwise saving into key buffer */
                if(tag[i] == '=') {
                    /* Switch state to reading value */
                    state = 1;
                    i++; /* Skipping the quote character so it's not saved into the value buffer */
                    quoteChar = tag[i];
                } else {
                    pair[0] += tag[i];
                }
                break;

            /* Reading value */
            case 1:
                if(tag[i] == quoteChar) {
                    /* Switch state to searching */
                    state = 2;
                    /* End of value reading - save parsed attribute and empty buffer pair */
                    nodeObject->setAttribute(pair[0], pair[1]);
                    pair[0] = "";
                    pair[1] = "";
                } else {
                    pair[1] += tag[i];
                }
                break;


            /* Searching */
            default:
                /* Checking for any character signifying the end of the tag */
                if(tag[i] == '>' || tag[i] == '?' || tag[i] == '!' || tag[i] == '/' || tag[i] == '<' || tag[i] == '\0') {
                    finished = true;
                } else if(!std::isspace(tag[i])) {
                    /* Switch state to reading key */
                    state = 0;
                    pair[0] += tag[i];
                }
                break;
        }
    }
}

Node * XmlDocument::getXMLObject(std::string const & trimmedNode, std::string const & nodeName, NodeTypeName nodeType, bool endLine, bool indent) {

    /* Result variable initialized to nullptr, so that nullptr is returned if anything goes wrong */
    Node * result = nullptr;

    /* Is set to true if the Node contains content within 2 tag parts */
    bool innerContent = false;
    /* Content set to the XML of the node by default, and to any content between null chars if any present */
    std::string content = trimmedNode;
    if(trimmedNode.find('\0') != std::string::npos) {
        content = trimmedNode.substr(trimmedNode.find_first_of('\0') + 1, (trimmedNode.find_last_of('\0') - (trimmedNode.find_first_of('\0') + 1)));
        innerContent = true;
    }

    /* Process trimmed XML Node declaration */
    switch(nodeType) {
        /* Standard XML Nodes */

        case NodeTypeName::Comment:
            content = trimmedNode.substr(5, trimmedNode.length()-9);
            result = new Comment(nodeName, content, false, endLine, indent);
            break;
        
        case NodeTypeName::ProcessingInstruction:
            result = new ProcessingInstruction(nodeName, endLine, indent);
            XmlDocument::saveAttributes(trimmedNode, result);
            break;
        
        case NodeTypeName::TextElement:
            result = new TextElement(nodeName, content, innerContent, indent, endLine, false);
            break;
        
        case NodeTypeName::XmlElement:
            result = new XmlElement(nodeName, (content.find('\n') == std::string::npos), endLine, indent, true);
            XmlDocument::saveAttributes(trimmedNode, result);
            /* Adding processed internal content */
            if(innerContent && !content.empty()) {
                for(std::pair<std::string, NodeTypeName> it : XmlDocument::getNodes(content)) {
                    /* Add child Node (since XmlDocument::getNodeObject allocates the Node dynamically, the allocated instance is deleted afterwards) */
                    Node * childNode = XmlDocument::getNodeObject(it.first, it.second);
                    /* Check that allocated correctly before adding */
                    if(childNode != nullptr) {
                        ((XmlElement *)result)->pushBackChild(*childNode);
                        delete childNode;
                    }
                }
            }
            break;

        case NodeTypeName::XmlProlog:
            result = new XmlProlog(nodeName);
            XmlDocument::saveAttributes(trimmedNode, result);
            result->setIndent(indent);
            result->setEndLine(endLine);
            break;
        
        default:
            result = new Node(nodeName, endLine, indent);
            XmlDocument::saveAttributes(trimmedNode, result);
            break;
    }

    return result;
}

Node * XmlDocument::getDTDObject(std::string const & trimmedNode, std::string const & nodeName, NodeTypeName nodeType, bool endLine, bool indent) {
    
    /* Result variable initialized to nullptr, so that nullptr is returned if anything goes wrong */
    Node * result = nullptr;

    /* List of attributes of the DTD Node, split into an std::vector */
    std::vector<std::string> attr;

    /* Splitting attributes */
    std::string buffer;
    char inQuotes = 0;
    for(size_t i = 2 + nodeName.length(); i < trimmedNode.length(); i++) {
        /* Character for the current iteration */
        char c = trimmedNode[i];
        /* Case 1: In Quotes */
        if(inQuotes != 0) {
            buffer += c;
            /* Testing if non-escaped end of quote found */
            if(c == inQuotes && trimmedNode[i-1] != '\\') {
                inQuotes = 0;
            }
        /* Case 2: Out of quotes */
        } else {
            /* Dumping buffer or ending processing if desired character reached */
            if(c == ' ') {
                if(!buffer.empty()) {
                    attr.push_back(buffer);
                    buffer = "";
                }
            } else if(c == '>') {
                /* End processing on the closing out-of-quote '>' */
                if(!buffer.empty()) {
                    attr.push_back(buffer);
                }
                break;
            } else {
                buffer += c;

                /* Taking care of starting quotes */
                if(c == '"' || c == '\'') {
                    inQuotes = c;
                } else if(c == '(') {
                    inQuotes = ')';
                } else if (c == '[') {
                    inQuotes = ']';
                }
            }
        }
    }

    /* Getting DTD Node objects */
    switch(nodeType) {
        
        case NodeTypeName::AttributeDTD:
            /* If more than 2 attributes, the Node is processed, otherwise the declaration is invalid */
            if(attr.size() >= 3) {
                result = new AttributeDTD(attr[0], attr[1], attr[2]);
                result->setIndent(indent);
                result->setEndLine(endLine);
                /* Saving the content as a string if single quote-surrounded content field, otherwise as the literal present value */
                if(attr.size() == 4 && attr[3].find('"') != std::string::npos) {
                    ((AttributeDTD *)result)->setAttrValue(attr[3].substr(1, attr[3].length()-2), true);
                } else {
                    buffer = "";
                    for(size_t i = 3; i < attr.size(); i++) {
                        buffer += attr[i];
                        /* Adding spaces if not last */
                        if((i+1) != attr.size())
                            buffer += " ";
                    }
                    ((AttributeDTD *)result)->setAttrValue(buffer, false);
                }
            }
            break;
        
        case NodeTypeName::DoctypeDTD:
            if(attr.size() >= 1) {
                result = new DoctypeDTD(attr[0], (trimmedNode.find('\n') == std::string::npos), indent, endLine);
                /* Processing nested DTD nodes (checking if the last element starts with a square bracket) */
                if(attr.size() >= 2 || attr[attr.size()-1][0] == '[') {
                    for(std::pair<std::string, NodeTypeName> it : XmlDocument::getNodes(attr[attr.size()-1].substr(1, attr[attr.size()-1].length()-2))) {
                        Node * childNode = XmlDocument::getNodeObject(it.first, it.second);
                        if(childNode != nullptr) {
                            ((DoctypeDTD *)result)->pushBackChild(*((DTD *)childNode));
                            delete childNode;
                        }
                    }
                }
                /* Adding ext if desired */
                if(attr.size() >= 3) {
                    ((DoctypeDTD *)result)->setExtType(attr[1]);
                    if(attr[2].find('"') != std::string::npos) {
                        ((DoctypeDTD *)result)->setExtLink(attr[2].substr(1, attr[2].length()));
                    } else {
                        ((DoctypeDTD *)result)->setExtLink(attr[2]);
                    }
                }
            }
            break;

        case NodeTypeName::ElementDTD:
            if(attr.size() >= 2) {
                result = new ElementDTD(attr[0], (attr[1].find('(') != std::string::npos ? attr[1].substr(1, attr[1].length()-2) : attr[1]), indent, endLine);
            }
            break;
        
        case NodeTypeName::EntityDTD:
            if(attr.size() >= 2) {
                /* Creating a new EntityDTD with the known values */
                result = new EntityDTD(attr[0]);
                result->setIndent(indent);
                result->setEndLine(endLine);
                /* Setting the entity value based on the read attributes */
                if(attr.size() == 2) {
                    /* Saving a single value, either as a string value (if '"' found) or as a non-string value */
                    if(attr[1][0] == '"' && attr[1][attr[1].length()-1] == '"') {
                        ((EntityDTD *)result)->setEntityValue(attr[1].substr(1, attr[1].length()-2));
                    } else {
                        ((EntityDTD *)result)->setEntityValue(attr[1], false);
                    }
                } else {
                    /* Saving all the remaining read attributes as space-joined non-string content */
                    buffer = "";
                    for(size_t i = 1; i < attr.size(); i++) {
                        buffer += attr[i];
                        /* Adding spaces if last */
                        if((i+1) != attr.size())
                            buffer += " ";
                    }
                    ((EntityDTD *)result)->setEntityValue(buffer, false);
                }
            }
            break;
        
        default:
            /* Concatenating all attributes as content */
            buffer = "";
            for(size_t i = 0; i < attr.size(); i++) {
                buffer += attr[i];
                /* Adding spaces if last */
                if((i+1) != attr.size())
                    buffer += " ";
            }
            /* Creating the default DTD */
            result = new DTD(nodeName, buffer, indent, endLine);
            break;
    }

    return result;
}


/* Static member functions */

std::vector<std::pair<std::string, NodeTypeName>> XmlDocument::getNodes(std::string const & fileContent) {
    std::vector<std::pair<std::string, NodeTypeName>> result;

    /* The temporary buffer the current Node declaration string is stored in */
    std::string buffer;
    /* The detected type of the last processed Node declaration */
    NodeTypeName currentNode = NodeTypeName::Node;


    /* Main processing loop, parses all characters within the text content */
    size_t i = 0;
    while(i < fileContent.length()) {

        /* Fall into corresponding processing loop based on the type of content */
        
        /* Ignore whitespace not enclosed within Nodes */
        if(isspace(fileContent[i])) {
            i++;
        
        /* Any content starting with '<' */
        } else if(fileContent[i] == '<') {

            /* Comment - process until next "-->" reached */
            if(fileContent.substr(i+1, 3).compare("!--") == 0) {
                
                /* Check that last processed characters (i-3 so that even the last '>' gets added to the buffer) weren't "-->" in condition */
                for(; (fileContent.substr(i-3, 3).compare("-->") != 0) && (i < fileContent.length()); i++) {
                    buffer += fileContent[i];
                }

                /* Saving Node type */
                currentNode = NodeTypeName::Comment;
            

            /* DTD or PI content - process until corresponding '>' reached */
            } else if(fileContent[i+1] == '!' || fileContent[i+1] == '?') {

                /* Getting the part of an XML tag (in the case of single-part DTD or PI it's the whole tag) - content enclosed in <...> */
                buffer += getNextTagPart(fileContent, &i);

                /* Saving Node type (testing if first occurence of the desired XML content begins the buffer string) */
                if(buffer.find("?xml") == 1) {
                    currentNode = NodeTypeName::XmlProlog;
                } else if(buffer[1] == '?') {
                    currentNode = NodeTypeName::ProcessingInstruction;
                } else {
                    /* Testing DTD Subtypes */
                    if(buffer.find("!" DTD_ATTRIBUTES) == 1) {
                        currentNode = NodeTypeName::AttributeDTD;
                    } else if(buffer.find("!" DTD_DOCTYPE) == 1) {
                        currentNode = NodeTypeName::DoctypeDTD;
                    } else if(buffer.find("!" DTD_ELEMENT) == 1) {
                        currentNode = NodeTypeName::ElementDTD;
                    } else if(buffer.find("!" DTD_ENTITY) == 1) {
                        currentNode = NodeTypeName::EntityDTD;
                    } else {
                        currentNode = NodeTypeName::DTD;
                    }
                }


            /* Tagged TextElement or XmlElement - process starting tag, then go through the remaining content until corresponding closing tag found */
            } else {

                /* Getting the Tag part started by the '<' at the current i (moves i to the end of the tag) */
                buffer += getNextTagPart(fileContent, &i);

                /* Single-part immediately closed XmlElement - the tag part already saved to buffer, so set type to XmlElement and skip the rest */
                if(buffer.substr(buffer.length()-2, 2).compare("/>") == 0) {
                    currentNode = NodeTypeName::XmlElement;
                
                /* Process content until the closing tag is reached (ignoring the closing tags of nested elements of the same name) */
                } else {

                    /* Inserting '\0' to the border between the tag part and content, to differentiate */
                    buffer += '\0';
                    
                    /* The name of the node - text between the start and the first occurence of a blank space or a closing '>', whichever is smaller */
                    std::string nodeName = buffer.substr(1, std::min(buffer.find(" "), buffer.find(">"))-1);
                    /* How deeply nested the program is in any node with the set nodeName */
                    int nodeCounter = 1;
                    /* Whether the inner content of the Node contains any XML tags (making it an XmlElement instead of a TextElement with a shown tag) */
                    bool containsXml = false;
                    /* Which type of quotes the processing is in, if in any */
                    char inQuotes = 0;
                    /* Whether the processing is inside an XML comment */
                    bool comment = false;
                    
                    for(; (nodeCounter > 0) && (i < fileContent.length()); i++) {
                        if(inQuotes) {
                            /* If in quotes, the only check done is whether the end of the quotes reached */
                            if(fileContent[i] == inQuotes && fileContent[i-1] != '\\') {
                                inQuotes = 0;
                            }
                        } else if(comment) {
                            /* If in a comment, only check whether the end of the comment reached */
                            if(fileContent.substr(i, 3).compare("-->") == 0) {
                                comment = false;
                            }
                        } else {
                            /* If tag opening angle bracket found (and not in quotes), process what the tag is */
                            if(fileContent[i] == '<') {
                                /* Comment if the angle bracket starts an XML comment */
                                if(fileContent.substr(i, 3).compare("<--") == 0) {
                                    comment = true;
                                /* Increment or decrement nodeCounter if tag name found (ignore if irrelevant tag) */
                                } else if(fileContent.substr(i+1, nodeName.length()).compare(nodeName) == 0) {
                                    nodeCounter++;
                                } else if(fileContent.substr(i+1, nodeName.length()+1).compare("/" + nodeName) == 0) {
                                    nodeCounter--;
                                }

                                /* Saving that tag content contains xml if angle bracket found and not final node part */
                                if(!containsXml && nodeCounter > 0)
                                    containsXml = true;
                            
                            /* Checking for an opening quote (if not angle bracket starting tag) */
                            } else if(fileContent[i] == '"' || fileContent[i] == '\'') {
                                inQuotes = fileContent[i];
                            }
                        }
                        /* Adding content to buffer unless the end reached */
                        if(nodeCounter > 0)
                            buffer += fileContent[i];
                    }

                    /* Decrementing as last step of loop incremented i, so that i stays at the '<' character of the second Node part */
                    i--;
                    /* Inserting the '\0' character to differentiate content from the closing tag part */
                    buffer += '\0';
                    /* Saving the closing Tag part of the content */
                    buffer += getNextTagPart(fileContent, &i);

                    /* Saving Node type and closing tag part after corresponding closing tag part found */
                    if(containsXml)
                        currentNode = NodeTypeName::XmlElement;
                    else
                        currentNode = NodeTypeName::TextElement;
                }

            }

        /* Plaintext content not starting with '<' (representable as TextElement) - save to buffer until new Node started */
        } else {
            
            /* Saving to buffer */
            for(; (fileContent[i] != '<') && (i < fileContent.length()); i++) {
                buffer += fileContent[i];
            }
            /* Saving Node type */
            currentNode = NodeTypeName::TextElement;
        
        }

        /* Checking whether the buffer is only whitespace characters */
        bool bufferBlank = true;
        if(!buffer.empty()) {
            for(char c : buffer) {
                if(!std::isspace(c) && c != '\0') {
                    bufferBlank = false;
                    break;
                }
            }
        }

        /* If buffer not empty after processing, dump buffer and empty it for the next processing step */
        if(!bufferBlank) {
            /* Adding leading tab or trailing linebreak if any exist, to keep new line formatting more consistend with loaded documents */
            if(fileContent[i] == '\n')
                buffer += '\n';
            /* Length is adjusted by 2 if '\0' character-based marker found in the buffer */
            int bLength = buffer.length() - (buffer.find('\0') == std::string::npos ? 0 : 2);
            if(fileContent[i-bLength] == '\t' || fileContent[i-bLength] == ' ')
                buffer = '\t' + buffer;
            
            /* Adding node to the result */
            result.push_back({buffer, currentNode});
            /* Resetting the detected node type to the default values */
            currentNode = NodeTypeName::Node;
        }

        /* Emptying buffer if anything left over (including whitespace) */
        if(!buffer.empty()) {
            buffer.clear();
        }

    }

    return result;
}

Node * XmlDocument::getNodeObject(std::string const & xmlNode, NodeTypeName nodeType) {

    /* Result variable initialized to nullptr, so that nullptr is returned if anything goes wrong */
    Node * result = nullptr;

    /* If whitespace-only content passed to the Node, ignore */
    bool blank = true;
    for(char c : xmlNode) {
        if(!std::isspace(c) && c != '\0') {
            blank = false;
            break;
        }
    }

    if(blank) {
        return result;
    }

    /* Whether the xmlNode ends the line it's on */
    bool endLine = (xmlNode[xmlNode.length()-1] == '\n');
    /* Whether the xmlNode content is indented in the front */
    bool indent = (xmlNode.find('\t') != std::string::npos);

    /* Get the name of the Node (or default if empty) */
    std::string nodeName = XmlDocument::getTagName(xmlNode);
    if(nodeName.compare("") == 0) {
        nodeName = "_default_node_name";
    }

    /* Trim leading tabs and trailing linebreaks */
    std::string trimmedNode = xmlNode.substr(xmlNode.find_first_not_of('\t'), xmlNode.find_last_not_of('\n') - xmlNode.find_first_not_of('\t') + 1);

    /* Due to how the NodeTypeName enumeration is structured (alphabetical sort, first XML followed by DTD), this will be only DTD types */
    if(nodeType >= NodeTypeName::AttributeDTD) {
        result = XmlDocument::getDTDObject(trimmedNode, nodeName, nodeType, endLine, indent);
    } else {
        result = XmlDocument::getXMLObject(trimmedNode, nodeName, nodeType, endLine, indent);
    }

    return result;
}


/* Constructors */

XmlDocument::XmlDocument(char const * filePath) {
    this->filePath = filePath;
    this->loadFromString(file_readString(filePath));
}

XmlDocument::XmlDocument(XmlDocument const & original) {
    /* Setting new members to original members */
    this->filePath = original.filePath;
    /* Copying any nodes found in the original */
    if(original.getChildAmount() > 0) {
        for(auto it : original.nodes) {
            this->pushBackNode(*it);
        }
    }
}

XmlDocument::~XmlDocument(void) {
    /* Deleting any allocated child nodes */
    if(this->getChildAmount() > 0) {
        for(auto it : this->nodes) {
            delete it;
        }
    }
}


/* Get functions for internal nodes */

Node * XmlDocument::getNode(int index) {
    if((size_t)index < this->nodes.size())
        return this->nodes.at((size_t)index);
    else
        return nullptr;
}

Node * XmlDocument::getNode(char const * name, size_t offset) {
    int index;
    if(this->findChild(name, &index, offset))
        return this->nodes.at((size_t)index);
    else
        return nullptr;
}

size_t XmlDocument::getChildAmount(void) const {
    return this->nodes.size();
}

size_t XmlDocument::getChildAmount(char const * name) const {
    int amount = 0;
    /* Counting all nodes with the specified name */
    for(auto it : this->nodes) {
        if(it->getName().compare(name) == 0) {
            amount++;
        }
    }
    return amount;
}

bool XmlDocument::findChild(char const * name, int * index, size_t offset) {
    /* Go through all child elements until the requested one found */
    for(size_t i = 0; i < this->getChildAmount(); i++) {
        if(this->nodes[i]->getName().compare(name) == 0) {
            if(offset > 0) {
                /* Decrement the offset if child with the requested name found, but not the correct n-th yet */
                offset--;
            } else {
                /* Returns and saves the index of the found instance, if correct n-th offset */
                if(index)
                    *index = i;
                return true;
            }
        }
    }
    /* Returns false and saves -1 if for loop finishes without finding any */
    if(index)
        *index = -1;
    return false;
}

/* Member functions modifying the base internal node vector */

void XmlDocument::addNode(Node const & node, int index) {
    this->nodes.insert(this->nodes.begin() + index, node._copy());
}

void XmlDocument::pushBackNode(Node const & node) {
    this->nodes.push_back(node._copy());
}

void XmlDocument::delNode(int index) {
    if((size_t)index < this->nodes.size()) {
        delete this->nodes.at(index);
        this->nodes.erase(this->nodes.begin() + index);
    } else {
        throw std::invalid_argument("Error: Can't erase at out-of-bounds index");
    }
}

void XmlDocument::popBackNode(void) {
    delete this->nodes.at(this->nodes.size()-1);
    this->nodes.pop_back();
}


/* Document manipulation functions */

void XmlDocument::clear(void) {
    /* Erasing the file path */
    this->filePath = "";
    /* Removing all nested nodes */
    if(this->getChildAmount() > 0) {
        while(!this->nodes.empty()) {
            this->popBackNode();
        }
    }
}

void XmlDocument::load(char const * filePath) {
    /* Clearing document in case anything in it */
    this->clear();
    /* Loading Nodes from the string contained within the file */
    this->filePath = filePath;
    this->loadFromString(file_readString(filePath));
}

void XmlDocument::save(char const * filePath) {
    /* Prints the XmlDocument content into the specified file using file_writeString() */
    file_writeString(filePath, this->print());
}

void XmlDocument::loadFromString(std::string const & xml) {
    /* Getting the XML declarations of each node */
    std::vector<std::pair<std::string, NodeTypeName>> declarations = XmlDocument::getNodes(xml);
    /* Getting and saving the object for each node */
    for(std::pair<std::string, NodeTypeName> xmlNode : declarations) {
        Node * object = XmlDocument::getNodeObject(xmlNode.first, xmlNode.second);
        if(object != nullptr) {
            this->pushBackNode(*object);
            delete object;
        } else {
            std::cerr << "WARNING: Error on loading XML node from string" << std::endl;
        }
    }

}

std::string XmlDocument::print(void) {
    std::string result;

    /* Print all nodes sequentially into a string and return it */
    for(auto it : this->nodes) {
        result += it->print();
    }

    return result;
}