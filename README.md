# Pokemon Sword/Shield auto hatcher

Automatically hatches pokemon in sword and shield with the aim of allowing users to farm shinies overnight. 

Scripts are currently complete for the following:
* 10240 base egg steps multi hatching (~10:00 for 3-5 eggs)
* 2560 base egg steps single egg hatching (~1:50/1 egg)
* 3840 base egg steps single egg hatching (~2:15/1 egg)
* 5120 base egg steps single egg hatching 
* 7680 base egg steps single egg hatching
* 10240 base egg steps single egg hatching
* 5 box release (releases 5 consecutive boxes of pokemon)

Scripts that support lower powered boards (arduinos mostly):
* 5 box release (releases 5 consecutive boxes of pokemon)
* All scripts will be updated for baseline support for ATMega16U2 and above + all new scripts will have support included

Scripts in the planning phase:
* Surprise trade whole box
* Hatch many boxes
* Watt farming


If you would like to just download the hex files for flashing, go [here](https://github.com/ironandstee1/pkmn-hexes). The directions on thie Readme are specifically for people who want to make the files themselves, either for the purpose of understanding or changing the code. The instuctions below require knowledge of how to install and use a gcc. A link/tutorial is provided for windows. 


## Requirements

### Hardware
One or the other of:

* Teensy++ 2.0 
  * Available on amazon
  * Must also have one of those fatter microUSB cables
* Arduino/pro micro/something with a compatible chip (ATMega16U2, ATMega32U4, etc)
  * Not all code is supported yet. 5 box release is the only thing supported at the moment. 

### Software
* [Teensy Loader](https://www.pjrc.com/teensy/loader.html)
* [Atmel Gnu Toolchain](http://fab.cba.mit.edu/classes/863.16/doc/projects/ftsmin/windows_avr.html)
  * This is necessary if you want to build the code or edit the scripts in any way on windows exclusively
  * There are issues with this and building for Arduino. If you want to build for Arduino follow my Installing Ubuntu + building guide below
  * I followed this tutorial up to installing avrdude
* [Git for windows](https://gitforwindows.org/)
  * Again, only necessary if you want to build the code or edit the scripts in any way
  * Can be used to clone this repo as well, but downloading as zip will do

## How to use this

### Installing Ubuntu on Windows Subsystem for Linux + building for ATMega and other boards

This is only necessary if you want to build the scripts yourself. Windows subsystem for linux isn't the easiest to interface with USB, so I'll be showing you how to make the files here and flash them with your program of choice (teensy loader, atmel flip) on windows. 

1. Open the microsoft store and install Ubuntu 
1. Let it set up and create a username and password for yourself
1. Enter this code once you're all set up
``` 
sudo apt-get update
sudo apt-get install -y make gcc-avr-libc
sudo apt-get install git
mkdir git
cd git
git clone https://github.com/ironandstee1/pkmn-auto-hatcher.git
cd pkmn-auto-hatcher
```
Edit the mcu in the makefile to be whatever you want it to be that's compatible (atmega16u2, etc). When you try the below steps, if you've typed the wrong one, it will tell you in the console. 
```
make clean
make
```
1. Open your windows file explorer and navigate to C:/Users/yourusername/AppData/Local/Packages/CanonicalGroupLimited.UbuntuOnWindows.../LocalState/rootfs/home/yourubuntuusername/git/pkmnauto-hatcher
1. Get your Joystick.hex file and move it to wherever is convenient for you
1. Create a shortcut or pin this location
1. Load it using atmel flip

### Making and loading for Teensy++ 2.o
1. Clone the repo to your local machine
1. Navigate to the directory
1. Uncomment the code you want or add your own script
1. Run "make clean"
1. Run make
1. Load the Teensy Loader program
1. Click the Open Hex File button (a little gray list) and select the hex file
1. Press the button on the Teensy++ 2.0. You should now see it appear in the Teensy Loader program
1. Press the program button (green arrow going into the hole) 

### Loading the script (no build) on Teensy++ 2.0
1. Download the appropriate hex file for your pokemon's egg steps.
  * Hex files can be found [here](https://github.com/ironandstee1/pkmn-hexes)
  * A list of pokemon egg steps can be found [here](https://bulbapedia.bulbagarden.net/wiki/List_of_Pok%C3%A9mon_by_base_Egg_cycles)
1. Plug your Teensy++ 2.0 into your computer
1. Load the Teensy Loader program
1. Click the Open Hex File button (a little gray list) and select the hex file
1. Press the button on the Teensy++ 2.0. You should now see it appear in the Teensy Loader program
1. Press the program button (green arrow going into the hole) 

### Preparing in game

1. Get the oval charm. Multi hatch scripts avoid some of the pitfalls of not having this, but this improves the efficiency. 
1. Get a pokemon with flame body in your party slot 6. I grabbed carkoal from the mine tracks as they can be easily caught due to low level and some already have the ability.
1. Make sure that your party is full and there are no eggs. 
1. Put your pokemon to breed in the daycare (look up the Shiny Charm and Masuda method - both will help your shiny chances)
1. Run around until the day care lady has an egg but don't grab it just yet. 
1. Warp to route 5. Make sure you are not on your bike. Make sure that when you open the menu that "Town Map" is where your selection defaults to when you press X. Don't move from in front of the camp. The script is pretty sensitive to positioning. If you need to, warp again once you're ready. 

### Getting going

1. Disconnect all your controllers from your switch. Attached joycons and procons included. If you are in the game this should not cause any issues and you will not see any pop ups. 
1. Plug the Teensy into one of your dock ports. 
1. Once your character walks up and starts talking to the day care lady and gets the first egg, you should be good to go

More specific instructions for certain scripts like Release can be found [here](https://github.com/ironandstee1/pkmn-hexes).

## Improvements from past scripts

* Added C macros
  * Simplifies the process of calling repetitive actions
  * Improves readability and editability of scripts
  * Main scripting work has been shifted off to the header file instead of the c file
* Added states
  * Supports far more intensive and robust scripts while significantly lowering requirements 
* Added new buttons and button macros - not a large improvement, but these are available

### Thanks

Thanks to Shiny Quagsire for his [Splatoon post printer](https://github.com/shinyquagsire23/Switch-Fightstick) and progmem for his [original discovery](https://github.com/progmem/Switch-Fightstick).

Thanks to [bertrandom](https://github.com/bertrandom/snowball-thrower/) the foundation of this script/method.

Thanks as well to all other contributors to previous projects. 

## How can you help?

### Suggest new scripts for pokemon or other games

Do you have an idea for a script for this game or another game? Let me know by adding comments somewhere here. I am willing to make scripts or even new projects if the call is there. 
