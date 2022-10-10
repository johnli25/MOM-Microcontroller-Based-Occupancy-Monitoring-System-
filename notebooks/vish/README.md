# Vish's Lab Notebook

## Table of Contents
---
- [9/13/22: First Meeting with TA](README.md#9/13/22:-First-Meeting-with-TA)
- [9/16/22: Meeting with Jack Blevins](README.md#9/16/22:-Meeting-with-Jack-Blevins)
- [9/17/22: Identifying signals from only phones](README.md#9/17/22:-Identifying-signals-from-only-phones)
- [9/20/22: Second Meeting with TA](README.md#9/20/22:-Second-Meeting-with-TA)
- [9/26/22: Design Document Draft Review with TA and Professor](README.md#9/26/22:-Design-Document-Draft-Review-with-TA-and-Professor)
- [10/4/22: Design Document Presentation](README.md#10/4/22:-Design-Document-Presentation)


## 9/13/22: First Meeting with TA
In our first meeting with our TA, we made some introductions and gave her our pitch for the project proposal. Our TA said she did a similar project during her time as an undergraduate in ECE 445, but they used a very different approach with ultrasonic sensors instead. She gave us some advice on our project such as just purchasing a Wi-Fi module instead of trying to build one ourselves.

## 9/16/22: Meeting with Jack Blevins
Jack is an alum from the ECE Department and took some particular interest into our project as he thought it was very interesting. We met with him and gave our pitch for the project as well. He was definitely very invested in our project and gave some thoughtful feedback. He gave us an interesting scenario where the microcontrollers would be placed in neighboring rooms. He told us to find a work-around to account for the fact that the signals from one room could be actually reaching the microcontroller in the other room and vice-versa. This would give an inaccurate count of the number of people in the room as the signals would be counted twice.

## 9/17/22: Identifying signals from only phones
We were initially planning to capture signals from all devices emitting Bluetooth and Wi-Fi signals. However, I thought a more accurate count of the number of people in a room might be just identifying the signals from mobile phones instead. Since most people carry only one phone this would be a lot more accurate. I found a recent [paper](https://cseweb.ucsd.edu/~schulman/docs/oakland22-bletracking.pdf) on this topic where researchers talk about identifying whether the device is a mobile phone from the Bluetooth signal that it is emitting. Here is an [article](https://threatpost.com/bluetooth-signals-track-smartphones/179937/) summarizing this as well. Phones transmit a signal called Bluetooth beacons with an average rate of 500 beacons per minute. If our microcontrollers can somehow identify and isolate the signals that are giving about 500 beacons per minute, then we would be able to identify that the device is a phone. This method, however, might come with its own ethical considerations as it is actively trying to fingerprint and track the device as a phone.

## 9/20/22: Second Meeting with TA
The TA agve her feedback on our project proposal and things to look into for our upcoming design document submission. She told us to update our block diagram as some of the lines connecting to the cloud were confusing, since that's mostly used to indicate physical things. She also mentioned to update our visual aid with more specific labels.

## 9/26/22: Design Document Draft Review with TA and Professor
The Professor gave us some very helpful advice on revising our design doc. Some of the comments he gave:
- Be more specific with the RV table. Should be more low-level as well.
- Don't have random numbers in the requirements. There should be a clear reasoning behind the figures that we are coming up with. 

## 10/4/22: Design Document Presentation
We had our design document presentation yesterday and although we did pretty well, there were a few things that the professor and other peer reviewers brought up. In order to get within our 85% estimation for accuracy that we had in our high level requirement, we are going to have to calibrate our RSSI value when we start prototyping with our MOM board. This value boundary may change depending on the size of the room/sector where we are testing as well, so we would have to do multiple iterations of it to find out what works to meet our accuracy requirement. During our meeting today there was also a good discussion we had about placement of the devices in a room. For example, what if someone on a floor above the room placed their phone on the ground, while the MOM board was attached on the ceiling of the room below. Arguably, the RSSI value from that device would be higher due to its proximity. Another case might be when a phone is charging from a wall outlet from a shared wall with the room where the MOM board is affixed to. Once again, the MOM board might be picking up signals from that phone, thinking its also a part of the room. There's a lot of nuances like theses cases that we have to do trial-and-error experiements to find an optimal RSSI value to calibrate our MOM boards to looks out for.
