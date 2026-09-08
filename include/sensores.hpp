#pragma once
#include "sensor.hpp"
#include <cmath>

class SensorNivel : public Sensor {
    double valor_ = 50.0;
public:
    explicit SensorNivel(std::string tag) : Sensor(std::move(tag)) {}
    double valor() const override { return valor_; }
    std::string unidade() const override { return "%"; }
    bool atualizar(double leitura) override {
        if (!std::isfinite(leitura) || leitura < 0 || leitura > 100) return false;
        valor_ = leitura;
        return true;
    }
    bool emAlerta() const override {
        // TODO: substituir o marcador pelo comportamento contratado.
        return false;
    }
};

class SensorTemperatura : public Sensor {
    double valor_ = 25.0;
public:
    explicit SensorTemperatura(std::string tag) : Sensor(std::move(tag)) {}
    double valor() const override { return valor_; }
    std::string unidade() const override { return "C"; }
    bool atualizar(double leitura) override {
        if (!std::isfinite(leitura) || leitura < -40 || leitura > 125) return false;
        valor_ = leitura;
        return true;
    }
    bool emAlerta() const override {
        // TODO: substituir o marcador pelo comportamento contratado.
        return false;
    }
};

class SensorPressao : public Sensor {
    double valor_ = 1.0;
public:
    explicit SensorPressao(std::string tag) : Sensor(std::move(tag)) {}
    double valor() const override { return valor_; }
    std::string unidade() const override { return "bar"; }
    bool atualizar(double leitura) override {
        // TODO ETAPA 02: validar antes de alterar o estado.
        (void)leitura;
        return false;
    }
    bool emAlerta() const override {
        // TODO: substituir o marcador pelo comportamento contratado.
        return false;
    }
};

