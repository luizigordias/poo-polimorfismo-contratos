from sensores import Sensor


def linha_painel(sensor: Sensor) -> str:
    # TODO ETAPA 01: consultar somente o contrato Sensor.
    return f"{sensor.tag}: {sensor.valor():.1f} {sensor.unidade()} | {'ALERTA' if sensor.em_alerta() else 'OK'}"
