#ED-Custom-Cockpit

##What it is

I am building a Custom Cockpit for Elite Dangerous (A Space Flight Sim)

In order to gain some more immersion (and because it is frigging cool) I am making a set of control panels that can interface with the game to control several inputs and by taking advantage of a microcomputer I can program multi Input events and LED feedback.
 
##How it works

By using the [UnoJoy](https://github.com/AlanChatham/UnoJoy) project I am able to flash the USB communication chip on a Arduino to function as a PS3 controller, With this in place I am able to write my own Arduno sketch and through a few simple commands I can send PS3 input.

##What makes it cool

Initially I plan on only building one 'Module' to handle a few button inputs for in game Stealth control however I have built a custom daisy-chainable Bus that will allow me to easily expand by adding new control panels without adding additional micro controllers, this is done via my 'ModuleBus'.

My Module bus is a simple bus with 6 lines: VCC, GND, Clock, Latch, Data and Return. By using shift registers and some clever code I can attach any number of simple Output and Input devices to this bus without the need of additional micro-controllers Additionally through the use of some custom classes in my code I can achieve PWM output on any of the outputs connected to this bus.

##The Code

So below you will find a brief rundown of the different classes I have created to manage this control panel:

####ModuleBus

The ModuleBus class allows you to define the number of modules attached to the data bus, each 'module' is just two '74hc595' Shift Registers wierd up in series with the first shift register dedicated to input devices and the second register dedicated to output devices. The ModuleBus class is responsible for sending data to our modules and for retrieving data from our module inputs. This is presented as three simple functions: getInput, setOutput and refreshBusCache (this invokes the communication with our hardware)

####Animator

All our outputs are digital, that means we have to use [PWM](https://www.google.co.uk/url?sa=t&rct=j&q=&esrc=s&source=web&cd=3&cad=rja&uact=8&ved=0ahUKEwiInaSJ4uDTAhXBb1AKHbpfDjUQFgg2MAI&url=https%3A%2F%2Flearn.sparkfun.com%2Ftutorials%2Fpulse-width-modulation&usg=AFQjCNFXn5ePS8DCIPs4NgF4-2IrJbLb3w) to control individual LED brightness, with this in mind I created the Animator class to alternate between off and on in rapid succession to emulate PWM. To use simply create a instance of the Animator class (passing in a reference to your module bus plus what module and pin your LED is on), set your animation through the setAnimation function and be sure to call the clock function every time your main loop function refreshes (this iterates over the next PWM value)

####InOut

Just a class to manage all my different Inputs and Animated outputs and give each one a human readable name (instead of Module 1 pin 2 etc)

####UnoJoy

UnoJoy is a existing project by 'AlanChatham' https://github.com/AlanChatham/UnoJoy the class used here is a carbon copy from his repo, for more information go to https://github.com/AlanChatham/UnoJoy