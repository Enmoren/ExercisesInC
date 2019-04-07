/*
 * Author: Enmo Ren
 * Copyright (c) Enmo Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software.
 *
 * Reflection: Writing the pseudo code before coding is really helpful.
 * It helps me to break down the program into few pieces. However, I spent
 * more time after finishing my first version of code as I found I somehow
 * misunderstood the problem.

 * Compared to my version, the posted implementation of code considers more
 * cases, which make troubleshooting easier.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

int main (int argc, char *argv[]){
	FILE *save;
	char ch;
	int append = 0; 			 //flag for text should append to the opened file
	char line[1000];

	if (argc < 1){
		fprintf(stderr,"Need up to 1 output file path!");
		exit(EXIT_FAILURE);
	}

	while ((ch = getopt(argc, argv, "ai"))!=EOF)
		switch (ch){
			case 'a':			// if option is detected, update flag value
				append = 1;
				break;
			case 'i': 		//implement i option here
				break;
			default: 			// if wrong options is given
				fprintf(stderr, "Unkown option: '%s'\n", optarg);
				return 1;
		}

	argc -= optind;		// update the options
	argv += optind;

	while(fgets(line, sizeof(line), stdin)!= NULL){
		for(int i = 0; i < argc; i++){
			if (append){
				save = fopen(argv[i],"a");
			}
			else{ 				// for new file, update append flag for possible following input
				save = fopen(argv[i],"w");
				append = 1;
			}
			fprintf(save, "%s", line);  // write to output file
			fprintf(stdout, "%s", line);// write to standard output

			fclose(save);
			}
		}
	return 0;
}
