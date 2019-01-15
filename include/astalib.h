#ifndef __ASTALIB_H__
#define __ASTALIB_H__

#include <cstdint>
#include <vector>

using task_id = std::int32_t; // [MININT,-1] Error codes. [0, MAXINT] Task ids
using task_type = std::uint32_t;
struct STaskStatus
{
	task_id 	id;
	task_type 	type;
	enum status { paused, running, stopped, completed };

};
using task_status = std::vector<STaskStatus>;

task_id 		startTask	();
task_id 		startTask	(const task_type& type);

task_id			pauseTask	(const task_id& id);
task_id			resumeTask	(const task_id& id);
task_id			stopTask	(const task_id& id);

task_status		status 		();

void			quit		();

#endif