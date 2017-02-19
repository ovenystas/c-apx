#ifndef APX_LOGGING_H
#define APX_LOGGING_H

/**
* temporary placeholder for APX logging functionality, replace later with system log, or file log support
*/

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

#define APX_LOG_DEBUG(fmt, ...) fprintf(stderr, fmt "\n", ##__VA_ARGS__)
#define APX_LOG_ERROR(fmt, ...) fprintf(stderr, fmt "\n", ##__VA_ARGS__)

//////////////////////////////////////////////////////////////////////////////
// CONSTANTS AND DATA TYPES
//////////////////////////////////////////////////////////////////////////////

#endif //APX_LOGGING_H