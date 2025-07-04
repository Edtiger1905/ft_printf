#include "ft_printf.h"

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
