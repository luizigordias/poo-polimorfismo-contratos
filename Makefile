CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -pedantic -Iinclude
.PHONY: build run test
build:
	mkdir -p build
	$(CXX) $(CXXFLAGS) src/main.cpp src/painel.cpp -o build/painel
run: build
	./build/painel
	PYTHONPATH=src python3 src/main.py
test: build
	@case "$(ETAPA)" in 01|02) ;; *) echo "Use make test ETAPA=01 ou ETAPA=02"; exit 2;; esac
	$(CXX) $(CXXFLAGS) tests/contrato.cpp src/painel.cpp -o build/contrato
	./build/contrato $(ETAPA)
	PYTHONPATH=src python3 tests/contrato.py $(ETAPA)
