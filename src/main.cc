#include <iostream>
#include <string>

#include "parser/XML/Node.hh"
#include "parser/XML/XmlElement.hh"
#include "parser/XML/TextElement.hh"
#include "parser/XML/XmlProlog.hh"
#include "parser/XML/Comment.hh"
#include "parser/XML/DTD/DTD.hh"
#include "parser/XML/DTD/DoctypeDTD.hh"
#include "parser/XML/DTD/ElementDTD.hh"
#include "parser/XML/DTD/AttributeDTD.hh"
#include "parser/XML/DTD/EntityDTD.hh"

#include "parser/XmlDocument.hh"

/** Data structure containing the current state of the command line program */
struct cmdState {
    /** Whether the program should run */
    bool run;
    /** A stack of XML Nodes, with the top element being the Active Node, nested within the previous Nodes */
    std::stack<Node *> active;
    /** The current user-specified query, including its arguments */
    std::string userQuery;

    /** The current XML Document */
    XmlDocument document;
};

/* Function declarations */

/** Generates the mapping of std::string values to command function pointers (for convenient command execution from user input) */
void genMap(std::map<std::string, void(*)(cmdState *)> * map);

/** Splits the entered string into substrings based on the delimiter */
std::vector<std::string> split(std::string original, char delim, int limit = -1);

/** Prints help information */
void help(cmdState * state);
/** Asks the program to exit */
void exit(cmdState * state);
/** Prints the current node */
void show(cmdState * state);
/** Allows the user to set or delete an attribute */
void attr(cmdState * state);
/** Allows the user to select either the root Node, the Node directly above the current one, or a nested Node */
void select(cmdState * state);
/** Allows the user to add or delete nested Nodes (for XmlElement) */
void nested(cmdState * state);
/** Manipulates the content of the Node (for TextElement or Comment) */
void content(cmdState * state);


/* Main function */

int main() {

    /* Demonstration code */

    /* Initializing default program state */
    cmdState state = { .run = true };

    /* Program introduction */
    std::printf("XML Parser demonstration program\nEnter the name of an XML file: ");
    std::string enteredFile;
    std::getline(std::cin, enteredFile);
    
    /* XML Document loading from file */
    std::printf("Loading file %s\n", enteredFile.c_str());
    state.document.load(enteredFile.c_str());
    std::printf("Loaded file!\n");

    std::printf("\nEntered document edit mode\n - type 'help' for more information\n");

    /* Getting executable commands map (from std::string for convenience) */
    std::map<std::string, void(*)(cmdState * state)> exec;
    genMap(&exec);


    /* Executing commands */
    while(state.run) {
        /* Showing the name of the currently selected Node */
        if(state.active.empty()) {
            std::printf("[XML Document]: ");
        } else {
            std::printf("[%s]: ", state.active.top()->getName().c_str());
        }
        /* Reading user input */
        std::string userIn;
        std::getline(std::cin, userIn);
        /* Processing the command */
        std::string cmdVerb = split(userIn, ' ', 1)[0];

        /* Executing command if known */
        if(exec.find(cmdVerb) != exec.end()) {
            state.userQuery = userIn;
            exec[cmdVerb](&state);
        } else {
            std::printf("Error: Command %s not found\n", cmdVerb.c_str());
        }
    }

    /* Program exit - saving document if desired */
    std::printf("Do you wish to save the document ([y]es|[n]o): ");
    std::string userIn;
    std::getline(std::cin, userIn);
    if(userIn[0] == 'y' || userIn[0] == 'Y') {
        std::printf("Enter the filename to save to: ");
        std::getline(std::cin, userIn);
        state.document.save(userIn.c_str());
        std::printf("Saved!\n");
    }

    return 0;
}


/* Function implementations */

void genMap(std::map<std::string, void(*)(cmdState *)> * map) {
    (*map)["help"] = help;
    (*map)["exit"] = exit;
    (*map)["show"] = show;
    (*map)["attr"] = attr;
    (*map)["select"] = select;
    (*map)["nested"] = nested;
    (*map)["content"] = content;
}


std::vector<std::string> split(std::string original, char delim, int limit) {
    std::vector<std::string> result;
    std::string buffer = "";
    for(char c : original) {
        if(c == delim && limit != 0) {
            result.push_back(buffer);
            buffer = "";
            limit--;
        } else {
            buffer += c;
        }
    }
    result.push_back(buffer);
    return result;
}


void help(cmdState * state) {
    std::printf("XML Command Line Demonstration:\n");
    std::printf(" an interactive editor\n");

    std::printf("\nAvailable commands:\n");

    std::printf("\n - basic commands:\n");
    std::printf("    help                      ... shows this help information\n");
    std::printf("    exit                      ... exits the program\n");
    std::printf("    show                      ... shows the current XML Node (tag + content)\n");
    std::printf("    attr set <name> <val>     ... sets the given attribute to the value (value can contain spaces, specified without quotes)\n");
    std::printf("    attr del <name>           ... deletes the given attribute\n");
    std::printf("    select home               ... unsets any current Nodes, showing the entire loaded XmlDocument\n");
    std::printf("    select ..                 ... sets the current Node to the one above the current\n");

    std::printf("\n - commands specific to XmlElement:\n");
    std::printf("    select <index>            ... selects the node with the given index (0-indexed)\n");
    std::printf("    nested del <index>        ... deletes the node with the given index (0-indexed)\n");
    std::printf("    nested add <type> <name>  ... adds a node of the given type with the given name\n");
    std::printf("        supported types: element, text, comment\n");
    std::printf("        Node: DoctypeDTD nested DTD Nodes not supported in this version\n");

    std::printf("\n - commands specific to TextElement, Comment:\n");
    std::printf("    content <new-content>     ... sets the content of the element to the new value\n");
}

