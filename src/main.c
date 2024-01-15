#include "../include/minishell.h"

void	add_token(char *str, int type, t_minishell *mini)
{
	t_token	*new_token;
	t_token	*last_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		exit(EXIT_FAILURE);
	if (ft_strlen(str) == 2)
		new_token->content = ft_strdup(str);
	else
		new_token->content = str;
	new_token->type = type;
	new_token->next = NULL;
	if (mini->token)
	{
		last_token = mini->token;
		while (last_token->next != NULL)
			last_token = last_token->next;
		last_token->next = new_token;
	}
	else
		mini->token = new_token;
}

int	check_meta(const char *input, t_minishell *mini)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '>')
		{
			add_token(">>", DOUBLE_GREAT, mini);
			i++;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			add_token("<<", DOUBLE_LESS, mini);
			i++;
		}
		else if (input[i] == '>' && input[i + 1] != '>')
			add_token(">", GREAT, mini);
		else if (input[i] == '<' && input[i + 1] != '<')
			add_token("<", LESS, mini);
		else if (input[i] == '|')
			add_token("|", PIPE, mini);
		i++;
	}
	return (1);
}

void	check_quote(const char *prompt, t_minishell *mini)
{
	int	quote;
	int	double_quote;

	quote = 0;
	double_quote = 0;
	while (*prompt)
	{
		if (*prompt == '"')
			double_quote++;
		if(*prompt == '\'')
			quote++;
		prompt++;
		
	}
}

void	lexer(const char *prompt, t_minishell *mini)
{
	check_meta(prompt, mini);
	check_quote(prompt, mini);
	check_space(prompt, mini);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;
	const char	*prompt;
	char		**tokens;

	mini = ft_calloc(1, sizeof(t_minishell));
	mini->token = ft_calloc(1, sizeof(t_token));
	mini->token->content = NULL;
	while (1)
	{
		prompt = readline("Minishell $> ");
		lexer(prompt, mini);
	}
}

/* 
Tokenização:
Terminar o seu trabalho com as aspas
~Validação de aspas (tá fechado, aspa dentro de aspa etc)
Adaptar a função para funcionar apenas foras das aspa, se caso tiver dentro imprimir como se fosse string

*/