/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:02:55 by luicasad          #+#    #+#             */
/*   Updated: 2023/10/12 14:15:51 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/* ************************************************************************** */
/* Allocate(), allocates memory for a table of 'num' pointers to char. Also   */
/* allocates one more pointer settled to ((void *)0).                         */
/*                                                                            */
/* GETS                                                                       */
/*  rows : the amount of rows we want the table to hold                       */
/*                                                                            */
/* RETURNS                                                                    */
/*  table : a pointer to the first row of the created table having last row   */
/*          Setttled to NULL                                                  */
/*                                                                            */
/* ************************************************************************** */
static char	**allocate(size_t rows)
{
	char	**table;

	table = (char **)malloc((rows + 1) * sizeof (char *));
	if (table == NULL)
		return (NULL);
	table[rows] = ((void *)0);
	return (table);
}

/* ************************************************************************** */
/* de_allocate(), frees memory holding a table of pointers                    */
/*                                                                            */
/* GETS                                                                       */
/*  table : the pointer to the table to release memory from                   */
/*  rows : the amount of rows already allocated into the table.               */
/*                                                                            */
/* RETURNS                                                                    */
/*  NULL, once all memory was released.                                       */
/*                                                                            */
/* OPERATES                                                                   */
/*  Loops table's from last one allocated row (--rows) releasing the          */
/*  memory for each row. Use pre-decrement cause 4 rows allocated are indexed */
/*  from 3, 2, 1, 0. LUIS REMEMBER THAT!!!!!!                                 */
/*                                                                            */
/*  Finally release the pointer to the table itself                           */
/*                                                                            */
/*   NOTE: not necessary release table[rows] = ((void *)0) settled inside     */
/*         allocate. was not a pointer to a word allocated memory             */
/* ************************************************************************** */
static char	**de_allocate(char **table, size_t allocated_rows)
{
	while (allocated_rows > 0)
	{
		free(table[--allocated_rows]);
	}
	free(table);
	return (NULL);
}

/* ************************************************************************** */
/* word_count(), counts chunks of chars in 's' between a separation char 'c'. */
/*                                                                            */
/* GETS                                                                       */
/*  s : the string to find the chunks in.                                     */
/*  c : the char that separates de chunks.                                    */
/*                                                                            */
/* RETURNS                                                                    */
/*  counter: the number of chunks found.                                      */
/*                                                                            */
/* OPERATES                                                                   */
/*  This function works thanks to a state variable 'in_word'.                 */
/*                                                                            */
/*  If the current character is a 'c' character, a separator, (*s == c) then  */
/*   the function sets in_word to 0: we are out of a word.                    */
/*                                                                            */
/*  If the current character is not a 'c' character and in_word is 0, then    */
/*  the function increments the word count and sets in_word to 1: we are in a */
/*  word.                                                                     */
/*                                                                            */
/*  The function considers that it is outside a word and there are not chunks */
/*  `counter = 0`. if s = "" it not enters into de while then returns zero    */
/*                                                                            */
/* ************************************************************************** */

static void set_flag(short *in_quote, char c)
{
    if (!*in_quote && (c == 34 || c == 39))
        *in_quote = 1;
    else if(*in_quote && (c == 34 || c == 39))
        *in_quote = 0;
}

static size_t	word_count(char const *s, char c)
{
	size_t	counter;
	short	in_word;
    short   in_quote;

	in_quote = 0;
    counter = 0;
	in_word = 0;
	while (*s)
	{
        set_flag(&in_quote, *s);
        if (!in_quote && *s == c)
			in_word = 0;
		else if (!in_word)
		{
			counter++;
			in_word = 1;
		}
		s++;
	}
	return (counter);
}

