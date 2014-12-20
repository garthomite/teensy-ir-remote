# IR/KB Remote for Teensy

I wanted a way to use my old cable box remote with Kodi/XBMC but apparently Kodi for android doesn't support it yet.

So I just added a IR receiver to pin 12 and using this ghetto sketch I convert the button input and map them to keyboard commands that Kodi does understand 

## Learning your remote

Load this sketch and open up the serial monitor. As you press buttons you should see the corresponding hex codes. Use these hex codes and modify sendForButton to fit your needs. When you are done change the USB type to Keyboard + Serial, plug it in to a usb port of whatever device you want to control then click away



