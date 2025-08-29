# Cub3D – 42 Amman Project

Cub3D is a **mini 3D game engine** built in C as part of the 42 curriculum, inspired by *Wolfenstein 3D*.  
It uses the **raycasting technique** to render a first-person view inside a maze-like environment.  
The project was developed to strengthen skills in **graphics programming, memory management, and low-level system handling** without external game engines.


---

## 🚀 Features
- **Raycasting Engine**: Real-time rendering of a 3D environment from a 2D map.  
- **Player Controls**: Move forward/backward, rotate left/right, and strafe.  
- **Collision Detection**: Prevents walking through walls.  
- **Texture Mapping**: Applies textures to walls for realism.  
- **Mini Map Parsing**: Reads a `.cub` configuration file to build custom maps.  
- **Cross-Platform**: Runs on Linux/Unix with the MiniLibX graphics library.  

---

## 🛠️ Technologies Used
- **Language**: C  
- **Graphics Library**: MiniLibX  
- **Raycasting Algorithm**: Inspired by Wolfenstein 3D (1992)  
- **Makefile**: For building and cleaning the project  

---

## 📂 Project Structure
cub3d/
│── src/ # Source code files
│── includes/ # Header files
│── textures/ # Wall textures
│── maps/ # Example .cub maps
│── Makefile # Build system

