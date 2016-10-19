all: buildrelease builddebug buildtest

run: runrelease

test: runtest

clean: cleanrelease cleandebug cleantest

buildrelease:
	cd Release && $(MAKE) all

builddebug:
	cd Debug && $(MAKE) all

buildtest:
	cd UnitTest && $(MAKE) all


cleanrelease:
	cd Release && $(MAKE) clean

cleandebug:
	cd Debug && $(MAKE) clean

cleantest:
	cd UnitTest && $(MAKE) clean


runrelease: buildrelease
	cd Release && ./ybscheme

rundebug: builddebug
	cd Debug && ./ybschemeDebug

runtest: buildtest
	cd UnitTest && ./ybschemeTest




