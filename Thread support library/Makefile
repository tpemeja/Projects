####### Flags #########
#######################
CFLAGS=-Wall -Wextra
CC=gcc -g
CC_PTHREAD=gcc -DUSE_PTHREAD

####### Vars #########
#######################
ECHO= "** NOTRE LIB **"
NBTHREADS = 8
NBYIELDS = 8
NBFIBO = 20
NBMUT = 20
####### Directories ###
#######################
BUILD_DIR=install
LIB_DIR=$(BUILD_DIR)/lib
BIN_DIR=$(BUILD_DIR)/bin
SRC_THREAD=src/thread
SRC_TEST=src/test
MODE1 =
MODE2 = -pthread
MODE3 =
MODE4 =
####### Targets #######
#######################
BIN=$(BIN_DIR)/example \
		 $(BIN_DIR)/01-main \
		 $(BIN_DIR)/02-switch \
		 $(BIN_DIR)/03-preemption \
		 $(BIN_DIR)/11-join \
		 $(BIN_DIR)/12-join-main\
		 $(BIN_DIR)/21-create-many \
		 $(BIN_DIR)/22-create-many-recursive \
		 $(BIN_DIR)/23-create-many-once\
		 $(BIN_DIR)/31-switch-many \
		 $(BIN_DIR)/32-switch-many-join \
		 $(BIN_DIR)/33-switch-many-cascade \
		 $(BIN_DIR)/51-fibonacci \
		 $(BIN_DIR)/61-mutex  \
		 $(BIN_DIR)/62-mutex \
		 $(BIN_DIR)/test-priority

BIN_PTHREAD=$(BIN_DIR)/example-pthread \
		 				$(BIN_DIR)/01-main-pthread \
		 				$(BIN_DIR)/02-switch-pthread \
		 				$(BIN_DIR)/03-preemption-pthread \
		 				$(BIN_DIR)/11-join-pthread \
		 				$(BIN_DIR)/12-join-main-pthread \
		 				$(BIN_DIR)/21-create-many-pthread \
		 				$(BIN_DIR)/22-create-many-recursive-pthread \
		 				$(BIN_DIR)/23-create-many-once-pthread \
		 				$(BIN_DIR)/31-switch-many-pthread \
		 				$(BIN_DIR)/32-switch-many-join-pthread \
						$(BIN_DIR)/33-switch-many-cascade-pthread \
		 				$(BIN_DIR)/51-fibonacci-pthread \
		 				$(BIN_DIR)/61-mutex-pthread \
		 				$(BIN_DIR)/62-mutex-pthread \
						$(BIN_DIR)/test-priority-pthread

.PHONY: all build_dir build_lib build_test build_test_pthread clean

######## Rules ########
#######################
all: test

install: build_dir build_test build_test_pthread

test: build_dir build_test build_test_pthread

build_dir:
	@if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi
	@if [ ! -d $(LIB_DIR) ]; then mkdir $(LIB_DIR); fi
	@if [ ! -d $(BIN_DIR) ]; then mkdir $(BIN_DIR); fi

build_lib: build_dir $(LIB_DIR)/libthread.a $(LIB_DIR)/libthread_premp.a $(LIB_DIR)/libthread_head.a

build_test: build_lib $(BIN)

build_test_pthread: build_dir $(BIN_PTHREAD)

######## Executable Test ########
#################################

example: build_lib $(BIN_DIR)/example$(MODE1) $(BIN_DIR)/example$(MODE2)
	@echo "/************ 00-EXEMPLE ****************/"
	@./$(BIN_DIR)/example$(MODE2)
	@echo $(ECHO)
	@./$(BIN_DIR)/example$(MODE1)

01-main: build_lib $(BIN_DIR)/01-main$(MODE1) $(BIN_DIR)/01-main$(MODE2)
	@echo "/************ 01-MAIN ****************/"
	@if [ "$(MODE1)" != "$(MODE2)" ];\
	 then \
	 ./$(BIN_DIR)/01-main$(MODE2); \
	 echo $(ECHO); \
	 ./$(BIN_DIR)/01-main$(MODE1); \
	 else \
	 ./$(BIN_DIR)/01-main$(MODE1); fi

02-switch: build_lib $(BIN_DIR)/02-switch$(MODE1) $(BIN_DIR)/02-switch$(MODE2)
	@echo "/************ 02-SWITCH ****************/"
	@if [ "$(MODE1)" != "$(MODE2)" ];\
	 then \
	 ./$(BIN_DIR)/02-switch$(MODE2); \
	 echo $(ECHO); \
	 ./$(BIN_DIR)/02-switch$(MODE1); \
	 else \
	 ./$(BIN_DIR)/02-switch$(MODE1); fi

