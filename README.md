# ...Making a Game 

## Overview

I came across a situation where I had to explain how to work with C++ project to group of first timers. After that I decided to put that in writing, as a result I am writing here about how to make a simple 2D game.



## Game Idea 

Lets make a game called brick shooter, I got the idea from an old game I used to play which is called [bubble shooter](https://www.shooter-bubble.com/).


![alt text](https://www.shooter-bubble.com/bubble-shooter.jpg)




For programming part, I used C++ and started with C++98/03 version. This way we can see whats the difference between versions when we move to later versions. I used the microsoft visual studio 2012 IDE for this game development.


![alt text](https://res.infoq.com/news/2014/08/cpp14-here-features/en/resources/1cpp14-is-here-1.png)


Obviously, The user interface(UI) for the game, or any application for that matter, with C++ is a whole lot of work. So I used the "Simple and Fast Multimedia Library" or simply SFML for UI support.


![alt text](https://www.sfml-dev.org/images/logo.png)


I have collected the 2D assets for the game from http://www.kenney.nl/


![alt text](https://2.bp.blogspot.com/-NYVDYXySojg/W0Qy2wEmNDI/AAAAAAAAAOg/UwaSryw5Ag4_malzZClWK36upSmjGPrMgCLcBGAs/s320/sample.jpg)


The above image shows some of the 2D assets. we can make different kinds of games using these assets, for example swipe game, pong game or shooter game.



I am planing to make a shooter game using those assets so they might look lot like this.



![alt text](https://3.bp.blogspot.com/-BRnGT4LcbOs/W0Q1GcDSwsI/AAAAAAAAAO4/RtzcaOJA9zAHcaElujsfGqyJzS2FsztsgCLcBGAs/s320/screenshot.png)


## Using This Project with Visual Studion 2017
I used the Visual Studio 2012 when i made this project.
If you want to use this project on Visual Studio 2017 you have to use the appropriate SFML version as well, in this case you can download SFML 2.5.* .
In this project, find and replace the files from 'Includes' and 'Libs' folders with latest SFML version files and also the SFML DLLs in the debug folder.


