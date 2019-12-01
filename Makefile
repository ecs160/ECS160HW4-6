objects := maxTweeter.o

CC := gcc
CFLAGS := -Wall -Werror
CFLAGS += -g 

ifneq ($(V),1)
Q = @
endif

#Generate executable
maxTweeter: $(objects)
	$(Q) $(CC) $(CFLAGS) -o $@ $< 

#Generate objects files from C files
maxTweeter.o: maxTweeter.c 
	$(Q) $(CC) $(CFLAGS) -c -o $@ $< 

	
# Clean generated files
clean:
	@echo "clean"
	$(Q) rm -f maxTweeter $(objects)