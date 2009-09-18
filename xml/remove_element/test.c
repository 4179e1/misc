#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

void
parseStory (xmlNodePtr cur){

	xmlUnlinkNode(cur);
	printf("%s removed\n", cur->name);
	xmlFreeNode(cur);
    return;
}

xmlDocPtr
parseDoc(char *docname, char *keyword) {

	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(docname);
	
	if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return (NULL);
	}
	
	cur = xmlDocGetRootElement(doc);
	
	if (cur == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return (NULL);
	}
	
	if (xmlStrcmp(cur->name, (const xmlChar *) "story")) {
		fprintf(stderr,"document of the wrong type, root node != story");
		xmlFreeDoc(doc);
		return (NULL);
	}
	
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"storyinfo"))){
			parseStory (cur);
		}
		 
	cur = cur->next;
	}
	return(doc);
}

int
main(int argc, char **argv) {

	char *docname;
	char *keyword;
	xmlDocPtr doc;

	if (argc <= 1){
		printf("Usage: %s docname, keyword\n", argv[0]);
		return(0);
	}

	docname = argv[1];
	doc = parseDoc (docname, keyword);
	if (doc != NULL) {
		xmlSaveFormatFile (docname, doc, 1);
		xmlFreeDoc(doc);
	}
	
	return (1);
}

