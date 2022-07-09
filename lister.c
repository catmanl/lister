#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define PROGRAM_NAME "lister"
#define VERSION "1.0"
#define EXTENSION ".lstr"
#define BUFFER_SIZE 1024

enum {
    ERR_NO_ARGS = 0,
    ERR_FILE_NOT_FOUND,
    ERR_WRONG_EXT
};

void error(int errcode);
void usage(FILE *out);
void version(FILE *out);
char *get_ext(char *filename);
bool starts_with(char *s1, char *s2);

int main(int argc, char **argv)
{
    if (argc < 2) {
        error(ERR_NO_ARGS);
        return 1;
    }

    // Check arguments
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        usage(stderr);
        return 0;
    }
    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        version(stderr);
        return 0;
    }

    // Program functionality
    char *filename = argv[1];

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        error(ERR_FILE_NOT_FOUND);
        return 1;
    }
    char *ext = get_ext(filename);
    if (!(strcmp(ext, EXTENSION) == 0)) {
        error(ERR_WRONG_EXT);
        fclose(f);
        return 1;
    }

    char buffer[BUFFER_SIZE] = { 0 };
    char *line = fgets(buffer, BUFFER_SIZE, f);
    int elements = 0;
    int checked = 0;
    int nsep = 0;
    printf("%s", line);
    for (int i = 0; i < strlen(line) - 1; i++) {
        printf("=");
        nsep++;
    }
    printf("\n");
    while ((line = fgets(buffer, BUFFER_SIZE, f)) != NULL) {
        line[strcspn(line, "\n")] = 0;
        if (starts_with(line, "x")) {
            printf("[x] - %s\n", line + 2);
            checked++;
        } else if (starts_with(line, "?")) {
            printf("[TBD] - %s\n", line + 2);
        } else {
            if (strlen(line) != 0) {
                printf("[] - %s\n", line);
            }
        }
        if (strlen(line) != 0) {
            elements++;
        }
    }
    for (int i = 0; i < nsep; i++) {
        printf("=");
    }
    printf("\n\nTotal elements: %d\nChecked: %d\n", elements, checked);

    fclose(f);
    return 0;
}

void error(int errcode)
{
    switch (errcode) {
        case ERR_NO_ARGS: usage(stderr); break;
        case ERR_FILE_NOT_FOUND: printf("%s: file not found\n", PROGRAM_NAME); break;
        case ERR_WRONG_EXT: printf("%s: wrong extension. Need %s\n", PROGRAM_NAME, EXTENSION); break;
    }
}

void usage(FILE *out)
{
    fprintf(out, "%s - checking list for an event\n", PROGRAM_NAME);
    fprintf(out, "  -h -- display this message\n");
    fprintf(out, "  -v -- display the version\n");
}

void version(FILE *out)
{
    fprintf(out, "%s %s\n", PROGRAM_NAME, VERSION);
    fprintf(out, "Written by Laurentino Luna\n");
}

char *get_ext(char *filename) // dot included
{
    return strchr(filename, '.');
}

bool starts_with(char *s1, char *s2)
{
    return strncmp(s1, s2, strlen(s2)) == 0;
}
