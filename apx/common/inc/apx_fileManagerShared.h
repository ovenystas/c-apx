#ifndef APX_FILE_MANAGER_SHARED_H
#define APX_FILE_MANAGER_SHARED_H

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
#include "apx_allocator.h"
#include "apx_fileMap.h"
#include "apx_fileManagerDefs.h"
#include "rmf.h"

//////////////////////////////////////////////////////////////////////////////
// CONSTANTS AND DATA TYPES
//////////////////////////////////////////////////////////////////////////////
//forward declarations
struct apx_file_tag;
struct rmf_fileInfo_tag;

typedef struct apx_fileManagerShared_tag
{
   void *arg;
   apx_allocator_t allocator;
   apx_fileMap_t localFileMap;
   uint32_t fmid; //a.k.a channel ID
   void (*fileOpenRequestedByRemote)(void *arg, const rmf_cmdOpenFile_t *cmdOpenFile);
   void (*fileCreated)(void *arg, const struct apx_file_tag *pFile);
   void (*sendFileInfo)(void *arg, const struct apx_file_tag *pFile);
   void (*sendFileOpen)(void *arg, const apx_file_t *file, void *caller);
}apx_fileManagerShared_t;


//////////////////////////////////////////////////////////////////////////////
// GLOBAL FUNCTION PROTOTYPES
//////////////////////////////////////////////////////////////////////////////
int8_t apx_fileManagerShared_create(apx_fileManagerShared_t *self, uint32_t fmid);
void apx_fileManagerShared_destroy(apx_fileManagerShared_t *self);
uint8_t *apx_fileManagerShared_alloc(apx_fileManagerShared_t *self, size_t size);
void apx_fileManagerShared_free(apx_fileManagerShared_t *self, uint8_t *ptr, size_t size);
void apx_fileManagerShared_start(apx_fileManagerShared_t *self);
void apx_fileManagerShared_stop(apx_fileManagerShared_t *self);
void apx_fileManagerShared_attachFile(apx_fileManagerShared_t *self, struct apx_file_tag *localFile);
int32_t apx_fileManagerShared_getNumFiles(apx_fileManagerShared_t *self);

int32_t apx_fileManagerShared_calcFileInfoMsgSize(const struct rmf_fileInfo_tag *fileInfo);
int32_t apx_fileManagerShared_serializeFileInfo(uint8_t *bufData, int32_t bufLen, const struct rmf_fileInfo_tag *fileInfo);

#endif //APX_FILE_MANAGER_SHARED_H
