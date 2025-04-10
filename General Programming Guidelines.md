# General Programming Guidelines

## 1. Class Member Declaration Order

To maintain consistency and readability, all class members should follow the order below:

1. **`friend` declarations** (if applicable) 
   - Use only when necessary, to grant specific access privileges.

2. **Constructors**  
   - Default and parameterized constructors.

3. **Copy constructors** (if applicable) 
   - Copy and move constructors.

4. **Destructor**  
   - Prefer virtual destructor when polymorphism is used.

5. **Singleton macros (if applicable)**  
   - For singleton-style classes.

6. **Member variables**  (if applicable)
   - All member variables prefixed with `M_`.

7. **Clone method**  (if applicable)
   - Example: `MF_Clone()` for duplicating the instance.

8. **Abstract methods (`virtual`)**  (if applicable)
   - All pure virtual functions declared here.

9. **Binding-related** methods (if applicable)
   - Functions related to GPU register bindings, such as MF_Bind_Transform(), MF_Bind_Texture(), and so on.

10. **Initialization and frame-based methods**  (if applicable)
   - `MF_Initialize()`, `MF_Prepare()`,  
     followed by `MF_Progress()`, `MF_Update()`, `MF_Tick()`.

11. **Getters and Setters**  (if applicable)
    - `MF_GetX()`, `MF_SetY()` style accessors.

12. **Public/Internal methods**  
    - Main logic and behavior functions.

13. **Modularized private/internal methods**  (if applicable)
    - Small helper methods and decomposed logic units.

---

## 2. Scale Handling Guidelines

### 2.1. Negative Scale Values
- When using **negative scale values**, exercise caution, particularly when interacting with libraries or systems that rely on positional data (e.g., physics engines, collision detection). Negative scales may lead to unexpected behaviors such as flipped geometries or incorrect transformations.

### 2.2. Zero Scale Values
- **Scale values of 0** can lead to issues such as rendering failures or incorrect matrix transformations. It is recommended to either **clamp** the scale to a small positive value or implement **exception handling** to prevent these errors. This ensures that objects with scale set to 0 do not cause unexpected behavior in the system.

### 2.3. Scale of 1
- A **scale of 1** indicates that the object maintains its **original size**, with **no influence** from parent object scaling. This is useful for cases where independent scaling is desired or to preserve an object's original dimensions in the scene.

---

## 3. General Guidelines for Transformations

- **World transformation matrices** should be updated consistently when position, rotation, or scale changes.
- Handle transformations separately for rendering and physics calculations, ensuring proper synchronization between the two.
- Always ensure that transformations are applied in the correct order (usually Scale → Rotation → Translation).

## 4. Key Considerations

- Maintain separation of concerns when handling transformations, ensuring that each system (rendering, physics, etc.) has access to the required data without interference.
- Regularly update and validate transformation matrices to avoid discrepancies during gameplay or simulation.