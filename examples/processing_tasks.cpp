#include <boost/fiber/all.hpp>
#include <random>

inline
void fn( std::string const& str, int n) {
    for ( int i = 0; i < n; ++i) {
        std::cout << i << ": " << str << std::endl;
        boost::this_fiber::yield();
    }
}

int main()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

    using task = std::function<void()>;
    boost::fibers::buffered_channel<task> ch{1024};
    auto worker = std::thread(
            [&ch]{
                // create pool of fibers
                for (int i=0; i<10; ++i) {
                    boost::fibers::fiber {
                        [&ch]{
                            task tsk;
                            // dequeue and process tasks
                            while (boost::fibers::channel_op_status::closed != ch.pop(tsk)) {
                                std::cout << "Fiber[" << boost::this_fiber::get_id() << "] poping task" << std::endl;
                                tsk();
                                boost::this_fiber::yield();
                            }
                        }
                    }.detach();
                }

                /*task tsk;
                // dequeue and process tasks
                while (boost::fibers::channel_op_status::closed != ch.pop(tsk)){
                    std::cout << "Thread poping task" << std::endl;
                    tsk();
                }*/

            });
    // feed channel with tasks
    for(int i=0; i < 10000; ++i)
    {
        std::cout << "Task[" << i << "] Push" << std::endl;
        ch.push([i, &gen]{
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
    }

    // signal termination
    ch.close();
    worker.join();

    return 0;
}