#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

void new_character();

int main(int argc, char *argv[])
{
	xmlDocPtr ncp;

	//create a new character
	new_character();

	exit(0);
}

void new_character()
{
	xmlDocPtr doc = NULL;
	xmlNodePtr root = NULL;
	xmlNodePtr cur = NULL;

	//get char_name form nc_basic(), and make it the file_name
	xmlChar *char_name = NULL;
	xmlChar *file_name = NULL;

	//create a new doc
	doc = xmlNewDoc(BAD_CAST "1.0");
	if(doc == NULL) {
		fprintf(stderr, "can't create a new file.\n");
		exit(1);
	}
	//add root nod
	root = xmlNewNode(NULL, BAD_CAST "character");
	if(root == NULL) {
		fprintf(stderr, "can't create root node <character>.\n");
		exit(1);
	}
	
	//set root nod
	cur = xmlDocSetRootElement(doc, root);
	/*
	if(cur == NULL) {
		fprintf(stderr, "can't get root node <character>.\n");
		return NULL;
	}
	*/

	//add basic value of the character
	xmlNodePtr ncb_node;

	//just for test
	xmlChar *firstname = "Elwin";
	xmlChar *lastname = "";
	xmlChar *race = "Elf";
	xmlChar *size = "middle";
	xmlChar *age = "121";
	xmlChar *gender = "male";
	xmlChar *height = "4'11\"";
	xmlChar *weight = "99";
	xmlChar *deity = "Ehlonna";

	//add atturibe to <basic>
	ncb_node = xmlNewChild(root, NULL, BAD_CAST "basic", NULL);

	xmlNewProp(ncb_node, BAD_CAST "firstname", firstname);
	xmlNewProp(ncb_node, BAD_CAST "lastname", lastname);
	xmlNewProp(ncb_node, BAD_CAST "race", race);
	xmlNewProp(ncb_node, BAD_CAST "size", size);
	xmlNewProp(ncb_node, BAD_CAST "age", age);
	xmlNewProp(ncb_node, BAD_CAST "gender", gender);
	xmlNewProp(ncb_node, BAD_CAST "height", height);
	xmlNewProp(ncb_node, BAD_CAST "weight", weight);

/***************************************
*	...
*	the other part to create a character
*	...
***************************************/

/*	char_name == first_name;

	if(char_name == NULL) {
		fprintf(stderr, "error: can't get character_name.\n");
		return NULL;
	} else */

	printf("ok1\n");


	printf("ok2\n");

	xmlSaveFormatFile("o.xml", doc, 0);

	printf("ok3\n");

	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();

}
