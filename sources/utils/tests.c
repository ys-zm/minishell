/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tests.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 16:49:18 by fra           #+#    #+#                 */
/*   Updated: 2023/06/11 18:36:37 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	test_clear_quotes(void)
// {
// 	char *string;

// 	string = "asd";
// 	ft_printf("str: >%s< - trimmed >%s<\n", string, clear_str(string));

// 	string = "\'asd\'";
// 	ft_printf("str: >%s< - trimmed >%s<\n", string, clear_str(string));

// 	string = "\"asd\"";
// 	ft_printf("str: >%s< - trimmed >%s<\n", string, clear_str(string));

// 	string = "";
// 	ft_printf("str: >%s< - trimmed >%s<\n", string, clear_str(string));

// 	string = "\'";
// 	ft_printf("str: >%s< - trimmed >%s<\n", string, clear_str(string));

// 	string = "\"";
// 	ft_printf("str: >%s< - trimmed >%s<\n", string, clear_str(string));

// 	string = "as\'d";
// 	ft_printf("str: >%s< - trimmed >%s<\n", string, clear_str(string));

// 	string = "as\"d";
// 	ft_printf("str: >%s< - trimmed >%s<\n", string, clear_str(string));

// 	string = "as\'ASD\'ed";
// 	ft_printf("str: >%s< - trimmed >%s<\n", string, clear_str(string));

// 	string = "\'asd\'ASD";
// 	ft_printf("str: >%s< - trimmed >%s<\n", string, clear_str(string));

// 	string = "asd\"ASD\"";
// 	ft_printf("str: >%s< - trimmed >%s<\n", string, clear_str(string));
	
// 	string = "a\"ASD\"a";
// 	ft_printf("str: >%s< - trimmed >%s<\n", string, clear_str(string));
	
// 	string = "asd\"ASD";
// 	ft_printf("str: >%s< - trimmed >%s<\n", string, clear_str(string));
// }

// void	test_pipe_2(void)
// {
// 	char *string;
//     uint32_t pos;

// 	string = "asd | ciao";
//     pos = 2;
// 	ft_printf("str: >%s< - pos: %s, result: %u\n", string, string + pos, get_order_cmd(string, pos));
// 	string = "asd | ciao";
//     pos = 3;
// 	ft_printf("str: >%s< - pos: %s, result: %u\n", string, string + pos, get_order_cmd(string, pos));
// 	string = "asd | ciao";
//     pos = 6;
// 	ft_printf("str: >%s< - pos: %s, result: %u\n", string, string + pos, get_order_cmd(string, pos));
// 	string = "asd | ciao | prova ancora | aadsas";
//     pos = 31;
// 	ft_printf("str: >%s< - pos: %s, result: %u\n", string, string + pos, get_order_cmd(string, pos));
// 	string = "asd | ciao | prova ancora ";
//     pos = 21;
// 	ft_printf("str: >%s< - pos: %s, result: %u\n", string, string + pos, get_order_cmd(string, pos));
// 	string = "asd | ciao | prova ancora | aadsas";
//     pos = 6;
// 	ft_printf("str: >%s< - pos: %s, result: %u\n", string, string + pos, get_order_cmd(string, pos));
// }



// void	test_pipes(void)
// {
// 	char *pipe_str;

// 	pipe_str = "sadasd|fg";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "sadasds||g";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "sadasd|||fg";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "sadasdss| asdasds | awsdasd ggh | fg";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "sadasdss|| asdasds | awsdasd ggh | fg";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "sada\"sdss||| a\"sdasds | awsdasd ggh | fg";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "sadasdss || asdasds | awsdasd ggh | fg";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "sadasd\'ss ||| a\'sdasds | awsdasd ggh | fg";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "sadasdss |   |asdasds | awsdasd ggh | fg";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "sadasdss| |asdasds | awsdasd ggh | fg";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "sadasdss | || |asdasds | awsdasd ggh | fg";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "|sadasdss| asdasds | awsdasd ggh | fg";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "| sadasdss| asdasds | awsdasd ggh | fg";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "|| sadasdss| asdasds | awsdasd ggh | fg";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "sa||dasd|ss| asdasds | awsdasd ggh | fg";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg|";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg|  ";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg||";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg|  a";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// 	pipe_str = "sadasdss| as |dasds | awsdasd ggh | fg |  ";
// 	ft_printf("str: %s - status %d\n", pipe_str, check_pipes(pipe_str));
// }

// void	test_redirections(void)
// {
// 	char *red_str;

// 	red_str = "sadasdss> asd";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasdss> asd";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasdss>asd";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasdss > asd";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasdss >>> asd";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasdss <<< asd";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasdss >>> asd";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasdss << < asd";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasdss >> > asd";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasdss < < asd";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasdss > < asd";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasdss > > asd";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasdss < > asd";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasds<asd";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasdss >";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasdss <   ";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasdss < \t";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasdss <";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasdss < |";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// 	red_str = "sadasdss < | adasdas";
// 	ft_printf("str: %s - status %d\n", red_str, check_redirections(red_str));
// }

// void	test_quotes(void)
// {
// 	char *quot_str;

// 	quot_str = "efdsdf\"asdasd\"asdasd";
// 	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
// 	quot_str = "efdsdf\'asdasd\'asdasd";
// 	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
// 	quot_str = "efdsdf\'asda\"sd\'asdasd";
// 	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
// 	quot_str = "efdsdf\'as\'dasd\'asdasd";
// 	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
// 	quot_str = "efdsdf\'as\"asdasd\"dasd\'asdasd";
// 	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
// 	quot_str = "efdsdf\'as\"asdasd\"dasd\'asdasdas\'asdasd\'dasd";
// 	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
// 	quot_str = "efdsdf\'as\"asdasd\"dasd\'asdasd\"asasdasddasd";
// 	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
// 	quot_str = "efdsdf\'as\"asdasd\"dasd\'asdas\'das\'asdasd\'dasd";
// 	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
// 	quot_str = "efdsdf\'asdasdasdasd";
// 	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
// 	quot_str = "efdsdf\'as\'da\"sd\"asdasd";
// 	ft_printf("str: %s - status %d\n", quot_str, check_quotes(quot_str));
// }

// void	test_last_pipe(void)
// {
// 	char *red_str;

// 	red_str = "asdadsd |";
// 	ft_printf("str: %s - status %d\n", red_str, has_trailing_pipe(red_str));
// 	red_str = "asdadsd |   ";
// 	ft_printf("str: %s - status %d\n", red_str, has_trailing_pipe(red_str));
// 	red_str = "asdadsd ";
// 	ft_printf("str: %s - status %d\n", red_str, has_trailing_pipe(red_str));
// 	red_str = "|";
// 	ft_printf("str: %s - status %d\n", red_str, has_trailing_pipe(red_str));
// 	red_str = "|  ";
// 	ft_printf("str: %s - status %d\n", red_str, has_trailing_pipe(red_str));
// 	red_str = " |   ";
// 	ft_printf("str: %s - status %d\n", red_str, has_trailing_pipe(red_str));
// 	red_str = "    ";
// 	ft_printf("str: %s - status %d\n", red_str, has_trailing_pipe(red_str));
// 	red_str = "";
// 	ft_printf("str: %s - status %d\n", red_str, has_trailing_pipe(red_str));
// }

// void	test_trim(void)
// {
// 	char *red_str;

// 	red_str = "asdadsd";
// 	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str, false));
// 	red_str = "   asdadsd   ";
// 	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str, false));
// 	red_str = "\tasdadsd\n";
// 	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str, false));
// 	red_str = "\nasd dfdsf adasdadsd";
// 	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str, false));
// 	red_str = "   ";
// 	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str, false));
// 	red_str = "";
// 	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str, false));
// 	red_str = NULL;
// 	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str, false));
// 	red_str = " 0 ";
// 	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str, false));
// 	red_str = " sf   ";
// 	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str, false));
// 	red_str = "'|' asdsd";
// 	ft_printf("str: |%s| - trimmed |%s|\n", red_str, ft_trim(red_str, false));
// }

// void	test_next_d_red(void)
// {
// 	char *str;

// 	str = "asdasd << asdasd";
// 	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
// 	str = "asdasd <<asdasd";
// 	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
// 	str = "asdasd < asda<<sd";
// 	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
// 	str = "asdasd < as < << dasd";
// 	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
// 	str = "asdasd asdasd";
// 	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
// 	str = "<<";
// 	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
// 	str = "   <<";
// 	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
// 	str = "<< ";
// 	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
// 	str = "  << ";
// 	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
// 	str = "<< a";
// 	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
// 	str = "<< sdsd";
// 	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
// 	str = "";
// 	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
// 	str = NULL;
// 	ft_printf("str: |%s| - next eof pos |%d|\n", str, find_next_eof_pos(str, 0));
// }

// void	test_eof(void)
// {
// 	char *str;

// 	str = "asd_asd << asdasd asd";
// 	ft_printf("str: |%s| - starting in: |%s| = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "asdsadsdasd <<asdasd   ";
// 	ft_printf("str: -%s- - starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "asdfgwfgsasd < asda<<sd\t";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "asdfghasd < as < << dasd  ";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "<<";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "   <<";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "<< ";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "  << ";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "<< a";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "<< sdsd";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "asdhjasd << asdasd|";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "aadfsdasd << asd|asd";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "as@#dasd << asda<sd";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "asda67sd << asd>asd";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "asda|sd << asda >sd";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "asdghasd << asda < sd";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "asda89sd << asda | sd";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "asda89sd asda << \"| sd\"";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "asda89sd asda <<\'| sd\'";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "asda89sd << \"asda\' sd\"";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "asda89sd << \"\"";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "asda89sd << \'\'";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// 	str = "asda89sd << 'as|asd'";
// 	ft_printf("str: -%s- = starting in: -%s- = next eof pos: -%d-\n", str, find_next_eof_pos(str, 0), isolate_eof(str + find_next_eof_pos(str, 0)));
// }

// void	test_n_cmds(void)
// {
// 	char *string;

// 	string = "asd\"asdsadasd\"adasd | adadasd";
// 	ft_printf("str: %%%s%% - n cmds: %u\n", string, n_cmds(string));

// 	string = "asdasd | AS'DA'SD | |D ada A adas ";
// 	ft_printf("str: %%%s%% - n cmds: %u\n", string, n_cmds(string));

// 	string = "     ";
// 	ft_printf("str: %%%s%% - n cmds: %u\n", string, n_cmds(string));

// 	string = "'|' asdsd";
// 	ft_printf("str: %%%s%% - n cmds: %u\n", string, n_cmds(string));

// 	string = "asd\" | \"a|dasd a|dada| sd";
// 	ft_printf("str: %%%s%% - n cmds: %u\n", string, n_cmds(string));

// 	string = "asdad |'a |   '|sd ada|dasd";
// 	ft_printf("str: %%%s%% - n cmds: %u\n", string, n_cmds(string));

// 	string = "  ada| dasd";
// 	ft_printf("str: %%%s%% - n cmds: %u\n", string, n_cmds(string));

// 	string = "  a d|asd gh g| ad a ";
// 	ft_printf("str: %%%s%% - n cmds: %u\n", string, n_cmds(string));

// 	string = "aasd| |asd  | ";
// 	ft_printf("str: %%%s%% - n cmds: %u\n", string, n_cmds(string));

// 	string = "asdasd'' dfgdf '' asdf asd|";
// 	ft_printf("str: %%%s%% - n cmds: %u\n", string, n_cmds(string));

// 	string = "| asdsad  ";
// 	ft_printf("str: %%%s%% - n cmds: %u\n", string, n_cmds(string));
	
// 	string = "|";
// 	ft_printf("str: %%%s%% - n cmds: %u\n", string, n_cmds(string));
// }

// void	helper(char *to_split)
// {
// 	ft_printf("to split: %%%s%%, n cmds; %u\n", to_split, n_cmds(to_split));
// 	char **str = split_into_cmds(to_split);
// 	char **tmp = str;
// 	while (*str)
// 		ft_printf("\t%%%s%%\n", *str++);
// 	ft_printf("\n");
// 	ft_free(tmp);
// }

// void	test_split_cmd(void)
// {
// 	helper("a\"sdad\"asd | adadasd");
// 	helper("asdasd | ASD'Adsasdasd'SD | |D ada A adas ");
// 	helper("     ");
// 	helper("'|' asdsd");
// 	helper("asd\" | \"a|dasd a|dada| sd");
// 	helper("asdad |'a |   '|sd ada|dasd");
// 	helper("  ada| dasd");
// 	helper("  a d|asd gh g| ad a ");
// 	helper("aasd| |asd  | ");
// 	helper("asdasd'' dfgdf '' asdf asd|");
// 	helper("| asdsad  ");
// 	helper("|");
// 	helper("asdad ada  sd | adad sdf asd");
// 	helper("asd'asd | ad' adasd | adadasd");
// 	helper("as|dada|sd | ad|a|dasd");
// }

// void	test_char_skip(void)
// {
// 	char *str;

// 	str = "asd_asd << asdasd asd";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 8 + skip_redirect_chars(str, 8));

// 	str = "asd_asd <<asdasd asd";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 8 +  skip_redirect_chars(str, 8));

// 	str = "asd_asd < asdasd asd";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 8 + skip_redirect_chars(str, 8));

// 	str = "asd_asd <asdasd asd";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 8 + skip_redirect_chars(str, 8));

// 	str = "<< asdasd asd";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + skip_redirect_chars(str, 0));

// 	str = "asd <<asdasd asd";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 4 + skip_redirect_chars(str, 4));

// 	str = "asd <asdasd asd";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 4 + skip_redirect_chars(str, 4));

// 	str = "asd >asdasd asd";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 4 + skip_redirect_chars(str, 4));
	
// 	str = "asd <<asdasd<asd prov";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 4 + skip_redirect_chars(str, 4));
	
// 	str = "asd >asdasd>fra asd";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 4 + skip_redirect_chars(str, 4));
	
// 	str = "asd >asdasd<<fgh<def asd";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 4 + skip_redirect_chars(str, 4));

// 	str = "asd >asdasd<<fgh,d ef asd";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 4 + skip_redirect_chars(str, 4));

// 	str = "asd >asda'sd<<f'gh,def asd";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 4 + skip_redirect_chars(str, 4));

// 	str = "asd >asdasd<<fgh >def asd";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 4 + skip_redirect_chars(str, 4));


// 	str = "asd>asdasd<<fgh >def asd";
// 	ft_printf("\nstr: |%s| - starting in: |%s|\n", str, str + 3 + skip_redirect_chars(str, 3));

// 	str = "asd>>asdasd<<fgh >def asd";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 3 + skip_redirect_chars(str, 3));

// 	str = "asd> asdasd<<fgh >def asd";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 3 + skip_redirect_chars(str, 3));

// 	str = "asd > asdasd<<fgh >def asd";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 4 + skip_redirect_chars(str, 4));

// 	str = "asd << asdasd<<fgh >def asd";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 4 + skip_redirect_chars(str, 4));

// 	str = "asd >' asasd <<' dasd<<fgh >def asd";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 4 + skip_redirect_chars(str, 4));

// 	str = "<<sdf";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + skip_redirect_chars(str, 0));

// 	str = ">dasda ";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + skip_redirect_chars(str, 0));

// 	str = " > asdad";
// 	ft_printf("str: |%s| - starting in: |%s|\n", str, str + 1 + skip_redirect_chars(str, 1));
// }


void	test_join(void)
{
	char *str1;
    char *str2;
    char *join;

	str1 = "dire dio cane";
    str2 = "e' bello";
    join = ft_strjoin(ft_strdup(str1), ft_strdup(str2), "", true);
	ft_printf("str1: |%s| - str2: |%s| - join: |%s|\n", str1, str2, join);
    free(join);

    str1 = "ciao";
    str2 = "bello";
    join = ft_strjoin(ft_strdup(str1), ft_strdup(str2), " ", true);
	ft_printf("str1: |%s| - str2: |%s| - join: |%s|\n", str1, str2, join);
    free(join);

    str1 = "ciao";
    str2 = "bello";
    join = ft_strjoin(ft_strdup(str1), ft_strdup(str2), "|", true);
	ft_printf("str1: |%s| - str2: |%s| - join: |%s|\n", str1, str2, join);
    free(join);

    str1 = "ciao";
    str2 = "bello";
    join = ft_strjoin(ft_strdup(str1), ft_strdup(str2), NULL, true);
	ft_printf("str1: |%s| - str2: |%s| - join: |%s|\n", str1, str2, join);
    free(join);

    str1 = "";
    str2 = "bello";
    join = ft_strjoin(ft_strdup(str1), ft_strdup(str2), "", true);
	ft_printf("str1: |%s| - str2: |%s| - join: |%s|\n", str1, str2, join);
    free(join);

    str1 = "";
    str2 = "";
    join = ft_strjoin(ft_strdup(str1), ft_strdup(str2), "", true);
	ft_printf("str1: |%s| - str2: |%s| - join: |%s|\n", str1, str2, join);
    free(join);

    str1 = "ciao";
    str2 = "";
    join = ft_strjoin(ft_strdup(str1), ft_strdup(str2), "|", true);
	ft_printf("str1: |%s| - str2: |%s| - join: |%s|\n", str1, str2, join);
    free(join);

    str1 = "";
    str2 = "";
    join = ft_strjoin(ft_strdup(str1), ft_strdup(str2), NULL, true);
	ft_printf("str1: |%s| - str2: |%s| - join: |%s|\n", str1, str2, join);
    free(join);

    str1 = "ciao ";
    str2 = " bello";
    join = ft_strjoin(ft_strdup(str1), ft_strdup(str2), "", true);
	ft_printf("str1: |%s| - str2: |%s| - join: |%s|\n", str1, str2, join);
    free(join);
}