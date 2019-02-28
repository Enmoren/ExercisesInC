# trout: trout.h trout.c util.c
# 	gcc -g -o trout trout.c util.c
# main: trout.h main.c trout.c until.c
# 	gcc -g -o main main.c trout.c util.c

trout.o: trout.h util.h trout.c
	gcc -c trout.c

util.o: trout.h util.h util.c
	gcc -c util.c

main.o: main.c trout.h util.h
	gcc -c main.c

main: main.o trout.o util.o
	gcc -Wall main.o trout.o util.o -o main
