# Monitoramento Urbano com ESP32, Node-RED, InfluxDB e Grafana

📌 Descrição do Projeto

Este projeto tem como objetivo monitorar o fluxo urbano utilizando microcontroladores ESP32 com sensores (ultrassônico e infravermelho) e enviar os dados para uma infraestrutura em nuvem composta por Node-RED, InfluxDB e Grafana. A proposta é auxiliar planos diretores urbanos por meio da coleta e análise de dados sobre a movimentação em determinados pontos da cidade.

⚙️ Tecnologias Utilizadas

ESP32 DevKit V4

Sensor Ultrassônico HC-SR04

Sensor PIR (Infravermelho)

Node-RED (EC2 AWS)

Broker MQTT público (HiveMQ)

InfluxDB Cloud

Grafana Cloud

🧩 Estrutura do Projeto

Cada ESP32 representa uma "estação" urbana.

Os sensores coletam os dados de distância e passagem de pessoas.

Os dados são publicados via MQTT no formato JSON:

{
  "distancia": 125.5,
  "passagens": 3,
  "estacao": "estacao1",
  "rota": "centro-norte"
}

O Node-RED recebe e separa os dados por tipo e envia para o InfluxDB com os campos e tags apropriados.

O Grafana consulta os dados do InfluxDB e exibe dashboards dinâmicos.

🚀 Como Executar o Projeto

ESP32 (Wokwi ou Físico)

Configure o código com as credenciais MQTT e Wi-Fi.

Publique os dados no tópico: TESTMACK1870/<estacao>/resumo

Node-RED

Conecte ao broker HiveMQ (broker.hivemq.com:1883)

Use um mqtt in com tópico: TESTMACK1870/+/resumo

A função deve processar o JSON e criar duas saídas (distância e passagens), cada uma com:

measurement: distancia ou passagens

field: value

tags: estacao, rota

Utilize dois nós influxdb out, apontando para o bucket Projeto no InfluxDB Cloud.

InfluxDB

Bucket: Projeto

Measurements: distancia, passagens

Campos: value

Tags: estacao, rota

Grafana

Configure o InfluxDB Cloud como fonte de dados

Crie os seguintes painéis:

Gauge: Passagens por estação (últimos 5 minutos)

Line Chart: Distância detectada ao longo do tempo

Bar Chart: Comparativo de passagens por rota

📊 Exemplo de Query (Flux)

from(bucket: "Projeto")
  |> range(start: -1h)
  |> filter(fn: (r) => r._measurement == "distancia" and r._field == "value" and r.estacao == "estacao1")

📎 Requisitos de Funcionalidade

Conexão Wi-Fi do ESP32

Comunicação com o broker MQTT

Leitura de sensores ultrassônico e PIR

Publicação em JSON com identificação da estação

Processamento no Node-RED

Armazenamento no InfluxDB com registros temporais

Visualização no Grafana
