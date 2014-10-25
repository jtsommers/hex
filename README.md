CMPS 109 Hex with GUI
===
Play a Hex Game with an AI using command line with GUI display

**Authors**
Matthew Balousek (mbalouse@ucsc.edu)
Jordan Sommers (jtsommer@ucsc.edu)

**Usage:** make will compile and run the program
**Input:** In addition to making moves as directed via command line, the player can enter "random" to fill the remaining spaces on the board randomly

This program implements a Monte Carlo AI player for the Hex game.

By running a large number of randomized game simulations before each possible move, the program is able to determine which move it needs to take to get the highest probability of winning. The computer takes about 5-7 seconds to decide on which move to make on our machines, but your mileage may vary.

We developed and tested on OSX, but the program is also confirmed to work on Unix with SSH. The user should interact with the program from the command line, and the GUI window will update accordingly after each move has been made.
A screenshot of a complete game has been included in case you are unable to get the GUI to display.

*A note on Unix: ssh -Y was required in our use case, your mileage may vary*
