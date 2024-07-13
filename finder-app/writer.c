/*
    Author: Wessam Shoman
    GitHub: https://github.com/We55am
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int close_file(int fd, char *argv[])
{
    if(close(fd) == -1)
    {
        /* error */
        perror("Error Closing");
        int hold_errno = errno;
        syslog(LOG_ERR, "Error Closing File %s: %s", argv[1], strerror(hold_errno));
        return -1;
    }
    else
    {
        return 0;
    }
}

int main (int argc, char *argv[])
{
    // Logging
    openlog(argv[0], 0, LOG_USER);
    
    // Check arguments
    if(argc != 3)
    {
        errno = EINVAL;
        perror("Error");
        fprintf(stderr, "Usage: %s <File Path> <string>\n", argv[0]);
        syslog(LOG_ERR, "Error: %s .. Usage: %s <File Path> <string>\n", strerror(EINVAL), argv[0]);
        return EXIT_FAILURE;
    }
    
    
    syslog(LOG_DEBUG, "Writing %s to %s", argv[2], argv[1]);

    int fd;
    // int open (const char *name, int flags);
    fd = open(argv[1], (O_RDWR | O_CREAT | O_TRUNC | S_IRWXU), (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));

    if(fd == -1)
    {
        /* error */
        int hold_errno = errno;
        perror("Error open File");
        syslog(LOG_ERR, "Error open file %s: %s", argv[1], strerror(hold_errno));
        return EXIT_FAILURE;
    }
    else
    {
        // Writing to the file.
        ssize_t nr = 0;
        while(nr < strlen(argv[2]))
        {
            nr = write(fd, argv[2], strlen(argv[2]));
            syslog(LOG_DEBUG, "Wrote %ld bytes on File: %s", nr, argv[1]);
            if(nr == -1)
            {
                /* error */
                int hold_errno = errno;
                perror("Error Writing to file");
                syslog(LOG_ERR, "Error Writing to File %s: %s", argv[1], strerror(hold_errno));
                close_file(fd, argv);
                return EXIT_FAILURE;
            }
            syslog(LOG_DEBUG, "Done Writing to File!");
        }
        
        if(close_file(fd, argv) == -1)
        {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}