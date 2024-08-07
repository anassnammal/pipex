#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef struct s_cmd
{
	char	*fullpath;
	char	**args;
}	t_cmd;

typedef struct s_pipex
{
	t_cmd	**cmd;
	int		infile;
	int		outfile;
	int		pipe_fd[2];
	pid_t	pid[2];
}	t_pipex;

typedef unsigned char	t_byte;	// unsigned byte (8 bits)

# define INFILE 0x01			// close infile fd
# define OUTFILE 0x02			// close outfile fd
# define PIPERD 0x04			// close pipe read end
# define PIPEWR 0x08			// close pipe write end
# define PIPE 0x0C				// close pipe both ends
# define CMDS 0x010				// free cmds fullpath and args
# define PROC_SUCCESS 0x020		// exit(EXIT_SUCCESS)
# define PROC_FAILURE 0x040		// exit(EXIT_FAILURE)
# define ALL_SUCCESS 0x13		// release all used ressourses
# define ALL_FAILURE 0x05F		// release all used ressourses, exit

# define FAIL -1

# define ERENV "pipex: cannot access Environment variables"
# define ERPATH "pipex: PATH variable not found"
# define ERHEAP "malloc: Failed to allocate the required memory"
# define ERARGS	"pipex: too few / many args"
# define EREMPT	"pipex: empty argument!"
# define USAGE	"USAGE: ./pipex \"infile\" \"cmd1\" \"cmd2\" \"outfile\""

// check if input command are valid and parse it
t_cmd	**parse_cmds(char const **av, char const **path);
// print error to the stderr
void	console_err(char *err_holder, ...);
// free array of strings
void	free_2d(char **ptr);
// free t_cmd struct
void	free_cmds(t_cmd **cmd, int i);
// release unused memory, file discriptor or even the program
void	release(t_pipex *pipex, t_byte option);

#endif