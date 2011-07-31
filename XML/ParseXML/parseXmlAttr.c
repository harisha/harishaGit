#include <stdio.h>
#include "libxml/parser.h"
#include "libxml/xmlschemas.h"
 
unsigned int getSubSystemId(char *ptr)
{
	if(!strncmp(ptr,"CIDS",strlen("CIDS")))
		return 0;
	if(!strcmp(ptr,"CMC",strlen("CMC")))
		return 1;
	if(!strcmp(ptr,"FMS",strlen("FMS")))
		return 2;
}


typedef struct labelTemp_T
{
	char label;
	unsigned int subsystemId;

}labelTemp_t; 

typedef struct labelRegisterTable_T
{
	int labels;
	labelTemp_t labelInfo[255];
	
}labelRegisterTable_t;

int main()
{
	labelRegisterTable_t reqLabel;
	memset(&reqLabel,0,sizeof(reqLabel));
        int i;
	xmlDocPtr docPtr; /* the resulting document tree */
	xmlNodePtr rootElement;
	xmlNodePtr labelNode;
	xmlChar *labelNum;

	docPtr = xmlReadFile("LabelInfoAttr.xml", "UTF-8", XML_PARSE_RECOVER);
	if(docPtr == NULL)
	{
		printf("xmlReadFile error !!!\n");
	}

	rootElement = xmlDocGetRootElement(docPtr);

	for (labelNode = rootElement->children; labelNode; labelNode = labelNode->next)
	{
		
		/* Check for Lower Root - LABELINFO */
		if(labelNode->type == XML_ELEMENT_NODE
			&& !strncmp((const char*)labelNode->name,"LABELINFO",strlen("LABELINFO")))
		{
			//printf("%s\n",labelNode->name);
		        //printf("%s\n",xmlGetProp(labelNode, "value"));
			labelNum=xmlGetProp(labelNode, "value");
			reqLabel.labelInfo[reqLabel.labels].label=atoi(labelNum);
			reqLabel.labels++;
			free(labelNum);
			xmlNodePtr lblNumSysIdNode;
			for(lblNumSysIdNode = labelNode->children;lblNumSysIdNode;lblNumSysIdNode=lblNumSysIdNode->next)
			{
				/* Label Number */
				//printf("%s\n",lblNumSysIdNode->name);
                                /* //- N/A as no text contents are there
				for (subnode = lblNumSysIdNode->children; subnode; subnode = subnode->next)
				{
					 if (subnode->type == XML_TEXT_NODE)
					 {
						printf("%s\n",subnode->content);
						sscanf(subnode->content,"%d",&reqLabel.labelInfo[reqLabel.labels].label);
							reqLabel.labels++;
					}
				}*/

				/* SubSystemId */
				if(lblNumSysIdNode->type == XML_ELEMENT_NODE
					&& !strncmp((const char *)lblNumSysIdNode->name,"SUBSYSTEMID",strlen("SUBSYSTEMID")))
				{
					//printf("%s\n",lblNumSysIdNode->name);
					xmlNodePtr subnode;
					for (subnode = lblNumSysIdNode->children; subnode; subnode = subnode->next)
					{
						 if (subnode->type == XML_TEXT_NODE)
						 {
							//printf("%s\n",subnode->content);
							reqLabel.labelInfo[reqLabel.labels].subsystemId=getSubSystemId(subnode->content);
							
						 }
					}
				}

		
			}
		}
	}


	/* Output the filled info for debugging */
	for(i=0;i<reqLabel.labels;i++)
	{
		printf("label:%d\n",reqLabel.labelInfo[i].label);
		printf("systemId:%d\n",reqLabel.labelInfo[i].subsystemId);
	}
}
