# Advanced Programming Technique - Assignment II

## More Than Meets The Eye

![Qwirkle_banner](https://user-images.githubusercontent.com/68840709/117711903-030b5b80-b217-11eb-8d22-32c48bb44402.png)

## Table of contents
* [Project info](#general-info)
* [How to run](#How-to-run)
* [Testing Infomation](#Testing-Infomation)

## General info

In this assignment project, we implemented a 2-player text-based version of the Board Game Qwirkle using C++.
In this game, player can,
- Play a new game.
- Load a saved game from a file.
- Save the current game.

Below are some screenshot of the game. 

<img width="398" alt="Screen Shot 2021-05-28 at 1 13 23 am" src="https://user-images.githubusercontent.com/68840709/119851672-f0e92700-bf51-11eb-8e89-273574b3221b.png">

<img width="376" alt="Screen Shot 2021-05-28 at 1 13 01 am" src="https://user-images.githubusercontent.com/68840709/119851763-078f7e00-bf52-11eb-9fdc-dee461cc972b.png">
	
## How to run
#### Use make file to compile the project  ``` $ make ```
#### Run the program using this code  ``` $ ./qwirkle ```

	
## Testing Infomation

This game is tested for all the class functions and passing integration testing. 
You can find the test files inside TestFiles.

To run a test case, you can use this form : ``` ./qwirkle < TEST-FILE  ```	

For example : ``` ./qwirkle < TestFiles/GameTesting/GamePlayTesting/incorrectTilePlacementTest.input ```
