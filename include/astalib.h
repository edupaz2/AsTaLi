#ifndef __ASTALIB_H__
#define __ASTALIB_H__

#include "astalib_defs.h"

task_id 		startTask	();
task_id 		startTask	(const task_type& type);

task_id			pauseTask	(const task_id& id);
task_id			resumeTask	(const task_id& id);
task_id			stopTask	(const task_id& id);

task_status		status 		();

void			quit		();

#endif