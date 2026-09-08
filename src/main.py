from sensores import SensorNivel, SensorTemperatura, SensorPressao
from painel import linha_painel

nivel = SensorNivel("LT-101")
temperatura = SensorTemperatura("TT-201")
pressao = SensorPressao("PT-301")
nivel.atualizar(15)
temperatura.atualizar(15)
pressao.atualizar(8.5)
print(linha_painel(nivel))
print(linha_painel(temperatura))
print(linha_painel(pressao))
