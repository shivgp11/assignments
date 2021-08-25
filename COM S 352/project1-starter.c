#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX_LINE 80
#define MAX_ARGS (MAX_LINE/2 + 1)
#define REDIRECT_OUT_OP '>'
#define REDIRECT_IN_OP '<'
#define PIPE_OP '|'
#define BG_OP '&'

/*
	This is a simple shell that uses structs to track the commands. The shell handles background and foreground commands.
	It also handles file redirection and piping which is handled in the foreground process code. The background and foreground processes
	are split up into two different sections in the code. Within the foreground processes section, I have seperate if blocks handling the 
	file redirection and piping. There were new functions created. The only extra fields added was a Cmd array called jobs that is use to hold the 
	background processes. Finally at the very end of the code, I check on the statuses of the background commands. 
*/






/*Holds a single command. */
typedef struct Cmd
{
	/*The command as input by the user. */
	char line[MAX_LINE + 1];
	/*The command as null terminated tokens. */
	char tokenLine[MAX_LINE + 1];
	/*Pointers to each argument in tokenLine, non-arguments are NULL. */
	char *args[MAX_ARGS];
	/*Pointers to each symbol in tokenLine, non-symbols are NULL. */
	char *symbols[MAX_ARGS];
	/*The process id of the executing command. */
	pid_t pid;

	/*TODO: Additional fields may be helpful. */

}

Cmd;

//CMd struct array to hold all of the background processes
Cmd *jobs[100];
//used to keep count of all the background processes in the array jobs array
int count = 0;

/*The process of the currently executing foreground command, or 0. */
pid_t foregroundPid = 0;

/*Parses the command string contained in cmd->line.
 * *Assumes all fields in cmd (except cmd->line) are initailized to zero.
 * *On return, all fields of cmd are appropriatly populated. */
void parseCmd(Cmd *cmd)
{
	char *token;
	int i = 0;
	strcpy(cmd->tokenLine, cmd->line);
	strtok(cmd->tokenLine, "\n");
	token = strtok(cmd->tokenLine, " ");
	while (token != NULL)
	{
		if (*token == '\n')
		{
			cmd->args[i] = NULL;
		}
		else if (*token == REDIRECT_OUT_OP || *token == REDIRECT_IN_OP ||
			*
			token == PIPE_OP || *token == BG_OP)
		{
			cmd->symbols[i] = token;
			cmd->args[i] = NULL;
		}
		else
		{
			cmd->args[i] = token;
		}

		token = strtok(NULL, " ");
		i++;
	}

	cmd->args[i] = NULL;
}

/*Finds the index of the first occurance of symbol in cmd->symbols.
 * *Returns -1 if not found. */
int findSymbol(Cmd *cmd, char symbol)
{
	for (int i = 0; i < MAX_ARGS; i++)
	{
		if (cmd->symbols[i] && *cmd->symbols[i] == symbol)
		{
			return i;
		}
	}

	return -1;
}

/*Signal handler for SIGTSTP (SIGnal - Terminal SToP),
 *which is caused by the user pressing control+z. */
void sigtstpHandler(int sig_num)
{
	/*Reset handler to catch next SIGTSTP. */
	signal(SIGTSTP, sigtstpHandler);
	if (foregroundPid > 0)
	{
		/*Foward SIGTSTP to the currently running foreground process. */
		kill(foregroundPid, SIGTSTP);
		/*TODO: Add foreground command to the list of jobs. */
	}
}

