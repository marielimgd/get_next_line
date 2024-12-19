#include <stdio.h>
#include <fcntl.h>  // For open()
#include <unistd.h> // For close()
#include <stdlib.h> // For free()

// Declare the get_next_line function
char *get_next_line(int fd);

// Function to print and verify the result
void print_result(char *line)
{
    if (line == NULL)
        printf("Returned NULL (error or EOF).\n");
    else
    {
        printf("Line: \"%s\"\n", line);
        free(line); // Free the allocated memory
    }
}

// Function to test a file
void test_file(const char *file_name)
{
    int fd = open(file_name, O_RDONLY);
    if (fd == -1)
    {
        perror("Failed to open file");
        return;
    }
    printf("Testing file: %s\n", file_name);
    char *line;
    while ((line = get_next_line(fd)) != NULL)
        print_result(line);
    close(fd);
}

int main(void)
{
    char *line;

    // Test 1: Large BUFFER_SIZE (>1024)
    #define BUFFER_SIZE 2048
    printf("Test 1: Large BUFFER_SIZE (%d)\n", BUFFER_SIZE);
    test_file("large_file.txt");

    // Test 2: Small BUFFER_SIZE (<8, including 1)
    #undef BUFFER_SIZE
    #define BUFFER_SIZE 1
    printf("\nTest 2: Small BUFFER_SIZE (%d)\n", BUFFER_SIZE);
    test_file("small_buffer_file.txt");

    #undef BUFFER_SIZE
    #define BUFFER_SIZE 7
    printf("\nTest 3: Small BUFFER_SIZE (%d)\n", BUFFER_SIZE);
    test_file("small_buffer_file.txt");

    // Test 3: BUFFER_SIZE exactly the length of a line
    #undef BUFFER_SIZE
    #define BUFFER_SIZE 10 // Assuming lines are exactly 10 characters long
    printf("\nTest 4: BUFFER_SIZE exactly the length of the line (%d)\n", BUFFER_SIZE);
    test_file("exact_line_length_file.txt");

    // Test 4: 1-byte variant between line and BUFFER_SIZE
    #undef BUFFER_SIZE
    #define BUFFER_SIZE 9 // 1 byte less than line length
    printf("\nTest 5: BUFFER_SIZE 1-byte variant (%d)\n", BUFFER_SIZE);
    test_file("exact_line_length_file.txt");

    #undef BUFFER_SIZE
    #define BUFFER_SIZE 11 // 1 byte more than line length
    printf("\nTest 6: BUFFER_SIZE 1-byte variant (%d)\n", BUFFER_SIZE);
    test_file("exact_line_length_file.txt");

    // Test 5: Read on stdin
    printf("\nTest 7: Read from stdin (Enter lines manually, end with Ctrl+D)\n");
    printf("Enter text:\n");
    while ((line = get_next_line(STDIN_FILENO)) != NULL)
        print_result(line);

    // Test 6: Read multiple/single long lines
    #undef BUFFER_SIZE
    #define BUFFER_SIZE 1024
    printf("\nTest 8: Read long lines (BUFFER_SIZE = %d)\n", BUFFER_SIZE);
    test_file("long_lines_file.txt");

    // Test 7: Read multiple/single short lines
    printf("\nTest 9: Read short lines (BUFFER_SIZE = %d)\n", BUFFER_SIZE);
    test_file("short_lines_file.txt");

    // Test 8: Empty lines
    printf("\nTest 10: Read empty lines (BUFFER_SIZE = %d)\n", BUFFER_SIZE);
    test_file("empty_lines_file.txt");

    return 0;
}
