# HARDWARE REPORT

This documents Diorama, Circuitry and Arduino codes used in the Future Of Heat Project.

# Diorama

The Diorama is 3 feet by 3 feet and about 4 inches tall. It has bottom paneling to hold electronics and a foam insulation top where the terrain and the buildings were placed. All the electronics are mounted on the floor of the diroma, except for the transformer
which is screwed into the side of the diorama. All buildings on the diorama were 3D printed on an SLA printer. They were painted using acrylic paints and an airbrush. The base was constructed out of 4 two by four wood planks and one 3 foot by 3 foot painting frame.
The insulation foam was decorated with acrylic paint, model trees and static grass. The frame was assembled using wood screws and a hand drill. After that was assembled the frame was attached to the painting frame and the foam insulation was glued into place.
The foam had building foundations and roads cut out and then spackle was laid down over the non paved areas. The ground covering was sprayed with brown paint and the roads and foundation were painted black. Then trees had their placement holes drilled in and they were test fired.
The buildings were printed and then assembled on the dirham for testing. Once circuitry was complete the buildings were painted and the LED were set in place and the buildings were glued to their bases.

## Pictures of the System

# Circuitry

The purpose of the circuitry is to mimic the power consumption of real houses depending on the adoption rate of electric heating/vehicle (User Input).
Thus, it is necessary for the circuit to be able to accept a signal and react to it by changing its load. To accomplish this, we eventually decided to
use PhotoMOS Relays to control the flow of current in specific load branches. The specific relay model we used is (AQY210EH) from Panasonic Industry.
Here is link to the [Relay Data Sheet](/Resources/relay_datasheet.pdf).

The important information to get from it are the Min-Max forward current of the input signal (1.3 mA - 50mA), the input dropout voltage (1.25V), and the device schematic.
![RelaySchematic](/images/RelaySchematic.jpg)

A single house load follows the following circuit schematic:
![HouseLoadSchematic](/images/HouseLoadSchematic.pdf)

When choosing the resistor values we took into account two major factors: One was the maximum voltage and current on the relay input. And the other was the relative power consumption of electric heating and electric vehicles.

We built two “House Units” on one PCB board, so here is a picture of what we have
![1_2](/images/HouseLoadBoard.jpg)

As for the “Hotel Unit”, it follows this design which is slightly different than the house unit design because of the increase in current going through the electric heating branch. Notice how the electric heating branch is now split into two to allow for two relays to bear the work.
![HotelLoadSchematic](/images/HotelLoadSchematic.JPG)

With this done, all that is needed to complete the load circuit is to connect all the houses and the hotel in series to use the same power source. This is pictured in the following schematic.
![WholeCircuitSchematic](/images/WholeCircuitSchematic.JPG) 

# Arduino+ESP8266+Wiring

Regarding the hardware for this portion both the Arduino Mega and the ESP8266 are powered directly via USB ports. The Arduino Mega has power requirements of  7~12 V and a current of 500 mA~1A. Additionally, the ESP8266 has power requirements of 3.3 V and a current of 250 mA~500 mA. Both of these requirements can be met via USB cables powered directly by an accompanying laptop.

The Arduino Mega interfaces between the ESP8266 Feather Huzzah and the web app. It takes the serial inputs and uses them to complete 2 major goals, control the diorama’s LEDs and control the photodiode relays for the loads circuit. As the wiring for the entire project, which includes the LED and load controls for the 11 houses and the hotel would be too messy to understand, only the schematic for wiring for one house module is attached below. Specifically the 12 buildings are split up into 4 submodules consisting of 3 similarly sized houses.
![OneSubmoduleSchematic](/images/WholeCircuitSchematic.JPG)

As the Arduino is current limited to 20 mA per digital I/O pin and 200 mA for the total driving current, it is used mostly for logical signals and only used to drive other components sparingly. As seen in the schematic above each module requires 4 digital pins to act as input control to the demultiplexers, more specifically 3 pins for the R/G LED control and 1 pin for the R/B control. These pins only act as logical signals and the CD403BMT demultiplexers’ high input impedance results in a low ~1 mA current draw. Note that based on the pinout of the demultiplexer, refer to the voltage input into the demultiplexer that drives the R/G LED’s comes strictly from an external 6V battery source, as such all of the R/G LEDs are powered externally. Additionally all of the demultiplexers are powered by an additional external 6V battery source. However for the R/B LEDs as they require a PWM signal the Arduino needs to power this set of LEDs. Note that here only one digital pin is needed for one module, powering all 3 R/B LEDs in parallel. The only other instance of the Arduino acting as a power source is to drive the photodiode relays for the loads. In this case the circuitry for the loads has a 1300 Ohm resistor to regulate the current draw on the arduino pins to ~2.8 mA. As there are 25 relay control pins, 2 for each of the 11 houses and 3 for the hotel load, the total current draw on the Arduino Mega is 70 mA. This 70 mA value is well below the total current limits of the Arduino. 

Regarding the demultiplexer wiring, this isn’t visible from the one module schematic attached above but all the demultiplexers share one Arduino digital control pin for the enable signal. This choice was due to the need to save on the usage of Arduino pins, as the Arduino Mega only has 54 digital pins.  

To supplement the fact that the schematic only presents the connections for one house module, there is attached below a table of the pinouts for the Adruino Mega, the demultiplexers, and the ESP8266. Specifically note that the only wiring between the ESP8266 and the Arduino Mega are their TX and RX connection pairs.

As the Arduino Mega interfaces between the LED control, load control, and ESP8266 a lot of wiring is needed. In this projects’ specific case breadboards were used simply due to the fact that the team ran into time constraints and started on a PCB design too late in the semester. It is definitely preferable to use PCB correctly sized PCB cabling to get a neater more professional end product. Regardless a few images of the internal circuitry underneath the foam core diorama can be seen attached below. Apologies in advance for the poor visibility in some areas as the wires powering the LEDs need to be fed up through foam core.  
![Internal2](/images/diorama_two.JPG) 
![Internal3](/images/diorama_three.JPG)
