CC=g++
STD=-std=c++17
WWW=
WWW=-Wall -Wextra -Werror
ifeq ($(OS),Windows_NT)
TESTFLAGS= -pthread -lstdc++
else
TESTFLAGS= -lgtest -pthread -lstdc++ -lgtest_main
endif
GA=graph_algorithms/ant.cc

all: test start
	$(GA)

s21_graph.a:
	@$(CC) $(STD) $(WWW) -c ./graph/s21_graph.cc -o s21_graph.o
	@ar rcs s21_graph.a s21_graph.o

search.o:
	@$(CC) $(STD) $(WWW) -c graph_algorithms/search.cc

shortest_path.o:
	@$(CC) $(STD) $(WWW) -c graph_algorithms/shortest_path.cc

spanning_tree.o:
	@$(CC) $(STD) $(WWW) -c graph_algorithms/spanning_tree.cc

genetic.o:
	@$(CC) $(STD) $(WWW) -c graph_algorithms/genetic.cc

salesman_problem_annealing.o:
	@$(CC) $(STD) $(WWW) -c graph_algorithms/tsm_helper.cc graph_algorithms/salesman_problem_annealing.cc

salesman_problem_ant.o:
	@$(CC) $(STD) $(WWW) -c graph_algorithms/salesman_problem_ant.cc


s21_graph_algorithms.a: search.o shortest_path.o spanning_tree.o salesman_problem_annealing.o salesman_problem_ant.o genetic.o
	@$(CC) $(STD) $(WWW) -c ./graph_algorithms/s21_graph_algorithms.cc
	@ar rcs s21_graph_algorithms.a search.o shortest_path.o spanning_tree.o salesman_problem_annealing.o salesman_problem_ant.o tsm_helper.o genetic.o s21_graph_algorithms.o

tests: test

test: clean s21_graph.a s21_graph_algorithms.a
	@$(CC) $(STD) $(WWW) ./tests/test.cc s21_graph.a s21_graph_algorithms.a $(TESTFLAGS) -o test
	./test

build: clean s21_graph.a s21_graph_algorithms.a
	@$(CC) $(STD) $(WWW) main.cc view/ConsoleView.cc s21_graph.a s21_graph_algorithms.a  $(TESTFLAGS) -o SimpleNavigator

start: build
	./SimpleNavigator

lint: clean
	@clang-format --style=Google -i ./*/*h ./*/*cc
	@clang-format --style=Google -n ./*/*h ./*/*cc

lcov: clean
	@$(CC) $(STD) $(WWW)  ./graph/s21_graph.cc graph_algorithms/*.cc ./tests/test.cc -fprofile-arcs -ftest-coverage $(TESTFLAGS) -o test
	@./test
	@lcov --no-external -c -d . -o tests.info
	@genhtml tests.info -o report
	@open report/index.html
	@rm -rf *.gcda *.gcno *.info

clean:
ifeq ($(OS),Windows_NT)
	del *.a *.o test *.gcda *.gcno *.info *.out report SimpleNavigator.exe
else
	@rm -rf *.a *.o test *.gcda *.gcno *.info *.out report SimpleNavigator
endif

.PHONY: test
