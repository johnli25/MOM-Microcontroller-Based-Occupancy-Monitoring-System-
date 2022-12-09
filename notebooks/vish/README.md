# Vish's Lab Notebook

## Table of Contents

- [9/13/22: First Meeting with TA](README.md#9/13/22:-First-Meeting-with-TA)
- [9/16/22: Meeting with Jack Blevins](README.md#9/16/22:-Meeting-with-Jack-Blevins)
- [9/17/22: Identifying signals from only phones](README.md#9/17/22:-Identifying-signals-from-only-phones)
- [9/20/22: Second Meeting with TA](README.md#9/20/22:-Second-Meeting-with-TA)
- [9/26/22: Design Document Draft Review with TA and Professor](README.md#9/26/22:-Design-Document-Draft-Review-with-TA-and-Professor)
- [10/4/22: Design Document Presentation](README.md#10/4/22:-Design-Document-Presentation)
- [10/16/22: Development Board Testing](README.md#10/16/22:-Development-Board-Testing)
- [10/24/22: Parts and waiting on PCB](README.md#10/24/22:-Parts-and-waiting-on-PCB)
- [10/31/22: AWS pipeline](README.md#10/31/22:-AWS-pipeline)
- [11/5/22: IoT rule and DynamoDB](README.md#11/5/22:-IoT-rule-and-DynamoDB)
- [11/10/22: Flask Web App](README.md#11/10/22:-Flask-Web-App)
- [11/16/22: Elastic Beanstalk](README.md#11/16/22:-Elastic-Beanstalk)
- [11/27/22: Future Work and Improvements](README.md#11/27/22:-Future-Work-and-Improvements)
- [12/2/22: Post Demo and Preparations for Final Presentation](README.md#12/2/22:-Post-Demo-and-Preparations-for-Final-Presentation)



## 9/13/22: First Meeting with TA
In our first meeting with our TA, we made some introductions and gave her our pitch for the project proposal. Our TA said she did a similar project during her time as an undergraduate in ECE 445, but they used a very different approach with ultrasonic sensors instead. She gave us some advice on our project such as just purchasing a Wi-Fi module instead of trying to build one ourselves.

## 9/16/22: Meeting with Jack Blevins
Jack is an alum from the ECE Department and took some particular interest into our project as he thought it was very interesting. We met with him and gave our pitch for the project as well. He was definitely very invested in our project and gave some thoughtful feedback. He gave us an interesting scenario where the microcontrollers would be placed in neighboring rooms. He told us to find a work-around to account for the fact that the signals from one room could be actually reaching the microcontroller in the other room and vice-versa. This would give an inaccurate count of the number of people in the room as the signals would be counted twice.

## 9/17/22: Identifying signals from only phones
We were initially planning to capture signals from all devices emitting Bluetooth and Wi-Fi signals. However, I thought a more accurate count of the number of people in a room might be just identifying the signals from mobile phones instead. Since most people carry only one phone this would be a lot more accurate. I found a recent [paper](https://cseweb.ucsd.edu/~schulman/docs/oakland22-bletracking.pdf) on this topic where researchers talk about identifying whether the device is a mobile phone from the Bluetooth signal that it is emitting. Here is an [article](https://threatpost.com/bluetooth-signals-track-smartphones/179937/) summarizing this as well. Phones transmit a signal called Bluetooth beacons with an average rate of 500 beacons per minute. If our microcontrollers can somehow identify and isolate the signals that are giving about 500 beacons per minute, then we would be able to identify that the device is a phone. This method, however, might come with its own ethical considerations as it is actively trying to fingerprint and track the device as a phone.

## 9/20/22: Second Meeting with TA
The TA gave her feedback on our project proposal and things to look into for our upcoming design document submission. She told us to update our block diagram as some of the lines connecting to the cloud were confusing, since that's mostly used to indicate physical things. She also mentioned to update our visual aid with more specific labels.

## 9/26/22: Design Document Draft Review with TA and Professor
The Professor gave us some very helpful advice on revising our design doc. Some of the comments he gave:
- Be more specific with the RV table. Should be more low-level as well.
- Don't have random numbers in the requirements. There should be a clear reasoning behind the figures that we are coming up with. 

## 10/4/22: Design Document Presentation
We had our design document presentation yesterday and although we did pretty well, there were a few things that the professor and other peer reviewers brought up. In order to get within our 85% estimation for accuracy that we had in our high-level requirement, we are going to have to calibrate our RSSI value when we start prototyping with our MOM board. This value boundary may change depending on the size of the room/sector where we are testing as well, so we would have to do multiple iterations of it to find out what works to meet our accuracy requirement. During our meeting today there was also a good discussion we had about placement of the devices in a room. For example, what if someone on a floor above the room placed their phone on the ground, while the MOM board was attached on the ceiling of the room below. Arguably, the RSSI value from that device would be higher due to its proximity. Another case might be when a phone is charging from a wall outlet from a shared wall with the room where the MOM board is affixed to. Once again, the MOM board might be picking up signals from that phone, thinking it's also a part of the room. There's a lot of nuances like these cases that we have to do trial-and-error experiments to find an optimal RSSI value to calibrate our MOM boards to looks out for.

## 10/16/22: Development Board Testing
After we received our ESP32 Development Board we started working on figuring out how to pick up probe requests. One of the issues that we found while running our tests was that Apple devices were randomizing their MAC addresses. While all Apple devices did this on default, it was also possible to randomize the hardware addresses for devices running Windows. This would be a problem for our MOM device design, because it would count a probe request coming from a different MAC address every time as a different device, when in fact it might just be the same device sending probe requests with a randomized hardware address every time.

## 10/24/22: Parts and waiting on PCB
We finished ordering all our parts, however, we are still just waiting on our PCB to be delivered. Meanwhile, we are continuing test on the Development Board.

## 10/31/22: AWS pipeline
This week, I spent the bulk of my time refining the AWS Cloud pipeline and how that is going to fit in with the overall scope of the project. AWS has a service called IoT Core that lets you connect billions of IoT devices and route trillions of messages to AWS services without managing infrastructure. When these IoT devices publish messages, they are transmitted and received using the MQTT protocol which minimizes the code footprint on the device and reduces network bandwidth requirements. AWS IoT core is then able to process these messages, communicate with other IoT devices and interact with other AWS services as well. So far, I have gotten the ESP-32 to send MQTT messages to the AWS IoT Core and then it displays it there.

## 11/5/22: IoT rule and DynamoDB
After the MQTT data is saved in the IoT Core we need to save that data in a database, so we can pull it to the web app later. For the database to save to I chose DynamoDB because it is a fully managed, serverless, key-value NoSQL database designed to run high-performance applications at any scale. After messages are received to IoT Core from the ESP-32 using the MQTT protocol, data can be saved to DynamoDB. This can be achieved using the IoT Act Rule. It gives devices the ability to interact with other AWS micro services. Rules are analyzed and actions are performed based on the MQTT topic stream such as writing data received from a device to an Amazon DynamoDB database. 

## 11/10/22: Flask Web App
Now that all the data is saved in DynamoDB, the Flask Web app needs to pull this and display it on the application. I had some trouble with getting the access keys from AWS IAM initially, but after setting up the certificates correctly the Flask Web app was able to pull from my AWS account.

## 11/16/22: Elastic Beanstalk
Since our web application should be accessible from any device, we need a place to host it from that can be accessible easily. Elastic Beanstalk seemed like a good option because it automatically handles the deployment details of capacity provisioning, load balancing, automatic scaling, and web application health monitoring. When trying to initially host it there, we ran into some trouble of getting the dependencies to work in the virtual environment. However, after including a requirements.txt file and writing an appropriate config file, the deployment was successful.

## 11/27/22: Future Work and Improvements
Contrary to our initial inception of the project where we wanted to use both Bluetooth and Wi-Fi signals for occupancy monitoring, we could only implement it with Wi-Fi signals in the end. Implementing occupancy monitoring using Bluetooth proved to be a lot harder than what we expected. However, in the future given more time to work on the project we plan on using a weighted average between cumulative Bluetooth and Wi-Fi traffic to better capture how busy a specific room is. 

Another future improvement to our project could be to include a graph of the most popular times when a room is busy and usually open. This graph would go right below our occupancy pie chart on our web application. The graph would forecast when a room is most available based on historical occupancy data that we would have collected and stored in our database. Using this approach, we could get a rough estimate of the number of people for a given future time. To forecast future occupancy, we could also use more sophisticated models such as an LSTM (Long Short-Term Memory) model which is a type of recurrent neural network that has vast applications when given time series data as inputs. Here is an [article](https://machinelearningmastery.com/how-to-develop-lstm-models-for-time-series-forecasting/) summarizing this well. It can predict pretty accurately when given proper data points and trained appropriately.

## 12/2/22: Post Demo and Preparations for Final Presentation
Our demo went great earlier this week, and our MOM device was 100% accurate in estimating the number of occupants in the senior design lab when we were demonstrating it. We got great feedback from the professor and TAs. As we get near the end of the semester, we need to finish our last two major assignments: Final Presentation and Final Report. We each went over what we will be presenting and rehearsed our sections with a mock presentation, so it would be smooth during the actual one. Also started working on the Final Report since it is due Wednesday next week.
