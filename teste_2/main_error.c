#include <stdio.h>
#include <fcntl.h>  
#include <unistd.h> 


char *get_next_line(int fd);

int main(void)
{
    char *line;
   
    printf("Test 1: Invalid file descriptor (42)\n");
    line = get_next_line(42); 
    if (line == NULL)
        printf("Passed: Returned NULL for invalid file descriptor.\n");
    else
        printf("Failed: Did not return NULL for invalid file descriptor.\n");
    printf("\nTest 2: Read error\n");
    int fd = open("test_file.txt", O_RDONLY); 
    if (fd == -1)
    {
        perror("Failed to open test_file.txt");
        return (1);
    }
    close(fd); 
    line = get_next_line(fd);
    if (line == NULL)
        printf("Passed: Returned NULL when `read` failed.\n");
    else
        printf("Failed: Did not return NULL when `read` failed.\n");
    printf("\nTest 3: Malloc failure\n");
    printf("Note: This test requires manual or simulated malloc failure to validate.\n");
    return (0);
}
