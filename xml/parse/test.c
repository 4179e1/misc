#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

static void parsedoc(char *docname);
void parsestory(xmlDocPtr doc, xmlNodePtr cur);

int main(int argc, char *argv[])
{
	char *docname;
	char *prog = argv[0];

	if(argc <= 1) {
		printf("usage: %s docname\n", prog);
		exit(1);
	}

	docname = argv[1];
	parsedoc(docname);

	exit(0);
}

static void parsedoc(char *docname)
{
	xmlDocPtr doc;		//xml树结构指针
	xmlNodePtr cur;		//xml节点指针

/****************************
xmlParseFile ()

xmlDocPtr	xmlParseFile		(const char * filename)

parse an XML file and build a tree. Automatic support for ZLIB/Compress compressed document is provided by default if found at compile-time.
filename:	the filename
Returns:	the resulting document tree if the file was wellformed, NULL otherwise.
*****************************/
	doc = xmlParseFile(docname);

	if( doc == NULL ){
		fprintf(stderr, "Document not parsed successfully.\n");
		return;
	}

/******************************
xmlDocGetRootElement ()

xmlNodePtr	xmlDocGetRootElement	(xmlDocPtr doc)

Get the root element of the document (doc->children is a list containing possibly comments, PIs, etc ...).
doc:	the document
Returns:	the #xmlNodePtr for the root or NULL
*******************************/
	cur = xmlDocGetRootElement(doc);

/*******************************
xmlFreeDoc ()

void	xmlFreeDoc			(xmlDocPtr cur)

Free up all the structures used by a document, tree included.
*******************************/
	if(cur == NULL) {
		fprintf(stderr, "empty document\n");
		xmlFreeDoc(doc);
		return;
	}

	if( xmlStrcmp(cur->name, (const xmlChar *) "story") != 0) {
		fprintf(stderr, "document of the wrong type, root node != story");
		xmlFreeDoc(doc);
		return;
	}

	printf("Debug1: cur->name = %s\n", cur->name);

	cur = cur->xmlChildrenNode;

	printf("Debug2: cur->name = %s\n", cur->name);

	while( cur != NULL) {
		if(xmlStrcmp(cur->name, (const xmlChar*) "storyinfo") == 0) {
			printf("debug3: cur->name = %s\n", cur->name);
			parsestory(doc, cur);
		}
		cur = cur->next;
	}

	xmlFreeDoc(doc);
	exit(0);
}

void parsestory(xmlDocPtr doc, xmlNodePtr cur)
{
	xmlChar *key;
	cur = cur->xmlChildrenNode;

/*******************************
xmlNodeListGetString ()

xmlChar *	xmlNodeListGetString	(xmlDocPtr doc, 
					 xmlNodePtr list, 
					 int inLine)

Build the string equivalent to the text contained in the Node list made of TEXTs and ENTITY_REFs
doc:	the document
list:	a Node list
inLine:	should we replace entity contents or show their external form
Returns:	a pointer to the string copy, the caller must free it with xmlFree().
*******************************/
	while(cur != NULL) {
		if(xmlStrcmp(cur->name, (const xmlChar*)"keyword") == 0) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			printf("keyword: %s\n", key);
			xmlFree(key);
		}
		cur = cur->next;
	}
	
	return;
}
