build:
	@if [ ! -d build ]; then mkdir build; fi
	cd build && cmake .. && make
	@echo ""
	@echo "Your programs have been built in build/bin"