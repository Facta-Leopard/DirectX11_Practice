# Naming Convention for This Practice Solution
- Made by Facta-Leopard : https://github.com/Facta-Leopard

---

## In Codebase

### Pointer & Reference Types
- **`CP`**: Prefix for objects wrapped by `ComPtr`.
- **`SP`**: Prefix for objects wrapped by `shared_ptr`.
- **`P`**: Prefix for raw pointers.
- **`PF`**: Prefix for function pointers.
- **`R`**: Prefix for references.

### Constant Types
- **`L`**: Prefix for literal constants defined by `const`.
- **`LL`**: Prefix for literal constants defined by `constexpr`.

### Structure & Member Types
- **`C`**: Prefix for class names.
- **`DS`**: Prefix for data structure names.
- **`M`**: Prefix for member variables.
- **`MF`**: Prefix for member functions.
- **`G`**: Prefix for global (extern) variables.
- **`GF`**: Prefix for global (extern) functions.
- **`S`**: Prefix for static variables.
- **`SF`**: Prefix for static functions.
- **`T`**: Prefix for temporary variables.
- **`TF`**: Prefix for temporary functions.

### STL Container Types
- **`STL`**: Prefix for types or variables implemented using STL containers.

### Platform or API Specific Types
- **`H`**: Prefix for Windows HANDLE types.
- **`DX`**: Prefix for DirectX-specific classes.

### Fixed Abbreviations
- **`E`**: Used alone for enum structures.
- **`EC`**: Used alone for `enum class`.
- **`_`**: Used alone as a suffix for enum members.
- **`V2`**: Used for Vector2 structure.
- **`V3`**: Used for Vector3 structure.
- **`V4`**: Used for Vector4 structure.
- **`M16`**: Used for Matrix (4x4) structure.

### Array Type
- **_s**: Suffix for Fixed-size array.

### Naming Rule Notes

#### General
- All prefixed names should include a **trailing underscore** (`_`) to improve readability and avoid naming conflicts (e.g., with macros or keywords).


#### Enum Structure
- To reduce overhead, enum class is not used.
- Instead, to minimize duplication, an underscore (_) is used as a suffix, and all letters are written in uppercase with words separated by underscores.

---

## Examples
```cpp
// Member variable of type ID3D11Device wrapped by ComPtr
// CP (ComPtr) + trailing '_' + M (Member) + trailing '_' + D (DirectX) + trailing '_'
ComPtr<ID3D11Device> CP_M_D_Device_;

// Temporary pointer to Vector3 structure
V3* T_V3_Position_;

// constexpr constant
constexpr int LL_MaxFrame_ = 60;

// Enum
enum PROJECTION_TYPE {
    _ORTHOGRAPHIC,
    _PERSPECTIVE,
};
```

---

## Frame Execution Method Naming Convention

This section defines the naming convention for methods executed per frame in a real-time system. Each level has a clear role and naming consistency to ensure readability and maintainability.

### Overview

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
