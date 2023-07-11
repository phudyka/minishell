#include "../../include/main.h"

void print_arguments(t_data *data, int start_index)
{
	int     i;
	size_t  arg_len;

	i = start_index;
	while (data->cmd[i])
	{
		arg_len = ft_strlen(data->cmd[i]);
		if (arg_len >= 2 && data->cmd[i][0] == '"' && data->cmd[i][arg_len - 1] == '"')
			write(1, data->cmd[i] + 1, arg_len - 2);
		else
			write(1, data->cmd[i], arg_len);
		i++;
		if (data->cmd[i])
			write(1, " ", 1);
	}
}

void builtin_echo(t_data *data)
{
	int skip_newline;
	int i;

	i = 1;
	skip_newline = 0;
	if (!data->cmd[i])
	{
		write(1, "\n", 1);
		return;
	}
	if (ft_strcmp(data->cmd[i], "-n") == 0)
	{
		skip_newline = 1;
		i++;
	}
	print_arguments(data, i);
	if (!skip_newline)
		write(1, "\n", 1);
}