# Background

This repository constains a simple example of a zephyr application as a west manifest file.

Some background on Zephyr workspaces and west manifest files.

https://docs.zephyrproject.org/latest/develop/application/index.html

https://blog.golioth.io/improving-zephyr-project-structure-with-manifest-files/


# Setup

1.) Create a working folder on your local machine i.e. 'mcxn-iot'


2.) cd into that folder and run:

```
west init -m https://github.com/wavenumber-eng/mcxn-iot --mr main
```

This initiazes the folder as a west/zephyr workspace registered to our application repository.


3.)  Run "west update".   This may take several minutes to pull in all of the dependencies.

In this step,  west will look at the manifest and pull down all the dependencies.   In this case, the dependecy is the vanilla Zephyr repository.   It is quite large and can take a few minutes but only has to be initialize once.  Future calls to west update are much quicker.

![zephyr_start](https://github.com/nxp-pro-support/zephyr-start/assets/152433281/8df1b0aa-721d-4895-a4ae-12a2d6c6ff4d)

4.) open the folder your created in step 1 in vs code.

You will see another folder of the same name "mcxn-iot" which has a hello world folder.

Right click on the hello world folder an "open in integrated terminal"

Run the command 

`west build -b frdm_mcxn947/mcxn947/cpu --pristine`

This will build the code for the MCXN947 EVK.  "pristine" tells west to start fresh.   Normally,  west builds without the pristine switch will only build what things that have changed.



5.)  Debug with Segger Ozone

In this workflow, I show using Segger Ozone to debug an application after a build.   

https://www.segger.com/products/development-tools/ozone-j-link-debugger/

Segger Ozone is a stand alone debugger that works with a j-link (or the EVK’s programmed as a J-Link).   It is a popular option in the Zephyr community.   It has many features that are not included in other debuggers such as live variable viewing and plotting data real-time.

Inside of the “hello_world” application is a file *mcxn947.jdebug* which is already configured to point to the output of the hello world build:

*hello-world/build/zephyr/zephyr.elf*

![debug_w_ozone](https://github.com/nxp-pro-support/zephyr-start/assets/152433281/a989f9bd-2523-4e7b-8b55-adedeb7094d7)

***Important note***

The MCX N series parts are flashless with a ROM bootloader.   There are a couple of extra steps to create a ozone project. 

You can use the mcxn947.jdebug as a template to copy to other example folders. 

You should be able to copy it to a folder of another project and it will point to the build/zephyr/zephyr.elf in the application folder.

https://wiki.segger.com/Debug_on_a_Target_with_Bootloader

'ROM bootloader
Should your setup be that you have a bootloader in ROM that needs to be executed first simply leave the functions AfterTargetDownload() and AfterTargetReset() empty (but not commented out!). This will override Ozone's default and nothing will be executed so the ROM bootloader can run without interference and jump to the application space where per default Ozone will then stop at main.'