int main(void)
{
	/*Listen for control+z (suspend process). */
	signal(SIGTSTP, sigtstpHandler);
	while (1)
	{
		printf("352> ");
		fflush(stdout);
		Cmd *cmd = (Cmd*) calloc(1, sizeof(Cmd));
		fgets(cmd->line, MAX_LINE, stdin);
		parseCmd(cmd);
		if (!cmd->args[0])
		{
			free(cmd);
		}
		else if (strcmp(cmd->args[0], "exit") == 0)
		{
			free(cmd);
			exit(0);

			/*TODO: Add built-in commands: jobs and bg. */

		}
		else
		{
			/*
				This is where the background processes are handled
				Once the parser finds the '&' within the command, it will go through this block of code
				I fork for the background process and save the process to the jobs array once the child finished executing
			*/
			if (findSymbol(cmd, BG_OP) != -1)
			{
				int status;
				cmd->pid = fork();
	
				if (cmd->pid == -1)
				{
					printf("fork failed");
					exit(1);
				}
				else if (cmd->pid == 0)
				{
					//printf("146: [%d] %d\n", count, getpid());
					execvp(cmd->args[0], cmd->args);
				}
				else 
				{
					jobs[count] = cmd;
					count++;
					printf("[%d] %d\n", count, cmd->pid);
				}
			}
			else
			{
				/*
					TODO: Run command in foreground. 
					This is where the foreground processes are handled
					The functionality is very similar to the background processes
					I fork to create a new process but I don't store them in the jobs array
					
				*/
				if (findSymbol(cmd, REDIRECT_OUT_OP) != -1)
				{
					/*
						for when we out redirecting out to a file 
					*/
					foregroundPid = fork();
					if (foregroundPid < 0)
					{
						printf("fork failed");
						exit(1);
					}
					else if (foregroundPid == 0)
					{
						//looking for the '>'
						int i = findSymbol(cmd, REDIRECT_OUT_OP);
						//redirect the output to standard output
						int fd = open(cmd->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IROTH);
						dup2(fd, STDOUT_FILENO);
						execvp(cmd->args[0], cmd->args);
					}
					else
					{
						//parent waits for the child process
						waitpid(foregroundPid, NULL, 0);
					}
				}
				else if (findSymbol(cmd, REDIRECT_IN_OP) != -1)
				{
					/*
						handles the commands for redirecting into a file
					*/
					foregroundPid = fork();
					if (foregroundPid < 0)
					{
						printf("fork failed");
						exit(1);
					}
					else if (foregroundPid == 0)
					{
						//looks for the '<' symbol in the command
						int i = findSymbol(cmd, REDIRECT_IN_OP);
						//takes the input from standard input, specified by the file
						int fd = open(cmd->args[i + 1], O_RDONLY);
						dup2(fd, STDIN_FILENO);
						execvp(cmd->args[0], cmd->args);
					}
					else
					{
						//parent waits for child to finish
						waitpid(foregroundPid, NULL, 0);
					}
				}
				else if (findSymbol(cmd, PIPE_OP) != -1)
				{
					//handles the commands for piping
					//create a pipe with 2 ends: read and write
					int pipefd[2];
					if (pipe(pipefd) < 0)
					{
						printf("pipe error\n");
						return 1;
					}

					foregroundPid = fork();
					if (foregroundPid < 0)
					{
						printf("fork failed");
						exit(1);
					}

					//for the first half of the command
					//this is the half that will be doing the writing
					if (foregroundPid == 0)
					{
						
						//close the read end of the pipe
						close(pipefd[0]);
						//redirect the output to the write end of the file: standard output
						dup2(pipefd[1], STDOUT_FILENO);
						//close the write end of the pipe
						close(pipefd[1]);
						execvp(cmd->args[0], cmd->args);
						return 0;
					}

					cmd->pid = fork();
					if (cmd->pid < 0)
					{
						printf("fork failed\n");
					}

					//for the second half the command, the part that will take an input
					if (cmd->pid == 0)
					{
						//close the write end of the file
						close(pipefd[1]);
						//read in from the read end of the pipe
						dup2(pipefd[0], STDIN_FILENO);
						close(pipefd[0]);
						//close the read end of the pipe
						int i = findSymbol(cmd, PIPE_OP);
						//the arguments for the second half the command start after '|' in the args
						execvp(cmd->args[i + 1], cmd->args + i + 1);
						return 0;
					}

					//close both ends of the pipe so it doesn't hang
					close(pipefd[0]);
					close(pipefd[1]);
					//parent waits for both child processes to finish executing
					waitpid(foregroundPid, NULL, 0);
					waitpid(cmd->pid, NULL, 0);

				}
				else
				{
					//same functionality as above but for simple commands 
					//no redirection or piping
					foregroundPid = fork();
					if (foregroundPid < 0)
					{
						printf("fork failed");
						exit(1);
					}
					else if (foregroundPid == 0)
					{
						execvp(cmd->args[0], cmd->args);
					}
					else
					{
						waitpid(foregroundPid, NULL, 0);
					}
				}
			}
		}
		
		/*TODO: Check on status of background processes. */
		
		//checks on the status of each of the background process in the jobs array
		int status = -1;
		for(int i = 0; i < count; i++) 
		{
			
			//call wait()  to save the status to the int status variable
			waitpid(jobs[i]->pid, &status, WNOHANG);
			if(status == 0) 
			{
				//if the process is done, remove it from the array and decrement the count
				printf("[%d] Done %s\n", i + 1, jobs[i]->line);
				free(jobs[i]);
				count--;
			}
			else if(status < -1) 
			{
				printf("error\n");
			}
		}
	}
	
	return 0;
}