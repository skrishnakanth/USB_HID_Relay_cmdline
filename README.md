# USB_RELAY Control via command-line


### DESCRIPTION
The purpose of this tool is to control the USB_HID_RELAY with different channels available in the market .
there is a build in GUI for controlling it but there is no any kind of exe done for Argument pass through command-line.

### REQUIREMENTS

1. 8 Channel 12V Relay Module USB :pager: .
2. Visual Studio Code IDE.
```
NOTE: To access and modify the source Code, I recommand Visual Stdio Code IDE.
```
### PROCEDURE :newspaper:
- Download this repository.
- Open PowerShell at this repository PATH and Follow the Command
```
.\usb_hid_relay.exe -h
```
3.Then HELP argument runs and you can start operating the relay
```
Usage: usb_hid_relay [options] [[--] args]
   or: usb_hid_relay [options]

A brief description of what the program does and how it works.

    -h, --help                show this help message and exit

Basic options
    -o, --relay_open=<str>    open the specific relay (Eg: 1,4,5)
    -c, --relay_close=<str>   close the specific relay (Eg: 1,4,5)
    -a, --open_all            open all relay
    -x, --close_all           close all relay

Additional description of the program after the description of the arguments.
```

### PROJECT FILE DESCRIPTION
1. The project file contains .c , .h and .dll files.
2. This project is Done completely in Visual Studio Code IDE.
3. The complete project files can be modified, so todo follow the steps
```
* Download TDM-GCC-32 since the .dll file is 32 bit.
* Open the repository PATH with VSCode.
* Then do check launch.json and tasks.json file for any Error while RUN.
```

## Caution: :warning:
* This project files are only for Window OS.
* This is completely for a demo purposes and not yet Developed with Standard protocols :beginner:.
* Still there is no complete access to .dll file content.
