# Mister automatic
An automated approach to misting my mushroom farm



## Introduction
For my birthday this year, I've received my own mushroom farm. 
This farm starts out as a block of mycelium but promises to turn into edible mushrooms in approximately 10 days. 
In order to do so, the mycelium should first be submersed in water for a couple of hours and misted twice a day until the mushrooms are ready. 
When starting this farm I completely forgot my upcoming 4 days away from home, which would most likely mean my mushroom farm would dry out.


Since it was too late to postpone the farm, a different solution had to be found to mist my mushrooms whilst I was away from home. 
Furthermore a solution had to be found and created within 4 days so there was no time to order new components.



## Design
The biggest problem was the amount of force required to activate the spray nozzle. The motor must obviously have enough torque but at the same time, the bottle should not move when the motor is activated.

Speaking of activation: this system should mist my mushrooms twice a day and each time it activates a couple of 'pumps' are required.
Preferably, there would also be a feedback to the user like emails or notifications to existing home automation sytems.
To obtain this behaviour, a wifi enabled microprocessor is required along with a small pcb to manage power distribution.

This problem is therefore divided into thre separate issues: 
- Selecting a sufficiently strong motor
- Designing a robust, preferably self-supporting system
- Controlling the system

At the end of this section, a proof of concept is evaluated.

### Motor
To solve the first issue, the MG996R servo motor was used; a high torque metal gear servo. Although this motor has sufficient torque (11kg/cm @ 6V), it can draw up to 2.5A of current.

The servo horn I had available is a metal arm with a maximum arm of 2.5cm, reducing the max torque to 4.4kg.
A quick test using a portable luggage scale was performed to verify if this would be enough. 
Since approximately 2 kg is required to fully retract the spray nozzle arm, the combination of the MG996R servo motor and 2.5cm servo horn should be strong enough.

Besides the 6V stall torque, the 4.8V stall torque was also specified by the manufacturer: 9.4kg/cm.
Using a 5V source and the same 2.5cm servo horn should still result in a max torque of ~3.8kg. 

This is very usefull information since I don't have any 6V sources which can supply up to 2.5A laying around but I do have many 5V usb chargers which can easily handle up to 3A.

### CAD
The second problem had to be solved using CAD. To prevent the bottle moving when spraying, the force used to activate the spray had to come from a part which is attached to the spray head but does not move during spraying.
By manually spraying a bit, I figured the most sturdy part which satisfies above demands would be the screwcap of the bottle.

The body of the system was thus designed to mimic how a human holds the spray bottle but with some attachements added for the selected servo motor. 
The image below shows the assembly of the cad model and the servo motor.

In order to attach the servo horn to the spray lever, a small clip which just snaps onto said lever and an arm to couple the clip to the servo horn was designed as well. 
These models are not explicitly shown in this section but will be visible in later pictures.

![](image/assembly.png)




### Controller
ESP8266 -> wemos D1 mini, usb breakout for power in, power distribution, protection diode on wemos module and on pcb, schematics

<!-- ![](image/schematic.svg) -->

### Proof of concept
![](image/spray_bottle.webp)

rotation unscrews nut from servo horn -> self-locking nut used
flex in the arm which actuates the spray lever is beneficiary compared to a fixed arm: requires less force and the system is more forgiving for fast accelerations. con: it will break over time

## Conclusion
Aluminium extrusions
completely non-invasive adjustments to automate spray bottle
files provided in amf and freecad format

![](image/result.jpg)

### Note
Please ignore the 'danger' and 'imflammable' labels on the spray bottle, this is what I had at hand and it has been cleaned thourouly, I promise!

<!-- More info and code:
<a href="https://github.com/klushok-etv/SantaSignaller"><img src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white"></a>

[test](test2)

[ ![](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white) ](https://github.com/klushok-etv/SantaSignaller) -->
