# ESP32 Climate Sensor (HomeKit)

```
ESP32_Climate_Sensor/
└── ESP32_Climate_Sensor.ino
```

A native Apple HomeKit temperature & humidity sensor built with an **ESP32** and a **DHT22** sensor, powered by the [HomeSpan](https://github.com/HomeSpan/HomeSpan) library. No hubs, no bridges, no third-party apps — the ESP32 pairs directly with the Home app over Wi-Fi.

## ✨ Features

- 🌡️ Real-time temperature reading (°C)
- 💧 Real-time relative humidity reading (%)
- 🍏 Native HomeKit integration — pairs directly with Apple Home
- ⚡ Non-blocking sensor polling (no `delay()` in the main loop)
- 🎯 Change-threshold filtering (only pushes updates when values shift ≥ 0.1)
- 🛡️ Sensor read validation with `NaN` and out-of-range guarding

## 🧰 Hardware Requirements

| Component        | Notes                                  |
|-------------------|-----------------------------------------|
| ESP32 Dev Board   | Any variant with Wi-Fi support           |
| DHT22 (AM2302)    | Temperature & humidity sensor            |
| 10kΩ resistor     | Pull-up between DHT22 `DATA` and `VCC`   |
| Jumper wires      | —                                        |
| Breadboard        | Optional, for prototyping                |

### Wiring

| DHT22 Pin | ESP32 Pin |
|-----------|-----------|
| VCC       | 3.3V      |
| DATA      | GPIO 4    |
| GND       | GND       |

> Add a 10kΩ pull-up resistor between `DATA` and `VCC` if your DHT22 module doesn't already include one on-board.

## 📦 Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software) (2.x recommended)
- [ESP32 board package](https://github.com/espressif/arduino-esp32) — install via **Boards Manager**
- Libraries (install via **Library Manager**):
  - [HomeSpan](https://github.com/HomeSpan/HomeSpan)
  - [DHT sensor library](https://github.com/adafruit/DHT-sensor-library) (Adafruit)
  - [Adafruit Unified Sensor](https://github.com/adafruit/Adafruit_Sensor) (dependency of the DHT library)

## 🚀 Getting Started

1. **Clone the repo**
   ```bash
   git clone https://github.com/<your-username>/ESP32_Climate_Sensor.git
   ```

2. **Open the sketch**
   In Arduino IDE: **File → Open** → select `ESP32_Climate_Sensor/ESP32_Climate_Sensor.ino`

3. **Install dependencies**
   **Tools → Manage Libraries** → search for and install `HomeSpan`, `DHT sensor library`, and `Adafruit Unified Sensor`.

4. **Select your board**
   **Tools → Board** → choose your ESP32 board variant, and select the correct **Port**.

5. **Wire the DHT22** to the ESP32 as described above.

6. **Upload**
   Click **Upload** (→) in the Arduino IDE.

7. **Pair with HomeKit**
   - Open the Serial Monitor at `115200` baud.
   - Follow the HomeSpan setup prompts to configure Wi-Fi (`W` command) and generate a pairing code.
   - Open the **Home** app on iOS → **Add Accessory** → **More options...** → select your ESP32 device → enter the pairing code shown in the Serial Monitor.

## ⚙️ Configuration

| Constant             | Description                          | Default |
|-----------------------|---------------------------------------|---------|
| `DHT_PIN`             | GPIO pin connected to DHT22 `DATA`   | `4`     |
| `DHT_TYPE`            | Sensor model                          | `DHT22` |
| `SENSOR_INTERVAL_MS`  | Polling interval (ms)                | `3000`  |

## 🗺️ Roadmap

- [ ] Add OTA firmware updates
- [ ] Add low-battery / sensor-fault HomeKit notification
- [ ] Support multiple sensors on one accessory

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).

## 🙏 Acknowledgements

- [HomeSpan](https://github.com/HomeSpan/HomeSpan) — HomeKit library for ESP32
- [Adafruit DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library)
