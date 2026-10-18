# ScaredyImp 👻

ScaredyImp is a classic 3D platformer developed with Unreal Engine 5 and C++. Players navigate through a series of challenging levels, overcoming enemies, environmental hazards, and interactive obstacles to reach their destination.

The project combines responsive character controls, AI-driven enemies, and diverse gameplay mechanics to deliver an engaging platforming experience.

## Technologies

- **Unreal Engine 5 / C++** – Core gameplay programming
- **Enhanced Input** – Character movement and controls
- **AI Perception & StateTree** – Enemy detection and behavior
- **Unreal Engine Physics** – Collision detection and interactive obstacles
- **Blueprints & UMG** – Gameplay integration and user interface

## Key Features

### Character Mechanics
- Sprinting and jumping
- Stomp attacks to defeat enemies
- Health system with damage and death handling
- Checkpoint and respawn system

### Enemy AI
- Ghost and Zombie enemies
- Player detection using **AI Perception**
- State-based enemy behavior using **StateTree**
- Enemy interaction through a shared `IStompable` interface

### Gameplay Elements
- Multiple levels connected through teleportation portals
- Collectible coins and hearts for health recovery
- Interactive obstacles, including rotating and swinging pendulums
- Level completion system

### Save System
- Persistent game progress using Unreal Engine's **SaveGame** system
- Saving and loading player progress across gameplay sessions

## Controls

| Input | Action |
|---|---|
| W / A / S / D | Move |
| Space | Jump |
| Left Shift | Sprint |

## Gameplay Demo

🎬 **[Watch ScaredyImp Gameplay Demo on YouTube](https://youtu.be/Ik7N4gRf-oo)**
