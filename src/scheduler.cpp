#include "scheduler.h"
/*
void thread( std::uint32_t thread_count) {
    // thread registers itself at work-stealing scheduler
    boost::fibers::use_scheduling_algorithm< boost::fibers::algo::work_stealing >( thread_count);
    ...
}

// count of logical cpus
std::uint32_t thread_count = std::thread::hardware_concurrency();
// start worker-threads first
std::vector< std::thread > threads;
for ( std::uint32_t i = 1 ; i < thread_count; ++i) { // count start-thread
    // spawn thread
    threads.emplace_back( thread, thread_count);
}
// start-thread registers itself at work-stealing scheduler
boost::fibers::use_scheduling_algorithm< boost::fibers::algo::work_stealing >( thread_count);
...
*/

Scheduler::~Scheduler()
{
	std::cout << "Scheduler::~Scheduler" << std::endl;
}

void Scheduler::awakened(boost::fibers::context* ctx) noexcept
{
	std::cout << "Scheduler::awakened" << std::endl;
	super::awakened(ctx);
}

boost::fibers::context* Scheduler::pick_next() noexcept
{
	std::cout << "Scheduler::pick_next" << std::endl;
	return super::pick_next();
}

bool Scheduler::has_ready_fibers() const noexcept
{
	std::cout << "Scheduler::has_ready_fibers" << std::endl;
	return super::has_ready_fibers();
}

void Scheduler::suspend_until(std::chrono::steady_clock::time_point const& tp) noexcept
{
	std::cout << "Scheduler::suspend_until" << std::endl;
	super::suspend_until(tp);
}

void Scheduler::notify() noexcept
{
	std::cout << "Scheduler::notify" << std::endl;
	super::notify();
}
