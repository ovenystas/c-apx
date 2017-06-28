#ifndef OS_TIMER_H
#define OS_TIMER_H

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "os_event.h"
#include "os_types.h"

//////////////////////////////////////////////////////////////////////////////
// CONSTANTS AND DATA TYPES
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
//////////////////////////////////////////////////////////////////////////////
extern os_schm_cfg_t g_schm_cfg;

//////////////////////////////////////////////////////////////////////////////
// GLOBAL FUNCTION PROTOTYPES
//////////////////////////////////////////////////////////////////////////////
void os_schm_init(os_schm_cfg_t *cfg);
void os_schm_shutdown(void);
void os_schm_start(void);
void os_schm_stop(void);
#ifdef UNIT_TEST
void os_schm_run(void);
#endif


#endif //OS_TIMER_H
