#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>


void ft_putchar(char c, int *len);
void ft_putstr(char *str, int *len);
void ft_putnbr(int n, int *len);
void ft_putUnbr(unsigned int n, int *len);
void ft_puthex(unsigned int n, int *len, int uppercase);
int ft_printf(const char *format, ...);

int main(void)
{
    char s = 'y';
    int a = 42;
    char *str = "DIVA";
    unsigned int n = 1337;
    unsigned int i = 255;

    ft_printf("print char :  %c\n", s);
    ft_printf("print digit : %d\n", a);
    ft_printf("print string :%s\n", str);
    ft_printf("print unsigned digit :%u\n",n);
    ft_printf("print lowercase hexa :%x\n",i);
    ft_printf("print uppercase hexa :%X\n",i);
    ft_printf("spicifier: %%\n");

 
    ft_printf("%s\n", ""); // Empty string
    ft_printf("%s\n", NULL); // NULL string
    ft_printf("%d\n", 0); // Zero
    ft_printf("%d\n", -123); // Negative number
    ft_printf("%u\n", UINT_MAX); // Maximum unsigned integer
    ft_printf("%x\n", UINT_MAX); // Maximum hexadecimal (lowercase)
    ft_printf("%X\n", UINT_MAX); // Maximum hexadecimal (uppercase
	return 0;
}

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

void ft_puthex(unsigned int n, int *len, int uppercase)
{
	char *hex_digits;
	
	if (uppercase)
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	
	if (n >= 16)
		
		ft_puthex(n / 16, len, uppercase); 
	
	ft_putchar(hex_digits[n % 16],len);
	
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
	    else if (format[i] == 'x')
		    ft_puthex(va_arg(args,unsigned int),&len,0);
	    else if (format[i] == 'X')
		    ft_puthex(va_arg(args,unsigned int),&len,1);
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

