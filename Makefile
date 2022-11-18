.PHONY: pretty clean

# main target
all: unit

# clean up
clean:
	rm -f unit

# additional flags
FLAGS = -Wall -Wextra -pedantic -Weffc++ -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch -Wundef -Wno-unused -Wnon-virtual-dtor -Wreorder -Wdeprecated -Wfloat-equal

# build unit tests
unit: test/unit.cpp include/nlohmann/fifo_map.hpp test/thirdparty/catch/catch.hpp
	$(CXX) -std=c++11 $(CXXFLAGS) $(FLAGS) $(CPPFLAGS) -I include -I test -I test/thirdparty $< $(LDFLAGS) -o $@

check: unit
	./unit "*"

check-fast: unit
	./unit

# pretty printer
pretty:
	astyle --style=allman --indent=spaces=4 --indent-modifiers \
	   --indent-switches --indent-preproc-block --indent-preproc-define \
	   --indent-col1-comments --pad-oper --pad-header --align-pointer=type \
	   --align-reference=type --add-brackets --convert-tabs --close-templates \
	   --lineend=linux --preserve-date --suffix=none \
	   include/nlohmann/fifo_map.hpp test/unit.cpp
