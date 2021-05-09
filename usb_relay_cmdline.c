#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "usb_relay_device.h"
#include "argparse.h"

static const char *const usages[] = {
	"usb_relay_cmdline [options] [[--] args]",
	"usb_relay_cmdline [options]",
	NULL,
};

int main(int argc, const char **argv)
{
	// definition for all the argument pass value.
	char *relay_open_str = NULL;
	char *relay_close_str = NULL;
	int open_relay = 0;
	int close_relay = 0;

	// options are used to show the --help with all other arguments.
	struct argparse_option options[] = {
		OPT_HELP(),
		OPT_GROUP("Basic options"),
		OPT_STRING('o', "relay_open", &relay_open_str, "open the specific relay (Eg: 1,4,5)", NULL, 0, relay_open),
		OPT_STRING('c', "relay_close", &relay_close_str, "close the specific relay (Eg: 1,4,5)", NULL, 0, relay_close),
		OPT_BOOLEAN('a', "open_all", &open_relay, "open all relay"),
		OPT_BOOLEAN('x', "close_all", &close_relay, "close all relay"),
		OPT_END(),
	};

	struct argparse argparse;

	argparse_init(&argparse, options, usages, 0);
	argparse_describe(&argparse, "\nA brief description of what the program does and how it works.", "\nAdditional description of the program after the description of the arguments.");
	argc = argparse_parse(&argparse, argc, argv);

	// These variables used for decoding the string with ',' seperator for ON .
	int relay_on[8];
	char *temp1 = NULL;
	uint8_t count1 = 0;

	// These variables used for decoding the string with ',' seperator for OFF .
	int relay_off[8];
	char *temp2 = NULL;
	uint8_t count2 = 0;

	char device_name[] = "HW554";	 // HID name of the device
	char relay_condition[6] = {0};	 // relay_condition either OPEN or CLOSE
	strcpy(relay_condition, "NULL"); // init relay_condition as NULL
	int ret = 0;

	// Decode of the string value RELAY_ON
	if (relay_open_str != NULL)
	{
		temp1 = strtok(relay_open_str, ",");
		while (temp1 != NULL)
		{
			relay_on[count1] = strtoul(temp1, NULL, 0);
			temp1 = strtok(NULL, ",");
			count1++;
		}
		strcpy(relay_condition, "open");
		printf("the no of realy ON command:");
		for (int i = 0; i < count1; i++)
		{
			printf(" %d", relay_on[i]);
		}
		printf("\n");
	}

	// Decode of the string value RELAY_OFF
	if (relay_close_str != NULL)
	{
		temp2 = strtok(relay_close_str, ",");
		while (temp2 != NULL)
		{
			relay_off[count2] = strtoul(temp2, NULL, 0);
			temp2 = strtok(NULL, ",");
			count2++;
		}
		strcpy(relay_condition, "close"); // argv2 passed for close condition "-c  1,3,4"
		printf("the no of realy OFF command:");
		for (int i = 0; i < count2; i++)
		{
			printf(" %d", relay_off[i]);
		}
		printf("\n");
	}

	usb_relay_init(); // init of the usb_relay

	//  The Device info is obtained by following "struct usb_relay_device_info *device_info"
	//  "usb_relay_device_enumerate()" is used to Enumerate the USB Device

	struct usb_relay_device_info *device_info = usb_relay_device_enumerate();
	struct usb_relay_device_info *current_info = device_info;
	int hd = usb_relay_device_open_with_serial_number(device_name, strlen(device_name)); // Open the communication throught serial of HID device .

	while (current_info != NULL)
	{
		printf("Serial number %s\n", current_info->serial_number);
		printf("Serial open %d\n", hd);
		current_info = current_info->next;
	}

	if (strcmp(relay_condition, "open") == 0 && relay_open_str != NULL)
	{
		printf("Relay ON:");
		for (int i = 0; i < count1; i++)
		{
			ret = usb_relay_device_open_one_relay_channel(hd, relay_on[i]); // ON the particular relay (eg:1,3,4)
			printf(" %d", relay_on[i]);
		}
	}

	else if (strcmp(relay_condition, "close") == 0 && relay_close_str != NULL)
	{
		printf("Relay OFF:");
		for (int i = 0; i < count2; i++)
		{
			ret = usb_relay_device_close_one_relay_channel(hd, relay_off[i]); // OFF the particular relay (eg:1,3,4)
			printf("%d ", relay_off[i]);
		}
	}

	else if (open_relay != 0)
	{
		printf("All Relay ON !!!");
		ret = usb_relay_device_open_all_relay_channel(hd); // ON all the Relay of a device (eg: device with 8 channel , all the 8 channel will  get ON)
	}

	else if (close_relay != 0)
	{
		printf("All Relay OFF !!!");
		ret = usb_relay_device_close_all_relay_channel(hd); // OFF all the Relay of a device (eg: device with 8 channel , all the 8 channel will get OFF)
	}

	else
	{
		ret = 1;
	}

	usb_relay_exit();
	return ret;
}