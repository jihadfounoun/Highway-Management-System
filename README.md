# Highway Management system
This project was the final exam for my Algorithms and Data Structures course at Politecnico di Milano in 2023.<br><br> Evalutation: 30/30
## Overview
This project is a practical demonstration of applying data structures and algorithms to address real-world challenges. Using C programming, I designed and implemented a highway management system. This system efficiently manages various elements of a highway, such as electric vehicle rental stations, vehicle additions and demolitions, and most importantly, route planning. A core focus was on implementing route planning algorithms that accounted for both time and space complexities
## Features
* Route Planning: Plan routes between stations, considering the constraints and capabilities of each station.
* Station Management : Add and remove stations.
* Vehicle Management: Add and remove vehicles at specific stations
## Algorithms and Data Structure used
* Binary Search Trees (BST): Used for efficient insertion, deletion, and search operations on stations.
* Recursion: Employed in various operations such as finding the minimum number of stops and planning the route.
* Sorting: Utilized to order stations based on specific criteria.
* Dynamic Programming Concepts: Applied in the route planning algorithm to ensure optimal path selection.
## Usage
The system accepts the following commands as input:

* aggiungi-stazione  <station_distance> <number_of_vehicles> <vehicle_ranges>: Adds a new station at the specified distance with the given vehicles.
* aggiungi-auto <station_distance> <vehicle_range>: Adds a vehicle to the station at the specified distance.
* rottama-auto <station_distance> <vehicle_range>: Removes a vehicle from the station at the specified distance.
* demolisci-stazione <station_distance>: Removes the station at the specified distance.
* pianifica-percorso <start_station_distance> <end_station_distance>: Plans the route between the start and end stations.
## Example
input:
```bash
aggiungi-stazione 91 9 5 4 5 5 4 6 5 4 5
aggiungi-stazione 24 6 5 4 5 4 4 5
pianifica-percorso 24 91
aggiungi-stazione 92 6 5 4 4 5 5 5
demolisci-stazione 59
aggiungi-stazione 52 9 13 14 13 17 17 15 18 15 16
aggiungi-auto 91 39
aggiungi-auto 52 39
aggiungi-auto 24 28
pianifica-percorso 24 92
```
output:
```bash
aggiunta
aggiunta
nessun percorso
aggiunta
non demolita
aggiunta
aggiunta
aggiunta
aggiunta
24 52 91 92
```
## Tools used
* Vallgring
* Callgring
* GCC
* GDB  
## Software used
* Visual studio code
* Clion
## Testing
The project includes a comprehensive set of 111 tests to ensure the correctness and robustness of the implemented functionalities. These tests cover various scenarios for station management, vehicle management, and route planning
## Documentation
For more detailed information about the project, refer to the SPECIFICATION folder included in the repository. This file contains comprehensive specifications and explanations of the system's functionalities and implementation details.
