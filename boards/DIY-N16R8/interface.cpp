#include "core/bus_HAL.h"
#include "core/powerSave.h"
#include "core/utils.h"
#include "hal/bright/bright.h"
#include "hal/device.h"
#include <Arduino.h>
#include <interface.h>

void _setup_gpio() {
    // Pines reservados (hardware pendiente)
    bruceConfigPins.irTx = 42;    // IR TX (pendiente)
    bruceConfigPins.irRx = 47;    // IR RX (pendiente)
    bruceConfigPins.rotation = 3; // Landscape 320x240
    bruceConfigPins.badusb_bus = {(gpio_num_t)-1, (gpio_num_t)-1}; // rx, tx (no disponible)
    
    // SD Card: SCK=12, MISO=13, MOSI=11, CS=14
    bruceConfigPins.SDCARD_bus = {
        (gpio_num_t)12, (gpio_num_t)13, (gpio_num_t)11, (gpio_num_t)14
    };
    
    // Bus SPI compartido para periféricos genéricos: SCK=12, MISO=13, MOSI=11, CS=10 (TFT)
    bruceConfigPins.outer_bus = {(gpio_num_t)12, (gpio_num_t)13, (gpio_num_t)11, (gpio_num_t)10};
    bruceConfigPins.PN532_bus = {(gpio_num_t)12, (gpio_num_t)13, (gpio_num_t)11, (gpio_num_t)10};
    
    // NRF24: CE=39, CSN=38
    pinMode(39, OUTPUT);  // CE
    pinMode(38, OUTPUT);  // CSN
    digitalWrite(38, HIGH); // CSN alto por defecto
    digitalWrite(39, LOW);  // CE bajo por defecto
    
    // Buzzer: GPIO 2
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);
    
    // Botones (pull-up interno)
    pinMode(4, INPUT_PULLUP);   // UP
    pinMode(5, INPUT_PULLUP);   // DOWN
    pinMode(6, INPUT_PULLUP);   // LEFT
    pinMode(17, INPUT_PULLUP);  // RIGHT
    pinMode(21, INPUT_PULLUP);  // OK
    pinMode(18, INPUT_PULLUP);  // BACK
    
    // CC1101 reservado (pendiente)
    pinMode(40, OUTPUT); // CC1101 CSN
    pinMode(41, OUTPUT); // CC1101 GD0
    digitalWrite(40, HIGH);
    
    // PN532 I2C reservado (pendiente) - pines 8/9
    // pinMode(8, INPUT_PULLUP);  // SDA
    // pinMode(9, INPUT_PULLUP);  // SCL
}

void _post_setup_gpio() {
    hal_bright_attach(7);  // TFT_BL = 7
    hal_bright_set(7, 100);
    
    // Test buzzer
    tone(2, 2000, 100);
}

void _setBrightness(uint8_t brightval) { 
    hal_bright_set(7, brightval); 
}

void InputHandler(void) {
    // Los botones se manejan por HAL, aquí solo lógica extra si hace falta
}

void powerOff() {}

void checkReboot() {}
