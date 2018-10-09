# Userland Stride Scheduler

In this project you will build a stride scheduler in userland (i.e. in Linux, not xv6). Your scheduler will read a data file containing information like timer interrupts, job arrivals, job terminations, etc. Your output will be graded against known good results. Any deviation (even by a space) will be counted as wrong, so follow the specification completely.

You will be able to run tests against my grading script to debug any textual differences.

## Partner rules

No partners - this project is solo.

## Stride Scheduler

Refer to chapter 9 of OSTEP.

## Command Line Options

Your program will take just one argument - the name of the data file to execute. It is an error if the file is not given or cannot be opened for reading.

## Input

Your program will take a data file as its command line argument. It contains comma separated lines with the following syntax:

| opcode | argument 1 | argument 2 | meaning |
| ------ | ---------- | ----------  | ------- |
| newjob | NAME | PRIORITY | A new job with specified PRIORITY and NAME has arrived |
| finish | | | The currently running job has terminated - it is an error if the system is idle |
| interrupt | | | A timer interrupt has occurred - the currently running job's quantum is over |
| block | | | The currently running job has become blocked |
| unblock | NAME | | The named job becomes unblocked - it is an error if it was not blocked |
| runnables | | | Print information about the jobs in the runnable queue |
| running | | | Print information about the currently running job |
| blocked | | | Print information about the jobs on the blocked queue |

My test input is guaranteed to have correct syntax so you do not have to check for errors.

## Operation

### newjob

A new job is entered into the system. Its name and priority are given. Assume all job names are unique. A new job's arrival does not cause a rescheduling unless the system was idle.

```
New job: C added with priority: 200
```

### finish

The currently running job has completed and should be removed from the system.

```
Job: B completed.
```

If the system is idle, it is an error.

```
Error. System is idle.
```

### interrupt

The currently running task has completed its quantum. Adjust your bookkeeping. The scheduler needs to run again. 

```
Job: C scheduled.
```

It is an error if ```interrupt``` is received when the system is idle.

```
Error. System is idle.
```

### block

The currently running task has become blocked. Perhaps it is asking for an I/O. 

```
Job: A blocked.
```

It is an error if the system is idle.

```
Error. System is idle.
```

### unblock

The named job has become unblocked. 

```
Job: A has unblocked. Pass set to: 5000
```

It is an error if the named job was not blocked. 

```
Error. Job: C not blocked.
```

Unblocked jobs return to the runnables. The scheduler is not run unless the system was idle.

### runnables

The runnables, if any, are listed. Example:

```
Runnable:
NAME    STRIDE  PASS  PRI   
C       500     1000  200   
A       500     1500  200
```

These must be listed in the order they would be scheduled.

### running

The running task is described (if system is not idle). Example:

```
Running:
NAME    STRIDE  PASS  PRI   
B       1000    1000  100
```

### blocked

The blocked tasks are listed, if any. Example:

```
Blocked:
NAME    STRIDE  PASS  PRI   
A       500     2000  200 
```

## Picking the next task to schedule

The task with the lowest pass value is chosen to run next. In the event of a tie, sort alphabetically. If ```A``` and ```B``` have the same pass value, ```A``` will run.

```
Job: C scheduled.
```


## Running the tests

Coming - you will have access to several tests. Other tests will not be given to you. You must match the expected output letter for letter.




