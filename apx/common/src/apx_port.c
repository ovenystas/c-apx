#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <assert.h>
#include <stdio.h>
#include "apx_port.h"
#include "apx_error.h"
#include "apx_types.h"
#ifdef MEM_LEAK_CHECK
#include "CMemLeak.h"
#endif


#define APX_MAX_PORT_SIG_LEN 1024




/**************** Private Function Declarations *******************/
#ifndef UNIT_TEST

#endif

/**************** Private Variable Declarations *******************/


/****************** Public Function Definitions *******************/
apx_error_t apx_port_create(apx_port_t *self, uint8_t portDirection, const char *name, const char* dataSignature, const char *attributes, int32_t lineNumber){
   if( (self != 0) && (dataSignature != 0) ){
      apx_error_t error;
      self->name = (name != 0)? STRDUP(name) : 0;
      self->portType = portDirection;
      self->portSignature = (char*) 0;
      self->portIndex = -1;
      self->lineNumber = -1;
      error = apx_dataSignature_create(&self->dataSignature, dataSignature);
      if (error != APX_NO_ERROR)
      {
         if (self->name != 0)
         {
            free(self->name);
         }
         return error;
      }
      if (attributes != 0)
      {
         self->portAttributes = apx_portAttributes_new(attributes);
      }
      else
      {
         self->portAttributes = (apx_portAttributes_t*) 0;
      }
      return APX_NO_ERROR;
   }
   errno = EINVAL;
   return -1;
}

void apx_port_destroy(apx_port_t *self){
	if(self != 0){
		if (self->name != 0)
		{
			free(self->name);
		}
		if (self->portAttributes != 0)
		{
			apx_portAttributes_delete(self->portAttributes);
		}
      if (self->portSignature != 0)
      {
         free(self->portSignature);
      }
      apx_dataSignature_destroy(&self->dataSignature);
	}
}

apx_port_t* apx_providePort_new(const char *name, const char* dataSignature, const char *attributes)
{
   apx_port_t *self = (apx_port_t*) malloc(sizeof(apx_port_t));
   if(self != 0){
      apx_port_create(self, APX_PROVIDE_PORT, name, dataSignature, attributes, 0);
   }
   else{
      errno = ENOMEM;
   }
   return self;
}

apx_port_t* apx_requirePort_new(const char *name, const char* dataSignature, const char *attributes)
{
   apx_port_t *self = malloc(sizeof(apx_port_t));
   if(self != 0){
      apx_port_create(self, APX_REQUIRE_PORT, name, dataSignature, attributes, 0);
   }
   else{
      errno = ENOMEM;
   }
   return self;
}

void apx_port_delete(apx_port_t *self)
{
   if (self != 0)
   {
      apx_port_destroy(self);
      free(self);
   }
}

void apx_port_vdelete(void *arg){
	apx_port_delete((apx_port_t*) arg);
}

#if 0
void apx_port_setDerivedDataSignature(apx_port_t *self, const char *dataSignature)
{
   if (self != 0)
   {
      apx_dataSignature_update(&self->derivedDsg,dataSignature);
   }
}

/**
 * creates a port signature string for this port of the form:
 * "{port_name}"{dsg}
 * the string is stored in self->self->portSignature
 */
const char *apx_port_derivePortSignature(apx_port_t *self)
{
   if (self != 0)
   {
      uint32_t namelen=0;
      uint32_t dsgLen=0;
      const char *dsgPtr=0;

      if (self->portSignature != 0)
      {
         free(self->portSignature);
         self->portSignature = 0;
      }

      if (self->name != 0)
      {
         namelen = (uint32_t) strlen(self->name);
      }
      if (self->derivedDsg.str != 0 )
      {
         dsgLen =  (uint32_t) strlen(self->derivedDsg.str);
         dsgPtr = self->derivedDsg.str;
      }
      else if (self->dataSignature != 0 )
      {
         dsgLen =  (uint32_t) strlen(self->dataSignature);
         dsgPtr = self->dataSignature;
      }

      if ( (namelen > 0) && (dsgLen > 0) && (dsgPtr != 0) )
      {
         uint32_t psgLen=namelen+dsgLen+3; //add 3 to fit null-terminator + 2 '"' characters
         self->portSignature = (char*) malloc(psgLen);
         if (self->portSignature != 0)
         {
            char *p = self->portSignature;
            *p++='"';
            memcpy(p,self->name,namelen); p+=namelen;
            *p++='"';
            memcpy(p,dsgPtr,dsgLen); p+=dsgLen;
            *p++='\0';
            assert(p == self->portSignature+psgLen);
            return self->portSignature;
         }
      }
   }
   return 0;
}
#endif

const char *apx_port_getPortSignature(apx_port_t *self)
{
   if (self != 0)
   {
      if (self->portSignature == 0)
      {
//         return apx_port_derivePortSignature(self);
         return 0;
      }
      else
      {
         return self->portSignature;
      }
   }
   return 0;
}


int32_t apx_port_getPackLen(apx_port_t *self)
{
   if (self != 0)
   {
      if(self->dataSignature.dsgType == APX_DSG_TYPE_SENDER_RECEIVER)
      {
         return apx_dataSignature_getPackLen(&self->dataSignature);
      }
   }
   return -1;
}


void apx_port_setPortIndex(apx_port_t *self, int32_t portIndex)
{
   if ( (self != 0) && (portIndex>=0) )
   {
      self->portIndex=portIndex;
   }
}

int32_t  apx_port_getPortIndex(apx_port_t *self)
{
   if (self != 0)
   {
      return self->portIndex;
   }
   return -1;
}



/***************** Private Function Definitions *******************/

