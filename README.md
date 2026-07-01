# ESP32-S3 Native USB HID Gamepad Emulator 🎮

This repository contains an open-source, high-performance ESP-IDF firmware project that turns an **ESP32-S3** into a native USB HID gamepad.

Originally designed for DIY simulator hardware such as button boxes for games like **Euro Truck Simulator 2 (ETS2)**, **American Truck Simulator (ATS)**, and racing simulators, this firmware can easily be modified for almost any custom USB HID controller.

> **Note:** This project is **not limited to button boxes**. With minor modifications, it can be adapted for custom gamepads, arcade controllers, flight simulator panels, stream decks, macro pads, and many other USB HID devices.

---

## 🚀 Features

- 🎮 **Native USB HID Support** – Uses the ESP32-S3's built-in USB controller with the TinyUSB stack.
- ⚡ **Low-Latency Performance** – Fast response times with native USB communication.
- 🔌 **No Additional USB HID Hardware Required** – The ESP32-S3 handles USB HID natively.
- 🔘 **Active-High Button Inputs** – Uses the ESP32-S3's internal pull-down resistors (`.pull_down_en = 1`) for reliable digital inputs.
- 🎛️ **Expandable Design** – Easily supports up to **32 digital buttons**.
- 🆔 **Custom USB Device Descriptor** – Uses a unique Product ID (PID) so Windows recognizes the controller as a separate device.
- 🛠️ **Open Source** – Fully customizable for your own projects.

---

## 🛠️ Hardware Requirements

- ESP32-S3 Development Board
- USB-C cable
- Momentary push buttons or toggle switches
- Jumper wires
- Breadboard or custom PCB

### Optional

- 3D-printed enclosure (Designed and printed on a Creality Ender 3 V3 SE for the button box version)

---

## 🔌 USB Connection

Most ESP32-S3 development boards have **two USB ports**:

- **This repo has only been tested with the two port model.
- **Native USB / USB-OTG** → Used for the USB HID gamepad.
- **USB-to-UART** → Typically used for flashing firmware and serial debugging.

> **Important:** When using the controller as a gamepad, plug the USB cable into the **Native USB/OTG** port. Some development boards require the UART port only for flashing firmware.

---

## 📌 Wiring Blueprint

Connect each momentary switch between **3.3V** and the configured GPIO pin.

```text
      3.3V
        │
    ┌───┴───┐
    │Switch │
    └───┬───┘
        │
GPIO (Example: GPIO4)
```

Because the firmware uses the ESP32-S3's **internal pull-down resistors**, each GPIO pin normally reads **LOW** and changes to **HIGH** when the switch is pressed.

---

## 📂 Project Structure

```text
ESP32-S3-USB-Gamepad/
│
├── main/
│   ├── main.c
│   ├── tusb_hid.c
│   └── gpio_config.c
│
├── CMakeLists.txt
├── sdkconfig
├── LICENSE
└── README.md
```

---

## 📜 License

This project is licensed under the **MIT License**.

You are free to use, modify, distribute, and build upon this project for personal or commercial use. See the [LICENSE](LICENSE) file for more information.

---

## 👋 About

Created by a **13-year-old maker** who enjoys electronics, 3D printing, programming, dirt bikes, and designing custom hardware.

If you found this project useful, consider ⭐ **starring the repository** and checking out the accompanying build videos on YouTube!

Happy building! 🎮
