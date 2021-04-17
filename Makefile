ODIR=obj
SDIR=src

CC=gcc
CFLAGS=-I$(SDIR) -g
DEPS=

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

xor: $(ODIR)/xor.o
	$(CC) -o $@ $^ $(CFLAGS)

xors: $(ODIR)/xor.o
	$(CC) -o $@ $^ $(CFLAGS) -static

clean:
		rm -f $(ODIR)/*.o *~ core.
