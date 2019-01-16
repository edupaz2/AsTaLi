#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "astalib_defs.h"
#include <boost/fiber/algo/round_robin.hpp>
#include <boost/fiber/context.hpp>

class Scheduler : public boost::fibers::algo::round_robin
{
public:
	virtual ~Scheduler();
	// round_robin virtual functions
	virtual void awakened(boost::fibers::context* f) noexcept; // Enqueues fiber f onto a ready queue.
    virtual boost::fibers::context* pick_next() noexcept; // Returns the fiber at the head of the ready queue, or nullptr if the queue is empty.
    virtual bool has_ready_fibers() const noexcept; // true if scheduler has fibers ready to run.
    virtual void suspend_until(std::chrono::steady_clock::time_point const&) noexcept;
    virtual void notify() noexcept;
    // round_robin virtual functions

private:
	typedef boost::fibers::algo::round_robin super;
};

#endif
