CC = g++ 
CFLAGS = -Wall
LIBS = `sdl2-config --cflags --libs` -lSDL2_image
OBJ = Defs.o Render.o Main.o Clock.o

all: clean main print_main clean_obj
debug: CFLAGS +=  -g
debug: clean main print_debug clean_obj
	
.cc.o:
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)
	@printf "make: object: $(CC) -c -o $@ $< $(CFLAGS) $(LIBS)\n"

main: $(OBJ)
	$(CC) -o PipOS.exe $^ $(CFLAGS) $(LIBS)

print_main:
	@printf "make: main: $(CC) -o main $^ $(CFLAGS) $(LIBS)\n"
	@printf "make: "
	@printf "\033[1;32m"
	@printf "Successfully created main"
	@printf "\033[0m\n"

print_debug:
	@printf "make: debug: $(CC) -o main $^ $(CFLAGS) $(LIBS)\n"
	@printf "make: "
	@printf "\033[1;32m"
	@printf "Successfully created main, run [gdb ./main] to debug"
	@printf "\033[0m\n"

clean_obj:
	rm -f $(OBJ)

clean:
	rm -f $(OBJ) main

prepare:
	hg pull
	hg update
