#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

xmlChar *get_element(int count_arg, xmlChar *content, xmlDocPtr doc, xmlNodePtr cur, ...);
xmlChar *parse_element(int count_arg, xmlChar *content, xmlDocPtr doc, xmlNodePtr cur, va_list ap);

int main(int argc, char *argv[])
{
	char *docname;

	xmlDocPtr doc;
	xmlNodePtr cur, root;
	xmlChar *content = NULL;

	docname = argv[1];
	doc = xmlParseFile(docname);

	if( doc == NULL ) {
		fprintf(stderr, "error: can't open file %s.\n", docname);
		return 1;
	}

	root = cur = xmlDocGetRootElement(doc);

	if(cur == NULL) {
		fprintf(stderr, "empty document\n");
		xmlFreeDoc(doc);
		return;
	}

	if( xmlStrcmp(cur->name, (const xmlChar *) "story") != 0) {
		fprintf(stderr, "wrong document, can't find root element %s\n", root);
		xmlFreeDoc(doc);
		return;
	}

	content = get_element(1, content, doc, cur, "storyinfo");
	
	printf("content: %s\n", content);

	xmlFreeDoc(doc);
	xmlFree(content);
	return 0;
}

static count_node;
xmlChar *get_element(int count_arg, xmlChar *content, xmlDocPtr doc, xmlNodePtr cur, ...)
{
	static va_list ap;
	count_node = -1;
	
	va_start(ap, cur);


	content = parse_element(count_arg, content, doc, cur, ap);

	va_end(ap);

	return content;
}

static xmlNodePtr last_match_ptr = NULL;
xmlChar *parse_element(int count_arg, xmlChar *content, xmlDocPtr doc, xmlNodePtr cur, va_list ap)
{
	xmlChar *element = va_arg(ap, xmlChar*);
	count_node++;

	printf("Debug4: cur->name = %s\n", cur->name);

	cur = cur->xmlChildrenNode;

	printf("Debug5: cur->name: %s\n", cur->name);

	printf("Debug: ATTT: node: %d\targ: %d\n", count_node, count_arg);

	while( cur->next != NULL ) {
		if(xmlStrcmp(cur->name, element) == 0) {
			printf("Debug6: SUCCESS: cur->name: %s\t element: %s\n",cur->name, element);
			last_match_ptr = cur;
			parse_element(count_arg, content, doc, cur, ap);
		} else {
			printf("Debug7: cur->name: %s\t element: %s\n",cur->name, element);
		}
		cur = cur->next;
	}

	if( count_node == count_arg && cur->xmlChildrenNode == NULL)
	{
			printf("Debug8: i come\n");
			content = xmlNodeListGetString(doc, last_match_ptr->xmlChildrenNode, 1);
			printf("Debug9: content: %s\n", content);
			return content;
	} else if( count_node < count_arg) {
		fprintf(stderr, "too many arguments.\n");
		return NULL;
	} else {
		fprintf(stderr, "not enough arguments.\n");
		return NULL;
	}

	//return content;
}
