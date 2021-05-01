# HARDWARE REPORT

This documents Diorama, Circuitry and Arduino codes used in the Future Of Heat Project.

# Diorama

The Diorama is 3 feet by 3 feet and about 4 inches tall. It has bottom paneling to hold electronics and a foam insulation top where the terrain and the buildings were placed. All the electronics are mounted on the floor of the diroma, except for the transformer
which is screwed into the side of the diorama. All buildings on the diorama were 3D printed on an SLA printer. They were painted using acrylic paints and an airbrush. The base was constructed out of 4 two by four wood planks and one 3 foot by 3 foot painting frame.
The insulation foam was decorated with acrylic paint, model trees and static grass. The frame was assembled using wood screws and a hand drill. After that was assembled the frame was attached to the painting frame and the foam insulation was glued into place.
The foam had building foundations and roads cut out and then spackle was laid down over the non paved areas. The ground covering was sprayed with brown paint and the roads and foundation were painted black. Then trees had their placement holes drilled in and they were test fired.
The buildings were printed and then assembled on the dirham for testing. Once circuitry was complete the buildings were painted and the LED were set in place and the buildings were glued to their bases.

## Pictures of the System
![DioramaTop View](/images/DioramaTopView.png)





# Circuitry

The purpose of the circuitry is to mimic the power consumption of a typical home depending on the adoption rates of electric heating/vehicle (User Input). Thus, it is necessary for the circuit to be
able to accept a signal and react to it by changing its load profile. To accomplish this, we decided to use PhotoMOS relays to control the flow of current in specific load branches. The relay model we
used is (AQY210EH) from Panasonic Industry. We chose this specific relay because it allows current control in both directions (supports AC), can handle the power draws of the load branches with ease, and
is very compact/low-profile. Here is the link to the data [Relay Datasheet](/Resources/relay_datasheet.pdf). The main important information to get from it are the minimum and maximum forward currents of the input signal (1.3mA - 50mA),
the input dropout voltage (1.25V), and the device schematic. ![RelaySchematic](/images/RelaySchematic.jpg)


A single house load follows the following circuit schematic: ![HouseLoadSchematic](/images/HouseLoadSchematic.pdf)



When choosing the resistor values, two major factors were taken into account: the maximum threshold voltage and current on
the relay input as well as the relative power consumptions of electric heating and electric vehicle branches.
We decided to build two “House Unit” on a single PCB board to save budget and space. ![House Load Board](/images/HouseLoadBoard.jpg)



The “Hotel Unit” follows a similar design to the “House Unit” but with a minor difference due to the large increase in current flowing
through the electric heating branch, approaching the current threshold of the relay. Notice how the electric heating branch is now split into two,
allowing for a safe and functional operation of the relay. ![HotelLoadSchematic](/images/HotelLoadSchematic.JPG).



Since we did not have the resistors necessary to construct the hotel load, we connected some 400 Ohm resistors in parallel to match the equivalent resistances of each branch. ![HotelPCB](/images/HotelPCB.jpg).



With the house and hotel loads complete, all that remains to complete the power grid is to connect all of the loads in parallel with respect to one another, forming a grid system.
This is pictured in the following schematic and in the diorama ![WholeCircuitSchematic](/images/WholeCircuitSchematic.JPG)


![WholePCB](/images/WholePCB.jpg)



The load circuitry is a major part, but no circuit is complete without a power source. This circuit draws power from a US standard wall socket (120V - 60Hz) and steps down the voltage using a transformer to ~14V.
The transformer we used is a class 2 transformer from Triad Magnetics with the model number (TCT50-03E07K). Here is the [Transformer Data Sheet](/Resources/TransformerDataSheet.pdf).

The transformer primary is soldered to a 3-prong power cable and the secondary to the circuit. The ground wire of the 3-prong power cable remains unconnected. To increase electrical safety, we added a 0.5A fuse
to the transformer primary since it is connected to the hazardous wall outlet. Although  highly unlikely, the fuse ensures that the transformer does not cause damage to either itself or to the rest of the circuit
if there were to be a short circuit or a power surge in the primary.


