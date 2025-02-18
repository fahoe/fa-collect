src=/home/Data/Projects/XBPM/Libera/progs/fa-collector/
INC=-I/opt/epics/base/include -I/opt/epics/base/include/compiler/gcc -I/opt/epics/base/include/os/Linux
LIB=-L/opt/epics/base/lib/linux-x86_64
project=fa_collect
test=test_server

#CFLAGS = -g -Wall -DDEBUG -pthread
CFLAGS = -Wall -pthread
DFLAGS = -g -Wall
TARGETS = $(project) $(test)


all: $(project) $(test)

$(project): $(project).c $(project).h
	gcc $< $(CFLAGS) $(INC) $(LIB) -lca -lcas -lCom -lgdd -ldbCore -ldbRecStd -lCap5 -o $@

$(test): $(test).c
	gcc $< $(DFLAGS) -o $@

clean:
	rm $(TARGETS)
