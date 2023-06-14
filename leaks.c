#include<unistd.h>
#include<stdlib.h>
int main()
{
	while (42)
	{
		system("leaks minishell");
		sleep(1);
	}
}