void exit(cmdState * state) {
    std::printf("Program exit\n");
    state->run = false;
}

void show(cmdState * state) {
    if(state->active.empty()) {
        std::printf("The current XML Document:\n%s\n", state->document.print().c_str());
    } else {
        std::printf("The current Active Node:\n%s\n", state->active.top()->print().c_str());
    }
}

void attr(cmdState * state) {
    if(state->active.empty()) {
        std::printf("Error: Operation not supported for XML Document!\n");
    } else {
        std::vector<std::string> cmd = split(state->userQuery, ' ', 3);
        if(cmd.size() == 4 && cmd[1].compare("set") == 0) {
            state->active.top()->setAttribute(cmd[2], cmd[3]);
        } else if(cmd.size() == 3 && cmd[1].compare("del") == 0) {
            state->active.top()->delAttribute(cmd[2]);
        } else {
            std::printf("Error: Issue processing subcommand %s and arguments!\n", cmd[1].c_str());
        }
    }
}

void select(cmdState * state) {
    std::vector<std::string> processed = split(state->userQuery, ' ', 1);
    if(processed.size() > 1) {

        /* Getting subcommand */
        std::string subcmd = processed[1];

        /* Home case */
        if(subcmd.compare("home") == 0) {
            /* Clearing the active nested Nodes to get back to the XML Document home */
            while(!state->active.empty()) {
                state->active.pop();
            }
        /* One above case */
        } else if(subcmd.compare("..") == 0) {
            if(!state->active.empty()) {
                state->active.pop();
            } else {
                std::printf("Warning: Root XML Document already reached\n");
            }
        /* Nesting further */
        } else {
            /* Getting the index from the subcommand */
            int idx = 0;
            try {
                idx = std::stoi(subcmd);
            } catch(const std::exception& e){
                std::printf("Error: Can't read Node index from command!\n");
                return;
            }

            /* Nesting into the XML Document */
            if(state->active.empty()) {
                Node * ptr = state->document.getNode(idx);
                if(ptr != nullptr) {
                    state->active.push(ptr);
                } else {
                    std::printf("Error: Can't select desired Node from the Document!\n");
                }

            /* Nesting into the current XmlElement */
            } else if(state->active.top()->getNodeType() == NodeTypeName::XmlElement) {
                Node * ptr = ((XmlElement *)state->active.top())->getChild(idx);
                if(ptr != nullptr) {
                    state->active.push(ptr);
                } else {
                    std::printf("Error: Can't selected desired Node from the given XML element!\n");
                }

            /* Nesting into the current DoctypeDTD */
            } else if(state->active.top()->getNodeType() == NodeTypeName::DoctypeDTD) {
                Node * ptr = ((DoctypeDTD *)state->active.top())->getChild(idx);
                if(ptr != nullptr) {
                    state->active.push(ptr);
                } else {
                    std::printf("Error: Can't selected desired Node from the given Doctype DTD!\n");
                }

            /* Nowhere to nest */
            } else {
                std::printf("Error: The current Node doesn't support nested Nodes!\n");
            }
        }

    } else {
        std::printf("Error: No argument specified!\n");
    }

}

void nested(cmdState * state) {
    if(state->active.top()->getNodeType() == NodeTypeName::XmlElement) {

        std::vector<std::string> processed = split(state->userQuery, ' ', 3);
        if(processed.size() > 2) {

            /* Add nested element case */
            if(processed.size() == 4 && processed[1].compare("add") == 0) {
                if(processed[2].compare("element") == 0) {
                    ((XmlElement *)state->active.top())->pushBackChild(XmlElement(processed[3]));
                } else if(processed[2].compare("text") == 0) {
                    ((XmlElement *)state->active.top())->pushBackChild(TextElement(processed[3]));
                } else if(processed[2].compare("comment") == 0) {
                    ((XmlElement *)state->active.top())->pushBackChild(Comment(processed[3]));
                } else {
                    std::printf("Error: Nested Node type %s not recognized!\n", processed[2].c_str());
                }

            /* Delete nested element case */
            } else if(processed.size() == 3 && processed[1].compare("del") == 0) {
                /* Deleting the element at the appropriate index */
                try {
                    int idx = std::stoi(processed[2]);
                    ((XmlElement *)state->active.top())->delChild(idx);
                } catch(const std::exception& e){
                    std::printf("Error: Can't read Node index from command!\n");
                    return;
                }

            /* Wrong command case */
            } else {
                std::printf("Error: Issue processing subcommand %s and arguments!\n", processed[1].c_str());
            }

        } else {
            std::printf("Error: Incorrect number of arguments\n");
        }

    } else {
        std::printf("Error: This Node type doesn't support nested elements!\n");
    }
}

void content(cmdState * state) {
    std::vector<std::string> processed = split(state->userQuery, ' ', 1);
    /* Check correct number of arguments */
    if(processed.size() == 2) {
        switch(state->active.top()->getNodeType()) {
            /* Editing Comment content */
            case NodeTypeName::Comment:
                ((Comment *)state->active.top())->setContent(processed[1]);
                break;
            /* Editing Text Element content */
            case NodeTypeName::TextElement:
                ((TextElement *)state->active.top())->setContent(processed[1]);
                break;
            default:
                std::printf("Error: Node type doesn't support inner content!\n");
                break;
        }
    } else {
        std::printf("Error: Incorrect number of arguments!\n");
    }
}