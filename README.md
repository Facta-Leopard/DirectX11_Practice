# General Programming Guidelines
- **Made by Facta-Leopard**: [https://github.com/Facta-Leopard](https://github.com/Facta-Leopard)

## 1. Key Considerations

- Maintain separation of concerns when handling transformations, ensuring that each system (rendering, physics, etc.) has access to the required data without interference.
- Regularly update and validate transformation matrices to avoid discrepancies during gameplay or simulation.

---

## 2. Class Member Declaration Order

To maintain consistency and readability, all class members should follow the order below:

1. **`friend` declarations** (if applicable) 
   - Use only when necessary, to grant specific access privileges.

2. **Constructors**  
   - Default and parameterized constructors.

3. **Copy constructors** (if applicable) 
   - Copy and move constructors.

4. **Destructor**  
   - Prefer virtual destructor when polymorphism is used.

5. **Singleton macros** (if applicable)  
   - For singleton-style classes.

6. **Member variables**  (if applicable)
   - All member variables prefixed with `M_`.

7. **Clone method**  (if applicable)
   - Example: `MF_Clone()` for duplicating the instance.

8. **Callback functions** (if applicable)
   - Functions acting as callbacks should follow the naming convention `MF_CallBack_`. The name should end with `MF_CallBack_` to indicate its role as a callback function. This ensures clarity in identifying callback-specific logic.

9. **Abstract methods (`virtual`)**  (if applicable)
   - All pure virtual functions declared here.

10. **Binding-related** methods (if applicable)
   - Functions related to GPU register bindings, such as `MF_Bind()`, `MF_Bind()`, and so on.

11. **Initialization and frame-based methods**  (if applicable)
   - `MF_Initialize()`, `MF_Prepare()`,  
     followed by `MF_Progress()`, `MF_Update()`, `MF_Tick()`.

12. **Getters and Setters**  
    - For all Getters and Setters, use the `inline` keyword to optimize performance, reduce function call overhead, and maintain the naming convention `MF_GetX()` and `MF_SetY()`.
    - This makes the code more efficient by directly accessing the member variables, improving performance without extra cost.

13. **Attach and Detach functions**
    - Functions to attach or detach elements or components should follow the naming convention `MF_Attach_` and `MF_Detach_`.

14. **Public/Internal methods**  
    - Main logic and behavior functions.

15. **Modularized private/internal methods**  (if applicable)
    - Small helper methods and decomposed logic units.

16. **Template methods** (if applicable)
    - Declare all function templates at the end of the class definition.
    - **DO NOT EVEN FUCKING TRY TO SPECIALIZE A MEMBER TEMPLATE FUNCTION JUST TO CHANGE ITS RETURN TYPE.**
    - **HOW DO I KNOW? BECAUSE I HAVE FUCKING TRY TO FUCK AND FUCK IT IN!**

### it is important to maintain clear separation based on access specifiers.

- For example, if there are multiple public members within the public section, or if there are redundant members in the protected or private sections, each section should still be clearly separated.

- Even in cases of redundancy, ensure that access specifiers are used clearly to maintain consistency and readability in the class structure.

---

## 3. Scale Handling Guidelines

### 3.1. Negative Scale Values

- When using **negative scale values**, exercise caution, particularly when interacting with libraries or systems that rely on positional data (e.g., physics engines, collision detection). Negative scales may lead to unexpected behaviors such as flipped geometries or incorrect transformations.

### 3.2. Zero Scale Values
- **Scale values of 0** can lead to issues such as rendering failures or incorrect matrix transformations. It is recommended to either **clamp** the scale to a small positive value or implement **exception handling** to prevent these errors. This ensures that objects with scale set to 0 do not cause unexpected behavior in the system.

---

## 4. General Guidelines for Transformations

- **World transformation matrices** should be updated consistently when position, rotation, or scale changes.

- Handle transformations separately for rendering and physics calculations, ensuring proper synchronization between the two.

- Always ensure that transformations are applied in the correct order (usually Scale → Rotation → Translation).

---

## 5. Collision Calculation Policy

### 5.1. Collision Flow Overview
Get calculation type -> Decide which axes to ignore and if it's 2D or 3D -> Check center distance to filter out obvious misses -> If needed, do a more accurate SAT check -> Final result handling

---

### 5.2. Summary

- Each stage has its own collision calculation type(`enum or other Structure`).

- This type(`collision calculation type`) fully controls how collision checks will run during that frame.

- First, center distance is used to quickly remove non-colliding objects. SAT is only used when checked or customed.

---

### 5.3. Collision Pair Storage Policy

- `std::unordered_map` is used to store collision pair states, since the number of collision-checking layers is very limited.

- This helps reduce overhead and provides faster lookups during frame-by-frame collision checks.

- Key pairs are stored as simple `Point` types(Windows SDK) to avoid alignment issues and `#pragma pack(#)`.

- This keeps the structure clean, easy to manage, and better aligned with `SIMD`(CPU-level vector instructions such as SSE, AVX, and NEON).

---

### 5.4. Benefits

- **Clear process**: The steps are always the same based on the collision type.

- **Good performance**: Fast filtering comes first, and detailed checks happen only if needed.

- **Easy to expand**: The enum-based setup makes it simple to add new types or change logic.

- **Clear rules**: The stage sets the rule, and the collision manager only runs the logic.

---

### 5.5. Caution

- **StageManager should not control collision types directly.**

- The collision type must be stored in the `Stage` itself.

- If `StageManager` tries to change or hold this data, it breaks the clean design.

- **The camera is not the same as view type and must never be used for collision logic.**

---

## Techniques and Rationale Used Here

### Yoda Condition Rule

When comparing against a constant or literal, always place it on the left side.  

This helps prevent bugs caused by accidental assignment (`=`) in conditionals.

I didn’t choose to be a Jedi… but I did choose Yoda.

I don't really know much about Star Wars, but the name has a wise ring to it.

---

### Components are for data, scripts are for logic.

I choose to attach scripts directly to objects not manage them globally for making editor-based control and maintenance easier.

---

### Branch Split Rule

If a function has 4 or more if or else if statements, and it may add more in the future, then it should be split the logic into separate functions.

Too many conditions make it hard for the CPU to predict, which can slow things down.

Splitting into functions makes the code cleaner and easier to update.

Function call cost is small, but bad branch prediction is expensive.

---

### About Memory Layout SoA(Structure of Array) and AoS(Array of Structure)

Think about for Using Structure of Arrays (SoA) instead of Array of Structures (AoS) when doing repeated math on many vectors, to make the code faster with better cache and SIMD use.

---

### Ternary Operator Rule

Nested ternary is allowed only inside for or while loops — my personal rule for compactness and clarity.

Outside loops, I choose if statements for better readability and cache safety.

---

### Using `Getter` function for classfied

I decide to use getters for other classes' members and access own class's members directly to keep things clear.

---

### About Scale and Rotation Transformation

The Quaternion Method was chosen due to its significantly faster processing time and protecting Zero Scale problem, and to avoid Gimbal Lock problem.

#### Overhead Comparison Table

| Transformation Method | DirectX Function | Processing Time | Speed Difference |
|----------------------|------------------|-----------------|------------------|
| Quaternion Method     | `XMQuaternionToAxisAngle()` → `XMConvertToDegrees()` | 627 nanoseconds | Reference |
| Matrix Method         | `XMMatrixRotationQuaternion()` → `XMMatrixDecompose()` → `XMConvertToDegrees()` | Approximately 3,637-4,452 nanoseconds | Approximately 5.8-7.1 times slower |

---

# In Codebase

---

## Naming Convention

---

### Pointer & Reference Types
- **`CP`**: Prefix for objects wrapped by `ComPtr`.
- **`SP`**: Prefix for objects wrapped by `shared_ptr`.
- **`P`**: Prefix for raw pointers.
- **`PF`**: Prefix for function pointers.
- **`R`**: Prefix for references.

---

### Constant Types
- **`L`**: Prefix for literal constants defined by `const`.
- **`LL`**: Prefix for literal constants defined by `constexpr`.

---

### Structure & Member Types
- **`C`**: Prefix for class names.
- **`DS`**: Prefix for data structure names.
- **`US`**: Prefix for union structure names.
- **`M`**: Prefix for member variables.
- **`MF`**: Prefix for member functions.
- **`G`**: Prefix for global (extern) variables.
- **`GF`**: Prefix for global (extern) functions.
- **`S`**: Prefix for static variables.
- **`SF`**: Prefix for static functions.
- **`T`**: Prefix for temporary variables.
- **`TF`**: Prefix for temporary functions.

---

### STL Container Types
- **`STL`**: Prefix for types or variables implemented using STL containers.

---

### Platform or API Specific Types
- **`H`**: Prefix for Windows HANDLE types.
- **`SDK`**: Prefix for types that are defined in the Windows SDK, such as DWORD, BOOL, HRESULT, LPARAM, and others.
- **`F`**: Prefix for FMOD classes in FMOD Library.
- **`I`**: Prefix for Using IMGUI Headers.
- **`DX`**: Prefix for DirectX-specific classes.

---

### Fixed Abbreviations
- **`E`**: Used alone for enum structures.
- **`EC`**: Used alone for `enum class`.
- **`_`**: Used alone as a suffix for enum members.
- **`Vector2`**: Used for Vector2 structure.
- **`Vector3`**: Used for Vector3 structure.
- **`Vector4`**: Used for Vector4 structure.
- **`MAT`**: Used for Matrix (4x4) structure.

---

### Array Type
- **_s**: Suffix for Fixed-size array.

---

#### Naming Rule Notes

#### General
- All prefixed names should include a **trailing underscore** (`_`) to improve readability and avoid naming conflicts (e.g., with macros or keywords).

---

#### Enum Structure
- To reduce overhead, enum class is not used.
- Instead, to minimize duplication, an underscore (`_`) is used as a suffix, and all letters are written in uppercase with words separated by underscores.

---

## Frame Execute Method Naming Convention for This Practice Solution  
- **Made by Facta-Leopard**: [https://github.com/Facta-Leopard](https://github.com/Facta-Leopard)

This document defines the naming convention for methods executed per frame in a real-time system.  
Each level has a clear role and naming consistency to ensure readability and maintainability.

---

### Overview

| Layer                   | Method Name                     | Description                                                                 |
|-------------------------|----------------------------------|-----------------------------------------------------------------------------|
| Program Level           | `MF_Initialize()`               | Used for initialization functions in the Program and Manager levels.       |
| Program Level           | `MF_Progress()`                 | Handles the overall program loop or frame progression.                     |
| Manager Level           | `MF_Initialize()`               | Used for initialization functions in the Program and Manager levels.       |
| Manager Level           | `MF_Update()`                   | Updates the status of systems or subsystems.                               |
| Stage Level             | `MF_Prepare()`                  | Used for preparation functions in the Stage, Object, and Component levels. |
| Stage Level             | `MF_Step()`, `MF_ComponentStep()` | Executes logic for a group of objects.                                      |
| Stage Post Level        | `MF_StepAfter()`                | Executes post-step logic after the regular `MF_Step()` has been processed.    |
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

#### Naming Rule

All frame-execute methods must follow these additional rules for clarity and uniformity:

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

This convention improves readability while keeping short method names clean.

---

#### Naming Example

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
```
