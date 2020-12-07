CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Werror
LDFLAGS = -lgtest -lgtest_main -pthread
INCLUDE = -I../include/
BINDIR = bin

default: $(BINDIR)/test_kway_merge

$(BINDIR)/%: %.cpp
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $< $(LDFLAGS)

.PHONY: default, clean
clean:
	$(RM) -r $(BINDIR)
