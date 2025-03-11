#include "libft.h"
#include <unistd.h>

static void ft_putchar(char c)
{
    write(1, &c, 1);
}

int ft_put_number(long long num, char *base)
{
    int count;
    int base_len;

    base_len = ft_strlen(base);
    count = 0;
    if (num >= base_len)
        count += ft_put_number(num / base_len, base);
    ft_putchar(base[num % base_len]);
    return (count + 1);
}