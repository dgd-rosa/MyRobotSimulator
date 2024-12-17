# **Robot Survival Game**

I developed this simple 2D Retro Game in C++ using the SFML library for multimedia elements. I created this to improve my C++ skills and had a lot of fun building this. Of course, there are some improvements to make as code organization or general gameplay. Below I will describe how to compile and run the game, as well as some highlights from the gameplay.

## **Installation**
Firstly install g++:

1. Update all the repositories by running the following command in the terminal.
```command
sudo apt update
```

2. Now install g++ by running the following command in the terminal:
```command
sudo apt install g++
```

3. Check if g++ was properly installed. If g++ is present, it will show the latest version of it. Otherwise, it will not show anything. Then you can install g++ first.
```command
g++ --version
```

### **SFML Library**
To build and run this program, we need to install the SFML library. The SFML library can be installed by running the following command in the terminal:

```command
sudo apt install libsfml-dev
```

## **How to Compile and Run**
Now that the setup is completed, I will show you how to compile and run this project.

1. Open a terminal in the project directory.
2. Run *ls* command to check if you are in the same directory as the makefile.
3. When you are in the makefile directory, just run:
```command
make
```
After this, the project will be compiled.
4. When the compilation is complete, run the following command to play the game:
```command
./robot_sim
```

After knowing this, you should have everything needed to compile and run this project/game.

## **GamePlay**

1.When you start the game, the this main menu appears. To start the game just select the "Start Game" option and press the **Enter** key.

<p align="center">
  <br><br> <!-- This adds spacing below the image -->
  <img src="https://github.com/user-attachments/assets/db5582ec-2add-462e-9729-02b89194357a" style="margin: 20px;">
  <br><br> <!-- This adds spacing below the image -->
</p>


2.The robot (player) can be moved using the arrow keys and can attack with projectiles pressing the **Z** key
<p align="center">
  <br><br> <!-- This adds spacing below the image -->
  <img src="https://github.com/user-attachments/assets/88df7302-7f6a-4fec-bbf4-7dfe9562a2c1" style="margin: 20px;">
  <br><br> <!-- This adds spacing below the image -->
</p>
<!--![robot_attack](https://github.com/user-attachments/assets/88df7302-7f6a-4fec-bbf4-7dfe9562a2c1)-->



3.There are some enemies that can attack the player. Attack them before they attack you.

<p align="center">
  <br><br> <!-- This adds spacing below the image -->
  <img src="https://github.com/user-attachments/assets/89b98400-ac35-4dc4-899e-45156b28cd20">
  <br><br> <!-- This adds spacing below the image -->
</p>
<!--![enemy_weak](https://github.com/user-attachments/assets/89b98400-ac35-4dc4-899e-45156b28cd20)-->


<p>
  4.During the game, enemies will spawn and the game will get more difficult over time. The main goal is to survive while gathering the most amount of points.
</p>

<p align="center">
  <br><br> <!-- This adds spacing below the image -->
  <img src="https://github.com/user-attachments/assets/d4763265-8902-49c7-864b-a5e97c64e40d" style="margin: 200;">
  <br><br> <!-- This adds spacing below the image -->
</p>

5.As some time pass, tougher enemies will spawn. Enemies tier list:
     1. Weakest - Blue
     2. Mid - Green
     3. Strongest - Orange

<p align="center">
  <img src="https://github.com/user-attachments/assets/1f6fb297-fab4-4991-9ae3-9ea54b57c9b4" style="margin: 20px;">
  <br><br> <!-- This adds spacing below the image -->
</p>

<!--![gameplay2](https://github.com/user-attachments/assets/1f6fb297-fab4-4991-9ae3-9ea54b57c9b4)-->

6. When the player gather enough XP (by picking Screws or killing enemies), the robot can level up and be stronger. This is the level up pop up that appears after leveling up:

<p align="center">
  <br><br> <!-- This adds spacing below the image -->
  <img src="https://github.com/user-attachments/assets/d594845c-6928-4092-a5af-609798ae6fa8">
  <br><br> <!-- This adds spacing below the image -->
</p>


<!--![LevelUpMenu](https://github.com/user-attachments/assets/d594845c-6928-4092-a5af-609798ae6fa8)-->

