# kb-hid-layer-read

allows you to read some data from a qmk keyboard.

keyboard must be configured with rules.mk RAW_ENABLE = yes.

use the `host_raw_hid_send` function to send hid raw bytes to your computer.

```c
static uint8_t current_layer = 0;
layer_state_t layer_state_set_user(layer_state_t state) {
    current_layer = get_highest_layer(state); // gets the highest layer
    return state;
}
uint16_t last_send = 0;

void matrix_scan_user(void) {
    if (timer_elapsed(last_send) > 200) { // prevents spamming. this function runs a lot, and will cause lag.
        uint8_t payload[32] = {0};
        payload[0] = current_layer; // first byte of the 32 is your layer num
        host_raw_hid_send(payload, sizeof(payload));
        last_send = timer_read();
    }
}
```

the script will run and wait for a message from the keyboard. script is pre-configured to identify layer 3 as "game" and all other layers as "normal". modify as needed. 

## usage

```bash
kb-readlayer 4d44 5244
kb-readlayer <vid> <pid>
```

## installation

depends on the hidapi package. arch users can install hidapi, idk about other distros.
```bash
gcc -Wall -Wextra -O2 -o kb-readlayer main.c -lhidapi-hidraw
# move resulting binary wherever
```

```bash
# pacman
makepkg -si
```
