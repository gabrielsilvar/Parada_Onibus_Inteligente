# Implementação do Painel Inteligente e do Gateway

- A pasta TCC_Ardu_Main contém os códigos do painel inteligente. Módulos utilizados:
-- E32-915T20D: Módulo LoRa 915MHz
-- DHT11: Sensor Temperatura e Umidade
-- 2.13" E-Ink display HAT: Tela e-Ink para exibir os dados.
- A pasta TCC_Gateway_Main contém os códigos do gateway. Módulo utilizado:
-- E32-915T20D: Módulo LoRa 915MHz



<p align="center">
  <img width="410" height="229" src="https://github.com/gabrielsilvar/tcc_final/blob/main/lora.png">
</p>

O sistema utiliza duas antenas LoRa, da empresa CDEByte, com o chip SX1276, calibrado para a frequência de 915MHz. 


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