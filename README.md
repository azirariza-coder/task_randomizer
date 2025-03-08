# Task Randomizer in C

## Description

this program used to randomize task that listed in folder task
folder task must exist first, this program doesnt create it automatically

## Installation

build the program with zig build, then run it with :

./zig-out/bin/task_randomizer_linux (for linux)
or ./zig-out/bin/task_randomizer_windows (for windows)

or build and run it with zig build run (linux only)


##  Usage
the task should be listed like this in task_example.txt file:

```txt

task
task
task

```

this program will write this to task/task_example.txt if file doesnt exist and file empty
```
const char *tasks[3] = {"Olahraga\n", "Programming\n","Gaming\n"};
```

variable buffer is used to contain strings read from task_example.txt, because this is static memory, user should manually change the array size in the code
```
char buffer[3][20];
```
this program only used pseudo random number generator using now time as a seed 
```
  time_t  result = time(NULL);
  (void) srand(result);
  (void)printf("Hasil randomize : %s\n",buffer[rand()% 3]);
```

## Planned
- Using UI with raylib framework 
- Use true random number generator
- Make it so that program create folder automatically when task folder doesnt exist
