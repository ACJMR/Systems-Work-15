default: kidsRgr8.o
	gcc -o test kidsRgr8.o
kidsRgr8.o: kidsRgr8.c
	gcc -c kidsRgr8.c
run:
	./test
clean:
	rm -f test *~ *o 