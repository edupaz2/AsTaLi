#include "processor.h"
#include "scheduler.h"

#include <boost/fiber/all.hpp>

Processor::~Processor()
{
	std::cout << "~Processor" << std::endl;
}

void Processor::init()
{
	m_channel = new Channel(1024);
	m_worker = new std::thread(
        [this] {
        	// Define the scheduling
        	boost::fibers::use_scheduling_algorithm<Scheduler>();
            // create pool of fibers
            for (int i=0; i<10; ++i)
            {
                boost::fibers::fiber
                {
                    [this]{
                        Task tsk;
                        // dequeue and process tasks
                        while (boost::fibers::channel_op_status::closed != this->m_channel->pop(tsk))
                        {
                        	std::cout << "Fiber[" <<  boost::this_fiber::get_id() << "] poping task" << std::endl;
                            tsk();
                            boost::this_fiber::yield();
                        }
                    }
                }.detach();
            }
            /*Task tsk;
            // dequeue and process tasks
            while (boost::fibers::channel_op_status::closed != this->m_channel->pop(tsk))
            {
            	std::cout << "Thread poping task" << std::endl;
                tsk();
            }*/
        });
}

void Processor::done()
{
	// TODO: Need to wait for the fibers to finish

	// signal termination
	m_channel->close();
	m_worker->join();

	delete m_channel;
	delete m_worker;
}

task_id Processor::startTask()
{
	// Choose a random type of task, launch it
	static int taskid = FIRST_TASK_ID;
	int i = taskid;
	++taskid;

	m_channel->push([i]
		{
			std::random_device rd;  //Will be used to obtain a seed for the random number engine
    		std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
			std::cout << "Processor::Task[" << i << "] Starting Task" << std::endl;
            std::uniform_int_distribution<> dis(100, INT_MAX);
            int number = dis(gen);
            for(int j=2; j < number; ++j)
            {
                if(number % j == 0)
                {
                    std::cout << "Processor::Task[" << i << "] Not prime " << number << std::endl;
                    return;
                }
            }
            std::cout << "Processor::Task[" << i << "] Prime " << number << std::endl;
        });
	return i;
}

task_id Processor::startTask(const task_type& type)
{
	return FIRST_TASK_ID;
}

task_id Processor::pauseTask(const task_id& id)
{
	return FIRST_TASK_ID;
}

task_id Processor::resumeTask(const task_id& id)
{
	return FIRST_TASK_ID;
}

task_id Processor::stopTask(const task_id& id)
{
	return FIRST_TASK_ID;
}

task_status Processor::status()
{
	return task_status();
}

void Processor::quit()
{}