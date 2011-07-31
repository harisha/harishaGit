#include "libxml/parser.h"
#include "libxml/xmlschemas.h"

#define SDU_NUMS 10
#define SDU_ATTR 2

int main()
{       

  int i,j;
  xmlDocPtr doc;
  xmlNodePtr node;	
  doc = xmlNewDoc(BAD_CAST "1.0");
  node = xmlNewNode(NULL, BAD_CAST "SDUINFORMATION");
  xmlDocSetRootElement(doc, node);

  for(i=0;i<SDU_NUMS;i++)
  {
  	xmlNodePtr column;
        column = xmlNewNode(NULL, BAD_CAST "SDU");
        xmlAddChild(node, column);

	for(j=0;j<SDU_ATTR;j++)
	{
		xmlNodePtr unit;
		xmlNodePtr state;
		/* Set SDUUNIT */
		if(j==0)
		{
			 unit = xmlNewNode(NULL, BAD_CAST"SDUUNIT");
			 xmlNodeSetContent(unit,BAD_CAST"15");
			 xmlAddChild(column,unit);
		}		
		else if (j==1)
		{
			state = xmlNewNode(NULL, BAD_CAST "SDUSTATE");
			xmlNodeSetContent(state,BAD_CAST"HEALTHY");
			xmlAddChild(column,state);
		}
	}
 
  }
  xmlSaveFileEnc ("SDUInformation.xml", doc, "ISO-8859-1");

}
