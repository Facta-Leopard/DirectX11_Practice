# Frame Execute Method Naming Convention for This Practice Solution
- Made by Facta-Leopard : https://github.com/Facta-Leopard

This document defines the naming convention for methods executed per frame in a real-time system.  
Each level has a clear role and naming consistency to ensure readability and maintainability.

---

## Overview

| Layer                  | Method Name                 | Description                                                                 |
|------------------------|-----------------------------|-----------------------------------------------------------------------------|
| Program Level          | `MF_Progress()`             | Handles the overall program loop or frame progression.                     |
| Manager Level          | `MF_Update()`               | Updates the status of systems or subsystems.                               |
| Stage Level            | `MF_Step()`, `MF_ComponentStep()` | Executes logic for a group of objects.                              |
| Stage Post Level       | `MF_StepAfter()`            | Executes post-step logic after the regular MF_Step() has been processed.  |
| Object Level           | `MF_Tick()`                 | Per-frame logic for an individual object.                                  |
| Object Post Level      | `MF_TickAfter()`            | Executes post-frame logic for an individual object or component.          |
| Component Level        | `MF_ComponentTick()`        | Executes per-frame logic for a component.                                  |
| Component Post Level   | `MF_ComponentTickAfter()`   | Executes post-frame logic for a component.                                 |
| Script Component Level | `MF_ScriptComponentTick()`  | Executes per-frame logic for a script component. This method is abstracted in `MF_ComponentTick()` and is blocked as final in the base `ComponentTick()` to prevent further modification. |

---

## Naming Rule

All frame-execute methods must follow these additional rules for clarity and uniformity:

- All method names **must start with the `MF_` prefix** to indicate that it is a member function.
- The **verb following `MF_` must not have an underscore** if it stands alone and is clear.
- If the method name includes **multiple words**, or **needs separation for clarity**, use an underscore after the verb.

> `MF_Update()`  
> `MF_Tick()`  
> `MF_Initialize()`  
> `MF_Prepare_Asset()`  
> `MF_Progress_()` ← Not needed unless followed by qualifiers like `MF_Progress_Render()`

This convention improves readability while keeping short method names clean.

---

## Naming Example

```cpp
// Program.cpp
void MF_Progress();

// Manager.cpp
void MF_Update();

// Group.cpp
void MF_Step();
void MF_StepAfter();

// Object.cpp
void MF_Tick();
void MF_TickAfter();

// Component.cpp
void MF_ComponentTick();
void MF_ComponentTickAfter();

// ScriptComponent.cpp
void MF_ScriptComponentTick();

// Example with extended verb
void MF_Initialize_Resource();
void MF_Prepare_Assets();