03-preemption: build_lib $(BIN_DIR)/03-preemption$(MODE1) $(BIN_DIR)/03-preemption$(MODE2)
	@echo "/************ 02-PREEMPTION ****************/"
	@if [ "$(MODE1)" != "$(MODE2)" ];\
	 then \
	 ./$(BIN_DIR)/03-preemption$(MODE2); \
	 echo $(ECHO); \
	 ./$(BIN_DIR)/03-preemption$(MODE1); \
	 else \
	 ./$(BIN_DIR)/03-preemption$(MODE1); fi

11-join: build_lib $(BIN_DIR)/11-join$(MODE1) $(BIN_DIR)/11-join$(MODE2)
	@echo "/************ 11-JOIN ****************/"
	@if [ "$(MODE1)" != "$(MODE2)" ];\
	 then \
	 ./$(BIN_DIR)/11-join$(MODE2); \
	 echo $(ECHO); \
	 ./$(BIN_DIR)/11-join$(MODE1); \
	 else \
	 ./$(BIN_DIR)/11-join$(MODE1); fi

12-join-main: build_lib $(BIN_DIR)/12-join-main$(MODE1) $(BIN_DIR)/12-join-main$(MODE2)
	@echo "/************ 12-JOIN-MAIN ****************/"
	@if [ "$(MODE1)" != "$(MODE2)" ];\
	 then \
	 ./$(BIN_DIR)/12-join-main$(MODE2); \
	 echo $(ECHO); \
	 ./$(BIN_DIR)/12-join-main$(MODE1); \
	 else \
	 ./$(BIN_DIR)/12-join-main$(MODE1); fi

21-create-many: build_lib $(BIN_DIR)/21-create-many$(MODE1) $(BIN_DIR)/21-create-many$(MODE2)
	@echo "/************ 21-CREATE-MANY ****************/"
	@if [ "$(MODE1)" != "$(MODE2)" ];\
	 then \
	 ./$(BIN_DIR)/21-create-many$(MODE2) $(NBTHREADS); \
	 echo $(ECHO); \
	 ./$(BIN_DIR)/21-create-many$(MODE1) $(NBTHREADS); \
	 else \
	 ./$(BIN_DIR)/21-create-many$(MODE1) $(NBTHREADS); fi

22-create-many-recursive: build_lib $(BIN_DIR)/22-create-many-recursive$(MODE1) $(BIN_DIR)/22-create-many-recursive$(MODE2)
	@echo "/************ 21-CREATE-MANY-RECURSIVE ****************/"
	@if [ "$(MODE1)" != "$(MODE2)" ];\
	 then \
	 ./$(BIN_DIR)/22-create-many-recursive$(MODE2) $(NBTHREADS); \
	 echo $(ECHO); \
	 ./$(BIN_DIR)/22-create-many-recursive$(MODE1) $(NBTHREADS); \
	 else \
	 ./$(BIN_DIR)/22-create-many-recursive$(MODE1) $(NBTHREADS); fi

23-create-many-once: build_lib $(BIN_DIR)/23-create-many-once$(MODE1) $(BIN_DIR)/23-create-many-once$(MODE2)
	@echo "/************ 23-CREATE-MANY-ONCE ****************/"
	@if [ "$(MODE1)" != "$(MODE2)" ];\
	 then \
	 ./$(BIN_DIR)/23-create-many-once$(MODE2) $(NBTHREADS); \
	 echo $(ECHO); \
	 ./$(BIN_DIR)/23-create-many-once$(MODE1) $(NBTHREADS); \
	 else \
	 ./$(BIN_DIR)/23-create-many-once$(MODE1) $(NBTHREADS); fi

31-switch-many: build_lib $(BIN_DIR)/31-switch-many$(MODE1) $(BIN_DIR)/31-switch-many$(MODE2)
	@echo "/************ 31-CREATE-MANY-ONCE ****************/"
	@if [ "$(MODE1)" != "$(MODE2)" ];\
	 then \
	 ./$(BIN_DIR)/31-switch-many$(MODE2) $(NBTHREADS) $(NBYIELDS); \
	 echo $(ECHO); \
	 ./$(BIN_DIR)/31-switch-many$(MODE1) $(NBTHREADS) $(NBYIELDS); \
	 else \
	 ./$(BIN_DIR)/31-switch-many$(MODE1) $(NBTHREADS) $(NBYIELDS); fi

