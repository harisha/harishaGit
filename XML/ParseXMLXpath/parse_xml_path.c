#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/xmlschemas.h>
#include <libxml/xpath.h>
#include <syslog.h>

#define APP_DEBUG(level, ...) \
                if ((level <= LOG_DEBUG)) {\
                        syslog((level), __VA_ARGS__);\
                }
				
				
xmlXPathObjectPtr getMatchingNode(xmlDocPtr doc, char *xpath)
{
    xmlXPathContextPtr context;
    xmlXPathObjectPtr result;

    context = xmlXPathNewContext(doc);
    if (context == NULL) 
    {
        APP_DEBUG(LOG_DEBUG,"Error in xmlXPathNewContext\n");
	    return NULL;
    }
    result = xmlXPathEvalExpression((xmlChar*)xpath, context);
    xmlXPathFreeContext(context);
    if (result == NULL)
    {
	    APP_DEBUG(LOG_DEBUG,"Error in xmlXPathEvalExpression\n");
	    return NULL;
    }
    if(xmlXPathNodeSetIsEmpty(result->nodesetval))
    {
	    xmlXPathFreeObject(result);
        APP_DEBUG(LOG_DEBUG,"No result\n");
	    return NULL;
    }
	
    return result;
}

int getTextValueFromXpath(xmlDocPtr docPtr,char* xpath, char* buffer, int len)
{
    xmlXPathObjectPtr result = NULL;
    xmlNodeSetPtr nodeset;

    result = getMatchingNode(docPtr,xpath);
    if(result && result->nodesetval)
    {
        nodeset = result->nodesetval;
        snprintf(buffer,len,"%s",xmlNodeListGetString(docPtr, nodeset->nodeTab[0]->xmlChildrenNode, 1));
		return 0;
    }
	
	return -1;
}

void fetchParameters(xmlDocPtr docPtr)
{
    xmlXPathObjectPtr result = NULL;
    xmlNodeSetPtr nodeset;
    char *xpath = NULL;
    char tempxpath[256];
    char paramName[256];
	
    int i;

    xpath="/parameters/parameter";
    result = getMatchingNode(docPtr,xpath);
    if(result && result->nodesetval)
    { 
        nodeset = result->nodesetval;
		for(int i=0;i<nodeset->nodeNr;++i)
		{
			snprintf(tempxpath,sizeof(tempxpath),"/parameters/parameter[%d]/name",i+1);
            if(getTextValueFromXpath(docPtr,tempxpath,paramName, sizeof(paramName)) == 0)
			{
				printf("%s\n", paramName);
			}
		}
	}
}
int readXMLConfiguration(char* filepath)
{
    xmlDocPtr docPtr = NULL;
    docPtr = xmlReadFile(filepath,"",0);
    if(docPtr == NULL)
    {
         APP_DEBUG(LOG_DEBUG, "error reading XML file")
         return -1;
    }
    
    fetchParameters(docPtr); 
    
    xmlFreeDoc(docPtr);
    xmlCleanupParser();
    return 0;
}


int main()
{
	readXMLConfiguration("/tmp/param.xml");
}
