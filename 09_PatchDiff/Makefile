run:	maze mazeS mazeTS mazeRTS
	./maze
	./mazeS 8
	./mazeTS " #" 6
	./mazeRTS 5324 "-4" 7

maze:	maze.c
	cc $< -o $@

mazeS:	size.patch maze.c
	cp maze.c maze.tmp.c
	patch maze.tmp.c < $<
	cc maze.tmp.c -o $@

mazeTS:	text-size.patch maze.c
	cp maze.c maze.tmp.c
	patch maze.tmp.c < $<
	cc maze.tmp.c -o $@

mazeRTS:random-text-size.patch maze.c 
	cp maze.c maze.tmp.c
	patch maze.tmp.c < $<
	cc maze.tmp.c -o $@

clean:
	rm -f *.tmp.c maze mazeS mazeTS mazeRTS 
