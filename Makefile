NAME = square

CC = gcc
PKG-CONFIG = $(shell which pkg-config)
RM = rm -f

CFLAGS = -Wall -Werror -Wextra
CFLAGS_GLUT = $(shell $(PKG-CONFIG) --cflags glut)

LIBS = -lGL
LIBS_GLUT = $(shell $(PKG-CONFIG) --libs glut)

$(NAME): square.o
	$(CC) $? -o $@ $(LIBS_GLUT) $(LIBS) 

square.o: square.c
	$(CC) $(CFLAGS) $(CFLAGS_GLUT) $? -c $@

clean:
	$(RM) *.o
	$(RM) $(NAME)

.PHONY: clean
