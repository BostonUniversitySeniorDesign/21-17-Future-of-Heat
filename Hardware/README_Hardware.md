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
Here is link to the data sheet (RelayDataSheet).

The important information to get from it are the Min-Max forward current of the input signal (1.3 mA - 50mA), the input dropout voltage (1.25V), and the device schematic.
![RelaySchematic](/images/RelaySchematic.jpg)

A single house load follows the following circuit schematic:
![HouseLoadSchematic](/images/House Load Schematic.png)

When choosing the resistor values we took into account two major factors: One was the maximum voltage and current on the relay input. And the other was the relative power consumption of electric heating and electric vehicles.

We built two “House Units” on one PCB board, so here is a picture of what we have (1_2).

As for the “Hotel Unit”, it follows this design which is slightly different than the house unit design because of the increase in current going through the electric heating branch.

Notice how the electric heating branch is now split into two to allow for two relays to bear the work. (HotelLoadSchematic).

With this done, all that is needed to complete the load circuit is to connect all the houses and the hotel in series to use the same power source. This is pictured in the following schematic (WholeCircuitSchematic). 

# Arduino + Wiring