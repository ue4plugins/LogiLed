# LogitechLed

Unreal Engine 4 plug-in for Logitech LED illumination keyboards.

![Logo](Docs/logo.png)


## About

This plug-in implements Blueprint functions for controlling the LED lights
in supported Logitech keyboards and mice.

Make sure to pull the Tag that matches your Unreal Engine version. If you sync
to Master the code may not compile, because it may depend on Engine changes that
are not yet available in the UE4 Master branch.


## Supported Platforms

This plug-in was last built against **Unreal Engine 4.19** with
*Logitech LED SDK 8.87* and tested on the following platforms:

- Windows


## Dependencies

This plug-in requires Visual Studio and either a C++ code project or the full
Unreal Engine 4 source code from GitHub. If you are new to programming in UE4,
please see the official [Programming Guide](https://docs.unrealengine.com/latest/INT/Programming/index.html)! 


## Usage

You can use this plug-in as a project plug-in, or an Engine plug-in.

If you use it as a project plug-in, clone this repository into your project's
*/Plugins* directory and compile your game in Visual Studio. A C++ code project
is required for this to work.

If you use it as an Engine plug-in, clone this repository into the
*/Engine/Plugins* directory and compile your game. Full Unreal Engine 4
source code from GitHub is required for this.


## Support

Please [file an issue](https://github.com/ue4plugins/LogiLed/issues), submit a
[pull request](https://github.com/ue4plugins/LogiLed/pulls?q=is%3Aopen+is%3Apr)
or email us at info@headcrash.industries


## References

* [Logitech G Developer Lab](http://gaming.logitech.com/en-us/developers)
* [Logitech Gaming Keyboards](http://gaming.logitech.com/en-us/gaming-keyboards)
* [Introduction to UE4 Plugins](https://wiki.unrealengine.com/An_Introduction_to_UE4_Plugins)
