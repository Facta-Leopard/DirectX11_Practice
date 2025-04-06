# Frame Execution Naming Convention
# Frame Excute Method Naming Convention for This Practice Solution
- Made by Facta-Leopard : https://github.com/Facta-Leopard

# This document defines the naming convention for methods executed per frame in a real-time system.  
Each level has a clear role and naming consistency to ensure readability and maintainability.

---

## Overview

| Layer           | Method Name          | Description                                             |
|-----------------|----------------------|---------------------------------------------------------|
| Program Level   | `MF_Progress()`       | Handles the overall program loop or frame progression. |
| Manager Level   | `MF_Update()`         | Updates the status of systems or subsystems.           |
| Stage Level     | `MF_Step()`, `MF_ComponentStep()` | Executes logic for a group of objects.                 |
| Object Level    | `MF_Tick()`           | Per-frame logic for an individual object.              |
| Component Level | `MF_ComponentTick()`  | Executes per-frame logic for a component.              |
| Script Component Level | `MF_ScriptComponentTick()` | Executes per-frame logic for a script component. This method is abstracted in `MF_ComponentTick()` and is blocked as final in the base `ComponentTick()` to prevent further modification. |

---

## Naming Example

```cpp
// Program.cpp
void MF_Progress();

// SceneManager.cpp
void MF_Update();

// EnemyGroup.cpp
void MF_Step();

// Enemy.cpp
void MF_Tick();

// HealthComponent.cpp
void MF_ComponentTick();

// ScriptComponent.cpp
void MF_ScriptComponentTick();
