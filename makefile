.c.o :
	gcc -c -w $< -o $@
touch.exe: touch.o
	gcc touch.o -lX11 -lXi -o $@
