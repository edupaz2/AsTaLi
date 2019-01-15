#include "scheduler.h"
#include <boost/fiber/all.hpp>
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

void Scheduler::init()
{
	m_channel = new Channel(1024);
	m_worker = new std::thread(
	        [this]{
	        	// Define the scheduling
	        	boost::fibers::use_scheduling_algorithm<Scheduler>();
	            // create pool of fibers
	            for (int i=0; i<10; ++i) {
	                boost::fibers::fiber {
	                    [this]{
	                        Task tsk;
	                        // dequeue and process tasks
	                        while (boost::fibers::channel_op_status::closed != this->m_channel->pop(tsk)){
	                            tsk();
	                        }
	                    }}.detach();
	            }
	            Task tsk;
	            // dequeue and process tasks
	            while (boost::fibers::channel_op_status::closed != this->m_channel->pop(tsk)){
	                tsk();
	            }
	        });
}

void Scheduler::done()
{
	// TODO: Need to wait for the fibers to finish

	// signal termination
	m_channel->close();
	m_worker->join();

	delete m_channel;
	delete m_worker;
}

task_id Scheduler::startTask()
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	// Choose a random type of task, launch it
	static int taskid = 0;
	int i = taskid;
	++taskid;

	m_channel->push([&i, &gen]{
            std::uniform_int_distribution<> dis(100, 3456784);
            int number = dis(gen);
            for(int j=2; j < number; ++j)
            {
                if(number % j == 0)
                {
                    std::cout << "Task[" << i << "] Not prime " << number << std::endl;
                    return;
                }
            }
            std::cout << "Task[" << i << "] Prime " << number << std::endl;
        });
	return 0;
}

task_id Scheduler::startTask(const task_type& type)
{
	return 0;
}

task_id Scheduler::pauseTask(const task_id& id)
{
	return 0;
}

task_id Scheduler::resumeTask(const task_id& id)
{
	return 0;
}

task_id Scheduler::stopTask(const task_id& id)
{
	return 0;
}

task_status Scheduler::status()
{
	return task_status();
}

void Scheduler::quit()
{}

void Scheduler::awakened(boost::fibers::context* ctx) noexcept
{
	std::cout << "awakened" << std::endl;
	super::awakened(ctx);
}

boost::fibers::context* Scheduler::pick_next() noexcept
{
	std::cout << "pick_next" << std::endl;
	return super::pick_next();
}

bool Scheduler::has_ready_fibers() const noexcept
{
	std::cout << "has_ready_fibers" << std::endl;
	return super::has_ready_fibers();
}

void Scheduler::suspend_until(std::chrono::steady_clock::time_point const& tp) noexcept
{
	std::cout << "suspend_until" << std::endl;
	super::suspend_until(tp);
}

void Scheduler::notify() noexcept
{
	std::cout << "notify" << std::endl;
	super::notify();
}