32-switch-many-join: build_lib $(BIN_DIR)/32-switch-many-join$(MODE1) $(BIN_DIR)/32-switch-many-join$(MODE2)
	@echo "/************ 32-CREATE-MANY-JOIN ****************/"
	@if [ "$(MODE1)" != "$(MODE2)" ];\
	 then \
	 ./$(BIN_DIR)/32-switch-many-join$(MODE2) $(NBTHREADS) $(NBYIELDS); \
	 echo $(ECHO); \
	 ./$(BIN_DIR)/32-switch-many-join$(MODE1) $(NBTHREADS) $(NBYIELDS); \
	 else \
	 ./$(BIN_DIR)/32-switch-many-join$(MODE1) $(NBTHREADS) $(NBYIELDS); fi

33-switch-many-cascade: build_lib $(BIN_DIR)/33-switch-many-cascade$(MODE1) $(BIN_DIR)/33-switch-many-cascade$(MODE2)
	@echo "/************ 33-CREATE-MANY-CASCADE ****************/"
	@if [ "$(MODE1)" != "$(MODE2)" ];\
	 then \
	 ./$(BIN_DIR)/33-switch-many-cascade$(MODE2) $(NBTHREADS) $(NBYIELDS); \
	 echo $(ECHO); \
	 ./$(BIN_DIR)/33-switch-many-cascade$(MODE1) $(NBTHREADS) $(NBYIELDS); \
	 else \
	 ./$(BIN_DIR)/33-switch-many-cascade$(MODE1) $(NBTHREADS) $(NBYIELDS); fi

51-fibonacci: build_lib $(BIN_DIR)/51-fibonacci$(MODE1) $(BIN_DIR)/51-fibonacci$(MODE2)
	@echo "/************ 51-FIBONACCI ****************/"
	@if [ "$(MODE1)" != "$(MODE2)" ];\
	 then \
	 ./$(BIN_DIR)/51-fibonacci$(MODE2) $(NBFIBO); \
	 echo $(ECHO); \
	 ./$(BIN_DIR)/51-fibonacci$(MODE1) $(NBFIBO); \
	 else \
	 ./$(BIN_DIR)/51-fibonacci$(MODE1) $(NBFIBO); fi

61-mutex: build_lib $(BIN_DIR)/61-mutex$(MODE1) $(BIN_DIR)/61-mutex$(MODE2)
	@echo "/************ 61-MUTEX ****************/"
	@if [ "$(MODE1)" != "$(MODE2)" ];\
	 then \
	 ./$(BIN_DIR)/61-mutex$(MODE2) $(NBMUT); \
	 echo $(ECHO); \
	 ./$(BIN_DIR)/61-mutex$(MODE1) $(NBMUT); \
	 else \
	 ./$(BIN_DIR)/61-mutex$(MODE1) $(NBMUT); fi

62-mutex: build_lib $(BIN_DIR)/62-mutex$(MODE1) $(BIN_DIR)/62-mutex$(MODE2)
	@echo "/************ 62-MUTEX ****************/"
	@if [ "$(MODE1)" != "$(MODE2)" ];\
	 then \
	 ./$(BIN_DIR)/62-mutex$(MODE2) $(NBMUT); \
	 echo $(ECHO); \
	 ./$(BIN_DIR)/62-mutex$(MODE1) $(NBMUT); \
	 else \
	 ./$(BIN_DIR)/62-mutex$(MODE1) $(NBMUT); fi

71-preemption: build_lib $(BIN_DIR)/71-preemption$(MODE1) $(BIN_DIR)/71-preemption$(MODE2)
	@echo "/************ 71-PREEMPTION ****************/"
	@if [ "$(MODE1)" != "$(MODE2)" ];\
	 then \
	 ./$(BIN_DIR)/71-preemption$(MODE2)  $(NBTHREADS);\
	 echo $(ECHO); \
	 ./$(BIN_DIR)/71-preemption$(MODE1)  $(NBTHREADS); \
	 else \
	 ./$(BIN_DIR)/71-preemption$(MODE1)  $(NBTHREADS); fi

test-priority: build_lib $(BIN_DIR)/test-priority$(MODE1)
	@echo "/************ TEST-PRIORITY ****************/"
	@./$(BIN_DIR)/test-priority$(MODE1)


###### Valgrind Test #######
############################

valgrind-example:
	@valgrind --log-file=$(BIN_DIR)/example-valgrind.txt $(BIN_DIR)/example$(MODE)

