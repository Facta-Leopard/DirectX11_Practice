# Naming Convention for This Practice Solution
- Made by Facta-Leopard : https://github.com/Facta-Leopard

---

## In Codebase

### Pointer & Reference Types
- **`CP`**: Prefix for objects wrapped by `ComPtr`.
- **`SP`**: Prefix for objects wrapped by `shared_ptr`.
- **`P`**: Prefix for raw pointers.
- **`FP`**: Prefix for function pointers.
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
- All prefixed names should include a **trailing underscore** (`_`) to improve readability and avoid naming conflicts (e.g., with macros or keywords).

### Examples
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

| Layer           | Method Name        | Description                                             |
|----------------|--------------------|---------------------------------------------------------|
| Program Level  | `Progress()`       | Handles the overall program loop or frame progression. |
| Manager Level  | `Update()`         | Updates the status of systems or subsystems.           |
| Group Level    | `Step()`           | Executes logic for a group of objects.                 |
| Object Level   | `Tick()`           | Per-frame logic for an individual object.              |
| Component Level| `TComponentick()`  | Executes per-frame logic for a component.              |

### Naming Example
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
void Componentick(); // Executes component logic (e.g., transform, state, regdi and so on)
```
