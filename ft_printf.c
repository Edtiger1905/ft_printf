#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

// Funzione principale
int ft_printf(const char *format, ...)
{
    va_list args;
    int char_count = 0; // Contatore dei caratteri stampati

    va_start(args, format);

    while (*format) {
        if (*format == '%' && *(format + 1)) {
            format++;
            char_count += take_format(format, args);
        } else {
            ft_putchar(*format);
            char_count++; // Incrementa il contatore
        }
        format++;
    }

    va_end(args);
    return char_count; // Restituisce il numero di caratteri stampati
}

// Gestione dei formati
int take_format(const char *format, va_list args)
{
    int char_count = 0;

    if (*format == 'd' || *format == 'i')
        char_count += print_int(va_arg(args, int));
    else if (*format == 's')
        char_count += print_string(va_arg(args, const char *));
    else if (*format == 'c') {
        ft_putchar(va_arg(args, int));
        char_count++;
    } else if (*format == 'x')
        char_count += print_hex(va_arg(args, unsigned int), 0);
    else if (*format == 'X')
        char_count += print_hex(va_arg(args, unsigned int), 1);
    else if (*format == 'p')
        char_count += print_pointer(va_arg(args, void *));
    else if (*format == 'u')
        char_count += print_unsigned(va_arg(args, unsigned int));
    else {
        ft_putchar('%');
        char_count ++; // Conta il '%' e il carattere successivo
    }
    return char_count;
}

void ft_putchar(char c)
{
    write(1, &c, 1);
}

// Funzione per stampare un intero
int print_int(int i)
{
    int char_count = 0;

    if (i < 0) {
        ft_putchar('-');
        char_count++;
        char_count += print_unsigned((unsigned int)(-i));
    } else {
        char_count += print_unsigned((unsigned int)i);
    }
    return char_count;
}

// Funzione per stampare una stringa
int print_string(const char *str)
{
    int char_count = 0;

    if (str == NULL) {
        str = "(null)";
    }
    while (*str) {
        ft_putchar(*str);
        char_count++;
        str++;
    }
    return char_count;
}

// Funzione per stampare un puntatore
int print_pointer(void *ptr)
{
    unsigned long address = (unsigned long)ptr;
    int char_count = 0;

    if(ptr != NULL)
    {
        ft_putchar('0');
        ft_putchar('x');
        char_count += 2; // Conta '0x'
    }
    char_count += print_hex(address, 0);
    return char_count;
}

// Funzione per stampare un numero senza segno
int print_unsigned(unsigned int val)
{
    int char_count = 0;

    if (val >= 10) {
        char_count += print_unsigned(val / 10);
    }
    ft_putchar('0' + (val % 10));
    char_count++;
    return char_count;
}

// Funzione per stampare un numero esadecimale
int print_hex(unsigned long value, int uppercase)
{
    int char_count = 0;
    char digit;

    if (value >= 16) {
        char_count += print_hex(value / 16, uppercase);
    }

    // Ottieni il digit corrente
    if ((value % 16) < 10) {
        digit = '0' + (value % 16);
    } else {
        if (uppercase)
            digit = 'A' + ((value % 16) - 10);
        else
            digit = 'a' + ((value % 16) - 10);
    }

    ft_putchar(digit);
    char_count++;
    return char_count;
}
