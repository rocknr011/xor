ODIR=obj
SDIR=src

CC=gcc
CFLAGS=-I$(SDIR)
DEPS=

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

xor64: $(ODIR)/xor64.o
	$(CC) -o $@ $^ $(CFLAGS)

xor64s: $(ODIR)/xor64.o
	$(CC) -o $@ $^ $(CFLAGS) -static

clean:
		rm -f $(ODIR)/*.o *~ core.
