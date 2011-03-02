SDL_LIBS=-L/opt/local/lib -lSDL -lSDLmain -framework Cocoa

CXXFLAGS=-I/opt/local/include/SDL
CXX=g++

SRC=main.cc utils.cc
OBJ:=$(SRC:cc=o)
DEPS:=$(SRC:cc=d)

cppgame: $(OBJ)
	$(CXX) $(OBJ) $(SDL_LIBS) -o $@

UTIL_SRC=utils_test.cc utils.cc
UTIL_OBJ:=$(UTIL_SRC:cc=o)
UTIL_DEPS:=$(UTIL_SRC:cc=d)

utils_test: $(UTIL_OBJ)
	$(CXX) $(UTIL_OBJ) $(SDL_LIBS) -o $@

all: cppgame utils_test

.PHONY: all

%.d: %.cc
	@set -e ; rm -f $@ ; \
    $(CXX) -MM $(CXXFLAGS) $< > $@.$$$$ ; \
    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@ ; \
    rm -f $@.$$$$

include $(DEPS)
include $(UTIL_DEPS)

clean:
	rm -f $(OBJ) $(DEPS) $(UTIL_OBJ) $(UTIL_DEPS) cppgame utils_test

.PHONY: test
