CC= gcc
AR= ar
MV= mv
ARFLAGS= rcs
LIB= -lpthread
TARGET=libWrapper.a
SOURCE: PosixWrapper.c
	$(CC) -c $< $(LIB)
	$(AR) $(ARFLAGS) libWrapper.a PosixWrapper.o 
	$(MV) $(TARGET) ..
	$(RM) *.o
.PHONY: clean
clean:
	$(RM) ../$(TARGET)
