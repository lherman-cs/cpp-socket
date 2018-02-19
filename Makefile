SOURCEDIR= src
BUILDDIR= build
PROG= UDP 
SOURCES=$(shell find $(SOURCEDIR) -type f -name *.cc ! -name *_test.cc)
OBJECTS=$(shell find $(SOURCEDIR) -type f -name *.cc ! -name *_test.cc | rev | cut -d '/' -f1 | rev | cut -d '.' -f-1 | xargs printf "%s.o\n")
INCLUDE=$(shell find $(SOURCEDIR) -type d | xargs printf "-I%s\n")
CXX= g++
CPPFLAGS= -g -I $(INCLUDE)

$(PROG): $(OBJECTS)
	$(CXX) $(CPPFLAGS) -o $@ $?
	mv $(OBJECTS) $(PROG) $(BUILDDIR)

$(OBJECTS): $(SOURCES)
	$(CXX) $(CPPFLAGS) -c $?

clean: 
	rm -f $(BUILDDIR)/* *.o

test: $(PROG) 
	@echo ""
	@echo "============================== Output =============================="
	@echo ""
	@$(BUILDDIR)/$(PROG)
