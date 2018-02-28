SOURCEDIR= src
BUILDDIR= build
PROG= cpp-socket 
BACKUPNAME= cpp-socket.tar.gz
SOURCES=$(shell find $(SOURCEDIR) -type f -name *.cc ! -name *_test.cc)
OBJECTS=$(shell find $(SOURCEDIR) -type f -name *.cc ! -name *_test.cc | rev | cut -d '/' -f1 | rev | cut -d '.' -f-1 | xargs printf "%s.o\n")
INCLUDE=$(shell find $(SOURCEDIR) -type d | xargs printf "-I%s\n")
CXX= g++
CPPFLAGS= -g $(INCLUDE)

$(PROG): $(OBJECTS)
	$(CXX) $(CPPFLAGS) -o $@ $?
	@if [ ! -d $(BUILDDIR) ]; then mkdir $(BUILDDIR); fi # Check if the build dir exists. Else, create it
	mv $(OBJECTS) $(PROG) $(BUILDDIR)

$(OBJECTS): $(SOURCES)
	$(CXX) $(CPPFLAGS) -c $?

clean: 
	rm -f $(BUILDDIR)/* $(PROG) *.o $(shell find $(SOURCEDIR) -type f -name *.out)

test: $(PROG) 
	@echo ""
	@echo "============================== Output =============================="
	@echo ""
	@$(BUILDDIR)/$(PROG)

backup: clean
	rm -f $(BACKUPNAME)
	tar -zcvf $(BACKUPNAME) *
