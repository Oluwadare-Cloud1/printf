#include "main.h"

<<<<<<< HEAD
/**
 * _strlen - Returns the length of a string
 * @s: The string
 *
 * Return: The length of the string
 */
int _strlen(const char *s)
{
	int len = 0;

	while (s[len])
		len++;

	return (len);
}

/**
 * _printf - prints anything
 * @format: the format string
 *
 * Return: the number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	printer printer;
	int i = 0;
	int characters_printed = 0;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		for (; format[i] != '%' && format[i]; i++)
		{
			_putchar(format[i]);
			characters_printed++;
		}
		if (!format[i])
			return (characters_printed);
		if (format[i] == '%' && _strlen(format) == 1)
			return (-1);
		printer = _get_printer(&format[i + 1]);
		if (printer.specifier != NULL)
		{
			characters_printed += printer.run(args);
			i += 2; /* move past the specifier */
			continue;
		}

		if (!format[i + 1])
			return (characters_printed);

		_putchar(format[i]);
		characters_printed++;

		if (format[i + 1] == '%')
			i += 2; /* move past the % */
		else
			i++;
	}
	va_end(args);
	return (characters_printed);
}
=======
void cleanup(va_list args, buffer_t *output);
int run_printf(const char *format, va_list args, buffer_t *output);
int _printf(const char *format, ...);

/**
 *cleanup - Peforms cleanup operations for _printf.
 *@args: A va_list of arguments provided to _printf.
 *@output: A buffer_t struct.
 */
void cleanup(va_list args, buffer_t *output)
{
va_end(args);
write(1, output->start, output->len);
free_buffer(output);
}

/**
 *run_printf - Reads through the format string for _printf.
 *@format: Character string to print - may contain directives.
 *@output: A buffer_t struct containing a buffer.
 *@args: A va_list of arguments.
 *Return: The number of characters stored to output.
 */
int run_printf(const char *format, va_list args, buffer_t *output)
{
int i, wid, prec, ret = 0;
char tmp;
unsigned char flags, len;
unsigned int (*f)(va_list, buffer_t *,
unsigned char, int, int, unsigned char);

for (i = 0; *(format + i); i++)
{
len = 0;
if (*(format + i) == '%')
{
tmp = 0;
flags = handle_flags(format + i + 1, &tmp);
wid = handle_width(args, format + i + tmp + 1, &tmp);
prec = handle_precision(args, format + i + tmp + 1,
&tmp);
len = handle_length(format + i + tmp + 1, &tmp);

f = handle_specifiers(format + i + tmp + 1);
if (f != NULL)
{
i += tmp + 1;
ret += f(args, output, flags, wid, prec, len);
continue;
}
else if (*(format + i + tmp + 1) == '\0')
{
ret = -1;
break;
}
}
ret += _memcpy(output, (format + i), 1);
i += (len != 0) ? 1 : 0;
}
cleanup(args, output);
return (ret);
}

/**
 *_printf - Outputs a formatted string.
 *@format: Character string to print - may contain directives.
 *Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
buffer_t *output;
va_list args;
int ret;

if (format == NULL)
return (-1);
output = init_buffer();
if (output == NULL)
return (-1);

va_start(args, format);

ret = run_printf(format, args, output);

return (ret);
}

>>>>>>> Dare
