# Highway Management System

**Final Project - Algorithms and Data Structures**  
*Politecnico di Milano, 2023*  
**Valutazione: 30/30**

## Overview

Efficient highway management system implemented in C, focusing on electric vehicle stations, route planning, and optimization. Designed to balance memory and time complexities, the project applies advanced algorithms and data structures to solve real-world challenges.

## Core Features

- **Route Planning:** Optimized algorithms for pathfinding and stop minimization.
- **Station Management:** Add/remove stations dynamically.
- **Vehicle Management:** Manage vehicles with specific ranges across stations.

## Key Algorithms and Structures

- **Binary Search Trees (BST):** Efficient station management.
- **Dynamic Programming:** Optimal route selection.
- **Sorting & Recursion:** For station ordering and route planning.

## Commands

- `aggiungi-stazione <station_distance> <number_of_vehicles> <vehicle_ranges>`
- `aggiungi-auto <station_distance> <vehicle_range>`
- `rottama-auto <station_distance> <vehicle_range>`
- `demolisci-stazione <station_distance>`
- `pianifica-percorso <start_station_distance> <end_station_distance>`

## Example Usage

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
Detailed specifications  are provided in the [specification](specification/) folder.
