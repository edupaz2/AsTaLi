#ifndef _ASTALIB_DEFS_H_
#define _ASTALIB_DEFS_H_

#include <cstdint>
#include <vector>

using task_id = std::uint32_t; // [0,49] Error codes. [50, MAXINT] Task ids
using task_type = std::uint32_t;
const task_id FIRST_TASK_ID = 50;
struct STaskStatus
{
	task_id 	id;
	task_type 	type;
	enum status { paused, running, stopped, completed };

};
using task_status = std::vector<STaskStatus>;

#endif
