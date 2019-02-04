/* Write a string to the file file_write_read.c.tmp, and read it back. */

#include "common.h"

/* Returns the size of the given open `FILE*`.
 *
 * If an error occurs, returns `-1L`.
 *
 * Does not work for pipes.
 */
long fget_file_size(FILE *fp) {
    long oldpos;
    long return_value;
    oldpos = ftell(fp);
    if (oldpos == -1L) {
        return -1L;
    }
    if (fseek(fp, 0, SEEK_END) != 0) {
        return -1L;
    }
    return_value = ftell(fp);
    if (return_value == -1L) {
        return -1L;
    }
    /* Restore the old position. */
    if (fseek(fp, oldpos , SEEK_SET) != 0) {
        return -1L;
    }
    return return_value;
}

/* Same as `file_size`, but takes the path instead of a `FILE*`. */
long file_size(char *path) {
    FILE *fp;
    long return_value;
    fp = fopen(path, "r");
    if (fp == NULL) {
        return -1L;
    }
    return_value = fget_file_size(fp);
    if (fclose(fp) == EOF) {
        return -1L;
    }
    return return_value;
}

/* Read the entire file to a char[] dynamically allocated inside this function.
 *
 * Returns a pointer to the start of that array.
 *
 * In case of any error, returns NULL.
 *
 * http://stackoverflow.com/questions/174531/easiest-way-to-get-files-contents-in-c
 */
char *file_read(char *path) {
    FILE *fp;
    char *buffer;
    long fsize;

    fp = fopen(path , "rb");
    if (fp==NULL) {
        return NULL;
    }
    fsize = fget_file_size(fp);
    if (fsize < 0){
        fprintf(stderr, "could not determine lenght of:\n%s\n", path);
        return NULL;
    }
    buffer = (char*)malloc(fsize);
    if (buffer == NULL) {
        return NULL;
    }
    if (fread(buffer, 1, fsize, fp) != fsize) {
        return NULL;
    }
    if (fclose(fp) == EOF){
        return NULL;
    }
    return buffer;
}

/* Write a null terminated string to file
 *
 * Return -1 on failure, 0 on success.
 */
int file_write(char *path, char *write_string) {
    long len;
    char *buffer;
    FILE *fp;

    fp = fopen(path, "wb");
    if (fp == NULL) {
        return -1;
    }
    len = strlen(write_string);
    /* copy the file into the buffer: */
    if (fwrite(write_string, 1, len, fp) != len) {
        return -1;
    }
    if (fclose(fp) == EOF) {
        return -1;
    }
    return 0;
}

int main(void) {
    char *path = COMMON_TMPFILE;
    char *input = "asdf\nqwer\n";

    /* Write entire string to file at once. */
    if (file_write(path, input) == -1) {
        COMMON_IO_ERROR("file_write", path);
    }

    /* Read entire file at once to a string. */
    {
        char *output = file_read(path);
        if (output == NULL) {
            COMMON_IO_ERROR("file_read", path);
        }
        assert(strcmp(input, output) == 0);
        free(output);
    }

    /* Get file size. */
    {
        long size = file_size(path);
        if (size == -1) {
            COMMON_IO_ERROR("file_size", path);
        }
        assert(size == strlen(input));
    }

    return EXIT_SUCCESS;
}
