#pragma once
#include <string>
#include <utility>

class Sensor {
    std::string tag_;
protected:
    explicit Sensor(std::string tag) : tag_(std::move(tag)) {}
public:
    virtual ~Sensor() = default;
    const std::string& tag() const { return tag_; }
    virtual double valor() const = 0;
    virtual std::string unidade() const = 0;
    virtual bool atualizar(double leitura) = 0;
    virtual bool emAlerta() const = 0;
};
