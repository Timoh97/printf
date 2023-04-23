/*
 * Authors: pius,
 *					timothy
 */

#include <unistd.h>
/**
 * _putchar - program to print characters
 * @c: character to be printed
 * Return: (charater written to stdout)
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

