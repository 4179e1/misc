/*******************************************
 * compile: gcc -I/usr/include/libxml2/ -lxml2 tree1.c
 * usage: create a xml tree
 *
*******************************************/
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>                    
int main(int argc, char **argv)
{
	xmlNodePtr test = NULL;
       xmlDocPtr doc = NULL;       /* document pointer */
       xmlNodePtr root_node = NULL, node = NULL, node1 = NULL; /* node pointers */                                                     
     
       //Creates a new document, a node and set it as a root node
       doc = xmlNewDoc(BAD_CAST "1.0");
       root_node = xmlNewNode(NULL, BAD_CAST "root");
	if(root_node == NULL) {
		printf("oops1\n");
	}
    test = xmlDocSetRootElement(doc, root_node);   
	if(test == NULL) {
		printf("oops2\n");
	}
     
       //creates a new node, which is "attached" as child node of root_node node.
       xmlNewChild(root_node, NULL, BAD_CAST "node1",BAD_CAST "content of node1");
 
       // xmlNewProp() creates attributes, which is "attached" to an node.
       node=xmlNewChild(root_node, NULL, BAD_CAST "node3", BAD_CAST"node has attributes");
       xmlNewProp(node, BAD_CAST "attribute", BAD_CAST "yes"); 
//Here goes another way to create nodes.
       node = xmlNewNode(NULL, BAD_CAST "node4");
       node1 = xmlNewText(BAD_CAST"other way to create content");
       xmlAddChild(node, node1);
       xmlAddChild(root_node, node);                           
//Dumping document to stdio or file
       xmlSaveFormatFileEnc(argc > 1 ? argv[1] : "-", doc, "UTF-8", 1); 
/*free the document */
       xmlFreeDoc(doc);
       xmlCleanupParser();
       xmlMemoryDump();      //debug memory for regression tests
 
       return(0);
}
