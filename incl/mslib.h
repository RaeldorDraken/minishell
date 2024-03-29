/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mslib.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:06:39 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/30 20:42:12 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSLIB_H
# define MSLIB_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

# include "../libft/libft.h"

// ? Global var
int	g_return_status;

typedef struct s_quotes {
	int	quote;
	int	miniquote;
}	t_quotes;

typedef struct s_separator {
	int		index;
	char	*separator;
	char	*prev_token;
	char	*next_token;
}	t_separator;

typedef struct s_cmd {
	int				index;
	int				argc;
	char			**argv;
	int				is_separator;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_counters {
	int				c1;
	int				c2;
}	t_counters;

typedef struct s_vars
{
	char			*input;
	int				looping;
	t_quotes		*quotes;
	t_counters		*c;
	char			**envar;
	char			*prompt;
	char			*inpli;
	char			**inpcomm;
	char			**tokens;
	int				inplen;
	int				sigbool;
	char			**paths;
	char			**cmd_buffer;
	t_cmd			*cmd;
	int				iofd[2];
	int				hdnumb;
	struct termios	term;
}	t_vars;

// * Main helpers

void	msh_free_memory_dynamic(t_vars *vars, int flag);
void	msh_reorder_input(t_vars *vars);
void	msh_execute_main2(t_vars *vars);
void	msh_execute_main(t_vars *vars);
int		msh_check_errors_syntax(t_vars *vars);
void	msh_set_init(t_vars *vars, char **envp);
int		msh_readline(t_vars *vars, int ac, char **av);
int		msh_check_inputline(t_vars *vars);

// * Utils

void	msh_sigint_handler(int sig);
char	*msh_strjoinchr(char *str, char ch);
void	msh_update_quotes_status(t_quotes *quotes, char c);
void	msh_init_quotes_struct(t_quotes *quote_struct);
char	*msh_free_return_null(char *ptr);
int		msh_cmd_is_built_in(t_cmd *cmd);
void	msh_str_to_lower(char *str);
void	msh_set_vars(t_vars *vars, char *input);

// * Helpers

void	msh_print_element(char *input, int start, int end);
void	msh_debug_cmd_list(t_cmd *first);
void	msh_print_env_vars(t_vars *vars, char *str);
void	msh_print_env_vars_extra(t_vars *vars, char *str, int env_length);
void	msh_print_env_vars_extra_two(t_vars *vars, char *str, int env_length);

// * env parser

int		msh_store_env_own_vars(t_vars *vars, char **envp);
int		msh_store_env_own_lines(t_vars *vars, char **envp, int index);

// * Parser

char	*msh_sanitize_input(char *str);
void	msh_reorder_redirs(t_vars *vars);
char	*msh_clean_irrelveant_spaces_in_input(char *input);
int		msh_malformed_quotes(char *input);
int		msh_quote_flag(char input, int qflag);
char	*msh_add_space_between_input(char *input, int qflag, int i, int j);
char	*msh_set_final_cmd(char **tcmds, char *cmd);

// * Validators

int		msh_chr_is_sep(char c);
int		msh_chr_is_double_redirection(char c, char x);
int		msh_is_startarg(char *input, int c, t_quotes *quotes);
int		msh_is_endarg(char *input, int c, t_quotes *quotes);
int		msh_is_space(int c);
int		msh_no_quotes(t_quotes *quotes);
int		msh_argv_need_expansion(char c);
int		msh_chr_is_redirection(char c);
int		msh_chr_is_pipe(char c);

// * Tokenizer-ish

char	**msh_split_cmd_argvs(char *input, int argc);
int		msh_count_tokens(char *input);
char	**msh_prepare_splitted_input_in_cmds(t_vars *vars);
t_cmd	*msh_tokenize(t_vars *vars);
int		msh_how_many_argv_have_the_cmd(char *input);
char	**msh_do_split_input_in_cmds(t_vars *v, char **splitted, char *cmd);
void	msh_do_split_input_in_cmds_extra(t_vars *v, char **splitted, char *cmd);
int		msh_count_tokens_extra(char *input, t_quotes quotes);

// * Destroyers

void	msh_free_cmd_list(t_cmd *first);
void	msh_free_raw_array(char **arr);
void	msh_free_envars(t_vars *vars);
void	msh_free_ptr(void *ptr);

//  * Built ins
void	msh_exec_builtin(t_cmd *cmd, t_vars *vars);

// ? exit built in
void	msh_exec_exit(t_cmd *cmd, t_vars *vars);
void	msh_exec_exit_extra(t_cmd *cmd, t_vars *vars, int *error);
int		msh_check_exit_param(char *param, int *error);
int		msh_check_out_range(int neg, unsigned long long num, int *error);
int		msh_atoi(char *str, int *error);
void	msh_atoi_extra(char *str, int *error, int *i);

// ? echo built in
void	msh_exec_echo(t_cmd *cmd, t_vars *vars);
int		msh_echo_has_n_flag(char *arg);
void	msh_echo_print(t_cmd *cmd, int n_flags, int index);

// ? env builtin
void	msh_exec_env(t_cmd *cmd, t_vars *vars);
int		msh_is_valid_env_var_key(char *var_name); 
int		msh_get_env_vars_length(t_vars *vars);

// ? pwd builtin
void	msh_exec_pwd(t_cmd *cmd, t_vars *vars);
int		msh_get_env_index(t_vars *vars, char *env_name);
void	msh_print_env_value(t_vars *vars, int env_index);
char	*msh_get_env_value(t_vars *vars, int env_index);

// ? cd builtin
void	msh_exec_cd(t_cmd *cmd, t_vars *vars);
void	msh_cd_go_home(t_vars *vars);
int		msh_cd_change_dir(t_vars *vars, char *path);
void	msh_cd_go_to_path(t_vars *vars, char *path, char *ret);
void	msh_set_pwds(t_vars *vars, char *path);
char	*msh_set_path(char *path, t_vars *vars);

// ? unset builtin
void	msh_exec_unset(t_cmd *cmd, t_vars *vars);
int		msh_remove_envar(t_vars *vars, int index);
char	**msh_realloc_env_vars(t_vars *vars, int length);

// ? export builtin
void	msh_exec_export(t_cmd *cmd, t_vars *vars);
int		msh_set_env_var(t_vars *vars, char *key, char *value);
char	**msh_get_env_var_key_value_pair(char *str);
void	msh_exec_export_extra(
			t_cmd *cmd, t_vars *vars, char **new_env_var, int c
			);

// ? Executions
int		msh_execute_start(t_vars *vars);
int		msh_cmd_execute(t_vars *vars, t_cmd *cmd);
char	*msh_getpath_cmd(t_vars *vars, char *cmd);
char	*msh_getpath_line(char **envp);
void	msh_getpath(t_vars *vars, char **envp);
int		msh_pipe_fork1(t_vars *vars, t_cmd *cmd, int prev_pobj[2], int rc);
int		msh_pipe_fork2(t_vars *vars, t_cmd tcmd, int pobj[2], pid_t child2);
void	msh_pipe_execute(t_vars *vars, t_cmd *tcmd2, t_cmd *tcmd);
void	msh_single_cmd(t_vars *vars, pid_t single, t_cmd *tcmd);
void	msh_final_return(void);

// ? Redirections
int		msh_is_pipe(t_cmd tcmd);
int		msh_next_pipe(t_cmd cmd);
void	msh_pipe_child1(int pobj[2], int prev_pobj[2], int recursion);
void	msh_pipe_child2(int pobj[2]);
int		msh_is_redirect(t_cmd tcmd);
int		msh_set_redirect(t_vars *vars, t_cmd *tcmd);
int		msh_exec_redirect(t_cmd *cmd, int fd, char *argv, int hdnbr);
int		msh_is_redirect_first(t_cmd tcmd);
int		msh_set_redirect_first(t_vars *vars, t_cmd *tcmd);
int		msh_exec_redirect_first(t_cmd *cmd, int fd, char *argv, int hdnbr);
void	msh_save_io(int save[2]);
void	msh_restore_io(int save[2]);
char	**ft_qsplit(char const *s, char c, size_t n, int qflags);

// ? Heredoc
void	msh_close_pipes(int pobj[2]);
int		msh_store_heredocs(t_vars *vars, int i, pid_t hdproc);
char	*msh_read_heredoc(int hdnbr);
void	msh_heredoc(char *delim, char *fnum);
void	msh_clean_heredoc(t_vars *vars);

// * Expander

void	msh_expander(t_vars *vars);
void	msh_expand_argv(t_vars *vars, char **argv, int c);
void	msh_expand_env_var(t_vars *vars, char *arg, char **new_arg);
char	*msh_read_env_name(char *arg);
int		msh_advance_from_env_var(char *arg);

// ? Errors

void	msh_print_error(char *param, char *msg);
void	msh_errors_exit(char *param, char *msg);
void	msh_errors_export(char *param, char *msg);
void	msh_errors_cd(char *param, char *msg);
int		msh_errors_syntax(t_cmd *cmd, char *param, int flag);
int		nsh_errors_syntax_extra(int flag, char *param);

// SIGNALs
void	msh_sigint_handler_block_cmds(int sig);
void	msh_sigquit_handler(int sig);
void	msh_ignore_signals(t_vars *vars, int ac, char **av);
void	msh_sigint_handler(int sig);
void	msh_sigint_heredoc(int sig);
void	msh_set_signals(int type);
int		msh_check_sigint(int signum);

#endif