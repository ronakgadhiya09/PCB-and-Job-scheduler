# PCB-and-Job-scheduler
Refer main.cpp for code

Multi-Processing Simulator:
This program simulates a multi-processing environment with dummy processes, utilizing a Process Control Block (PCB), a long-term scheduler, and a short-term scheduler.
Features

Dummy Processes: The program initializes and simulates the execution of multiple dummy processes, each represented by a PCB (Process Control Block) with specific attributes such as process ID, priority, CPU requirements, memory requirements, and time requirement.

Reading From txt File: The program can also read processes from txt file 

Long-Term Scheduler: The long-term scheduler is responsible for moving processes from the job pool to the ready queue based on certain criteria. In this simple example, all processes are moved to the ready queue.

Short-Term Scheduler: The short-term scheduler executes processes from the ready queue based on priority and available resources (CPU and memory). It simulates the passage of time during process execution.

Adjust Configuration:
You can customize the initial available resources (totalAvailableCPU and totalAvailableMemory) in the JobScheduler constructor.
If desired, modify the number and attributes of dummy processes in the initializeDummyProcesses method.

Additional Information
Read Processes from File:
If you have a file with process details (e.g., "processes.txt"), you can use the readProcessesFromFile method in the JobScheduler class to read processes from the file.

Dependencies:
The code uses C++ and relies on standard libraries. Ensure that you have a C++ compiler installed on your system.

