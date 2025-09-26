#include <hidapi/hidapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 3) { 
    printf("Usage: %s <VID hex> <PID hex>\n", argv[0]);
    return 1;
  } 

  unsigned int vid = (unsigned int)strtoul(argv[1], NULL, 16);
  unsigned int pid = (unsigned int)strtoul(argv[2], NULL, 16);

  if (hid_init()) {
    return -1;
  }
  struct hid_device_info *devs = hid_enumerate(vid, pid);
  struct hid_device_info *cur = devs;
  hid_device *handle = NULL;

  while (cur) {
    if (cur->usage_page == 0xFF60) {
      handle = hid_open_path(cur->path);
      break;
    }
    cur = cur->next;
  }
  hid_free_enumeration(devs);

  if (!handle) {
    return 1;
  }

  unsigned char buf[32];
  int res = hid_read_timeout(handle, buf, sizeof(buf), 100);
  if (res > 0) {
    unsigned char layer = buf[0];
    if (layer == 3){
      printf("{\"layer\":\"Game\"}\n");
    } else {
      printf("{\"layer\":\"Normal\"}\n");
    }
  } else{
      printf("{\"layer\":\"Error\"}\n");
  }
  hid_close(handle);
  return 0;
}
