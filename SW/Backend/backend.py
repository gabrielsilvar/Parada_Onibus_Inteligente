import paho.mqtt.client as mqtt     # Para coletar os dados de temperatura
import time                         # Para pegar a hora e dia precisos
import csv                          # Para armazenar os dados do painel
import folium                       # Para o mapa

painel = 0
l020 = 0
l075 = 0
la075 = ''
lo075 = ''
la020 = ''
lo020 = ''
temperatura = ''
umidade = ''

try:
    open('dados_paineis.csv', 'r')
except IOError:
    print("Arquivo nao existe. Será criado.")
    with open('dados_paineis.csv', 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["Latitude", "Longitude", "Temperatura", "Umidade", "Data", "Hora"])


def escreve_csv(dados):
    #print(dados)
    with open('dados_paineis.csv', 'a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow([dados[0:9], dados[10:20],
                         dados[21:25], dados[26:30],
                         dados[31:41], dados[42:50]]) # AJEITAR ESTA MIERDA

def on_message(client, userdata, message):
    global painel, l020, l075, lat020, lon020, lat075, lon075, temperatura, umidade
    print("message received= ", str(message.payload.decode("utf-8")))
    print("message topic=", message.topic)
    #print("message qos=", message.qos)
    #print("message retain flag=", message.retain)

    recebido = str(message.payload.decode("utf-8"))

    if(message.topic == "sistema/pontobus"):
        temperatura = recebido[21:25]
        umidade = recebido[26:30]
        escreve_csv(recebido + time.strftime(',%d/%m/%Y,%H:%M:%S', time.localtime()))
        painel = 1

    if (message.topic == "sistema/linha/020"):
        lat020 = recebido[0:9]
        lon020 = recebido[10:20]
        l020 = 1

    if (message.topic == "sistema/linha/075"):
        lat075 = recebido[0:9]
        lon075 = recebido[10:20]
        l075 = 1

    if(painel == 1 and l020 == 1 and l075 == 1):
        mapa = folium.Map(  # Criando o mapa
            location=[-3.738770, -38.569295]
            # ,tiles="Stamen Toner"
            , zoom_start=12
        )
        folium.Marker(
            [-3.738770, -38.569295]
            , popup='Ponto de Ônibus'
            , tooltip='Temperatura:' + temperatura + ' Umidade: ' + umidade
        ).add_to(mapa)
        folium.Marker(
            [lat020, lon020]
            , popup='Linha: 020'
            , tooltip='Campus Pici Interno'
            , icon=folium.Icon(color='green')
        ).add_to(mapa)
        folium.Marker(
            [lat075, lon075]
            , popup='Linha: 075'
            , tooltip='Campus do Pici Unifor'
            , icon=folium.Icon(color='red')
        ).add_to(mapa)
        mapa.save("mapadeteste.html")
        print("> Mapa Atualizado.")

# clia um cliente para supervisã0
client = mqtt.Client(client_id='backend',
                     protocol=mqtt.MQTTv31)
#conecta a funcao de callback la de cima
client.on_message = on_message

# conecta no broker
client.connect("broker.hivemq.com", port=1883)

#inicia o loop
#client.loop_start()

# se inscrever no topico
client.subscribe("sistema/pontobus")
client.subscribe("sistema/linha/020")
client.subscribe("sistema/linha/075")

#time.sleep(4) #esperar
#client.loop_stop()
# permace em loop, recebendo mensagens
client.loop_forever()
