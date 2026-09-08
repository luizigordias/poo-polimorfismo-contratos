from abc import ABC, abstractmethod
from math import isfinite


class Sensor(ABC):
    def __init__(self, tag: str):
        self._tag = tag

    @property
    def tag(self):
        return self._tag

    @abstractmethod
    def valor(self):
        raise NotImplementedError

    @abstractmethod
    def unidade(self):
        raise NotImplementedError

    @abstractmethod
    def atualizar(self, leitura):
        raise NotImplementedError

    @abstractmethod
    def em_alerta(self):
        raise NotImplementedError


class SensorNivel(Sensor):
    def __init__(self, tag):
        super().__init__(tag)
        self._valor = 50.0

    def valor(self):
        return self._valor

    def unidade(self):
        return "%"

    def atualizar(self, leitura):
        if not isfinite(leitura) or leitura < 0 or leitura > 100:
            return False
        self._valor = leitura
        return True

    def em_alerta(self):
        # TODO: substituir o marcador pelo comportamento contratado.
        return False


class SensorTemperatura(Sensor):
    def __init__(self, tag):
        super().__init__(tag)
        self._valor = 25.0

    def valor(self):
        return self._valor

    def unidade(self):
        return "C"

    def atualizar(self, leitura):
        if not isfinite(leitura) or leitura < -40 or leitura > 125:
            return False
        self._valor = leitura
        return True

    def em_alerta(self):
        # TODO: substituir o marcador pelo comportamento contratado.
        return False


class SensorPressao(Sensor):
    def __init__(self, tag):
        super().__init__(tag)
        self._valor = 1.0

    def valor(self):
        return self._valor

    def unidade(self):
        return "bar"

    def atualizar(self, leitura):
        # TODO ETAPA 02: validar antes de alterar o estado.
        return False

    def em_alerta(self):
        # TODO: substituir o marcador pelo comportamento contratado.
        return False
