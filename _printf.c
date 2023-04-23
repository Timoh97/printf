/*
 * Authors: pius and timothy
 */

#include "main.h"

void cleanup(va_list args, buffer_t *output);
int run_printf(const char *format, va_list args, buffer_t *output);
int _printf(const char *format, ...);

/**
 * cleanup - Peforms cleanup operations for _printf.
 * @args: A va_list of arguments provided to _printf.
 * @output: A buffer_t struct.
 */
void cleanup(va_list args, buffer_t *output)
{
	va_end(args);
	write(1, output->start, output->len);
	free_buffer(output);
}

/**
 * run_printf - Reads through the format string for _printf.
 * @format: Character string to print - may contain directives.
 * @output: A buffer_t struct containing a buffer.
 * @args: A va_list of arguments
 * Return: The number of characters stored to output.
 */
int run_printf(const char *format, va_list args, buffer_t *output)
{
	int index, width, precision, result = 0;
	char temporary;
	unsigned char flags, length;
	unsigned int (*f)(va_list, buffer_t *, unsigned char, int, int,
					  unsigned char);

	for (index = 0; *(format + index); index++)
	{
		length = 0;
		if (*(format + index) == '%')
		{
			temporary = 0;
			flags = handle_flagging(format + index + 1, &temporary);
			width = handle_wid(args, format + index + temporary + 1, &temporary);
			precision = handle_prec(args, format + index + temporary + 1,
									&temporary);
			length = handle_len(format + index + temporary + 1, &temporary);

			f = handle_specs(format + index + temporary + 1);
			if (f != NULL)
			{
				index += temporary + 1;
				result += f(args, output, flags, width, precision, length);
				continue;
			}
			else if (*(format + index + temporary + 1) == '\0')
			{
				result = -1;
				break;
			}
		}
		result += _memcpy(output, (format + index), 1);
		index += (length != 0) ? 1 : 0;
	}
	cleanup(args, output);
	return (result);
}

/**
 * _printf - Outputs a formatted string.
 * @format: Character string to print - may contain directives.
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
	buffer_t *output;
	va_list args;
	int result;

	if (!format)
		return (-1);
	output = initialize_buffer();
	if (!output)
		return (-1);

	va_start(args, format);

	result = run_printf(format, args, output);

	return (result);
}
