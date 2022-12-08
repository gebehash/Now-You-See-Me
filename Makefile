CC=gcc-11
CFLAGS=-g -I. -Wall -lm
EXNAME=tema1
LANGUAGE=c
build: $(EXNAME).$(LANGUAGE)
	@$(CC) -o $(EXNAME) $(EXNAME).$(LANGUAGE) $(CFLAGS)

run:
	@./$(EXNAME)

.PHONY: clean

clean:
	@rm $(EXNAME)
