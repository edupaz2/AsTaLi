#include <boost/fiber/all.hpp>
#include <random>

#include "scheduler.h"

int main()
{
    Scheduler s;
    s.init();

    for(int i=0; i < 50; ++i)
    {
        s.startTask();
    }

    while(true);;

    s.done(); 

    return 0;
}