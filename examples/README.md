# Examples and utils
This files help to do some research examples

## Dependencies
Boost library > 1.62

## Build instructions
We are assuming at this point that Boost library is installed at:
- Headers: third_party/
- Libraries: lib/

```
export LD_LIBRARY_PATH=./../lib
g++ -o proctasks processing_tasks.cpp -std=c++11 -I ../third_party/ -L ../lib -lboost_fiber -lboost_context -lpthread
```

## Examples
### Processing Tasks
Based on Boost::Fibers idea of Running with worker threads
https://www.boost.org/doc/libs/1_69_0/libs/fiber/doc/html/fiber/worker.html#fiber.worker.processing_tasks