example-valgrind: build_lib $(BIN_DIR)/example$(MODE) 	valgrind-example
	@echo "/************ 00-EXEMPLE ****************/"
	@if [ "$(shell grep -c "All heap blocks were freed" $(BIN_DIR)/example-valgrind.txt)"  = "1" ];\
	 then echo "Test free valgrind : SUCCESS"; else echo "Test free valgrind : FAILURE"; fi
	@if [ "$(shell grep -c "ERROR SUMMARY: 0" $(BIN_DIR)/example-valgrind.txt)" = "1" ];\
	 then echo "Test error valgrind : SUCCESS"; else echo "Test error valgrind : FAILURE"; fi
	@echo ""

valgrind-01-main:
	@valgrind --log-file=$(BIN_DIR)/01-main-valgrind.txt $(BIN_DIR)/01-main$(MODE1)

01-main-valgrind: build_lib $(BIN_DIR)/01-main$(MODE1) valgrind-01-main
	@echo "/************ 01-MAIN ****************/"
	@if [ "$(shell grep -c "All heap blocks were freed" $(BIN_DIR)/01-main-valgrind.txt)"  = "1" ];\
	 then echo "Test free valgrind : SUCCESS"; else echo "Test free valgrind : FAILURE"; fi
	@if [ "$(shell grep -c "ERROR SUMMARY: 0" $(BIN_DIR)/01-main-valgrind.txt)" = "1" ];\
	 then echo "Test error valgrind : SUCCESS"; else echo "Test error valgrind : FAILURE"; fi
	@echo ""

valgrind-02-switch:
	@valgrind --log-file=$(BIN_DIR)/02-switch-valgrind.txt $(BIN_DIR)/02-switch$(MODE1)

02-switch-valgrind: build_lib $(BIN_DIR)/02-switch$(MODE1) valgrind-02-switch
	@echo "/************ 02-SWITCH ****************/"
	@if [ "$(shell grep -c "All heap blocks were freed" $(BIN_DIR)/02-switch-valgrind.txt)"  = "1" ];\
	 then echo "Test free valgrind : SUCCESS"; else echo "Test free valgrind : FAILURE"; fi
	@if [ "$(shell grep -c "ERROR SUMMARY: 0" $(BIN_DIR)/02-switch-valgrind.txt)" = "1" ];\
	 then echo "Test error valgrind : SUCCESS"; else echo "Test error valgrind : FAILURE"; fi
	@echo ""

valgrind-11-join:
	@valgrind --log-file=$(BIN_DIR)/11-join-valgrind.txt $(BIN_DIR)/11-join$(MODE1)

11-join-valgrind: build_lib $(BIN_DIR)/11-join$(MODE1) valgrind-11-join
	@echo "/************ 11-JOIN ****************/"
	@if [ "$(shell grep -c "All heap blocks were freed" $(BIN_DIR)/11-join-valgrind.txt)"  = "1" ];\
	 then echo "Test free valgrind : SUCCESS"; else echo "Test free valgrind : FAILURE"; fi
	@if [ "$(shell grep -c "ERROR SUMMARY: 0" $(BIN_DIR)/11-join-valgrind.txt)" = "1" ];\
	 then echo "Test error valgrind : SUCCESS"; else echo "Test error valgrind : FAILURE"; fi
	@echo ""

valgrind-12-join-main:
	@valgrind --log-file=$(BIN_DIR)/12-join-main-valgrind.txt $(BIN_DIR)/12-join-main$(MODE1)

12-join-main-valgrind: build_lib $(BIN_DIR)/12-join-main$(MODE1) valgrind-12-join-main
	@echo "/************ 12-JOIN-MAIN ****************/"
	@if [ "$(shell grep -c "All heap blocks were freed" $(BIN_DIR)/12-join-main-valgrind.txt)"  = "1" ];\
	 then echo "Test free valgrind : SUCCESS"; else echo "Test free valgrind : FAILURE"; fi
	@if [ "$(shell grep -c "ERROR SUMMARY: 0" $(BIN_DIR)/12-join-main-valgrind.txt)" = "1" ];\
	 then echo "Test error valgrind : SUCCESS"; else echo "Test error valgrind : FAILURE"; fi
	@echo ""

valgrind-21-create-many:
	@valgrind --log-file=$(BIN_DIR)/21-create-many-valgrind.txt $(BIN_DIR)/21-create-many$(MODE1) $(NBTHREADS)

