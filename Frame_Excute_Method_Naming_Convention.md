# Frame Execution Naming Convention
# Frame Excute Method Naming Convention for This Practice Solution
- Made by Facta-Leopard : https://github.com/Facta-Leopard

# This document defines the naming convention for methods executed per frame in a real-time system.  
Each level has a clear role and naming consistency to ensure readability and maintainability.

---

## Overview

| Layer           | Method Name        | Description                                             |
|------------------|---------------------|---------------------------------------------------------|
| Program Level    | `Progress()`        | Handles the overall program loop or frame progression. |
| Manager Level    | `Update()`          | Updates the status of systems or subsystems.           |
| Group Level      | `Step()`            | Executes logic for a group of objects.                 |
| Object Level     | `Tick()`            | Per-frame logic for an individual object.              |
| Component Level  | `ComponentTick()`   | Executes per-frame logic for a component.              |

---

## Naming Example

```cpp
// Program.cpp
void Progress(); // Main loop control

// SceneManager.cpp
void Update(); // Scene or system-level update

// EnemyGroup.cpp
void Step(); // Handles group-level logic

// Enemy.cpp
void Tick(); // Individual enemy behavior

// HealthComponent.cpp
void ComponentTick(); // Executes component logic (e.g., transform, state, rigid, and so on)
