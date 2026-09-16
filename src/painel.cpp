#include "painel.hpp"
#include <iomanip>
#include <sstream>
#include <format>

std::string linhaPainel(const Sensor& sensor) {
    // TODO ETAPA 01: consultar somente o contrato Sensor.
    std::ostringstream streamValor;
    streamValor << std::fixed << std::setprecision(1) << sensor.valor();

    return sensor.tag() + ": " + streamValor.str() + " " + sensor.unidade() + " | " + (sensor.emAlerta() ? "ALERTA" : "OK");
}