21-create-many-valgrind: build_lib $(BIN_DIR)/21-create-many$(MODE1) valgrind-21-create-many
	@echo "/************ 21-CREATE-MANY ****************/"
	@if [ "$(shell grep -c "All heap blocks were freed" $(BIN_DIR)/21-create-many-valgrind.txt)"  = "1" ];\
	 then echo "Test free valgrind : SUCCESS"; else echo "Test free valgrind : FAILURE"; fi
	@if [ "$(shell grep -c "ERROR SUMMARY: 0" $(BIN_DIR)/21-create-many-valgrind.txt)" = "1" ];\
	 then echo "Test error valgrind : SUCCESS"; else echo "Test error valgrind : FAILURE"; fi
	@echo ""

valgrind-22-create-many-recursive:
	@valgrind --log-file=$(BIN_DIR)/22-create-many-recursive-valgrind.txt $(BIN_DIR)/22-create-many-recursive$(MODE1) $(NBTHREADS)

22-create-many-recursive-valgrind: build_lib $(BIN_DIR)/22-create-many-recursive$(MODE1) valgrind-22-create-many-recursive
	@echo "/************ 21-CREATE-MANY-RECURSIVE ****************/"
	@if [ "$(shell grep -c "All heap blocks were freed" $(BIN_DIR)/22-create-many-recursive-valgrind.txt)"  = "1" ];\
	 then echo "Test free valgrind : SUCCESS"; else echo "Test free valgrind : FAILURE"; fi
	@if [ "$(shell grep -c "ERROR SUMMARY: 0" $(BIN_DIR)/22-create-many-recursive-valgrind.txt)" = "1" ];\
	 then echo "Test error valgrind : SUCCESS"; else echo "Test error valgrind : FAILURE"; fi
	@echo ""

valgrind-23-create-many-once:
	@valgrind --log-file=$(BIN_DIR)/23-create-many-once-valgrind.txt $(BIN_DIR)/23-create-many-once$(MODE1) $(NBTHREADS)

23-create-many-once-valgrind: build_lib $(BIN_DIR)/23-create-many-once$(MODE1) valgrind-23-create-many-once
	@echo "/************ 23-CREATE-MANY-ONCE ****************/"
	@if [ "$(shell grep -c "All heap blocks were freed" $(BIN_DIR)/23-create-many-once-valgrind.txt)"  = "1" ];\
	 then echo "Test free valgrind : SUCCESS"; else echo "Test free valgrind : FAILURE"; fi
	@if [ "$(shell grep -c "ERROR SUMMARY: 0" $(BIN_DIR)/23-create-many-once-valgrind.txt)" = "1" ];\
	 then echo "Test error valgrind : SUCCESS"; else echo "Test error valgrind : FAILURE"; fi
	@echo ""

valgrind-31-switch-many:
	@valgrind --log-file=$(BIN_DIR)/31-switch-many-valgrind.txt $(BIN_DIR)/31-switch-many$(MODE1) $(NBTHREADS) $(NBYIELDS)

31-switch-many-valgrind: build_lib $(BIN_DIR)/31-switch-many$(MODE1) valgrind-31-switch-many
	@echo "/************ 31-CREATE-MANY-ONCE ****************/"
	@if [ "$(shell grep -c "All heap blocks were freed" $(BIN_DIR)/31-switch-many-valgrind.txt)"  = "1" ];\
	 then echo "Test free valgrind : SUCCESS"; else echo "Test free valgrind : FAILURE"; fi
	@if [ "$(shell grep -c "ERROR SUMMARY: 0" $(BIN_DIR)/31-switch-many-valgrind.txt)" = "1" ];\
	 then echo "Test error valgrind : SUCCESS"; else echo "Test error valgrind : FAILURE"; fi
	@echo ""

valgrind-32-switch-many-join:
	@valgrind --log-file=$(BIN_DIR)/32-switch-many-join-valgrind.txt $(BIN_DIR)/32-switch-many-join$(MODE1) $(NBTHREADS) $(NBYIELDS)

32-switch-many-join-valgrind: build_lib $(BIN_DIR)/32-switch-many-join$(MODE1) valgrind-32-switch-many-join
	@echo "/************ 32-CREATE-MANY-JOIN ****************/"
	@if [ "$(shell grep -c "All heap blocks were freed" $(BIN_DIR)/32-switch-many-join-valgrind.txt)"  = "1" ];\
	 then echo "Test free valgrind : SUCCESS"; else echo "Test free valgrind : FAILURE"; fi
	@if [ "$(shell grep -c "ERROR SUMMARY: 0" $(BIN_DIR)/32-switch-many-join-valgrind.txt)" = "1" ];\
	 then echo "Test error valgrind : SUCCESS"; else echo "Test error valgrind : FAILURE"; fi
	@echo ""

