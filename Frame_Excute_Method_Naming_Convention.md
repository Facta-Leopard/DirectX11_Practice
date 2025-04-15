# Frame Execute Method Naming Convention for This Practice Solution
- **Made by Facta-Leopard**: [https://github.com/Facta-Leopard](https://github.com/Facta-Leopard)

- This document defines the naming convention for methods executed per frame in a real-time system.  

- Each level has a clear role and naming consistency to ensure readability and maintainability.

---

## Overview

| Layer                   | Method Name                     | Description                                                                 |
|-------------------------|----------------------------------|-----------------------------------------------------------------------------|
| Program Level           | `MF_Initialize()`               | Used for initialization functions in the Program and Manager levels.       |
| Program Level           | `MF_Progress()`                 | Handles the overall program loop or frame progression.                     |
| Manager Level           | `MF_Initialize()`               | Used for initialization functions in the Program and Manager levels.       |
| Manager Level           | `MF_Update()`                   | Updates the status of systems or subsystems.                               |
| Stage Level             | `MF_Prepare()`                  | Used for preparation functions in the Stage, Object, and Component levels. |
| Stage Level             | `MF_Step()`, `MF_ComponentStep()` | Executes logic for a group of objects.                                      |
| Stage Post Level        | `MF_StepAfter()`                | Executes post-step logic after the regular MF_Step() has been processed.    |
| Group Level             | `MF_Tick()`                     | Per-frame logic for an individual object.                                  |
| Group Function          | `MF_Prepare()`                  | Used for preparation functions in the Stage, Object, and Component levels. |
| Group Post Level        | `MF_TickAfter()`                | Executes post-frame logic for an individual object or component.            |
| Object Level            | `MF_Tick()`                     | Per-frame logic for an individual object.                                  |
| Object Function         | `MF_Prepare()`                  | Used for preparation functions in the Stage, Object, and Component levels. |
| Object Post Level       | `MF_TickAfter()`                | Executes post-frame logic for an individual object or component.            |
| Component Level         | `MF_Prepare()`                  | Used for preparation functions in the Stage, Object, and Component levels. |
| Component Level         | `MF_ComponentTick()`            | Executes per-frame logic for a component.                                  |
| Component Post Level    | `MF_ComponentTickAfter()`       | Executes post-frame logic for a component.                                 |
| Script Component Level  | `MF_ScriptComponentTick()`      | Executes per-frame logic for a script component. This method is abstracted in `MF_ComponentTick()` and is blocked as final in the base `ComponentTick()` to prevent further modification. |
| Callback Function       | `MF_CallBack_`                  | Functions acting as callbacks should follow this naming convention. The name should end with `CallBack_` to indicate its role as a callback function. |
| Getter Function         | `MF_Get_`                       | Used for getter functions. The name must end with `_`.                      |
| Setter Function         | `MF_Set_`                       | Used for setter functions. The name must end with `_`.                      |
| Attach/Detach Function  | `MF_Attach_`, `MF_Detach_`      | Functions to attach or detach elements or components should end with `Attach_` or `Detach_`. |

---

## Naming Rule

**All frame-execute methods must follow these additional rules for clarity and uniformity:**

- All method names **must start with the `MF_` prefix** to indicate that it is a member function.

- The **verb following `MF_` must not have an underscore** if it stands alone and is clear.

- If the method name includes **multiple words**, or **needs separation for clarity**, use an underscore after the verb.

- **Getter and Setter functions** should use `MF_Get_` and `MF_Set_` as prefixes, respectively.

- **Attach and Detach functions** should end with `Attach_` and `Detach_` respectively to indicate adding or removing components or elements.

> `MF_Initialize()`
> `MF_Prepare()`
> `MF_Progress_()`
> `MF_Update()`
> `MF_Step()`  
> `MF_StepAfter()`    
> `MF_Tick()`  
> `MF_TickAfter()` 
> `MF_CallBack_OnSuccess()`  
> `MF_CallBack_OnFailure()`  
> `MF_Get_`  
> `MF_Set_`  
> `MF_Attach_`  
> `MF_Detach_`

**This convention improves readability while keeping short method names clean.**

---

## Naming Example

```cpp
// Program.cpp
void MF_Initialize();
void MF_Progress();

// Manager.cpp
void MF_Initialize();
void MF_Update();

// Stage.cpp
void MF_Prepare();
void MF_Step();
void MF_StepAfter();

// Group.cpp
void MF_Prepare();
void MF_Tick();
void MF_TickAfter();

// Object.cpp
void MF_Prepare();
void MF_Tick();
void MF_TickAfter();

// Component.cpp
void MF_Prepare();
void MF_ComponentTick();
void MF_ComponentTickAfter();

// ScriptComponent.cpp
void MF_ScriptComponentTick();

// Callback Example
void MF_CallBack_Return();

// Getter and Setter Example
type MF_Get_Position();
type MF_Set_Position();

// Attach and Detach Example
void MF_Attach_Component();
void MF_Detach_Component();
