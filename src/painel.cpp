#include "painel.hpp"
#include <iomanip>
#include <sstream>

std::string linhaPainel(const Sensor& sensor) {
    // TODO ETAPA 01: consultar somente o contrato Sensor.
    return sensor.tag() + ": PENDENTE";
}
