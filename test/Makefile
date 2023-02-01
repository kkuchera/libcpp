CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -Werror
LDFLAGS = -lgtest -lgtest_main -pthread
INCLUDE = -I../include/
BINDIR = bin

default: $(BINDIR)/test_kway_merge \
	$(BINDIR)/test_lru_cache \
	$(BINDIR)/test_unique_fd \
	$(BINDIR)/test_zipper

$(BINDIR)/%: %.cpp
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $< $(LDFLAGS)

.PHONY: default, clean
clean:
	$(RM) -r $(BINDIR)
