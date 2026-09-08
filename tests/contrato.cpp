#include "sensores.hpp"
#include "painel.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <type_traits>

void exigir(bool ok, const std::string& mensagem) {
    if (!ok) { std::cerr << "FALHA: " << mensagem << '\n'; std::exit(1); }
}
void verificar(Sensor& sensor, double minimo, double maximo, const std::string& unidade) {
    const auto tag = sensor.tag();
    exigir(sensor.unidade() == unidade, tag + ": unidade incorreta");
    for (double leitura : {minimo, maximo, (minimo + maximo)/2}) {
        exigir(sensor.atualizar(leitura), tag + ": deve aceitar leitura valida " + std::to_string(leitura));
        exigir(sensor.valor() == leitura, tag + ": deve guardar leitura aceita");
        const double antes = sensor.valor();
        const bool alerta = sensor.emAlerta();
        exigir(sensor.emAlerta() == alerta && sensor.valor() == antes, tag + ": consulta deve ser estavel e sem mutacao");
        for (double invalido : {minimo-1, maximo+1, std::numeric_limits<double>::infinity(),
                               -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::quiet_NaN()}) {
            exigir(!sensor.atualizar(invalido), tag + ": deve rejeitar leitura invalida");
            exigir(sensor.valor() == antes && sensor.emAlerta() == alerta, tag + ": rejeicao deve preservar estado");
        }
        exigir(sensor.tag() == tag, "tag deve permanecer estavel");
    }
}
void alerta(Sensor& sensor, double leitura, bool esperado) {
    exigir(sensor.atualizar(leitura), sensor.tag() + ": leitura do teste deve ser aceita");
    exigir(sensor.emAlerta() == esperado, sensor.tag() + ": alerta incorreto em " + std::to_string(leitura));
}
// Tipo desconhecido do painel: aceita qualquer numero finito na unidade u.
class SensorTeste : public Sensor {
    double valor_ = 3.5;
public:
    SensorTeste() : Sensor("TESTE") {}
    double valor() const override { return valor_; }
    std::string unidade() const override { return "u"; }
    bool atualizar(double v) override {
        if (!std::isfinite(v)) return false;
        valor_ = v;
        return true;
    }
    bool emAlerta() const override { return valor_ > 4; }
};
int main(int argc, char** argv) {
    static_assert(std::is_abstract_v<Sensor>);
    static_assert(std::has_virtual_destructor_v<Sensor>);
    SensorNivel n{"LT-101"}; SensorTemperatura t{"TT-201"};
    exigir(n.valor() == 50 && t.valor() == 25, "valores iniciais devem ser validos");
    verificar(n, 0, 100, "%"); verificar(t, -40, 125, "C");
    for (double v : {0., 19.9}) alerta(n, v, true);
    for (double v : {20., 20.1, 100.}) alerta(n, v, false);
    for (double v : {-40., 44.9, 45.}) alerta(t, v, false);
    for (double v : {45.1, 125.}) alerta(t, v, true);
    n.atualizar(15); t.atualizar(15);
    exigir(linhaPainel(n) == "LT-101: 15.0 % | ALERTA", "painel deve despachar nivel: LT-101: 15.0 % | ALERTA");
    exigir(linhaPainel(t) == "TT-201: 15.0 C | OK", "painel deve despachar temperatura: TT-201: 15.0 C | OK");
    SensorTeste probe;
    exigir(linhaPainel(probe) == "TESTE: 3.5 u | OK", "painel deve aceitar um novo subtipo pelo contrato");
    probe.atualizar(5);
    exigir(linhaPainel(probe) == "TESTE: 5.0 u | ALERTA", "painel deve consultar estado atual do novo subtipo");
    std::cout << "OK C++ etapa 01: contrato, fronteiras e painel\n";
    if (argc > 1 && std::string(argv[1]) == "02") {
        SensorPressao p{"PT-301"};
        exigir(p.valor() == 1, "pressao inicial deve ser 1 bar");
        verificar(p, 0, 10, "bar");
        for (double v : {0., 7.9, 8.}) alerta(p, v, false);
        for (double v : {8.1, 10.}) alerta(p, v, true);
        p.atualizar(8.5);
        exigir(linhaPainel(p) == "PT-301: 8.5 bar | ALERTA", "pressao deve funcionar no mesmo painel");
        std::cout << "OK C++ etapa 02: pressao e regressoes\n";
    }
}
