sources=$(wildcard *.cpp)
objs=$(sources:.c=.o)
# Ovde postaviti ime izvrsnog fajla: result=ime_izvrsnog_fajla
result=main

all: $(result)
$(result): $(objs)
	@echo -n "Building output binary: "
	@echo $@
	g++ -o $@ $(objs) -lsystemc -lpthread -DSC_INCLUDE_FX -w
%.o: %.c
	@echo -n "Compiling source into: "
	@echo $@
	g++ -c $< -lsystemc -DSC_INCLUDE_FX -w
.PHONY: clean
clean:
	@rm -rf $(result) *.o *.d
	@echo "Clean done.."
