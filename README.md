# TCC - Painel de Ônibus Inteligente utilizando redes sem fio de longo alcance

Este repositório armazena os códigos de uso dos módulos necessários para o desenvolvimento do sistema embarcado do TCC.
HW: Possui os códigos do painel inteligente e do gateway
SW: Possui o código que simula a movimentação de duas linhas de ônibus e o código que atualiza a página web

<p align="center">
  <a href="#objetivo">Objetivo</a> • 
  <a href="#proposta">Proposta</a> • 
  <a href="#tecnologias">Tecnologias</a> • 
  <a href="#composição">Composição</a> • 
  <a href="#status">Status</a>
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


<p align="center">
  <img width="410" height="229" src="https://github.com/gabrielsilvar/tcc_final/blob/main/lora.png">
</p>

Os códigos ebytereceiver e ebytesender são relacionados às antenas LoRa.
O código dentro da pasta epd2in13-busdisp é o código do display e-ink. Ainda estou vendo como funciona. Já tenho noção do funcionamento básico, e é interessante como ele permite tanto a atualização total, como parcial, da tela.

> Transmissor/Receptor de dados LoRa:

Link: http://www.ebyte.com/en/product-view-news.aspx?id=131
Frequência: 915MHz     | Potência Transmissão: 10-20dBm
Taxa de dados: 2.4kbps | Distância máxima teste: 3000 m
Tamanho: 21 mm x 36 mm | Tipo de antena: SMA-K

Outras infomações técnicas no website.

Pinagem:

<p align="center">
  <img width="460" height="235" src="https://raw.githubusercontent.com/gabrielsilvar/Arduino/master/loramodule.png">
</p>
Foto do modulo 915T20D

1:M0 | 2:M1 | 3:RXD | 4:TXD | 5:AUX | 6:VCC | 7:GND

M0 e M1 são controlados no microcontrolador para decidir os modos de operação. Em caso de dúvida, para o teste inicial, só coloque GND nos dois pinos, já que não podem ficar flutuando.
RX e TX são os pinos UART usados para tráfego de dados com o microcontrolador. Pode configurar como dreno aberto ou pull-up (RXD), ou pushpull (TXD).
AUX pode ser usado para acordar o microcontrolador durante a inicialização do equipamento. Pode ficar flutuando.
VCC: aceita 2.3V a 5.2V (use 3V3 ou 5V)
GND: ground.


> Display e-ink:

Link: https://www.waveshare.com/wiki/2.13inch_e-Paper_HAT

Este módulo é uma tela com tecnologia que utiliza "mini esferas" com pigmentos de cor, que ficam suspensas no painel e movem-se de acordo com a carga eletrônica aplicada nas mesmas. Os e-Papers (papéis eletrônicos) refletem a luz ambiente, então não necessitam de luz atrás da tela. Quando mais iluminação ambiente, maior a qualidade de visualização, especialmente na luz do sol. O ângulo de visão também é muito bom, de 180 graus. Esta tecnologia é excelente para painéis de dispositivos focados em leitura, como os e-Readers (por exemplo, o Kindle, da Amazon, ou o Kobo Aura, da Kobo).
Outra vantagem está no gasto energético. Estes painéis só gastam energia quando precisam atualizar o conteúdo exibido. Depois de atualizar a tela, não gastam energia; portanto, para aplicações em que não necessita de alta taxa de atualização de dados em telas, consegue-se otimizar ainda mais o consumo energético do dispositivo.


Dica para fazer um README melhor: https://medium.com/@raullesteves/github-como-fazer-um-readme-md-bonit%C3%A3o-c85c8f154f8

Guia rápido para alinhar imagens no GitHub: https://gist.github.com/DavidWells/7d2e0e1bc78f4ac59a123ddf8b74932d