/* split() parses s, detects text-chunkst between separators 'c', allocates   */
/* memory for the chunk, and add the pointer to results table if memory       */
/* allocation success, releasing all previous allocated memory otherwise.     */
/*                                                                            */
/* GETS                                                                       */
/*  *s : the strig to split                                                   */
/*  c : the delimiter character                                               */
/*  **result : the table to collect pointers to chunks/words memory           */
/* RETURNS                                                                    */
/*   An array (NULL-TERMINATED) of new strings resulting form splitting s.    */
/*   NULL if memory allocation fails.                                         */
/* OPERATION                                                                  */
/*  Initializes a word counter to Zero. it is only incremented after a new    */
/*  pointer has been added to the result table.                               */
/*                                                                            */
/*  loops s:                                                                  */
/*     First while advances if not separators. Finds word end.                */
/*                                                                            */
/*     A word appears when (j != i). Allocates (j-i) bytes of memory with     */
/*     ft_substr, that returns the word in buf when success.                  */
/*                                                                            */
/*     if no success de_allocates from result previously allocated memory for */
/*     'word_counter' words                                                   */
/*                                                                            */
/*     second while advances if separators. Finds word init.                  */
/*                                                                            */
static char	**split(char const *s, char c, char **result)
{
	size_t	i;
	size_t	j;
	char	*buf;
	size_t	word_counter;
    short   in_quote;

	word_counter = 0;
	i = 0;
	while (s[i] != '\0')
	{
		j = i;
        set_flag(&in_quote, s[j]);
        if (!in_quote)
		    while (s[j] != '\0' && s[j] != c)
			    j++;
        else
        {
            while (s[j] != '\0' && in_quote)
                set_flag(&in_quote, s[j++]);
        }
        if (j != i)
		{
			buf = ft_substr(s, i, (j - i));
			if (buf == NULL)
				return (de_allocate(result, word_counter));
			result[word_counter++] = buf;
		}
		while (s[j] != '\0' && s[j] == c)
			j++;
		i = j;
	}
	return (result);
}

/* ft_split() allocates (with malloc(3)) and returns an array of strings      */
/* obtained by slitting 's' using the character c as delimiter.               */
/* The array must end wiht a NULL pointer                                .    */
/*                                                                            */
/* GETS                                                                       */
/*  s: the strig to split                                                     */
/*  c: the delimiter character                                                */
/*                                                                            */
/* RETURNS                                                                    */
/*   An array (NULL-TERMINATED) of new strings resulting form splitting s.    */
/*   NULL if memory allocation fails.                                         */
/* OPERATION                                                                  */
/*  In TWO arguments are NULL, returns NULL.                                  */
/*                                                                            */
/*  Count words/chunks inside c.                                              */
/*                                                                            */
/*  Allocate memory for a table of pointers to chunks/words                   */
/*   when words = 0, allocate returns                                         */
/*                _                                                           */
/*     result -> |_-> ((void *)                                               */
/*                                                                            */
/*   Exiting function at first (result == NULL)                               */
/*                                                                            */
/*  When no memory available returns NULL                                     */
/*                                                                            */
/*  split s into chunks                                                       */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/* PROBLEMS I GOT                                                             */
/* Getting crazy to reduce Francinette error                                  */
/*                                                                            */
/*if (!s || !c)                                                               */
/*  return (NULL);                                                            */
/*if (!s)                                                                     */
/*  return (NULL);                                                            */
/*                                                                            */
/* Releasing the memory of pre-allocated words memory was a problem in this   */
/* Function. I started releasing all rows allocated to the table. that was    */
/* wrong. @gemartin @mporras- opened my eyes.                                 */
/* I was releasing from the table rows wiht no pointer at all.                */
/* I MUST understant that empty rows of the table are released when releasing */
/* pointer to the table itself.                                               */
/*                                                                            */
/* With this in main is not necessary propagate to the called functions the   */
/* table size. that helps me to nest wordcount call inside allocate function. */
/*                                                                            */
char	**ft_split_pipex(char const *s, char c)
{
	char	**result;

	if (!s && !c)
		return (NULL);
	result = allocate(word_count(s, c));
	if (result == NULL)
		return (NULL);
	result = split(s, c, result);
	if (result == NULL)
		return (NULL);
	return (result);
}
