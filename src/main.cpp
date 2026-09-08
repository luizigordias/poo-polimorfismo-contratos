#include "painel.hpp"
#include "sensores.hpp"
#include <iostream>
int main() {
    SensorNivel nivel{"LT-101"};
    SensorTemperatura temperatura{"TT-201"};
    SensorPressao pressao{"PT-301"};
    nivel.atualizar(15);
    temperatura.atualizar(15);
    pressao.atualizar(8.5);
    std::cout << linhaPainel(nivel) << '\n';
    std::cout << linhaPainel(temperatura) << '\n';
    std::cout << linhaPainel(pressao) << '\n';
}
