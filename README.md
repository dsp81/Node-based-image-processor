# Node-based-image-processor

# Node-Based Image Manipulation Interface

This project is a custom image processing tool built using C++ with Qt for the UI and OpenCV for the core image operations. The idea is simple: instead of chaining operations manually through code or menus, the user visually creates a graph of image processing operations using nodes. Each node represents an operation, and the final image is the result of passing data through this node graph.

This README outlines the motivation behind the project, the design philosophy, the underlying components, and the roadmap moving forward.

---

## Motivation

Most image editors work linearly — you apply a filter, undo it, tweak parameters, try again. This project aims to flip that. Here, users create a flow of operations as a graph. Want to blur an image, tweak its contrast, and blend it with something else? Just add the relevant nodes and wire them up. This makes the entire process more flexible, more transparent, and easier to experiment with.

This is especially useful when the same sequence of processing steps needs to be repeated across multiple images or tweaked slightly without losing track of the original pipeline.

---

## How It Works

The application consists of three core components:

### 1. **Canvas (Qt-based)**
The canvas is where the user interacts with the node graph. Nodes can be added, moved around, connected via input/output pins, and edited. It provides a visual and interactive way to build the processing pipeline.

### 2. **Nodes**
Each node represents an atomic image operation — blur, sharpen, grayscale, threshold, edge detection, arithmetic blending, etc. Nodes may take one or more input images and produce one output. Each has configurable parameters accessible through the UI.

### 3. **Execution Engine**
Underneath the UI, there's an execution engine that builds a directed acyclic graph (DAG) from the node connections. When the graph is evaluated, it recursively computes the output of each node based on its inputs, passing the image data through OpenCV functions.

---

## Project Structure

- `main.cpp`: Initializes the Qt application and loads the canvas.
- `NodeEditor/`: Core classes for canvas, node rendering, interaction handling.
- `Nodes/`: Definitions of various image processing nodes and their behavior.
- `GraphEngine/`: Handles execution of the node graph.
- `Images/`: Temporary input/output images (placeholder for file loading/saving).
- `CMakeLists.txt`: Cross-platform build configuration.

---

## Current Status

As of now, the project is in its initial stage:

- Qt window and custom canvas working.
- Basic node structure defined, with dummy visuals.
- Execution engine and node interconnectivity under development.

Functionality will be added incrementally, with each stage committed separately to reflect design decisions and the implementation path taken.

---

## Roadmap

The project will progress through several defined stages:

1. **Stage 0: Setup**
   - Build system with CMake
   - Working Qt window and canvas
   - Testing base rendering and event loops

2. **Stage 1: Node Infrastructure**
   - Node base class and registry
   - I/O handling and serialization
   - Visual layout and drag interaction

3. **Stage 2: Basic Operations**
   - Implement grayscale, blur, sharpen, edge detection
   - Add parameter sliders for each node
   - Display output on a preview widget

4. **Stage 3: Graph Execution Engine**
   - Parse node connections into a DAG
   - Topologically sort nodes
   - Execute OpenCV operations accordingly

5. **Stage 4: File I/O and Export**
   - Load input images
   - Export processed output
   - Save/load entire node graph sessions

6. **Stage 5: Extras**
   - Undo/redo support
   - Preset graphs
   - Node grouping and custom macros

---

## Why Build This

This isn’t just another GUI tool. It’s an exercise in:
- Designing modular, extensible architecture.
- Working with UI frameworks like Qt.
- Integrating real-time image processing using OpenCV.
- Building something that mirrors actual pipelines in tools like Nuke or Blender’s compositor, but from scratch.

The final application should feel intuitive enough for someone to load an image and build a custom filter from scratch without touching a line of code — while also being extensible for developers to register new custom nodes.

---

## Build Instructions

Requires:
- Qt 6.5.3 with MinGW
- CMake 3.16+
- OpenCV 4.x
- Windows with a C++17+ compatible compiler

```bash
cd NodeEditor
mkdir build
cd build
cmake ..
mingw32-make
