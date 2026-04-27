#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SDA_PIN 8
#define SCL_PIN 9
#define OLED_ADDR 0x3C
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ─── Bitmap 16x16 de un corazón ───────────────────────────────────────────
const unsigned char heart_bmp[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x06, 0x60, 0x0F, 0xF0,
  0x1F, 0xF8, 0x3F, 0xFC, 0x7F, 0xFE, 0xFF, 0xFF,
  0xFF, 0xFF, 0x7F, 0xFE, 0x3F, 0xFC, 0x1F, 0xF8,
  0x0F, 0xF0, 0x07, 0xE0, 0x03, 0xC0, 0x01, 0x80
};

// ─── Bitmap 8x8 de una carita ─────────────────────────────────────────────
const unsigned char face_bmp[] PROGMEM = {
  0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C
};

// ─── Datos para gráfica de barras simulada ────────────────────────────────
const int barData[] = {20, 45, 30, 60, 50, 55, 40, 35};
const int barCount  = 8;

// ─── Datos para gráfica de línea simulada ─────────────────────────────────
const int lineData[] = {32, 38, 35, 42, 40, 50, 47, 55, 52, 60, 57, 62, 58, 64, 60, 63};
const int lineCount  = 16;

// ══════════════════════════════════════════════════════════════════
//  ESCENAS
// ══════════════════════════════════════════════════════════════════

// ── 1. Splash / bienvenida ────────────────────────────────────────
void scene_splash() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Marco exterior
  display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
  display.drawRect(2, 2, 124, 60, SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(10, 10);
  display.println("ESP32-S3");

  display.setTextSize(1);
  display.setCursor(18, 30);
  display.println("SSD1306 DEMO");

  display.setCursor(22, 44);
  display.println("128 x 64 OLED");

  display.display();
  delay(3000);
}

// ── 2. Tamaños de texto ──────────────────────────────────────────
void scene_text_sizes() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Tamaño 1: ocupa 8px → empieza en Y=0, siguiente en Y=10
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Tamano 1: Hola!");

  // Tamaño 2: ocupa 16px → empieza en Y=10, siguiente en Y=28
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.print("Tam 2");

  // Tamaño 3: ocupa 24px → empieza en Y=28, acaba en Y=52 (cabe justo)
  display.setTextSize(3);
  display.setCursor(0, 28);
  display.print("T: 3");

  // Tamaño 1 al final como etiqueta extra (Y=54)
  display.setTextSize(1);
  display.setCursor(70, 54);
  display.print("8x6 font");

  display.display();
  delay(3000);
}

// ── 3. Inversión de color ────────────────────────────────────────
void scene_invert() {
  for (int i = 0; i < 4; i++) {
    display.clearDisplay();
    display.fillRect(0, 0, 128, 64, (i % 2 == 0) ? SSD1306_WHITE : SSD1306_BLACK);
    display.setTextColor((i % 2 == 0) ? SSD1306_BLACK : SSD1306_WHITE);
    display.setTextSize(2);
    display.setCursor(10, 20);
    display.println("INVERSO!");
    display.display();
    delay(500);
  }
  delay(1000);
}

// ── 4. Formas geométricas ────────────────────────────────────────
void scene_shapes() {
  // Rectángulos
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Rectangulos");
  display.drawRect(0,  12, 40, 20, SSD1306_WHITE);
  display.fillRect(45, 12, 40, 20, SSD1306_WHITE);
  display.drawRoundRect(90, 12, 36, 20, 6, SSD1306_WHITE);
  display.fillRoundRect(0, 38, 36, 20, 6, SSD1306_WHITE);
  display.display();
  delay(2500);

  // Círculos
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Circulos");
  display.drawCircle(20,  38, 18, SSD1306_WHITE);
  display.fillCircle(64,  38, 18, SSD1306_WHITE);
  display.drawCircle(108, 38,  8, SSD1306_WHITE);
  display.fillCircle(108, 52,  8, SSD1306_WHITE);
  display.display();
  delay(2500);

  // Triángulos y líneas
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Triangulos y lineas");
  display.drawTriangle(10, 60, 40, 15, 70, 60, SSD1306_WHITE);
  display.fillTriangle(75, 60, 105, 15, 125, 60, SSD1306_WHITE);
  for (int x = 0; x < 128; x += 8) {
    display.drawPixel(x, 62, SSD1306_WHITE);
  }
  display.display();
  delay(2500);
}

