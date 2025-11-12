#include "minishell.h"

void	test_setenv(char *name, char *value, t_env **env)
{
	ft_printf("setting %s at %s ...\n", name, value);
	ft_set_env(name, value, env);
	char *strenv = ft_export_noargs(env);
	ft_printf("%s\n", strenv);
}

void	test_rmenv(char *name, t_env **env)
{
	ft_printf("removing %s ...\n", name);
	ft_rm_env(name, env);
	char *strenv = ft_export_noargs(env);
	ft_printf("%s\n", strenv);
}

void	test_env(t_env **env)
{
	ft_printf("testing env command ...\n");	
	ft_env(env);
}

void	test_unset(char **args, t_env ** env)
{
	int i = 0;
	ft_printf("testing unset");	
	while (args[i] && args[i][0])
	{
		ft_printf(" %s", args[i]);
		i++;
	}
	ft_printf("...\n");	
	ft_unset(args, env);
	char *strenv = ft_export_noargs(env);
	ft_printf("%s\n", strenv);
	test_env(env);
}

void	test_export(char **args, t_env ** env)
{
	int i = 0;
	ft_printf("testing export");	
	while (args[i] && args[i][0])
	{
		ft_printf(" %s", args[i]);
		i++;
	}
	ft_printf("...\n");	
	ft_export(args, env);
	char *strenv = ft_export_noargs(env);
	ft_printf("%s\n", strenv);
	test_env(env);
}

int main (void)
{
	ft_putendl_fd("main start", 1);
	t_env **env = ft_initialize_env();
	ft_putendl_fd("inititalizing OK", 1);
	char *strenv = ft_export_noargs(env);
	ft_printf("%s\n", strenv);
	test_setenv("HELLO", "world", env);
	test_setenv("HOME", "chez_moi", env);
	test_setenv("EMPTY", "", env);
	test_setenv("NIL", NULL, env);
	test_rmenv("SHLVL", env);
	test_rmenv("world", env);
	test_rmenv("HELLO", env);
	test_rmenv("PWD", env);
	test_rmenv("PATH", env);
	test_rmenv("HOME", env);
	test_rmenv("vide", env);
	test_setenv("HELLO", "\\/\\/0|27|)", env);
	test_setenv("HOME", "chez_toi", env);

	char *a10 = "HOME=mine";
	char *a11 = "ROOM";
	char *a12 = "ATTIC=player";
	char *a13 = "CAVE=bat";
	char *a14 = "DINING=";
	char *a15 = "SECRET=1+1=2";
	char **a1 = malloc(sizeof(char *) * 7);
	a1[0] = a10;
	a1[1] = a11;
	a1[2] = a12;
	a1[3] = a13;
	a1[4] = a14;
	a1[5] = a15;
	a1[6] = NULL;
	test_export(a1, env);

	char *a20 = "HOME=mine";
	char *a21 = "ROOM";
	char *a22 = "ATTIC";
	char *a23 = "CAV";
	char *a24 = "DININGR";
	char *a25 = "";
	char **a2 = malloc(sizeof(char *) * 7);
	a2[0] = a20;
	a2[1] = a21;
	a2[2] = a22;
	a2[3] = a23;
	a2[4] = a24;
	a2[5] = a25;
	a2[6] = NULL;
	test_unset(a2, env);
}
