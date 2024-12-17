#include <stdio.h> //Used for standard I/O functions.
#include <stdlib.h> //Used for atoi and exit functions.
#include <unistd.h> //Used for fork and execvp system calls.
#include <sys/wait.h> //Used for waitpid and process management.

int main(int argc, char* argv[]) {
    //Validates the commond line argument(s).
    if (argc != 4) {
        fprintf(stderr, "Usage: %s START END NUMBER_OF_CALLS\n", argv[0]);
        return 1;
    }

    //Parses through the input arguments.
    int start = atoi(argv[1]); //Starting # of range.
    int end = atoi(argv[2]); //Ending # of range.
    int calls = atoi(argv[3]); //# of child processes to create.
    
    //Calculates the range size for each child process.
    //Divides the range into subranges.
    int range = (end - start + calls - 1) / calls;  

    //Array to store process IDs of child processes.
    int processids[calls];

    //Variable to store total # of primes.
    int total = 0;

    //Forks and calls countprimes in a loop.
    for (int i = 0; i < calls; i++) {
        //Calculate the subrange for each child process.
        int substart = start + i * range;
        int subend = (i == calls - 1) ? end : substart + range;

        //For a new process which will become a child process.
        if ((processids[i] = fork()) == 0) {
            //Converts subrange start and end to strings for execvp.
            char arg1[10], arg2[10];
            sprintf(arg1, "%d", substart);
            sprintf(arg2, "%d", subend);

            //Prepare arguments for execvp.
            char* arguments[] = {"./countprimes", arg1, arg2, NULL};
            
            //Replace child process with countprimes.
            execvp(arguments[0], arguments);
            
            //If execvp fails, print an error and exit.
            perror("execvp failed");
            exit(1);
        }
    }

    //Wait for child processes and sum their results.
    for (int i = 0; i < calls; i++) {
        int status;
        //Wait for each child process to finish.
        waitpid(processids[i], &status, 0);
        //Check if the child process exited normally.
        if (WIFEXITED(status)) {
            //Use WEXITSTATUS to retrieve the return value (prime ct).
            total += WEXITSTATUS(status);
        }
    }
    //Print the total count of primes.
    printf("Total prime numbers: %d\n", total);
    return 0;
}
