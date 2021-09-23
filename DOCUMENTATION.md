| Drew Funderburk       |
| :-------------------- |
| s208059               |
| Physics ocumentation  |
| 09/23/2021            |

---

## Requirements
#### Custom Physics Simulation
Evidence that includes:
- Implementation and demonstration of custom physics systems implemented within a real time application including:
  - Implementation of static and dynamic rigid body physics that interact together
  - Forces applied to physics bodies
  - Visualisation of physics bodies
  - Physics simulations run as expected without physical errors

#### Custom Physics Documentation
Evidence that includes:
- Creation of class diagrams for the Custom Physics Simulation including:
  - Physics System’s classes, their properties, relationships and how they interact together
- Creation of a written document that includes:
  - References and research material used to influence the creation of the Custom Physics Simulation
  - What the Custom Physics Simulation is demonstrating and how the physical bodies are interacting together
  - Third-party libraries used to create the Custom Physics Simulation, if any
  - Identification of improvements that could be made to the Custom Physics Simulation to support further features and more accurate simulations

## Code Documentation
####  Third Party Libraries
This project uses [AIE's Boostrap](https://github.com/AcademyOfInteractiveEntertainment/aieBootstrap)

#### Table of Contents
##### Classes
- [PhysicsGame](#class-PhysicsGame)
- [PhysicsObject](#class-PhysicsObject)
- [PhysicsScene](#class-PhysicsScene)
- [RigidBody](#class-RigidBody)
- [Plane](#class-Plane)
- [Sphere](#class-Sphere)

##### Enums
- [ShapeType](#enum-class-ShapeType)

#### class [PhysicsGame](Physics/PhysicsGame.h)

Function  | Use
:---------|:----
| **Public**
PhysicsGame()                        | Default constructor
virtual ~PhysicsGame()               | Default destructor
virtual bool startup()               | Handles boostrap startup and adds objects to the scene
virtual bool shutdown()              | Cleans up memory
virtual void update(float deltaTime) | Updates boostrap gizmos and scenes
virtual void draw()                  | Draws scene objects to the screen

Variable  | Use
:---------|:----
| **Private**
aie::Renderer2D* m_renderer                        | Bootstrap renderer
aie::Font* m_scene                                 | Bootstrap font
[PhysicsScene](#class-PhysicsScene)* m_scene       | Scene to hold objects

<br/>

#### class [PhysicsObject](Physics/PhysicsObject.h)

Function  | Use
:---------|:----
| **Protected**
PhysicsObject([ShapeType](#enum-class-ShapeType) shapeType)                | Default constructor. Requires a [ShapeType](#enum-class-ShapeType) to determine what collision functions should be used
~PhysicsObject()                                                           | Default destructor
| **Public**                                                               
virtual void fixedUpdate(glm::vec2 gravity, float timestep) = 0            | Physics update
virtual void draw() = 0                                                    | Draw this object to the screen
virtual void resetPosition()                                               | Reset this object to its start position. **Not implemented!**[^1]
[ShapeType](#enum-class-ShapeType) getShapeID()                            | Getter for m_shapeID

Variable  | Use
:---------|:----
| **Private**
[ShapeType](#enum-class-ShapeType) m_shapeID | Used by collision functions to determine what algorithm to use

[^1]: Added this function in class but never got around to implementing it. I've not needed it so I left it how it was.

<br/>

#### class [PhysicsScene](Physics/PhysicsScene.h)

Function  | Use
:---------|:----
| **Public**
PhysicsScene()                                                                                                             | Default constructor
~PhysicsScene()                                                                                                            | Default destructor
void addActor([PhysicsObject](#class-PhysicsObject)* actor)                                                                | Add a [PhysicsObject](#class-PhysicsObject) to the scene
void removeActor([PhysicsObject](#class-PhysicsObject)* actor)                                                             | Remove a [PhysicsObject](#class-PhysicsObject) from the scene
void update(float deltaTime)                                                                                               | Update the scene
void draw()                                                                                                                | Draw the scene to the screen
void setGravity(const glm::vec2 gravity)                                                                                   | Setter for m_gravity
glm::vec2 getGravity() const                                                                                               | Getter for m_gravity
void setTimeStep(const float timeStep)                                                                                     | Setter for m_timeStep
float getTimeStep() const                                                                                                  | Getter for m_timeStep
static bool planeToPlane([PhysicsObject](#class-PhysicsObject)* object1, [PhysicsObject](#class-PhysicsObject)* object2)   | [Plane](#class-Plane) to [Plane](#class-Plane) collision
static bool planeToSphere([PhysicsObject](#class-PhysicsObject)* object1, [PhysicsObject](#class-PhysicsObject)* object2)  | [Plane](#class-Plane) to [Sphere](#class-Sphere) collision
static bool planeToBox([PhysicsObject](#class-PhysicsObject)* object1, [PhysicsObject](#class-PhysicsObject)* object2)     | [Plane](#class-Plane) to Box collision
static bool sphereToPlane([PhysicsObject](#class-PhysicsObject)* object1, [PhysicsObject](#class-PhysicsObject)* object2)  | [Sphere](#class-Sphere) to [Plane](#class-Plane) collision
static bool sphereToSphere([PhysicsObject](#class-PhysicsObject)* object1, [PhysicsObject](#class-PhysicsObject)* object2) | [Sphere](#class-Sphere) to [Sphere](#class-Sphere) collision
static bool sphereToBox([PhysicsObject](#class-PhysicsObject)* object1, [PhysicsObject](#class-PhysicsObject)* object2)    | [Sphere](#class-Sphere) to Box collision
static bool boxToPlane([PhysicsObject](#class-PhysicsObject)* object1, [PhysicsObject](#class-PhysicsObject)* object2)     | Box to [Plane](#class-Plane) collision
static bool boxToSphere([PhysicsObject](#class-PhysicsObject)* object1, [PhysicsObject](#class-PhysicsObject)* object2)    | Box to [Sphere](#class-Sphere) collision
static bool boxToBox([PhysicsObject](#class-PhysicsObject)* object1, [PhysicsObject](#class-PhysicsObject)* object2)       | Box to Box collision

Variable  | Use
:---------|:----
| **Private**
glm::vec2 m_gravity                                       | Value to be used when calculating this scene's gravity
float m_timeStep                                          | How quickly fixedUpdate() should run
std::set<[PhysicsObject](#class-PhysicsObject)*> m_actors | Set of actors in this scene

<br/>

#### class [RigidBody](Physics/RigidBody.h)

Function  | Use
:---------|:----
| **Public**
RigidBody([ShapeType](#enum-class-ShapeType) shapeID, glm::vec2 position, glm::vec2 velocity, float orientation, float mass) | Default constructor
~Rigidbody()                                                                                                                 | Default destructor
virtual void fixedUpdate(glm::vec2 gravity, float timeStep)                                                                  | Physics update
void applyForce(glm::vec2 force)                                                                                             | Apply force to this object
void applyForceToOther([RigidBody](#class-RigidBody)* other, glm::vec2 force)                                                | Apply force to another rigidbody
void resolveCollision([RigidBody](#class-RigidBody)* other)                                                                  | Resolve a collision between two [RigidBody](#class-RigidBody)s and apply forces to each
glm::vec2 getPosition()                                                                                                      | Getter for m_position
glm::vec2 getVelocity()                                                                                                      | Getter for m_velocity
float getOrientation()                                                                                                       | Getter for m_orientation
float getMass()                                                                                                              | Getter for m_mass

Variable  | Use
:---------|:----
| **Private**
glm::vec2 m_position | This [RigidBody](#class-RigidBody)'s position
glm::vec2 m_velocity | This [RigidBody](#class-RigidBody)'s velocity
float m_orientation  | This [RigidBody](#class-RigidBody)'s orientation
float m_mass         | This [RigidBody](#class-RigidBody)'s mass

<br/>

#### class [Plane](Physics/Plane.h)

Function  | Use
:---------|:----
| **Public**
Plane(glm\::vec2 normal, float distance, glm::vec4 color)         | Default constructor
~Plane()                                                          | Default destructor
virtual void fixedUpdate(glm::vec2 gravity, float timeStep)       | Physics update
virtual void draw()                                               | Draw this [Plane](#class-Plane) to the screen
void resolveCollision([RigidBody](#class-RigidBody)* other)       | Resolve collisions with another [RigidBody](#class-RigidBody) by applying forces to it. Plane's are static and do not move
glm::vec2 getNormal()                                             | Getter for m_normal
float getDistance()                                               | Getter for m_distance
glm::vec4 getColor()                                              | Getter for m_color

Variable  | Use
:---------|:----
| **Private**
glm::vec2 m_normal | This [Plane](#class-Plane)'s normal vector
float m_distance   | This [Plane](#class-Plane)'s distance from the origin
glm::vec4 m_color  | This [Plane](#class-Plane)'s color

<br/>

#### class [Sphere](Physics/Sphere.h)

Function  | Use
:---------|:----
| **Public**
Sphere(glm\::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 color) | Default constructor
~Sphere()                                                                                  | Default destructor
virtual void draw()                                                                        | Draw this sphere to the screen
float getRadius()                                                                          | Getter for m_radius
glm::vec4 getColor()                                                                       | Getter for m_color

Variable | Use
:---------|:----
| **Private**
float m_radius    | This [Sphere](#class-Sphere)'s radius
glm::vec4 m_color | This [Sphere](#class-Sphere)'s color

<br/>

#### enum class [ShapeType](Physics/PhysicsObject.h)

Value |
:-----|
PLANE = 0  |
SPHERE     |
BOX        |
LENGTH[^2] |

[^2]: LENGTH is used as an easy indicator of how many possible [ShapeType](#enum-class-ShapeType)s there are