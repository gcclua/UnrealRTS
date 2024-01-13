# Unreal Engine 5 RTS Game

## Overview
This project is a Real-Time Strategy (RTS) game developed using Unreal Engine 5. It uniquely blends the power of C++ with the flexibility of Blueprints, ensuring robust and extendable gameplay mechanics. My approach involves building a strong C++ foundation, with every Blueprint deriving from a C++ base.

## Key Features
- **C++ and Blueprint Integration**: Leveraging the strengths of both C++ for performance-critical tasks and Blueprints for rapid prototyping and iteration.
- **RTS Gameplay Mechanics**: Implementing core RTS features like unit control, resource management, and AI opponents.
- **Iterative Design**: Focusing on achieving a full gameplay loop before commencing the art pass, ensuring a solid gameplay foundation.

## Current Progress
- [x] Camera movement
- [x] User interface to spawm and place buildings
- [x] Builders that will move to placed buildings and construct them
- [x] Resource farmers that will increment a resource count on the HUD
- [x] Enemies that will move to a goal over a set of randomised points
- [x] Towers and Units that will target and shoot at nearby enemies
- [x] Click and Drag unit selection
- [x] Sending a group of selected units to a location
- [ ] Full gameplay loop
- [ ] More sophisticated AI for enemies
- [ ] Buildings cost resources
- [ ] Different types of units
- [ ] More towers
- [ ] Art Pass
- [ ] Niagra Effects
- [ ] Ability to load and start a game from a menu

## Getting Started
### Prerequisites
- Unreal Engine 5.3.2
- Visual Studio 2022 or Rider

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/ErrolMc/UnrealRTS.git
    ```
2. Right click on TowerDefense.uproject and select "Regerate visual studio project files"
3. Open TowerDefense.sln in Visual Studio 2022/Rider and build the solution
4. Open TowerDefense.uproject in Unreal Engine 5.3.2

