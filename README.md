# ESP32-S3 Native USB HID Gamepad Emulator 🎮

This repository contains an open-source, high-performance ESP-IDF firmware solution to emulate a native USB HID Gamepad using an **ESP32-S3** microcontroller. 

It is specifically designed for DIY simulator hardware builders looking to create custom button boxes for games like *Euro Truck Simulator 2 (ETS2)*, *American Truck Simulator (ATS)*, and racing simulators.

NOTE THIS CAN BE USED WITHOUGHT INTENT TO CREATE A BUTTON BOX IT WOULD JUST NEED TO BE MODIFIED

## 🚀 Features
- **Native USB Execution**: Runs directly on the ESP32-S3 internal USB controller via the TinyUSB stack. No external UART bridge chips are required.
- **Active-High Logic**: Configured with internal pull-down resistors (`.pull_down_en = 1`). Buttons trigger safely and instantly when hit with a **3.3V** signal.
- **Multi-Button Array Layout**: Code framework scales seamlessly to support up to 32 digital buttons simultaneously.
- **Custom Device Descriptor**: Pre-configured with a unique Product ID (PID) to bypass Windows registry caching and instantly register as `ETS/ATS Button Box` in the Game Controllers menu.

## 🛠️ Hardware Requirements
- **ESP32-S3 Development Board** (Ensure you plug into the Native USB/OTG port when trying to use, only use the UART port when flashing!)
- Momentary push buttons or toggle switches
- Jumper wires
  
- 3D Printed enclosure (Designed and sliced using a Creality Ender 3 V3 SE) -- ONLY FOR BUTTON BOX

## 📌 Wiring Blueprint
Connect your momentary switches directly between the configured GPIO pin and the 3.3V power rail:

```text
  [ 3.3V Pin ] ------ (Switch) ------ [ GPIO Pin (e.g., GPIO 4) ]
```

## 📜 License
This project is licensed under the **MIT License**—see the [LICENSE](LICENSE) file for full details. You are free to modify, distribute, and build upon this code for your own custom simulator hardware!

---
*Created by a 13-year-old maker blending dirt bikes, 3D printing, and custom engineering. Check out the full build tutorial video on my YouTube channel!*
