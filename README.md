# TCC - Painel de Ônibus Inteligente utilizando redes sem fio de longo alcance

Este repositório armazena os códigos de uso dos módulos necessários para o desenvolvimento do sistema embarcado do TCC.
HW: Possui os códigos do painel inteligente e do gateway
SW: Possui o código que simula a movimentação de duas linhas de ônibus e o código que atualiza a página web

<p align="center">
  <a href="#objetivo">Objetivo</a> • 
  <a href="#proposta">Proposta</a> • 
  <a href="#tecnologias">Tecnologias</a>
</p>

<h4 align="center">Codificação finalizada. Preparando apresentação. </h4>

### Objetivo

Desenvolver um dispositivo IoT de visualização de dados para mobilidade urbana em Cidades Inteligentes, referente ao tempo de chegada de ônibus em determinada parada de ônibus do seu trajeto. O dispositivo também coleta e exibe dados de umidade do ar e temperatura local, que podem ser enviados ao sistema central para análise.

### Proposta
<p align="center">
  <img width="50%" heigth="30%" src="https://github.com/gabrielsilvar/tcc_final/blob/main/proposta.PNG">
</p>

- O sistema utiliza um painel inteligente, composto por um microcontrolador, um painel e-Ink e um sensor de temperatura e umidade. Ele coleta os dados climáticos e envia para o gateway utilizando a tecnologia LoRa (Long Range).
- O gateway recebe estes dados e os envia para o Back-End, que armazena os dados para futura análise, caso necessário.
- O ônibus envia suas coordenadas para o Back-End e para os gateways interessados, utilizando o protocolo MQTT.
- O gateway recebe os dados de localização das linhas de ônibus, agrupa-os em pacotes e envia ao painel inteligente utilizando a tecnologia LoRa.
- O painel recebe as coordenadas, calcula a distância e o tempo de chegada do ônibus e o exibe na tela.
- O usuário pode conferir quanto tempo leva para o ônibus chegar na parada em que se encontra e decidir se espera na parada.

### Tecnologias
- [LoRa](https://www.semtech.com/lora/what-is-lora)
- [MQTT](https://mqtt.org/)
- [Python](https://www.python.org/)
- C, C++

Para mais informações de implementação, olhar os READMEs das pastas HW e SW.


Dica para fazer um README melhor: https://medium.com/@raullesteves/github-como-fazer-um-readme-md-bonit%C3%A3o-c85c8f154f8

Guia rápido para alinhar imagens no GitHub: https://gist.github.com/DavidWells/7d2e0e1bc78f4ac59a123ddf8b74932d
