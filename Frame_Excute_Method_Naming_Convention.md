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
| Stage Post Level	| 'MF_StepAfter()'	| Executes post-step logic after the regular MF_Step() has been processed. |
| Object Level    | `MF_Tick()`           | Per-frame logic for an individual object.              |
| Object Post Level | 'MF_TickAfter()' | 	Executes post-frame logic for an individual object or component after the regular Tick() has been processed. |
| Component Level | `MF_ComponentTick()`  | Executes per-frame logic for a component.              |
| Component Post Level | MF_ComponentTickAfter()      |	Executes post-frame logic for a component after the regular MF_ComponentTick() has been processed. |
| Script Component Level | `MF_ScriptComponentTick()` | Executes per-frame logic for a script component. This method is abstracted in `MF_ComponentTick()` and is blocked as final in the base `ComponentTick()` to prevent further modification. |

---

## Naming Example

```cpp
// Program.cpp
void MF_Progress();

// Manager.cpp
void MF_Update();

// Group.cpp
void MF_Step();

// Group.cpp
void MF_StepAfter();

// Object.cpp
void MF_Tick();

// Object.cpp
void MF_TickAfter();

// Component.cpp
void MF_ComponentTick();

// Component.cpp
void MF_ComponentTickAfter();

// ScriptComponent.cpp
void MF_ScriptComponentTick();