// ── 5. Bitmaps ───────────────────────────────────────────────────
void scene_bitmaps() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Bitmaps PROGMEM");

  // Corazón x3 tamaños
  display.drawBitmap(10, 20, heart_bmp, 16, 16, SSD1306_WHITE);
  display.drawBitmap(40, 16, heart_bmp, 16, 16, SSD1306_WHITE);  // mismo bitmap
  // Cara x4
  for (int i = 0; i < 4; i++) {
    display.drawBitmap(80 + i * 10, 20, face_bmp, 8, 8, SSD1306_WHITE);
  }

  display.setCursor(0, 50);
  display.println("Heart  x2   Face x4");
  display.display();
  delay(3000);
}

// ── 6. Scroll hardware ───────────────────────────────────────────
void scene_scroll() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("SCROLL HARDWARE");
  display.setCursor(0, 16);
  display.println("Derecha >>>>>>>>>>>");
  display.setCursor(0, 28);
  display.println("El SSD1306 puede");
  display.setCursor(0, 40);
  display.println("hacer scroll sin");
  display.setCursor(0, 52);
  display.println("usar el CPU!");
  display.display();

  display.startscrollright(0x00, 0x07);
  delay(3000);
  display.stopscroll();
  delay(500);

  display.startscrollleft(0x00, 0x07);
  delay(3000);
  display.stopscroll();
  delay(500);

  display.startscrolldiagright(0x00, 0x07);
  delay(3000);
  display.stopscroll();
  delay(1000);
}

// ── 7. Gráfica de barras ─────────────────────────────────────────
void scene_bar_chart() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Bar Chart");

  int barW    = 12;
  int spacing = 4;
  int originX = 8;
  int originY = 55;
  int maxH    = 40;

  // Eje Y
  display.drawLine(originX - 2, originY - maxH, originX - 2, originY, SSD1306_WHITE);
  // Eje X
  display.drawLine(originX - 2, originY, 128, originY, SSD1306_WHITE);

  for (int i = 0; i < barCount; i++) {
    int h = map(barData[i], 0, 64, 0, maxH);
    int x = originX + i * (barW + spacing);
    display.fillRect(x, originY - h, barW, h, SSD1306_WHITE);
  }
  display.display();
  delay(3000);
}

// ── 8. Gráfica de línea ──────────────────────────────────────────
void scene_line_chart() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Line Chart");

  int originX = 8;
  int originY = 58;
  int maxH    = 45;
  int stepX   = (128 - originX) / (lineCount - 1);

  display.drawLine(originX - 2, originY - maxH, originX - 2, originY, SSD1306_WHITE);
  display.drawLine(originX - 2, originY, 128, originY, SSD1306_WHITE);

  // Cuadrícula horizontal suave (punteada)
  for (int y = originY - maxH; y < originY; y += 10) {
    for (int x = originX; x < 128; x += 4) {
      display.drawPixel(x, y, SSD1306_WHITE);
    }
  }

  // Dibujar línea de datos
  for (int i = 0; i < lineCount - 1; i++) {
    int x1 = originX + i * stepX;
    int y1 = originY - map(lineData[i],     0, 64, 0, maxH);
    int x2 = originX + (i + 1) * stepX;
    int y2 = originY - map(lineData[i + 1], 0, 64, 0, maxH);
    display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
    display.fillCircle(x1, y1, 2, SSD1306_WHITE);
  }
  // Último punto
  int xl = originX + (lineCount - 1) * stepX;
  int yl = originY - map(lineData[lineCount - 1], 0, 64, 0, maxH);
  display.fillCircle(xl, yl, 2, SSD1306_WHITE);

  display.display();
  delay(3000);
}

// ── 9. Barra de progreso animada ─────────────────────────────────
void scene_progress() {
  for (int pct = 0; pct <= 100; pct += 5) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(30, 5);
    display.println("Cargando...");

    // Marco
    display.drawRoundRect(4, 28, 120, 14, 4, SSD1306_WHITE);
    // Relleno
    int fillW = map(pct, 0, 100, 0, 116);
    display.fillRoundRect(6, 30, fillW, 10, 3, SSD1306_WHITE);

    // Porcentaje
    display.setTextSize(1);
    display.setCursor(52, 48);
    display.print(pct);
    display.println("%");

    display.display();
    delay(60);
  }
  delay(1000);
}

