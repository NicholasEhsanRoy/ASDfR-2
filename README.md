# ASDfR-2
For Advanced Software Development for Robotics Assignment2

Measurements: Note: measured using htop

Single core without stress  : Range: 30-42% && 600MHz : Total time: 73s
Single core with stress     : Range: 100%   && 1800MHz: Total time: 58s

Between cores without stress: Range: 30% for core 3, 60-70 for core1 && 600MHz: Total time: 74s
Between cores with    stress: 

Seems to be the same conclusion whether on single or multiple cores.

Reason: Stressing the cpu increases the core frequency. This makes it run faster.

