# 🎮 ESP32-S3 Native USB HID Gamepad Emulator

Turn your **ESP32-S3** into a fully functional **USB HID gamepad** that Windows automatically recognizes as a standard game controller. Development requires ESP-IDF v5.5.4, but no additional Windows drivers are needed.

Built with **ESP-IDF** and **TinyUSB**, this project provides a lightweight, low-latency USB HID implementation that's perfect for custom controllers, simulator hardware, robotics, and other embedded projects.

Originally created for DIY button boxes used in **Euro Truck Simulator 2 (ETS2)**, **American Truck Simulator (ATS)**, and racing simulators, the firmware can easily be customized for almost any USB HID controller.

> **This project isn't limited to button boxes.** It can be adapted for custom gamepads, arcade controllers, flight simulator panels, stream decks, macro pads, control panels, and much more.

---

# ✨ Features

* 🎮 Native USB HID Gamepad emulation
* 🖥️ Plug-and-play support on Windows
* 🔘 Supports up to **32 programmable buttons**
* ⚡ Low-latency USB communication using TinyUSB
* 🛠️ Built with **ESP-IDF v5.5.4**
* 🔓 Fully open source and easy to customize
* 📦 Lightweight firmware with minimal overhead

---

# 🖥️ Compatibility

## Operating Systems

* ✅ Windows 10
* ✅ Windows 11

## Supported Boards

* ESP32-S3 development boards with **Native USB (USB-OTG) and UART** support
* Dual USB port development boards are the only type tested and known to be working

> ⚠️ **XIAO ESP32-S3 boards have not yet been tested.** They may work, but compatibility has not been confirmed.

---

# ⚠️ Before You Install

Before building or flashing the firmware, make sure the following requirements are met:

* Install **ESP-IDF v5.5.4**. This version has been tested and is known to work.
* Your board has both a **Native USB (USB-OTG)** port and a **USB-to-UART** port.
* The **USB-OTG pads** on the back of the board are bridged. While this may not be required on every board, all successful testing has been performed with the pads connected.
* Flash the firmware using the **UART** port.
* After flashing, reconnect the USB cable to the **Native USB (USB-OTG)** port.

If these steps are not followed, Windows may not detect the controller correctly.

---

# 🚀 Installation

New to ESP32 development?

Follow the complete setup guide here:

**🎥 YouTube:** *(Insert Video Link Here)*

## 1. Install ESP-IDF

Install **ESP-IDF v5.5.4** from the official Espressif documentation.

> 📎 **ESP-IDF Installation Guide:** *([Insert Link Here](https://docs.espressif.com/projects/esp-idf/en/v5.5.4/esp32/get-started/index.html#installation))*

---

## 2. Download the latest release

Download the latest release and unzip it. Then move the **tusb_hid** file into your project workspace

---

## 3. Open terminal

In the windows search bar search **ESP IDF** and open

---

## 4. Cd into the project workspace

```bash
cd DRIVE\Folder\Folder\Project\tusb_hid
```
---

## 5. Set the Project Target

```bash
idf.py set-target esp32s3
```

---


## 6. Build the Project

```bash
idf.py build
```

---

## 7. Flash the Firmware

Connect your board using the **UART** port and run:

```bash
idf.py flash
```

---

## 8. Connect as a Gamepad

After flashing:

1. Disconnect the USB cable.
2. Connect it to the **Native USB (USB-OTG)** port.
3. Windows should automatically detect the device as a USB HID Gamepad.
4. Verify operation by opening **Set up USB Game Controllers** (`joy.cpl`).

---

# 🔌 Wiring

Connect each button between **3.3V** and the configured GPIO pin.

```text
      3.3V
        │
    ┌───┴────┐
    │ Button │
    └───┬────┘
        │
GPIO (Example: GPIO4)
```

The firmware uses the ESP32-S3's **internal pull-down resistors**, meaning every GPIO remains **LOW** until the button is pressed, at which point it reads **HIGH**.

---

# 📂 Project Structure

```text
ESP32-S3-USB-Gamepad/
│
├── main/
│   ├── main.c
│   ├── tusb_hid.c
│   ├── gpio_config.c
│   └── CMakeLists.txt
│
├── sdkconfig
├── CMakeLists.txt
├── LICENSE
└── README.md
```

---

# 💡 Great For

* DIY game controllers
* Button boxes
* Flight simulators
* Racing simulators
* Arcade cabinets
* Robotics
* USB HID development
* Custom control panels

---

# 📜 License

Licensed under the **MIT License**.

You are free to use, modify, distribute, and build upon this project for personal or commercial use. See the **LICENSE** file for details.

---

# 👋 About

Hi! I'm a **13-year-old maker** who enjoys electronics, programming, 3D printing, CAD, dirt bikes, and building custom hardware.

This project started as a way to create affordable simulator hardware and has grown into a flexible USB HID framework for the ESP32-S3.

If this project helped you, please consider ⭐ **starring the repository**. It really helps support future development!

Bug reports, feature requests, and pull requests are always welcome.

Happy building! 🎮
