#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unistd.h>

class PCB
{
public:
    int processID;
    int priority;
    int cpuRequirement;
    int memoryRequirement;
    int timeRequirement; // Time required for execution

    PCB(int pid, int prio, int cpu, int mem, int timeReq) : processID(pid), priority(prio), cpuRequirement(cpu), memoryRequirement(mem), timeRequirement(timeReq) {}
};

class JobScheduler
{
public:
    // Job pool for long-term scheduling
    std::vector<PCB> jobPool;

    // Ready queue for short-term scheduling
    std::vector<PCB> readyQueue;

    // Total available CPU and memory
    int totalAvailableCPU;
    int totalAvailableMemory;

    // Current time unit
    int currentTimeUnit;

    // Constructor to initialize total available CPU and memory
    JobScheduler(int cpu, int mem) : totalAvailableCPU(cpu), totalAvailableMemory(mem), currentTimeUnit(0) {}

    //Function to create dummy processes
    void initializeDummyProcesses()
    {
        // For simplicity, create 5 dummy processes
        for (int i = 1; i <= 5; ++i)
        {
            jobPool.emplace_back(i, rand() % 10 + 1, rand() % 20 + 1, rand() % 200 + 1, rand() % 10 + 1);
        }
    }

    // Long-term scheduler
    void longTermScheduler()
    {
        // Move processes from job pool to ready queue based on some criteria
        // For simplicity, let's just move all processes for this example
        readyQueue.insert(readyQueue.end(), jobPool.begin(), jobPool.end());
        jobPool.clear(); // Clear the job pool after moving processes
    }

    // Short-term scheduler
    void shortTermScheduler()
    {
        while (!readyQueue.empty())
        {
            // Sort the ready queue based on priority (higher priority first)
            std::sort(readyQueue.begin(), readyQueue.end(), [](const PCB &a, const PCB &b)
                      { return a.priority > b.priority; });

            PCB currentProcess = readyQueue.front();

            // Check if the current process can be executed based on available resources
            if (currentProcess.cpuRequirement <= totalAvailableCPU && currentProcess.memoryRequirement <= totalAvailableMemory)
            {
                // Deduct resources at the beginning of the process execution
                totalAvailableCPU -= currentProcess.cpuRequirement;
                totalAvailableMemory -= currentProcess.memoryRequirement;
                std::cout << "Total available CPU : " << totalAvailableCPU << " "
                          << "Total available Memory : " << totalAvailableMemory << std::endl;

                // Execute the process over its time requirement
                for (int i = 0; i < currentProcess.timeRequirement; ++i)
                {
                    std::cout << "Time Unit " << currentTimeUnit << ": Executing Process " << currentProcess.processID
                              << " with Priority " << currentProcess.priority
                              << " (Time " << (i + 1) << "/" << currentProcess.timeRequirement << ")"
                              << " CPU: " << currentProcess.cpuRequirement
                              << " Memory: " << currentProcess.memoryRequirement
                              << std::endl;

                    // Increment the current time unit
                    currentTimeUnit++;

                    // Sleep for a short duration to simulate the passage of time
                    usleep(1000000 / currentProcess.timeRequirement); // Sleep proportional to the time requirement
                }

                // free resources after process execution is done
                totalAvailableCPU += currentProcess.cpuRequirement;
                totalAvailableMemory += currentProcess.memoryRequirement;

                // Remove the executed process from the ready queue
                readyQueue.erase(readyQueue.begin());
            }
            else
            {
                // Skip the process if resources are not available
                std::cout << "Time Unit " << currentTimeUnit << ": Skipping Process " << currentProcess.processID << " due to insufficient resources." << std::endl;
                std::cout << "Total available CPU : " << totalAvailableCPU << " "
                          << "Total available Memory : " << totalAvailableMemory << std::endl;

                // Remove the skipped process from the ready queue
                readyQueue.erase(readyQueue.begin());
            }
        }

        if (readyQueue.empty())
        {
            std::cout << "No process in the ready queue." << std::endl;
        }
    }

    // Read processes from a file
    void readProcessesFromFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                std::istringstream iss(line);
                int pid, prio, cpu, mem, timeReq;
                if (iss >> pid >> prio >> cpu >> mem >> timeReq)
                {
                    jobPool.emplace_back(pid, prio, cpu, mem, timeReq);
                }
            }
            file.close();
        }
        else
        {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }
};

int main()
{
    // Initialize job scheduler with total available CPU and memory
    JobScheduler scheduler(20, 200);


    //initialize 5 dummy processes
    scheduler.initializeDummyProcesses();

    // Read processes from the file
    //scheduler.readProcessesFromFile("processes.txt");

    // Run long-term scheduler
    scheduler.longTermScheduler();

    // Run short-term scheduler
    scheduler.shortTermScheduler();

    return 0;
}
