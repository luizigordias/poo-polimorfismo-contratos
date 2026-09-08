from math import isfinite
import inspect
import sys
import unittest
from sensores import Sensor, SensorNivel, SensorTemperatura, SensorPressao
from painel import linha_painel

ETAPA = sys.argv.pop() if sys.argv[-1] in ("01", "02") else "01"

class SensorTeste(Sensor):
    """Sensor de teste com faixa de entrada igual aos numeros finitos."""
    def __init__(self):
        super().__init__("TESTE")
        self.v = 3.5
    def valor(self): return self.v
    def unidade(self): return "u"
    def atualizar(self, leitura):
        if not isfinite(leitura):
            return False
        self.v = leitura
        return True
    def em_alerta(self): return self.v > 4

class Contrato(unittest.TestCase):
    def verificar(self, sensor, minimo, maximo, unidade):
        tag = sensor.tag
        self.assertEqual(sensor.unidade(), unidade)
        for leitura in (minimo, maximo, (minimo + maximo)/2):
            with self.subTest(sensor=tag, leitura=leitura):
                self.assertIs(sensor.atualizar(leitura), True, "aceitar leitura valida")
                self.assertEqual(sensor.valor(), leitura)
                antes, alerta = sensor.valor(), sensor.em_alerta()
                self.assertIs(type(alerta), bool)
                self.assertEqual(sensor.em_alerta(), alerta)
                self.assertEqual(sensor.valor(), antes, "consulta nao pode alterar leitura")
                for invalido in (minimo-1, maximo+1, float("inf"), -float("inf"), float("nan")):
                    self.assertIs(sensor.atualizar(invalido), False, "rejeitar leitura invalida")
                    self.assertEqual(sensor.valor(), antes, "preservar ultima leitura valida")
                    self.assertEqual(sensor.em_alerta(), alerta)
                self.assertEqual(sensor.tag, tag)

    def verificar_alertas(self, sensor, casos):
        for leitura, esperado in casos:
            with self.subTest(sensor=sensor.tag, leitura=leitura):
                self.assertTrue(sensor.atualizar(leitura))
                self.assertIs(sensor.em_alerta(), esperado, "regra de alerta incorreta")

    def test_01_contrato(self):
        self.assertTrue(inspect.isabstract(Sensor))
        with self.assertRaises(TypeError): Sensor("X")
        n, t = SensorNivel("LT-101"), SensorTemperatura("TT-201")
        self.assertEqual((n.valor(), t.valor()), (50, 25))
        self.verificar(n, 0, 100, "%")
        self.verificar(t, -40, 125, "C")
        self.verificar_alertas(n, [(0, True), (19.9, True), (20, False), (20.1, False), (100, False)])
        self.verificar_alertas(t, [(-40, False), (44.9, False), (45, False), (45.1, True), (125, True)])
        n.atualizar(15); t.atualizar(15)
        self.assertEqual(linha_painel(n), "LT-101: 15.0 % | ALERTA")
        self.assertEqual(linha_painel(t), "TT-201: 15.0 C | OK")
        probe = SensorTeste()
        self.assertEqual(linha_painel(probe), "TESTE: 3.5 u | OK")
        probe.atualizar(5)
        self.assertEqual(linha_painel(probe), "TESTE: 5.0 u | ALERTA")

    @unittest.skipUnless(ETAPA == "02", "extensao reservada a etapa 02")
    def test_02_pressao(self):
        p = SensorPressao("PT-301")
        self.assertEqual(p.valor(), 1)
        self.verificar(p, 0, 10, "bar")
        self.verificar_alertas(p, [(0, False), (7.9, False), (8, False), (8.1, True), (10, True)])
        p.atualizar(8.5)
        self.assertEqual(linha_painel(p), "PT-301: 8.5 bar | ALERTA")

if __name__ == "__main__": unittest.main(verbosity=2)
