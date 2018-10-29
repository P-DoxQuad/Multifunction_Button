# Multifunction_Button-master

"The simplest solutions can solve the most complex questions - that is exactly the purpose of this project!"

Devices are seemingly becoming more and more complex having many instances of needing multiple user input to perform a designated action. This can be seen in the presence of having physical buttons, toggle switches, and even capacitive sensors to detect finger gestures. Generally speaking, a developer tries to make the experience as intuitive and hassle free as possible. Unfortunately this isn't always the case when paired up with an individual who has some kind of physical impairment. Such impairments can completely remove the ability to press a button or flick a switch - Thus rendering the device inoperable by the user. With that being said, this doesn't mean these types of users should be held back from being able to use the device. The barrier lies within the input method to the device and not the users physical limitations.


Two things need to be considered: 
1. What physical abilities does the user have. 
2. What is the best input modality, and how can it be maximized to the fullest potential.

This software assumes that a user has one reliable physical gesture that could be performed multiple times with purposeful intent, as well as the ability to alter the pattern of that gesture to create multiple actions.

Essentially the code monitors a pressed state of an input signal (typically given by a switch of some sort) and calculates the time variance to give two distinct activation gestures - short press, and long press. If the input signal is active within the duration of a short press, then the first action is executed. Vice-versa happens with a long press, executing the second action. 

All the details on how it works are commented within the source files. This code was written for Arduino and is intended to work standalone, as well as be dropped into any project of your choice that needs variance in user control. Download the sketch and all the accompanying source files to go with it. Open inside of the Arduino software or using the specific Visual Studio project files. Compile and flash the code to the microcontroller - or take the foundation of the logic and apply it to another project outside of Arduino.

If you have any questions feel free to contact me!

--ParadoxicalQuad
