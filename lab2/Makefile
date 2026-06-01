

#Grace Humer, CMPT201 Summer 2026

#Run Lab 2, compile all prereq files, actually run lab2 ONLY
run: lab2
	echo "Running: $^"
	./lab2

test.exe: test.c
	echo "Compiling $^"
	clang test.c -fsanitize=address -o test

#Compile program lab2 from lab2.c
lab2: lab2.c
	echo "Compiling $@ from $^"
	clang lab2.c -fsanitize=address -o lab2
