#include <hidapi/hidapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  unsigned int vid = 0;
  unsigned int pid = 0;

  if (argc > 2) { // given 3 total args, two of which are the vid and pid
    vid = (unsigned int)strtoul(argv[1], NULL, 16);
    pid = (unsigned int)strtoul(argv[2], NULL, 16);
  } else {
    printf("Usage: %s <VID hex> <PID hex>", argv[0]);
    return 1;
  }

  int res;
  struct hid_device_info *devs, *cur_dev;
  hid_device *handle = NULL;
  char *raw_path = NULL;

  if (hid_init()) {
    return -1;
  }
  devs = hid_enumerate(vid, pid);
  cur_dev = devs;
  while (cur_dev) {
    // Look for vendor-defined Raw HID usage_page
    if (cur_dev->usage_page == 0xFF60 || cur_dev->usage_page == 0xFF00) {
      raw_path = strdup(cur_dev->path); // save for opening
    }

    cur_dev = cur_dev->next;
  }
  hid_free_enumeration(devs);
  if (!raw_path) {
    return 1;
  }
  handle = hid_open_path(raw_path);
  if (!handle) {
    return 1;
  }

  unsigned char buf[32];
  res = hid_read(handle, buf, sizeof(buf));
  if (res > 0) {
    switch (buf[0]) {
    case 3:
      printf("Game\n");
      break;
    default: // anything other than game is a normal layer
        printf("Normal\n");
        break;
    }
  }
  hid_close(handle);
  hid_exit();
}
