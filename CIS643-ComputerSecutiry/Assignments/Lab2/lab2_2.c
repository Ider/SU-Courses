#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
    char buf[1000]="";
    int fp, size;
    unsigned int *address;
    
    address = (unsigned int *) buf;
    *address = 0x22080;
    
    scanf("%s", buf+4);
    size = strlen(buf+4) + 4;
    printf("The string length is %d\n", size);
    
    fp = open("mystring", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fp != -1) {
        write(fp, buf, size);
        close(fp);
    } else {
        printf("Open failed!\n");
    }
}