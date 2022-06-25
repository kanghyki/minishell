#include "cmd.h"

void	ft_execute(t_argument *argument, int is_parent)
{
	int				is_path;
	char			*pa_path;
	char			*command;
	enum e_btype	bull_type;

	command = argument->pa_argument[COMMAND_POSITION];
	bull_type = INVAILD;
	if (is_builtin(command, &bull_type) == true)
	{
		ft_builtin(argument, bull_type, is_parent);
		return ;
	}
	is_path = false;
	if (ft_strchr(argument->pa_argument[COMMAND_POSITION], '/') != false)
		is_path = true;
	else
		is_path = false;
	if (is_path)
		ft_execute_path(argument);
	pa_path = ft_search_command_path_malloc(argument->env, argument->pa_argument[COMMAND_POSITION]);
	if (pa_path != NULL)
		ft_execute_nopath(argument, pa_path);
	if (ft_is_command_dir())
		ft_execute_except_case(argument);
	ft_execute_error(command, is_parent);
}

int		ft_execute_path(t_argument *arg)
{
	char	**env;

	env = ft_bstenv_to_dpenv(arg->env);
	g_exit = execve(arg->pa_argument[COMMAND_POSITION], arg->pa_argument, env);
	ft_remove_copy_env(env);
	return 0;
}

void	ft_execute_error(char * command, int is_parent)
{
	if (errno == 13)
		ft_error(EXE_PERMISSION, command, is_parent);
	else if (errno == 2)
		ft_error(EXE_NO_DIR, command, is_parent);
	else
		ft_error(EXE_CMD_NOT, command, is_parent);
}

