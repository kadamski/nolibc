#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char *addr = malloc(4096*100);
    pause();
    return 0;
}