All wires are insulated with electrical tape and all electronics are mounted inside of the diorama away from user access to maximize safety and minimize the likelihood of electrical failure/injury. The transformer
is fixed onto the inner side of the diorama and the load PCB boards are hot-glued onto the bottom paneling. The completed circuitry under the diorama: ![diorama_one](/images/diorama_one.jpeg)




# Arduino+ESP8266+Wiring

Regarding the hardware for this portion both the Arduino Mega and the ESP8266 are powered directly via USB ports. The Arduino Mega has power requirements of 7-12 V and a current of 500 mA-1A. Additionally, the ESP8266 has power requirements of 3.3 V and a current of 250 mA-500 mA. Both of these requirements can be met via USB cables powered directly by an accompanying laptop.

The Arduino Mega interfaces between the ESP8266 Feather Huzzah and the web app. It takes the serial inputs and uses them to complete 2 major goals, control the diorama’s LEDs and control the photodiode relays for the loads circuit. As the wiring for the entire project, which includes the LED and load controls for the 11 houses and the hotel would be too messy to understand, only the schematic for wiring for one house module is attached below. Specifically the 12 buildings are split up into 4 submodules consisting of 3 similarly sized houses.


![OneSubmoduleSchematic](/images/ArduinoPinout.JPG)


As the Arduino is current limited to 20 mA per digital I/O pin and 200 mA for the total driving current, it is used mostly for logical signals and only used to drive other components sparingly. As seen in the schematic above each module requires 4 digital pins to act as input control to the demultiplexers, more specifically 3 pins for the R/G LED control and 1 pin for the R/B control. These pins only act as logical signals and the CD403BMT demultiplexers’ high input impedance results in a low ~1 mA current draw. Note that based on the pinout of the [demultiplexer](/Resources/Demultiplexer_CD403BMT_ Datasheet.pdf) ,
refer to the voltage input into the demultiplexer that drives the R/G LED’s comes strictly from an external 6V battery source, as such all of the R/G LEDs are powered externally. Additionally all of the demultiplexers are powered by an additional external 6V battery source. However for the R/B LEDs as they require a PWM signal the Arduino needs to power this set of LEDs. Note that here only one digital pin is needed for one module, powering all 3 R/B LEDs in parallel. The only other instance of the Arduino acting as a power source is to drive the photodiode relays for the loads. In this case the circuitry for the loads has a 1300 Ohm resistor to regulate the current draw on the arduino pins to ~2.8 mA. As there are 25 relay control pins, 2 for each of the 11 houses and 3 for the hotel load, the total current draw on the Arduino Mega is 70 mA. This 70 mA value is well below the total current limits of the Arduino. 


Regarding the demultiplexer wiring, this isn’t visible from the one module schematic attached above but all the demultiplexers share one Arduino digital control pin for the enable signal. This choice was due to the need to save on the usage of Arduino pins, as the Arduino Mega only has 54 digital pins.  

To supplement the fact that the schematic only presents the connections for one house module, there is attached below a table of the pinouts for the Adruino Mega, the demultiplexers, and the ESP8266. Specifically note that the only wiring between the ESP8266 and the Arduino Mega are their TX and RX connection pairs.


![PinoutTable](/images/ArduinoPinoutTable.JPG) 


As the Arduino Mega interfaces between the LED control, load control, and ESP8266 a lot of wiring is needed. In this projects’ specific case breadboards were used simply due to the fact that the team ran into time constraints and started on a PCB design too late in the semester. It is definitely preferable to use PCB correctly sized PCB cabling to get a neater more professional end product. Regardless a few images of the internal circuitry underneath the foam core diorama can be seen attached below. Apologies in advance for the poor visibility in some areas as the wires powering the LEDs need to be fed up through foam core.  


![Internal2](/images/diorama_two.jpeg) 


![Internal3](/images/diorama_three.jpeg)
