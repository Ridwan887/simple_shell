#include "shell.h"

int programEntry(int argumentCount, char **argumentVector)
{
	Data_d data[] = { INIT_DATA };
	int fileDescriptor = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fileDescriptor)
			: "r" (fileDescriptor));

	if (argumentCount == 2)
	{
		fileDescriptor = open(argumentVector[1], O_RDONLY);
		if (fileDescriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_printString(argumentVector[0]);
				_printString(": 0: Can't open ");
				_printString(argumentVector[1]);
				_printChar('\n');
				_printChar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readfd = fileDescriptor;
	}
	initializeEnvironment(data);
	readCommandHistory(data);
	shellMain(data, argumentVector);
	return (EXIT_SUCCESS);
}
