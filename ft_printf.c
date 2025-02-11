#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

// Function prototypes
void ft_putchar(char c, int *len);
void ft_putstr(char *str, int *len);
void ft_putnbr(int n, int *len);
void ft_putUnbr(unsigned int n, int *len);
void ft_puthex
int ft_printf(const char *format, ...);

// Main function
int main(void)
{
    char s = 'y';
    int a = 13;
    char *str = "hi imane";
    unsigned int n = 1234;

    ft_printf("Hi %c\n", s);
    ft_printf("hi %d\n", a);
    ft_printf("%s\n", str);
    ft_printf("%u\n",n);
    printf("hello %c\n", s);

    return 0;
}

// Function definitions
void ft_putchar(char c, int *len)
{
    write(1, &c, 1);
    (*len)++;
}

void ft_putstr(char *str, int *len)
{
    if (!str)
        str = "(null)";
    while (*str)
        ft_putchar(*str++, len);
}

void ft_putnbr(int n, int *len)
{
    if (n == -2147483648)
    {
        ft_putstr("-2147483648", len);
        return;
    }

    if (n < 0)
    {
        ft_putchar('-', len);
        n = -n;
    }

    if (n >= 10)
        ft_putnbr(n / 10, len);

    ft_putchar((n % 10) + '0', len);
}

void ft_putUnbr(unsigned int n, int *len)
{
	if (n >= 10)
	{
		ft_putUnbr((n / 10),len);
	}
	ft_putchar((n % 10)+48, len);
}

int ft_printf(const char *format, ...)
{
    va_list args;
    int i = 0;
    int len = 0;

    va_start(args, format);
    while (format[i])
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == 'c')
                ft_putchar(va_arg(args, int), &len);
            else if (format[i] == 's')
                ft_putstr(va_arg(args, char*), &len);
            else if (format[i] == 'd' || format[i] == 'i')
                ft_putnbr(va_arg(args, int), &len);
	    else if (format[i] == 'u')
		    ft_putUnbr(va_arg(args, unsigned int),&len);
            else if (format[i] == '%')
                ft_putchar('%', &len);
        }
        else
        {
            ft_putchar(format[i], &len);
        }
        i++;
    }
    va_end(args);
    return len;
}

