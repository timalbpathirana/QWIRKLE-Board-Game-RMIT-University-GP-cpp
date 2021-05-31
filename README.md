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

<img width="406" alt="Screen Shot 2021-05-16 at 6 46 47 pm" src="https://user-images.githubusercontent.com/68840709/118391364-374ba580-b677-11eb-9109-75c14eb3fcc6.png">

<img width="410" alt="Screen Shot 2021-05-16 at 6 47 03 pm" src="https://user-images.githubusercontent.com/68840709/118391372-429ed100-b677-11eb-8265-aad849122914.png">

<img width="408" alt="Screen Shot 2021-05-16 at 6 47 28 pm" src="https://user-images.githubusercontent.com/68840709/118391381-4a5e7580-b677-11eb-9ce3-9bf854a13eb9.png">

	
## How to run
#### Use make file to compile the project  ``` $ make ```
#### Run the program using this code  ``` $ ./qwirkle ```

	
## Testing Infomation

This game is tested for all the class functions and passing integration testing. 
You can find the test files inside TestFiles.

To run a test case, you can use this form : ``` ./qwirkle < TEST-FILE  ```	

For example : ``` ./qwirkle < TestFiles/GameTesting/GamePlayTesting/incorrectTilePlacementTest.input ```
