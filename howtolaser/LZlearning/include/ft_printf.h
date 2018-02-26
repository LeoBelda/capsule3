/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquenel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:01:39 by jquenel           #+#    #+#             */
/*   Updated: 2017/12/07 04:31:55 by jquenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include <libft.h>
# include <inttypes.h>

# define CLIST_SIZE		15
# define FLIST_SIZE		6

# define MSET			"0123456789#-+ .hljzL"
# define FSET			"sSpdDioOuUxXcCfFb%"

enum			e_bflags
{
	F_ERR = 0x80000000,
	F_ALT = 0x00400000,
	F_ZPAD = 0x00200000,
	F_RPAD = 0x00100000,
	F_PLUS = 0x00080000,
	F_SPACE = 0x00040000,
	F_FW = 0x00020000,
	F_PREC = 0x00010000,
	F_LD = 0x00000040,
	F_HH = 0x00000020,
	F_H = 0x00000010,
	F_LL = 0x00000008,
	F_L = 0x00000004,
	F_J = 0x00000002,
	F_Z = 0x00000001
};

# define RAINBOW		"{rainbow}"
# define DISCO			"{disco}"

# define RED			"\e[30m "
# define GREEN			"\e[31m "
# define YELL			"\e[32m "
# define BLUE			"\e[33m "
# define MAJ			"\e[34m "
# define LBLUE			"\e[35m "

# define BRED			"\e[41m "
# define BGREEN			"\e[42m "
# define BYELL			"\e[43m "
# define BBLUE			"\e[44m "
# define BMAJ			"\e[45m "
# define BLBLUE			"\e[46m "
# define BWHITE			"\e[47m "

typedef struct	s_clist
{
	char		*set;
	int			(*f)(char *, char **, va_list *);
}				t_clist;

int				ft_printf(char *expr, ...);
char			**pf_parser(char *expr, char **tab);
int				pf_converter(va_list *ap, char **c_str, char **tab);
int				pf_printer(char *p_str, int count);

/*
**		List of argument converter functions
*/

char			*pf_init_charset(char id);
int				pf_init_clist(t_clist **clist);
int				pf_init_flist(t_clist **clist);
int				pf_malloc_error(int rip, ...);
int				pf_report_error(int error);

int				pf_convert_int(char *expr, char **c_str, va_list *arg);
int				pf_convert_uint(char *expr, char **c_str, va_list *ap);
int				pf_convert_oct(char *expr, char **c_str, va_list *ap);
int				pf_convert_hex(char *expr, char **c_str, va_list *ap);
int				pf_convert_char(char *expr, char **c_str, va_list *ap);
int				pf_convert_wchar(char *expr, char **c_str, va_list *ap);
int				pf_convert_plain(char *expr, char **c_str, va_list *ap);
int				pf_convert_percent(char *expr, char **c_str, va_list *ap);
int				pf_convert_adr(char *expr, char **c_str, va_list *ap);
int				pf_convert_float(char *expr, char **c_str, va_list *ap);
int				pf_convert_bin(char *expr, char **c_str, va_list *ap);
int				pf_get_binary(int *flags, char **c_str, uintmax_t data);

/*
**		List of flag modifiers functions
*/

int				pf_get_flags(char *expr, int **flags);

int				pf_flag_alt_oct(char **str, int count);
int				pf_flag_alt_hex(char **str, int count, char id);
int				pf_flag_signed(char **str, int size, int flags);
int				pf_flag_minfw(char **str, int *flags, int size, int len);
int				pf_flag_num_minfw(char **str, int *flags, int size, int len);
int				pf_flag_hex_minfw(char **str, int *flags, int size, int len);
int				pf_flag_sprec(char **str, int p);
int				pf_flag_nprec(char **str, int size, int add);

int				pf_print_the_rainbow(char *expr, int count);
int				pf_disco_time(char *expr, int count);

#endif
