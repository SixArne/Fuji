# Fuji Engine

Welcome to the Fuji Engine, a modern C++ game engine written in C++20 with
modules and the Vulkan API.

## Motivation

This engine's goal is to provide a very optimized engine specifically for standalone VR and MR game development.
Fuji will also support Desktop games but the emphases is set to standalone VR.
As such this engine will only support the Vulkan rendering API.

## Building

Please download and set up the following tools

- CMAKE version 3.28.rc3
- Ninja build tool 1.11
- C++ compiler with support for modules. (this project assumes MSVC)

## Features to support

### ECS system

A full Entity Component System to support the maximum performance.

### Vulkan Renderer

A rendering system/pipeline written with the Vulkan API

### Meta SDK

Support for the Meta Software Development Kit.

### Pico SDK

Support for the PICO Software Development Kit;

## Libraries

- `glm` for mathematical operations on the C++ side
- `vsp` for compiling and processing Vulkan shader files (in the making)
- `spdlog` as a logging library for the engine and game.
- `glfw` for the editor window creation 