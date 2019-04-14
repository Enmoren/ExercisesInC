/* The original program will only print result from first RSS feed.
And it was modified by Enmo using fork() system call to execute different processes.

Author: Enmo Ren
Copyright (c) Enmo Corporation.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <wait.h>


void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <search phrase>\n", argv[0]);
        return 1;
    }
    const char *PYTHON = "/usr/bin/python2";
    const char *SCRIPT = "rssgossip.py";
    char *feeds[] = {
        "http://www.nytimes.com/services/xml/rss/nyt/Africa.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/Americas.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/MiddleEast.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/Europe.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/AsiaPacific.xml"
    };
    int num_feeds = 5;
    char *search_phrase = argv[1];
    char var[255];
    pid_t parent_pid, child_pid;
    int status;

    // Create child process for each rss feed by calling fork()
    for (int i=0; i<num_feeds; i++) {
        sprintf(var, "RSS_FEED=%s", feeds[i]);
        char *vars[] = {var, NULL};

        pid_t child_pid = fork(); //Clone process
        if (child_pid == -1){     //Error checking for cloning process
          fprintf(stderr,"Can't fork process: %s\n", strerror(errno));
          return 1;
        }
        if (child_pid == 0){     //running child process when pid is 0
          int res = execle(PYTHON, PYTHON, SCRIPT, search_phrase, NULL, vars);
          if (res == -1) {
              error("Can't run script.");
              return 1;
          }
        }
    }

/* First way of parent process waiting for child processes*/

    while ((parent_pid = wait(&status)) > 0);
    return 0;

/* Second way of parent process that waits for child processes and print errors */

    // printf("Hello from the parent.\n");
    //
    // for (i=0; i<num_feeds; i++) {
    //     //wait for child processes to complete
    //     pid = wait(&status);
    //
    //     if (pid == -1) {
    //         fprintf(stderr, "wait failed: %s\n", strerror(errno));
    //         perror(argv[0]);
    //         exit(1);
    //     }
    //
    //     // check the exit status of the child
    //     status = WEXITSTATUS(status);
    // }
    // exit(0);
}
