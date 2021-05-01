# Future Of Heat

Welcome to *“The Future of Heat”* project, created by Team 17 of BU’s Senior Design class 2020-21.
As global warming is becoming more severe, non-renewable energy sources such as natural gas and oil are falling out of favor.
Using natural gas and oil to heat homes and businesses only continues to accelerate the warming of our planet.
One of the promising alternatives is using electricity for heating and transportation. So we were tasked by National Grid to create an
educational model that will teach the public about the benefits of electric heating and how it will affect power grid systems in
the future. The project will be a web application connected to a three by three feet diorama. Users input variables like the
adoption rate of electric heating, and the diorama responds accordingly by changing the LED colors and changing the power consumption of
the miniature power grid inside of it. 

There are three major components to this teaching device:
*   The web application
*   The power grid circuitry
*   The diorama.

The web application takes in user inputs and sends it via Wifi to the arduino receiver unde the diorama.
The arduino then interprets the data and outputs the necessary commands to the circuitry to display the appropriate heat and resource LEDS.
The diorama has 11 houses, one hotel, and one power plant. The houses and hotels have two color changing LEDS, one that smoothly transitions between blue and red to show internal house temperature, and one LED that digitally transitions between green(electrical heating) and red(gas heating).

Each house is mimicked by a load circuit that is hooked up to the arduino, and the hotel has a specialized load circuit that mimics multiple rooms in a hotel. The website is able to take in specified weather and temperature conditions from the user and sends them to the arduino.
The website application will also show users a series of graphs and data plots of relevant information related to the electrical grid and the adoption rate of electrical heating/vehicles

The following “README” files go into depth about the specifics of the project. So, if you are curious about how we implemented some of the project’s functionality, just go to the appropriate file and you will find your answer. To facilitate easier navigation, we will summarize the project parts below and where to read more about them.

*	[Software README](/Software/README_Software.md):
	-	Web application back end and front end.
	-	Arduino code controlling the LEDs.
	-	Serial communication between the Arduino and the webapp.

*	[Hardware README](/Hardware/README_Hardware.md):
	-	Diorama components and building process.
	-	Power grid circuitry design and component values.
	-	Ardunio Mega wiring. 
 
