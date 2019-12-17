// The MIT License (MIT)
//
// Copyright (c) 2016, 2017 Trevor Bakker
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

/*

    Name: Matthew Grossweiler
    ID: 1001626716

*/




#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 10     // Mav shell only supports ten arguments


static void handle_signal (int sig)
{

}


int main()
{

  char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );


  pid_t child_pid;
  int status, i;
  int pid_array[14];
  int array_count = 0;
  int history_count = 0;
  int return_exec = 0;
  char c_history[14][MAX_COMMAND_SIZE];

  memset(&pid_array, '\0', 15* sizeof(int));

  struct sigaction act;

  memset(&act, '\0', sizeof(act));

  act.sa_handler = &handle_signal;

  while( 1 )
  {
    // Print out the msh prompt
    printf ("msh> ");

    // Read the command from the commandline.  The
    // maximum command that will be read is MAX_COMMAND_SIZE
    // This while command will wait here until the user
    // inputs something since fgets returns NULL when there
    // is no input
    while( !fgets (cmd_str, MAX_COMMAND_SIZE, stdin) );



    // Large if/else if statement that will check the input string for the ! character.
    // If the ! character is found it will also check for a number corresponding to a command in the history array.
    // If that number is valid then it will copy over that past command in place of the '!n' and run it.
    // If a valid number is found then will print 'Command not found'.
    if ((cmd_str[0] == '!') && (cmd_str[1] == '1') && (cmd_str[2] == '\n'))
    {
      strcpy(cmd_str, c_history[0]);
    }

    else if ((cmd_str[0] == '!') && (cmd_str[1] == '2') && (cmd_str[2] == '\n'))
    {
      strcpy(cmd_str, c_history[1]);
    }
    else if ((cmd_str[0] == '!') && (cmd_str[1] == '3') && (cmd_str[2] == '\n'))
    {
      strcpy(cmd_str, c_history[2]);
    }
    else if ((cmd_str[0] == '!') && (cmd_str[1] == '4') && (cmd_str[2] == '\n'))
    {
      strcpy(cmd_str, c_history[3]);
    }
    else if ((cmd_str[0] == '!') && (cmd_str[1] == '5') && (cmd_str[2] == '\n'))
    {
      strcpy(cmd_str, c_history[4]);
    }
    else if ((cmd_str[0] == '!') && (cmd_str[1] == '6'))
    {
      strcpy(cmd_str, c_history[5]);
    }
    else if ((cmd_str[0] == '!') && (cmd_str[1] == '7'))
    {
      strcpy(cmd_str, c_history[6]);
    }
    else if ((cmd_str[0] == '!') && (cmd_str[1] == '8'))
    {
      strcpy(cmd_str, c_history[7]);
    }
    else if ((cmd_str[0] == '!') && (cmd_str[1] == '9'))
    {
      strcpy(cmd_str, c_history[8]);
    }
    else if ((cmd_str[0] == '!') && (cmd_str[1] == '1') && (cmd_str[2] == '0'))
    {
      strcpy(cmd_str, c_history[9]);
    }
    else if ((cmd_str[0] == '!') && (cmd_str[1] == '1') && (cmd_str[2] == '1'))
    {
      strcpy(cmd_str, c_history[10]);
    }
    else if ((cmd_str[0] == '!') && (cmd_str[1] == '1') && (cmd_str[2] == '2'))
    {
      strcpy(cmd_str, c_history[11]);
    }
    else if ((cmd_str[0] == '!') && (cmd_str[1] == '1') && (cmd_str[2] == '3'))
    {
      strcpy(cmd_str, c_history[12]);
    }
    else if ((cmd_str[0] == '!') && (cmd_str[1] == '1') && (cmd_str[2] == '4'))
    {
      strcpy(cmd_str, c_history[13]);
    }
    else if ((cmd_str[0] == '!') && (cmd_str[1] == '1') && (cmd_str[2] == '5'))
    {
      strcpy(cmd_str, c_history[14]);
    }


    /* Parse input */
    char *token[MAX_NUM_ARGUMENTS];


    int   token_count = 0;

    // Pointer to point to the token
    // parsed by strsep
    char *arg_ptr;

    char *working_str  = strdup( cmd_str );

    // we are going to move the working_str pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    char *working_root = working_str;





    // Tokenize the input stringswith whitespace used as the delimiter
    while ( ( (arg_ptr = strsep(&working_str, WHITESPACE))  != NULL) &&
              (token_count<MAX_NUM_ARGUMENTS))
    {
      token[token_count] = strndup( arg_ptr, MAX_COMMAND_SIZE );

      if( strlen( token[token_count] ) == 0 )
      {
        token[token_count] = NULL;
      }
        token_count++;
    }



    // Filling c_history which is an array of strings. If is used to fill the initial 15 entries.
    // Else is used to replace older entries once the 15 limit is reached.


    if(history_count <= 14)
    {
      strcpy(c_history[history_count], cmd_str);
      history_count = history_count + 1;
    }
    else
    {
      for(i = 0; i <= 13; i++)
      {
        strcpy(c_history[i], c_history[i+1]);
      }
      strcpy(c_history[14], cmd_str);
    }



    // Checking for a newline in which case the loop is reset.
    if (token[0] == '\0')
    {
      continue;
    }



    // Calling the signal handler in case of ctrl-z or ctrl-c so that only the child processes are effected. Voids their functionality for the parent.
    if (sigaction(SIGINT, &act, NULL) < 0)
    {
      return 1;
    }
    else if (sigaction(SIGTSTP, &act, NULL) < 0)
    {
      return 1;
    }


    // Using "exit" and "quit" as an exiting condition
    if ( ( strcmp("exit", token[0]) == 0) || (strcmp("quit", token[0]) == 0))
    {
      exit(0);
    }


    // Checking for cd -- Changing directory
    else if ( strcmp("cd", token[0]) == 0)
    {
       chdir(token[1]);
    }

    // Checking for listpids keyword to then display the last 15 pids.
    else if ( strcmp("listpids", token[0]) == 0)
    {
      for (i = 0; i <= 14; i++)
      {
        if (pid_array[i] != 0)
        {
          printf("%d. %d\n", i+1, pid_array[i]);
        }
      }
    }


    // Checking for history keyword to then display last 50 commands.
    else if ( strcmp("history", token[0]) == 0)
    {
      for(i = 0; i <= history_count-1; i++)
      {
         printf("%d. %s", i+1, c_history[i]);
      }
    }


    // Checking for bg keyword to then push process to background.`
    else if (strcmp(token[0], "bg") == 0)
    {
      kill(token[1], SIGCONT);
    }



    // Main functionality. Forks the process so that a child process can do different things while parent waits.
    else
    {

      child_pid = fork();

      pid_array[array_count] = getpid();


      if (child_pid == 0)
      {
        return_exec =  execvp(token[0], token);
        if (return_exec == -1)
        {
          printf("Command Not Found\n");
        }
      }






      //Saving the pids in an array to display later
      if (pid_array[14] == 0)
      {
        pid_array[array_count] = getpid();
        array_count = array_count + 1;
      }
      else if (pid_array[14] != 0)
      {
        for (i = 0; i <= 13; i++)
        {
          pid_array[i] = pid_array[i+1];
        }

        pid_array[14] = getpid();
      }



      // Parent Process waiting for child to finish up.
      waitpid (child_pid, &status, 0);

    }


    free( working_root );

  }
  return 0;
}
