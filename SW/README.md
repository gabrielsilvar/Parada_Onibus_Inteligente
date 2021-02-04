# Implementação do Simulador de rotas de ônibus e do Back-End

- A pasta Backend contém os códigos em python que atualizam o mapa e uma página HTML para visualizar o mapa com as informações no navegador. Módulos utilizados:
  - CSV: armazena dados climáticos enviados pelos painéis
  - Folium: biblioteca de mapas. Pode-se criar um mapa e atualizá-lo.
  - Paho: cliente MQTT para python
  - Time: biblioteca para utilizar recursos de data e hora.
- A pasta SimuladorGPSonibus contém os códigos que simulam o movimento dos ônibus nos trajetos usuais. Módulos utilizados:
  - Paho: cliente MQTT para python
  - Time: utiliza-se os recursos de data e hora da mesma.

O sistema utiliza duas antenas LoRa, da empresa CDEByte, com o chip SX1276, calibrado para a frequência de 915MHz. 

O código backend.py se inscreve em todos os tópicos MQTT das linhas de ônibus, e todos os tópicos MQTT dos painéis inteligentes. Ele recebe as coordenadas de cada linha, os dados climáticos de cada painel, e atualiza o mapa. Além disso, os dados climáticos são salvos em um csv para consulta futura.

<p align="center">
  <img width="30%" height="30%" src="https://github.com/gabrielsilvar/tcc_final/blob/main/SW/csv.PNG">
</p>
Foto do arquivo csv que armazena os dados climáticos.

<p align="center">
  <img width="30%" height="30%" src="https://github.com/gabrielsilvar/tcc_final/blob/main/SW/paginainicial.png">
</p>
Foto da página inicial.
