#include <iostream>
#include <string>
#include <sstream>

#include "processor.h"

void printCommands()
{
    std::cout << "#-----------------#" << std::endl;
    std::cout << "Commands available:" << std::endl;
    std::cout << " start"                   << "\t\t\t\tStarts a task and prints its ID." << std::endl;
    std::cout << " start <task_type_id>"    << "\t\tStarts a task of a given type and prints its ID." << std::endl;
    std::cout << " pause <task_id>"         << "\t\tPause the task with the given ID and print a confirmation message." << std::endl;
    std::cout << " resume <task_id>"        << "\t\tResume task with the given ID (if paused) and print a confirmation message." << std::endl;
    std::cout << " stop <task_id>"          << "\t\t\tStop the task with the given ID (if not stopped) and print a confirmation message." << std::endl;
    std::cout << " status"                  << "\t\t\t\tPrints the ID, type ID, the status (paused, running, stopped, completed) and an optional indicator of progress for each task." << std::endl;
    std::cout << " status <task_id>"        << "\t\tPrints the ID, type ID, the status (paused, running, stopped, completed) and an optional indicator of progress for the task with the given ID." << std::endl;
    std::cout << " quit"                    << "\t\t\t\tQuit gracefully." << std::endl;
    std::cout << "#-----------------#" << std::endl;
}

void printStatus(const task_status& status)
{
	std::cout << "The status is" << std::endl;
}

void printCommandOutput(task_id id, const std::string& cmd)
{
	if(id >= FIRST_TASK_ID)
    {
		std::cout << "Command: " << cmd << " successful. Task [" << id << "]." << std::endl;
    }
    else
    {
		std::cout << "Oh oh. There was a problem when starting the task." << std::endl;
    }
}

int main(int argc, char* argv[]) {
	// Check arguments
	if(argc > 1)
	{
		// No need to check if arg[1] is help or not. Just print it anyways
        std::cout << "Usage: " << argv[0] << std::endl;
        std::cout << "Program will be launched and waiting for commands from the standard input" << std::endl;
        printCommands();
        return 0;
	}

    Processor processor;
    processor.init();

    while (true)
    {
        std::string line;
        std::cout << ">>> Enter Command >>> ";
        std::getline(std::cin, line);

		std::vector<std::string> inputCmd;
		std::istringstream iss(line);
	    do
	    {
	        std::string subs;
	        iss >> subs;
	        inputCmd.push_back(subs);
	    } while (iss);

	    int cmd_count = inputCmd.size();
	    if(cmd_count > 0 && cmd_count <= 2)
	    {
	    	if(inputCmd[0] == "start")
            {
                for(int i=0; i < 50; ++i)
                {
                    processor.startTask();
                }
                //printCommandOutput(processor.startTask(), inputCmd[0]);
                continue;
            }
            else if(inputCmd[0] == "pause")
            {
                printCommandOutput(processor.pauseTask(0), inputCmd[0]);
                continue;
            }
            else if(inputCmd[0] == "resume")
            {
                printCommandOutput(processor.resumeTask(0), inputCmd[0]);
                continue;
            }
            else if(inputCmd[0] == "stop")
            {
                printCommandOutput(processor.stopTask(0), inputCmd[0]);
                continue;
            }
            else if(inputCmd[0] == "status")
            {
                printStatus(processor.status());
                continue;
            }
            else if(inputCmd[0] == "quit")
            {
                std::cout << "QUIT" << std::endl;
                processor.quit();
                goto quit;
            }
            else
            {
            	goto bad_cmd;
            }
	    }
bad_cmd:
    	// Something went wrong
    	printCommands();
    	continue;
    }

quit:
    processor.done();
	std::cout << "Exiting" << std::endl;
    return 0;
}