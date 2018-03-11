makefile:

clean:
	@-rm Main
	@echo "Done cleaning."
all:
	@echo "[Compiling...]"
	@gcc -o Main Main.c
	@echo "[Done.]"