PROGS = fork fork2
LIB = libapue.a

all: $(PROGS)

%: 	%.c  $(LIB)
	$(CC) $< -o $@ -L. $(LIB)

.PHONY:clean
clean:
	rm -f $(PROGS)