// ── 10. Animación pelota rebotando ───────────────────────────────
void scene_bounce() {
  float x = 20, y = 20;
  float vx = 2.5, vy = 1.8;
  int r = 6;

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 0);
  display.println("Animacion!");
  display.display();
  delay(800);

  for (int frame = 0; frame < 120; frame++) {
    display.clearDisplay();

    // Marco
    display.drawRect(0, 0, 128, 64, SSD1306_WHITE);

    // Mover
    x += vx; y += vy;
    if (x - r <= 1 || x + r >= 127) vx = -vx;
    if (y - r <= 1 || y + r >= 63)  vy = -vy;

    // Sombra
    display.fillCircle((int)x + 2, (int)y + 2, r, SSD1306_BLACK);
    // Pelota
    display.fillCircle((int)x, (int)y, r, SSD1306_WHITE);
    // Brillo
    display.fillCircle((int)x - 2, (int)y - 2, 2, SSD1306_BLACK);

    display.display();
    delay(16); // ~60 FPS
  }
}

// ── 11. Dashboard estilo UI ──────────────────────────────────────
void scene_dashboard() {
  for (int tick = 0; tick < 40; tick++) {
    float temp = 22.5 + sin(tick * 0.3) * 3.0;
    float hum  = 55.0 + cos(tick * 0.2) * 8.0;
    int   rssi = -60 + (tick % 10) - 5;

    display.clearDisplay();

    // ── Cabecera ──
    display.fillRect(0, 0, 128, 12, SSD1306_WHITE);
    display.setTextColor(SSD1306_BLACK);
    display.setTextSize(1);
    display.setCursor(2, 2);
    display.print("ESP32-S3  Dashboard");

    // ── Temperatura ──
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 16);
    display.setTextSize(1);
    display.println("TEMP:");
    display.setTextSize(2);
    display.setCursor(0, 24);
    display.print(temp, 1);
    display.println("C");

    // ── Separador vertical ──
    display.drawLine(68, 14, 68, 63, SSD1306_WHITE);

    // ── Humedad ──
    display.setTextSize(1);
    display.setCursor(72, 16);
    display.println("HUM:");
    display.setTextSize(2);
    display.setCursor(72, 24);
    display.print(hum, 0);
    display.println("%");

    // ── Barra RSSI ──
    display.setTextSize(1);
    display.setCursor(0, 50);
    display.print("WiFi:");
    display.print(rssi);
    display.print("dB");
    int bars = map(constrain(rssi, -90, -40), -90, -40, 0, 5);
    for (int b = 0; b < 5; b++) {
      if (b < bars)
        display.fillRect(80 + b * 9, 58 - b * 4, 7, 4 + b * 4, SSD1306_WHITE);
      else
        display.drawRect(80 + b * 9, 58 - b * 4, 7, 4 + b * 4, SSD1306_WHITE);
    }

    display.display();
    delay(100);
  }
}

// ── 12. Texto con efecto typewriter ─────────────────────────────
void scene_typewriter() {
  const char* msg = "ESP32-S3 + SSD1306\nOLED 128x64px\nI2C @ 0x3C\nAdafruit GFX v2";
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  int row = 0, col = 0;
  for (int i = 0; msg[i] != '\0'; i++) {
    if (msg[i] == '\n') {
      row++;
      col = 0;
      display.setCursor(0, row * 12);
    } else {
      display.setCursor(col * 6, row * 12);
      display.print(msg[i]);
      col++;
    }
    display.display();
    delay(40);
  }
  delay(2000);
}

// ══════════════════════════════════════════════════════════════════
//  SETUP & LOOP
// ══════════════════════════════════════════════════════════════════

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("ERROR: SSD1306 no encontrado");
    while (true);
  }
  display.clearDisplay();
  display.display();
  delay(200);
}

void loop() {
  scene_splash();        // 1. Bienvenida con marco
  scene_text_sizes();    // 2. Tamaños de fuente
  scene_invert();        // 3. Color invertido
  scene_shapes();        // 4. Rect, círculos, triángulos
  scene_bitmaps();       // 5. Bitmaps en PROGMEM
  scene_scroll();        // 6. Scroll hardware
  scene_bar_chart();     // 7. Gráfica de barras
  scene_line_chart();    // 8. Gráfica de línea con cuadrícula
  scene_progress();      // 9. Barra de progreso animada
  scene_bounce();        // 10. Pelota rebotando ~60fps
  scene_dashboard();     // 11. Dashboard temp/hum/wifi
  scene_typewriter();    // 12. Efecto máquina de escribir
}