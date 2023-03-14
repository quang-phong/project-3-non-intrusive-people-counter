<h1> Non-intrusive People Counter
<img src="https://github.com/quang-phong/project-3-non-intrusive-people-counter/blob/main/media/gif/doy-says-hi.gif" width="80px">
</h1>

<img align='right' src="https://github.com/quang-phong/project-3-non-intrusive-people-counter/blob/main/media/gif/walkman.gif" width="400px">

[![Linkedin Badge](https://img.shields.io/badge/-@quangphong-0072b1?style=flat&logo=LinkedIn&link=https://www.linkedin.com/in/quangphong/)](https://www.linkedin.com/in/quangphong/) 
[![Github Badge](https://img.shields.io/badge/-@quang--phong-171515?style=flat&logo=github&logoColor=white&link=https://github.com/quang-phong)](https://github.com/quang-phong)
[![Email Badge](https://img.shields.io/badge/-quangtrieuphong@outlook.com-00a2ed?style=flat&logo=microsoftoutlook&logoColor=white&link=mailto:quangtrieuphong@outlook.com)](mailto:quangtrieuphong@outlook.com)


Author: **Quang Phong**  
Year: 2022

## 🧐 What?
"Non-intrusive People Counter" is a privacy-preserving approach to monitor the number of occupants without infringing their privacy and negatively affecting customer experience. 

## 🤷 Why?  
With the rising public concern about privacy and the introduction of EU’s new data protection law, namely General Data Protection Regulation (GDPR), the use of different sensors and devices now have confronted more obstacles. As a result, non-intrusive sensors are preferable to invasive devices (Alam, Rahman, Kim, & Han, 2017). Air quality sensor is considered among the most privacy-preserving types. Meanwhile, CCTVs, which have been globally used to monitor rooms and examine people, are regarded as invasive of privacy (Brennan, Taylor, & Spachos, 2018). Not as revealing about occupants’ behaviors as CCTVs, noise monitors still process sounds and voices, which may make it not fully GDPR compliant. Above all, while an occupant can try to remain silence, no person is able to hold their breath during their entire stay, which is the main reason why seemingly subtle air quality sensors are believed to reveal information about occupancy.

The device is non-intrusive and privacy-preserving because no personal information can be taken out of the readings.

## ⚒️ How?  
This device has 2 active infrared sensors (IR sensors), working on the main principle of detecting the difference between the readings of the two sensors at a specific time to determine whether and in which direction one person has passed the device. Whenever one has to enter or leave the staff lounge, they have to pass the hallway, where the device is mounted under a shelf.

Besides, except for cases when occupants passing at a very fast pace, which is not usual, the device can detect the direction and the presence of visitors. As for each sensor, one emitter shoots out a pulse of IR light, which then hits objects blocking its way and is reflected back to the receiver. If it does not face any obstacle, the beam will not be directed back, which means readings of 0 values. In this case, the IR light will hit a couch at a fixed distance and be reflected back to the receiver, thus the sensor will always return stable readings. When somebody passes the device, they have to block the IR light emitted from either of the two sensors first, resulting in suddenly high values read by that sensor. Then the code behind it ensures the transition state is turned on, and the device only looks for the next abnormally high values returned by the other sensor to conclude that one entry or exit has been detected.

The data is collected on an event-based basis and updated in real time to an IoT platform.

## 🧱 Structure?
To avoid violating GDPR and the agreement of data confidentiality with the facility manager of the building, the data will not be made public here.  

This repository contains 3 folders:
- **src**
- **media** (media files)
  
## ✌️ Result?  
In normal settings, the device can easily detect whether somebody walks past the device in the corridor and their directions.

## 🪁 Future?
There are three fundamental upgrades that render the device more suitable for deployment. First, the IR sensors are sensitive to sunlight, demanding a flexible selection of thresholds to detect people during the day. Changes in daylight result in noises in IR sensor readings, and preselecting a fixed threshold is inappropriate. Second, although the counter is mounted at a place where people do not pay much attention to it and do not tend to stay there for informal dialogues, the sofa is far from the device. When entering or leaving the room, some people tend to walk close to the sofa rather than the shelf, making the sensors fail to detect significant changes out of their range. Third, although the IR lights are aimed at the lower torso of occupants, when one person walks by, they do not keep their arms close to their bodies. Arm swings in their locomotion exaggerate the number of people who pass the device. Last, since the hallway is not narrow, people can pass by the device in a group of two or three, which is the case because many tutors like to go together in a group to enter and leave the staff lounge. Consequently, sometimes the device will underestimate the real changes in occupancy.
