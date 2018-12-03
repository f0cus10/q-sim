This is a project based on assignment requirements by [Eric Schweitzer](http://cs.hunter.cuny.edu/~eschweit/) and the requirements can be found [here](http://cs.hunter.cuny.edu/~eschweit/OSstuff/340hw1.pdf).

# System
The system runs using keyboard input from the user. That is, for anything to happen, the user must provide an input. At the beginning, the user will be prompted for *system information* and a system with those **printer**, **disk**, and **flash** devices will be generated.

*All interrupts and system calls will be made by the user* and they are handled *atomically*

## System Generation
The installer (aka user) specifies how many devices of each type are present in the system in response to the prompts. There is only **one** CPU.
