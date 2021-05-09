gcc -m32 usb_hid_relay.c argparse.c usb_relay_device.dll -o usb_hid_relay
strip usb_hid_relay.exe
pause
