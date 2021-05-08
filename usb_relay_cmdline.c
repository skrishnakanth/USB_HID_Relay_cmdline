#include<stdio.h>
#include "usb_relay_device.h"


int main()
{
   	
	usb_relay_init();

	struct usb_relay_device_info *device_info = usb_relay_device_enumerate();

	struct usb_relay_device_info *current_info =  device_info;

	 while (current_info != NULL) 
	{
      printf("Serial number %s\n", current_info-> serial_number);
		current_info = current_info->next;
	}

	
   return 0;
}