# Operação docente

Planejamento: dois encontros de 120 min, detalhados no site. Antes da aula, prepare ferramentas e habilite Actions no fork se a interface solicitar.

A `main` inicial contém TODOs: o workflow executa somente `make run`. Verde na main comprova apenas baseline, não conclusão da atividade. Branch `pratica/01-painel` e seu PR executam `make test ETAPA=01`; `pratica/02-pressao` e seu PR executam `make test ETAPA=02`. A seleção rejeita outros nomes de branches de prática. Não são necessários segredos; token tem apenas leitura do conteúdo.

Depois de integrar, confira a evidência funcional no PR e no SHA testado: a execução da main continua sendo apenas a baseline. O mesmo vale para execução manual na main.

Não publique a solução de referência no starter. Avalie o primeiro incremento guiado e o segundo por adaptação: regra da pressão, limites, rejeição de NaN/infinito, despacho pelo contrato e preservação do cliente. Compare com o artefato que a turma realmente produziu na aula 06; o starter é um recorte, não contém seu controlador nem sua suíte anterior.

Peça ao estudante prever nível=15 e temperatura=15, localizar a chamada virtual, explicar o const C++ e mostrar um caso inválido preservando estado. Em avaliação, use defesa oral curta. Evite ensinar coleções, alocação dinâmica e exceções junto com este incremento.
