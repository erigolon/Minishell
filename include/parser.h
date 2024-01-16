/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:10:50 by vicrodri          #+#    #+#             */
/*   Updated: 2024/01/16 20:08:30 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_ms		t_ms;
typedef struct s_cmdlist	t_cmdlist;
typedef struct s_envlist	t_envlist;

enum e_tokens {
	CHAR_PIPE = '|',
	CHAR_SQUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SPACE = ' ',
	CHAR_TILDE = '~',
	CHAR_LESS = '<',
	CHAR_GREAT = '>',
	CHAR_LESSLESS = 63,
	CHAR_GREATGREAT = 65,
	DELIMITER,
	INFILE,
	OUTFILE,
	OUTFILE_APPEND,
	EXPANDED,
	CHAR_NORMAL = -1,
	CHAR_NULL = 0,
};

enum e_status {
	NORMAL,
	ESCAPED,
};

enum e_quote_status {
	NO_QUOTE,
	DOUBT_QUOTE,
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
};

typedef struct s_token	t_token;

typedef struct s_token
{
	int		type;
	char	*str;
	int		status;
	int		escaped;
	int		join_next;
	t_token	*next;
	t_token	*prev;
}	t_token;

typedef struct s_lexer
{
	t_token	*token_list;
	int		n_tokens;
	int		error;
}	t_lexer;


t_lexer		*ft_tokenize_line(char *input, t_ms *ms);
void		join_tokens(t_token *token);
void		join_dollars(t_token *token);

/* parser/lexer_utils.c */

void		lexer_init(char *input, t_token *token);
void		lexer_free(t_lexer *lexer);
int			lexer_files(t_token *token);
int			count_tokens(t_lexer *lexer);

/* parser/tokens.c */

int			close_quotes(t_token *tok);
t_token		*other_tokens(t_token *token, int type, int *j, int len);
t_token		*redirect_token(t_token *token, char *input, int *j, int *i);
t_token		*quote_token(t_token *token, int type, int *j, int len);

/* parser/tokens_utils.c */

int			get_token_type(char c);
t_token		*new_token(t_token *token, int size);
void		free_token(t_token *token);
void		remove_empty_tokens(t_lexer	*lexer);
void		trim_quotes_token(t_token *token);

/* parser/expander.c */
t_token		*expand_tokens(t_lexer *lexer, t_ms *ms);
int			replace_next_dollar(char *str, t_ms *ms, t_token *tok);
int			replace_exit_status(t_token *tok, t_ms *ms, char *free_str);
int			replace_dollar_digit(t_token *tok, t_ms *ms, char *free_str);
void		replace_tilde(t_token *tok, t_ms *ms);

/* parser/expander_utils.c */
t_envlist	*get_env_var(char *str, t_ms *ms);
char		*replace_str(char *og, char *find, char *repl);
char		*get_dollar_name(char *str);

/* parser/wildcard_expander.c */
void		expand_all_wildcards(t_lexer *lex);
t_token		*expand_wildcard(t_token *tok, char **wildcards);

/* parser/fill_cmds.c */
void		tokens_to_commands(t_ms *ms, t_lexer *lex);
t_token		*fill_cmd(t_cmdlist *s, t_token *tok);
void		get_all_args(t_cmdlist *cmd, t_token *tok);
int			count_args(t_token *tok);
int			open_files_cmd(t_cmdlist *cmd);

#endif