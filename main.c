#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "tinyusb.h"
#include "tinyusb_default_config.h"
#include "class/hid/hid_device.h"

static const char *TAG = "gamepad";

/* ===== GPIO BUTTON ARRAY ===== */
// List all the GPIO pins you want to use as buttons for your box here
static const gpio_num_t button_pins[] = {
    GPIO_NUM_4,   // Button 1 (Bit 0)
    GPIO_NUM_5,   // Button 2 (Bit 1)
    GPIO_NUM_6,   // Button 3 (Bit 2)
    GPIO_NUM_7,   // Button 4 (Bit 3)
    GPIO_NUM_15,  // Button 5 (Bit 4)
    GPIO_NUM_16,  // Button 6 (Bit 5)
    GPIO_NUM_17,  // Button 7 (Bit 6)
    GPIO_NUM_18   // Button 8 (Bit 7)
    // Add up to 32 pins here if needed!
};

#define BUTTON_COUNT (sizeof(button_pins) / sizeof(button_pins[0]))

/* ===== HID REPORT ===== */
const uint8_t hid_report_descriptor[] = {
    TUD_HID_REPORT_DESC_GAMEPAD()
};

/* ===== STRING DESCRIPTORS ===== */
const char* hid_string_descriptor[5] = {
    (char[]){0x09, 0x04},
    "ESP32-S3",
    "ETS/ATS Button Box",
    "123456",
    "ETS/ATS Button Box"
};

/* ===== CONFIG DESCRIPTOR ===== */
#define TUSB_DESC_TOTAL_LEN (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN)

static const uint8_t hid_configuration_descriptor[] = {
    TUD_CONFIG_DESCRIPTOR(1, 1, 0, TUSB_DESC_TOTAL_LEN,
                          TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100),

    TUD_HID_DESCRIPTOR(0, 4, false,
                       sizeof(hid_report_descriptor),
                       0x81, 16, 10),
};

/* ===== DEVICE DESCRIPTOR ===== */
// Custom device descriptor layout to force Windows to refresh the name cache
static const tusb_desc_device_t my_device_descriptor = {
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = 0x0200,
    .bDeviceClass       = TUSB_CLASS_MISC,
    .bDeviceSubClass    = MISC_SUBCLASS_COMMON,
    .bDeviceProtocol    = MISC_PROTOCOL_IAD,
    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,
    
    .idVendor           = 0x303A, // Espressif VID
    .idProduct          = 0x4005, // Unique PID to force a fresh Windows registration
    .bcdDevice          = 0x0100,
    
    .iManufacturer      = 0x01,
    .iProduct           = 0x02,  // Points to Index 2: "ETS/ATS Button Box"
    .iSerialNumber      = 0x03,
    .bNumConfigurations = 0x01
};

/* ===== CALLBACKS ===== */
uint8_t const *tud_hid_descriptor_report_cb(uint8_t instance)
{
    return hid_report_descriptor;
}

uint16_t tud_hid_get_report_cb(uint8_t instance,
                                uint8_t report_id,
                                hid_report_type_t report_type,
                                uint8_t *buffer,
                                uint16_t reqlen)
{
    return 0;
}

void tud_hid_set_report_cb(uint8_t instance,
                           uint8_t report_id,
                           hid_report_type_t report_type,
                           uint8_t const *buffer,
                           uint16_t bufsize)
{
}

/* ===== MAIN ===== */
void app_main(void)
{
    ESP_LOGI(TAG, "Starting Multi-Button HID Gamepad");

    /* Calculate a 64-bit mask containing all our chosen button pins */
    uint64_t pin_mask = 0;
    for (int i = 0; i < BUTTON_COUNT; i++) {
        pin_mask |= (1ULL << button_pins[i]);
    }

    /* Configure all pins in the mask simultaneously with internal pull-downs */
    gpio_config_t io_conf = {
        .pin_bit_mask = pin_mask,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = 0,               // Disabled pull-up
        .pull_down_en = 1,             // Enabled pull-down (Active High: triggers when hit with 3.3V)
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    /* TinyUSB init */
    tinyusb_config_t tusb_cfg = TINYUSB_DEFAULT_CONFIG();

    tusb_cfg.descriptor.device = &my_device_descriptor; // Explicitly pass our custom descriptor
    tusb_cfg.descriptor.full_speed_config = hid_configuration_descriptor;
    tusb_cfg.descriptor.string = hid_string_descriptor;
    tusb_cfg.descriptor.string_count =
        sizeof(hid_string_descriptor) / sizeof(hid_string_descriptor[0]);

#if (TUD_OPT_HIGH_SPEED)
    tusb_cfg.descriptor.high_speed_config = hid_configuration_descriptor;
#endif

    ESP_ERROR_CHECK(tinyusb_driver_install(&tusb_cfg));

    while (1) {
        if (tud_mounted()) {

            uint32_t button_states_mask = 0;

            /* Loop through array, check voltages, and build the button report bitmask */
            for (int i = 0; i < BUTTON_COUNT; i++) {
                if (gpio_get_level(button_pins[i]) == 1) {
                    // Turn on the exact bit corresponding to this array index
                    button_states_mask |= (1UL << i);
                }
            }

            hid_gamepad_report_t report = {0};
            report.x = 0;
            report.y = 0;
            report.z = 0;
            report.rz = 0;
            report.rx = 0;
            report.ry = 0;
            report.hat = 0;
            report.buttons = button_states_mask; // Delivers up to 32 mapped button fires

            tud_hid_report(0, &report, sizeof(report));
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