valgrind-33-switch-many-cascade:
	@valgrind --log-file=$(BIN_DIR)/33-switch-many-cascade-valgrind.txt $(BIN_DIR)/33-switch-many-cascade$(MODE1) $(NBTHREADS) $(NBYIELDS)

33-switch-many-cascade-valgrind: build_lib $(BIN_DIR)/33-switch-many-cascade$(MODE1) valgrind-33-switch-many-cascade
	@echo "/************ 33-CREATE-MANY-CASCADE ****************/"
	@if [ "$(shell grep -c "All heap blocks were freed" $(BIN_DIR)/33-switch-many-cascade-valgrind.txt)"  = "1" ];\
	 then echo "Test free valgrind : SUCCESS"; else echo "Test free valgrind : FAILURE"; fi
	@if [ "$(shell grep -c "ERROR SUMMARY: 0" $(BIN_DIR)/33-switch-many-cascade-valgrind.txt)" = "1" ];\
	 then echo "Test error valgrind : SUCCESS"; else echo "Test error valgrind : FAILURE"; fi
	@echo ""

valgrind-51-fibonacci:
	@valgrind --log-file=$(BIN_DIR)/51-fibonacci-valgrind.txt $(BIN_DIR)/51-fibonacci$(MODE1) $(NBFIBO)

51-fibonacci-valgrind: build_lib $(BIN_DIR)/51-fibonacci$(MODE1) valgrind-51-fibonacci
	@echo "/************ 51-FIBONACCI ****************/"
	@if [ "$(shell grep -c "All heap blocks were freed" $(BIN_DIR)/51-fibonacci-valgrind.txt)"  = "1" ];\
	 then echo "Test free valgrind : SUCCESS"; else echo "Test free valgrind : FAILURE"; fi
	@if [ "$(shell grep -c "ERROR SUMMARY: 0" $(BIN_DIR)/51-fibonacci-valgrind.txt)" = "1" ];\
	 then echo "Test error valgrind : SUCCESS"; else echo "Test error valgrind : FAILURE"; fi
	@echo ""

valgrind-61-mutex:
	@valgrind --log-file=$(BIN_DIR)/61-mutex-valgrind.txt $(BIN_DIR)/61-mutex$(MODE1) $(NBMUT)

61-mutex-valgrind: build_lib $(BIN_DIR)/61-mutex$(MODE1) valgrind-61-mutex
	@echo "/************ 61-MUTEX ****************/"
	@if [ "$(shell grep -c "All heap blocks were freed" $(BIN_DIR)/61-mutex-valgrind.txt)"  = "1" ];\
	 then echo "Test free valgrind : SUCCESS"; else echo "Test free valgrind : FAILURE"; fi
	@if [ "$(shell grep -c "ERROR SUMMARY: 0" $(BIN_DIR)/61-mutex-valgrind.txt)" = "1" ];\
	 then echo "Test error valgrind : SUCCESS"; else echo "Test error valgrind : FAILURE"; fi
	@echo ""

valgrind-62-mutex:
	@valgrind --log-file=$(BIN_DIR)/62-mutex-valgrind.txt $(BIN_DIR)/62-mutex$(MODE1) $(NBMUT)

62-mutex-valgrind: build_lib $(BIN_DIR)/62-mutex$(MODE1) valgrind-62-mutex
	@echo "/************ 62-MUTEX ****************/"
	@if [ "$(shell grep -c "All heap blocks were freed" $(BIN_DIR)/62-mutex-valgrind.txt)"  = "1" ];\
	 then echo "Test free valgrind : SUCCESS"; else echo "Test free valgrind : FAILURE"; fi
	@if [ "$(shell grep -c "ERROR SUMMARY: 0" $(BIN_DIR)/62-mutex-valgrind.txt)" = "1" ];\
	 then echo "Test error valgrind : SUCCESS"; else echo "Test error valgrind : FAILURE"; fi
	@echo ""

valgrind-03-preemption:
	@valgrind --log-file=$(BIN_DIR)/03-preemption-valgrind.txt $(BIN_DIR)/03-preemption$(MODE1)

