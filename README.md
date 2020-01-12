# Pokemon Sword/Shield auto hatcher

Automatically hatches pokemon in sword and shield with the aim of allowing users to farm shinies overnight. 

This script is currently in progress - it is functional for 2 hatches at 5,120 base egg steps at a little over 5 minutes, or a little over 2.5 minutes per hatch. That's 20-24 pokemon per hour, or 160-192 pokemon per night. Mileage may vary as this script is still a work in progress. 

## Requirements

### Hardware
* Teensy++ 2.0 
  * Other teensy boards can be used but require different procedures than are listed here
  * Arduino Unos can be adapted for use with these scripts using a DFU programmer. Instructions will not be provided here until I can work this out myself. 
  * Must also have one of those fatter microUSB cables if you're using a Teensy++ 2.0. 

Note: I do this on a docked switch. I've tested versions of this script for about a dozen hours at a time. 


### Software
* [Teensy Loader](https://www.pjrc.com/teensy/loader.html)
* [Atmel Gnu Toolchain](http://fab.cba.mit.edu/classes/863.16/doc/projects/ftsmin/windows_avr.html)
  * This is necessary if you want to build the code or edit the scripts in any way
  * I followed this tutorial up to installing avrdude
* [Git for windows](https://gitforwindows.org/)
  * Again, only necessary if ou want to build the code or edit the scripts in any way
  * Can be used to clone this repo as well, but downloading as zip will do

 

## How to use this

### Loading the script
1. Download the appropriate hex file for your pokemon's egg steps.
  * Hex files can be found [here]
  * A list of pokemon egg steps can be found here [https://bulbapedia.bulbagarden.net/wiki/List_of_Pok%C3%A9mon_by_base_Egg_cycles]
1. Plug your Teensy++ 2.0 into your computer
1. Load the Teensy Loader program
1. Click the Open Hex File button (a little gray list) and select the hex file
1. Press the button on the Teensy++ 2.0. You should now see it appear in the Teensy Loader program
1. Press the program button (green arrow going into the hole. 

### Preparing in game

1. Get the oval charm. This is necessary otherwise the timing on the script will be messed up becasue you can't get eggs fast enough. 
1. Get a pokemon with flame body in your party slot 6. I grabbed carkoal from the mine tracks as they can be easily caught due to low level and some already have the ability.
1. Make sure that your party is full and there are no eggs. 
1. Put your pokemon to breed in the daycare (look up the Shiny Charm and Masuda method - both will help your shiny chances)
1. Run around until the day care lady has an egg but don't grab it just yet. 
1. Warp to route 5. Make sure you are not on your bike. Make sure that when you open the menu that "Town Map" is where your selection defaults to. Dont move from in front of the camp. The script is pretty sensitive to positioning. If you need to, warp again once you're ready. 

### Getting going

1. Disconnect all your controllers from your switch. Attached joycons and procons included. If you are in the game this should not cause any issues and you will not see any pop ups. 
1. Plug the Teensy into one of your dock ports. 
1. Once your character walks up and starts talking to the day care lady and gets the first egg, you should be good to go. 

## Improvements from past scripts

* Added C macros
  * Simplifies the process of calling repetitive actions
  * Improves readability and editability of scripts
  * Main scripting work has been shifted off to the header file instead of the c file
* Added new buttons and button macros - not a large improvement, but these are available. 

## Future work and needed help

* Day care optimization
  * The average daycare egg hatch time is much less than I have implemented here. This is due to the fact that the current script will break if the daycare does not have an available egg. 
  * Tight timing can possibly fix this
    * Case 1: If you press A twice when there is an egg present, a pause in between the egg acceptance message and your ability to click will happen
    * Case 2: If you press A twice then B twice when there is no egg present, the process will exit without you taking your pokemon out from the day care
    * With tight timing, you may be able to implement a double B click and a direction change in the time that the pause happens in Case 1. This will allow you to avoid taking pokemon out of the daycare even if the daycare lady has no egg. Using this, you could bring down the amount of turns needed to get the egg on average and pick up more eggs before moving on to the route script
    * This timing has previously been too tight for me to work through in a timely manner
    


### Thanks

Thanks to Shiny Quagsire for his [Splatoon post printer](https://github.com/shinyquagsire23/Switch-Fightstick) and progmem for his [original discovery](https://github.com/progmem/Switch-Fightstick).

Thanks to [bertrandom](https://github.com/bertrandom/snowball-thrower/) he pretty much made the foundation for this script. This is an improved/more modular verison catered to pokemon shiny hunting. 

Thanks as well to all contributors to previous projects. 
