.SILENT:

DIRS	+= FutureCore
#DIRS	+= FutureMath
DIRS	+= FutureGame
DIRS	+= FutureTest

.PHONY: debug profile release clean

default: debug

debug profile release clean:
	for dir in $(DIRS) ; do \
		echo "-------------------------------------------------------------------------------" ; \
		echo "Building $$dir" ; \
		if [ ! -d $$d ] ; then \
			echo "Module $$dir is missing.  Skipping." ; \
		else \
			$(MAKE) -C $$dir $(MAKECMDGOALS) ; \
		fi ; \
	done ;