03-preemption-valgrind: build_lib $(BIN_DIR)/03-preemption$(MODE1) valgrind-03-preemption
	@echo "/************ TEST-PREEMPT ****************/"
	@if [ "$(shell grep -c "All heap blocks were freed" $(BIN_DIR)/03-preemption-valgrind.txt)"  = "1" ];\
	 then echo "Test free valgrind : SUCCESS"; else echo "Test free valgrind : FAILURE"; fi
	@if [ "$(shell grep -c "ERROR SUMMARY: 0" $(BIN_DIR)/03-preemption-valgrind.txt)" = "1" ];\
	 then echo "Test error valgrind : SUCCESS"; else echo "Test error valgrind : FAILURE"; fi
	@echo ""

valgrind-test-priority:
	@valgrind --log-file=$(BIN_DIR)/test-priority-valgrind.txt $(BIN_DIR)/test-priority$(MODE1)

test-priority-valgrind: build_lib $(BIN_DIR)/test-priority$(MODE1) valgrind-test-priority
	@echo "/************ TEST-PRIORITY ****************/"
	@if [ "$(shell grep -c "All heap blocks were freed" $(BIN_DIR)/test-priority-valgrind.txt)"  = "1" ];\
	 then echo "Test free valgrind : SUCCESS"; else echo "Test free valgrind : FAILURE"; fi
	@if [ "$(shell grep -c "ERROR SUMMARY: 0" $(BIN_DIR)/test-priority-valgrind.txt)" = "1" ];\
	 then echo "Test error valgrind : SUCCESS"; else echo "Test error valgrind : FAILURE"; fi
	@echo ""

######### Graph ############
############################

21-create-many-graph: build_lib $(BIN_DIR)/21-create-many$(MODE1) $(BIN_DIR)/21-create-many$(MODE2) $(BIN_DIR)/21-create-many$(MODE3) $(BIN_DIR)/21-create-many$(MODE4)
	@echo "/************ 21-CREATE-MANY ****************/"
	@python3 graph.py 21-create-many$(MODE1) 21-create-many$(MODE2) 21-create-many$(MODE3) 21-create-many$(MODE4) 7

22-create-many-recursive-graph: build_lib $(BIN_DIR)/22-create-many-recursive$(MODE1) $(BIN_DIR)/22-create-many-recursive$(MODE2) $(BIN_DIR)/22-create-many-recursive$(MODE3) $(BIN_DIR)/22-create-many-recursive$(MODE4)
	@echo "/************ 22-CREATE-MANY-RECURSIVE ****************/"
	@python3 graph.py 22-create-many-recursive$(MODE1) 22-create-many-recursive$(MODE2) 22-create-many-recursive$(MODE3) 22-create-many-recursive$(MODE4) 7

23-create-many-once-graph: build_lib $(BIN_DIR)/23-create-many-once$(MODE1) $(BIN_DIR)/23-create-many-once$(MODE2) $(BIN_DIR)/23-create-many-once$(MODE3) $(BIN_DIR)/23-create-many-once$(MODE4)
	@echo "/************ 23-CREATE-MANY-ONCE ****************/"
	@python3 graph.py 23-create-many-once$(MODE1) 23-create-many-once$(MODE2) 23-create-many-once$(MODE3) 23-create-many-once$(MODE4) 9

31-switch-many-graph: build_lib $(BIN_DIR)/31-switch-many$(MODE1) $(BIN_DIR)/31-switch-many$(MODE2) $(BIN_DIR)/31-switch-many$(MODE3) $(BIN_DIR)/31-switch-many$(MODE4)
	@echo "/************ 31-SWITCH-MANY ****************/"
	@python3 graph2.py 31-switch-many$(MODE1) 31-switch-many$(MODE2) 31-switch-many$(MODE3) 31-switch-many$(MODE4) 5

32-switch-many-join-graph: build_lib $(BIN_DIR)/32-switch-many-join$(MODE1) $(BIN_DIR)/32-switch-many-join$(MODE2) $(BIN_DIR)/32-switch-many-join$(MODE3) $(BIN_DIR)/32-switch-many-join$(MODE4)
	@echo "/************ 32-SWITCH-MANY-JOIN ****************/"
	@python3 graph2.py 32-switch-many-join$(MODE1) 32-switch-many-join$(MODE2) 32-switch-many-join$(MODE3) 32-switch-many-join$(MODE4) 8

51-fibonacci-graph: build_lib $(BIN_DIR)/51-fibonacci$(MODE1) $(BIN_DIR)/51-fibonacci$(MODE2) $(BIN_DIR)/51-fibonacci$(MODE3) $(BIN_DIR)/51-fibonacci$(MODE4)
	@echo "/************ 51-FIBONACCI ****************/"
	@python3 graph_fibo.py 51-fibonacci$(MODE1) 51-fibonacci$(MODE2) 51-fibonacci$(MODE3) 51-fibonacci$(MODE4) $(NBFIBO)
