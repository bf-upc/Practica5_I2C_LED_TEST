# 🖥️ ESP32-S3 OLED SSD1306 Demo (Práctica 5)

[![PlatformIO](https://img.shields.io/badge/PlatformIO-ESP32--S3-blue)](https://platformio.org/)
[![Framework](https://img.shields.io/badge/Framework-Arduino-00979D)](https://www.arduino.cc/)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)

Demostración completa de las capacidades gráficas de una pantalla **OLED SSD1306 (128x64 píxeles)** controlada por un microcontrolador **ESP32-S3** a través del protocolo **I2C**, utilizando las bibliotecas **Adafruit GFX** y **Adafruit SSD1306**.

El proyecto implementa una secuencia de 12 escenas que muestran desde formas geométricas básicas hasta animaciones y paneles de control simulados.

![Demo Animada](https://via.placeholder.com/800x200/007BFF/FFFFFF?text=ESP32-S3+SSD1306+Demo+Scenes) <!-- Reemplazar por un GIF real si está disponible -->

---

## 📋 Tabla de Contenidos

- [Características](#-características)
- [Requisitos de Hardware](#-requisitos-de-hardware)
- [Conexiones](#-conexiones-i2c)
- [Configuración del Software](#-configuración-del-software)
- [Estructura del Proyecto](#-estructura-del-proyecto)
- [Escenas de Demostración](#-escenas-de-demostración)
- [Cómo Compilar y Cargar](#-cómo-compilar-y-cargar)
- [Uso](#-uso)
- [Posibles Mejoras](#-posibles-mejoras)
- [Licencia](#-licencia)

---

## ✨ Características

- **12 escenas** secuenciales que cubren la mayoría de las funciones de la biblioteca:
  - Texto con diferentes tamaños.
  - Modo de color invertido.
  - Gráficos geométricos (rectas, círculos, triángulos, píxeles).
  - Mapas de bits almacenados en PROGMEM (corazón 16x16, carita 8x8).
  - Scroll por hardware (horizontal y diagonal).
  - Gráficas simples de barras y líneas con ejes y cuadrícula.
  - Barra de progreso animada.
  - Animación de una pelota rebotando (~60 FPS).
  - Dashboard simulado con datos dinámicos (temperatura, humedad, señal WiFi RSSI).
  - Efecto de texto "máquina de escribir".
- Uso de pines I2C personalizables.
- Código modular y bien comentado (en español).

---

## 🛠️ Requisitos de Hardware

| Componente | Cantidad | Descripción |
| :--- | :---: | :--- |
| **ESP32-S3** | 1 | Placa de desarrollo (probado en RYMCU ESP32-S3 DevKitC-1). |
| **OLED SSD1306** | 1 | Módulo I2C de 0.96 pulgadas, resolución 128x64. |
| **Cables jumper** | 4 | Macho-Hembra o Hembra-Hembra. |
| **Cable USB** | 1 | Para alimentación y programación. |
| Protoboard (opcional) | 1 | Para montaje organizado. |

---

## 🔌 Conexiones I2C

Conecta los pines de la pantalla OLED al ESP32-S3 según esta tabla:

| OLED SSD1306 | ESP32-S3 Pin |
| :--- | :--- |
| **VCC** | 3.3V |
| **GND** | GND |
| **SDA** | GPIO 8 |
| **SCL** | GPIO 9 |

*Nota: Los pines `SDA` y `SCL` se pueden modificar en el código (`SDA_PIN` y `SCL_PIN`). La dirección I2C por defecto es `0x3C`.*

---

## ⚙️ Configuración del Software

### Dependencias (PlatformIO)

Las bibliotecas se manejan automáticamente con `platformio.ini`:

```ini
[env:rymcu-esp32-s3-devkitc-1]
platform = espressif32
board = rymcu-esp32-s3-devkitc-1
framework = arduino
monitor_speed = 115200
lib_deps = 
    adafruit/Adafruit SSD1306@^2.5.16
    adafruit/Adafruit GFX Library
```

### Parámetros Principales en Código

```cpp
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define SDA_PIN       8    // Pin SDA del I2C
#define SCL_PIN       9    // Pin SCL del I2C
#define OLED_ADDR     0x3C // Dirección I2C del módulo OLED
#define OLED_RESET    -1   // Sin pin de reset dedicado
```

---

## 🗂️ Estructura del Proyecto

```
Practica5_I2C_LED_TEST/
├── src/
│   └── main.cpp          # Código principal con todas las escenas
├── platformio.ini        # Configuración del entorno de compilación
├── .gitignore            # Archivos a ignorar por Git
└── README.md
```

---

## 🎬 Escenas de Demostración

El programa ejecuta un bucle continuo mostrando las siguientes escenas:

| # | Escena | Función Principal | Duración Aprox. |
| :-: | :--- | :--- | :---: |
| 1 | **Splash** | Limpia pantalla, muestra un marco y texto de bienvenida ("ESP32-S3 SSD1306 DEMO"). | 3 s |
| 2 | **Tamaños de Texto** | Imprime líneas con `setTextSize(1)`, `(2)` y `(3)` para comparar fuentes. | 3 s |
| 3 | **Color Invertido** | Alterna fondos blanco/negro y texto negro/blanco cada 500 ms (4 ciclos). | 3 s |
| 4 | **Formas Geométricas** | Tres subescenas que dibujan rectángulos, círculos, triángulos y líneas de píxeles. | ~7.5 s total |
| 5 | **Bitmaps** | Dibuja dos corazones y cuatro caritas desde arrays PROGMEM. | 3 s |
| 6 | **Scroll Hardware** | Desplaza el contenido de la pantalla hacia la derecha, izquierda y en diagonal usando funciones nativas del controlador. | ~10 s |
| 7 | **Gráfica de Barras** | Dibuja un gráfico de barras simple a partir de los datos del array `barData[]`, con ejes X e Y. | 3 s |
| 8 | **Gráfica de Líneas** | Dibuja un gráfico de líneas con puntos y cuadrícula punteada a partir de `lineData[]`. | 3 s |
| 9 | **Barra de Progreso** | Anima una barra de carga redondeada con porcentaje numérico de 0% a 100%. | ~2.2 s |
| 10 | **Animación Pelota** | Simula una pelota rebotando dentro de un marco a ~60 FPS durante 2 segundos. | 2 s |
| 11 | **Dashboard** | Panel simulado de IoT con temperatura, humedad y barras de señal WiFi RSSI actualizándose. | 4 s |
| 12 | **Typewriter** | Escribe un texto de 4 líneas con un efecto de máquina de escribir. | ~4 s |

*El bucle se repite indefinidamente.*

---

## 🚀 Cómo Compilar y Cargar

1.  Asegúrate de tener [Visual Studio Code](https://code.visualstudio.com/) con la extensión [PlatformIO](https://platformio.org/install/ide?install=vscode) instalada.
2.  Clona este repositorio:
    ```bash
    git clone https://github.com/bf-upc/Practica5_I2C_LED_TEST.git
    ```
3.  Abre la carpeta del proyecto en VSCode.
    *   PlatformIO detectará automáticamente el archivo `platformio.ini` y descargará las bibliotecas.
4.  Conecta tu placa ESP32-S3 al PC mediante el cable USB.
5.  Haz clic en el botón **Upload** (→) de la barra inferior de PlatformIO. Compilará y cargará el código en la placa.
6.  Si encuentras problemas, verifica los pines en el código y la dirección I2C.

---

## 🖥️ Uso

Una vez cargado el programa, la secuencia de escenas comenzará a ejecutarse automáticamente en bucle. Puedes abrir el monitor serie (115200 baudios) para observar mensajes de error, aunque la interacción principal es visual.

---

## 💡 Posibles Mejoras

-   [ ] Añadir un sensor real DHT11/DHT22 para mostrar datos en el dashboard.
-   [ ] Implementar un menú interactivo con botones físicos para saltar entre escenas.
-   [ ] Usar una imagen del ESP32-S3 o un logotipo personalizado como bitmap de bienvenida.
-   [ ] Incluir más tipos de gráficos (velocímetro, gráfico de pastel).
-   [ ] Agregar efectos de transición más suaves entre escenas (fade, wipe).



