PROGS = fork test wait exec system time sig_usr daemonize
LIB = libapue.a

all: $(PROGS)

%: 	%.c  $(LIB)
	$(CC) $< -o $@ -L. $(LIB)

.PHONY:clean
clean:
	rm -f $(PROGS) core.*