#
# 61-mutex-graph: build_lib $(BIN_DIR)/61-mutex $(BIN_DIR)/61-mutex-pthread
# 	@echo "/************ 61-MUTEX ****************/"
#
# 62-mutex-graph: build_lib $(BIN_DIR)/62-mutex $(BIN_DIR)/62-mutex-pthread
# 	@echo "/************ 62-MUTEX ****************/"

#Lance tous les exécutables
check: example \
			 01-main \
			 02-switch \
			 03-preemption \
			 11-join \
			 12-join-main \
			 21-create-many \
			 22-create-many-recursive \
			 23-create-many-once \
			 31-switch-many \
			 32-switch-many-join \
			 33-switch-many-cascade \
			 51-fibonacci \
			 61-mutex \
			 62-mutex \
			 test-priority

#Lance tous les exécutables avec un test valgrind
valgrind: example-valgrind \
			 01-main-valgrind \
			 02-switch-valgrind \
			 03-preemption-valgrind \
			 11-join-valgrind \
			 12-join-main-valgrind \
			 21-create-many-valgrind \
			 22-create-many-recursive-valgrind \
			 23-create-many-once-valgrind \
			 31-switch-many-valgrind \
			 32-switch-many-join-valgrind \
			 33-switch-many-cascade-valgrind \
			 51-fibonacci-valgrind \
			 61-mutex-valgrind \
			 62-mutex-valgrind \
			 test-priority-valgrind

pthreads: build_test_pthread

graphs: 21-create-many-graph \
				22-create-many-recursive-graph \
				23-create-many-once-graph \
				51-fibonacci-graph

################ COMPIL AVEC NOTRE LIB  ############

## Compilation de libthread.a ##
###############################

$(LIB_DIR)/thread.o: $(SRC_THREAD)/thread.c $(SRC_THREAD)/thread.h
	$(CC) $(CFLAGS) -c $< -o $@ -lrt

$(LIB_DIR)/thread_premp.o: $(SRC_THREAD)/thread.c $(SRC_THREAD)/thread.h
	$(CC) $(CFLAGS) -D PREEMPT -c $< -o $@ -lrt

$(LIB_DIR)/thread_head.o: $(SRC_THREAD)/thread.c $(SRC_THREAD)/thread.h
	$(CC) $(CFLAGS) -D HEAD -c $< -o $@ -lrt

$(LIB_DIR)/libthread.a : $(LIB_DIR)/thread.o
	ar crs $@ $<
	rm $(LIB_DIR)/thread.o

$(LIB_DIR)/libthread_premp.a : $(LIB_DIR)/thread_premp.o
	ar crs $@ $<
	rm $(LIB_DIR)/thread_premp.o

$(LIB_DIR)/libthread_head.a : $(LIB_DIR)/thread_head.o
	ar crs $@ $<
	rm $(LIB_DIR)/thread_head.o

######## Creation des .o ########
#################################

$(BIN_DIR)/%.o : $(SRC_TEST)/%.c $(SRC_THREAD)/thread.h
	$(CC) $(CFLAGS) -c $< -o $@ -I$(SRC_THREAD)

######## Link avec la lib ########
##################################

$(BIN_DIR)/% : $(BIN_DIR)/%.o $(LIB_DIR)/libthread.a
	$(CC) $(CFLAGS) -o $@ $< -lthread -L$(LIB_DIR) -lrt

$(BIN_DIR)/%-premp : $(BIN_DIR)/%.o $(LIB_DIR)/libthread_premp.a
	$(CC) $(CFLAGS) -o $@ $< -lthread_premp -L$(LIB_DIR) -lrt

$(BIN_DIR)/%-head : $(BIN_DIR)/%.o $(LIB_DIR)/libthread_head.a
	$(CC) $(CFLAGS) -o $@ $< -lthread_head -L$(LIB_DIR) -lrt

################ COMPIL AVEC PTHREAD  ############

$(BIN_DIR)/%.pthread.o : $(SRC_TEST)/%.c $(SRC_THREAD)/thread.h
	$(CC_PTHREAD) $(CFLAGS) -c $< -o $@ -I$(SRC_THREAD)

$(BIN_DIR)/%-pthread: $(BIN_DIR)/%.pthread.o
	$(CC_PTHREAD) $(CFLAGS) -o $@ $< -lpthread



clean:
	rm -rf $(BUILD_DIR)
