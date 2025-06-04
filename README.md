# Projeto IoT - Monitoramento de Fluxo Urbano com ESP32, MQTT, Node-RED e Grafana

Este projeto visa simular um sistema de monitoramento de fluxo urbano utilizando microcontroladores ESP32 e sensores, com envio de dados para um dashboard em tempo real via Node-RED, InfluxDB e Grafana.

---

## 🔧 Tecnologias Utilizadas

- **ESP32 (simulado no Wokwi)**
- **Sensor Ultrassônico HC-SR04**
- **Sensor PIR (Infravermelho)**
- **MQTT (Broker: HiveMQ)**
- **Node-RED**
- **InfluxDB Cloud**
- **Grafana**

---

## 📡 Funcionamento

1. **Coleta de Dados**  
   O ESP32 coleta:
   - A distância de objetos através do sensor HC-SR04
   - A contagem de passagens com sensor PIR

2. **Publicação MQTT**  
   Os dados são publicados no broker HiveMQ nos tópicos:
   ```
   TESTMACK1870/estacao1/resumo
   ```
   Com payload JSON:
   ```json
   {
     "distancia": 120,
     "passagens": 4,
     "estacao": "estacao1",
     "rota": "leste"
   }
   ```

3. **Node-RED**  
   - Recebe os dados via `mqtt in`
   - Processa os dados com uma `function node`
   - Envia para o InfluxDB com as medições `distancia` e `passagens`, adicionando tags `estacao` e `rota`

4. **Armazenamento**  
   Dados enviados para:
   - Bucket: `Projeto`
   - Tags: `estacao`, `rota`
   - Campos: `value`

5. **Visualização (Grafana)**  
   Dashboards com:
   - Gráfico de linha para distância ao longo do tempo
   - Contador acumulado de passagens
   - Filtros por estação e rota

---

## 📂 Organização do Repositório

- `/Wokwi/.ino`: Código Arduino para ESP32
- `/node-red/`: Fluxo exportado da interface Node-RED (.json)

---

## ✅ Status

Projeto finalizado com simulações no ambiente Wokwi e dashboards operando em tempo real com Grafana.

---

Mackenzie - Projeto de IoT - Sistemas de Informação
