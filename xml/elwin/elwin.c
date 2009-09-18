#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#define FILE_NAME_LENGTH 105

xmlDocPtr new_character();
xmlChar *nc_basic(xmlDocPtr doc, xmlNodePtr cur);

int main(int argc, char *argv[])
{
	xmlDocPtr ncp;

	//create a new character
	ncp = new_character();

	if( ncp != NULL )
		printf("Success!\n");
	else
		printf("can't creat a new character.\n");

	xmlFreeDoc(ncp);
	xmlCleanupParser();
	xmlMemoryDump();
	exit(0);
}

xmlDocPtr new_character()
{
	xmlDocPtr doc = NULL;
	xmlNodePtr root = NULL;
	xmlNodePtr cur = NULL;

	//get char_name form nc_basic(), and make it the file_name
	xmlChar *character_name = NULL;
	char file_name[FILE_NAME_LENGTH];

	//create a new doc
	doc = xmlNewDoc(BAD_CAST "1.0");
	if(doc == NULL) {
		fprintf(stderr, "can't create a new file.\n");
		return NULL;
	}
	//add root nod
	root = xmlNewNode(NULL, BAD_CAST "character");
	if(root == NULL) {
		fprintf(stderr, "can't create root node <character>.\n");
		return NULL;
	}
	cur = root;
	
	//set root nod
	xmlDocSetRootElement(doc, root);

	//add basic value of the character
	character_name = nc_basic(doc, cur);

/***************************************
*	...
*	the other part to create a character
*	...
***************************************/


	if(character_name == NULL) {
		fprintf(stderr, "error: can't get character_name.\n");
		return NULL;
	} else {
		strcpy(file_name, character_name);
		strcat(file_name, ".xml");
	}
	
	// 1 to save file in tree form & 0 not
	xmlSaveFormatFile(file_name, doc, 1);

	return doc;
}

xmlChar *nc_basic(xmlDocPtr doc, xmlNodePtr cur)
{
	xmlNodePtr ncb_node;

	//just for test
	xmlChar *first_name = "Elwin";
	xmlChar *last_name = "";
	xmlChar *race = "Elf";
	xmlChar *size = "middle";
	xmlChar *age = "121";
	xmlChar *gender = "male";
	xmlChar *height = "4'11\"";
	xmlChar *weight = "99";
	xmlChar *deity = "Ehlonna";

	//add atturibe to <basic>
	ncb_node = xmlNewChild(cur, NULL, BAD_CAST "basic", NULL);

	xmlNewProp(ncb_node, BAD_CAST "first_name", first_name);
	xmlNewProp(ncb_node, BAD_CAST "last_name", last_name);
	xmlNewProp(ncb_node, BAD_CAST "race", race);
	xmlNewProp(ncb_node, BAD_CAST "size", size);
	xmlNewProp(ncb_node, BAD_CAST "age", age);
	xmlNewProp(ncb_node, BAD_CAST "gender", gender);
	xmlNewProp(ncb_node, BAD_CAST "height", height);
	xmlNewProp(ncb_node, BAD_CAST "weight", weight);

	return first_name;
}
