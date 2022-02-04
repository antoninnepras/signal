flags= -Wall -lm -o3
cc= gcc

target=signal

main: signal.c
	$(cc) $(flags) signal.c -o $(target)

install: main
	cp $(target) /usr/local/bin

uninstall:
	rm /usr/local/bin/$(target)

run: main
	./$(target)

