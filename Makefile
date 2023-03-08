CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c2x -O3 -fpic
LIBS=

TARGET=libvector.so
CACHE=.cache
OUTPUT=$(CACHE)/release

MODULES += vector.o
TEST += test.o


OBJ=$(addprefix $(CACHE)/,$(MODULES))

T_OBJ=$(addprefix $(CACHE)/,$(TEST))

all: env $(OBJ)
	$(CC) -shared $(OBJ) $(LIBS) -o $(OUTPUT)/$(TARGET)


%.o:
	$(CC) $(CFLAGS) -c $< -o $@


-include dep.list


exec: all $(T_OBJ)
	$(CC) $(T_OBJ) $(OBJ) $(LIBS) -o $(OUTPUT)/test
	$(OUTPUT)/test


.PHONY: env dep clean


dep:
	$(CC) -MM test/*.c src/*.c | sed 's|[a-zA-Z0-9_-]*\.o|$(CACHE)/&|' > dep.list


env:
	mkdir -pv $(CACHE)
	mkdir -pv $(OUTPUT)


clean: 
	rm -rvf $(OUTPUT)
	rm -vf $(CACHE)/*.o



