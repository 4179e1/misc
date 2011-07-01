SRC=$(shell ls *.cpp)
TAR=$(SRC:%.cpp=%)
LDFLAGS+=-lstdc++ -lACE

all: $(TAR)

$(TAR): %: %.cpp
	$(CC) $< -o $@ $(CFLAGS) $(LDFLAGS)
	

.PHONY: clean
clean:
	$(RM) -rf $(TAR)
