# Utility_AI

A Utility AI implementation for the Godot Engine using gdextension. If you don't know what Utility AI is, Wikipedia defines it as follows:

*"...Utility AI, is a simple but effective way to model behaviours for non-player characters. Using numbers, formulas and scores to rate the relative benefit of possible actions, one can assign utilities to each action. A behaviour can then be selected based on which one scores the highest 'utility'...* - [Wikipedia - Utility system](https://en.wikipedia.org/wiki/Utility_system)

You can download the latest version of the source code from the releases. The releases in this repository contain only the source code. To get the binaries and the example project, go to this repository: [Utility AI GDExtension](https://github.com/JarkkoPar/Utility_AI_GDExtension).

## Compatibility

Godot 4.1.2 or newer.

## Node listing

* *UtilityAIAgent* This is the main node that is used manage the UtilityAI. It represents an AI entity.
* *UtilityAIBehaviour* The various things the AI agent can do are called _behaviours_. Each Behaviour consists of _considerations_ and _actions_.
* *UtilityAIBehaviourGroup* The behaviours can be grouped with _behaviour groups_. A Behaviour Group uses _considerations_ to decide if the Behaviours that are its child nodes should be evaluated.
* *UtilityAIConsideration* The AI agent does it's reasoning on what behaviour to use by going through the behaviour's considerations and producing a score for each behaviour. This node is used to represent a single thing the AI Agent should consider about a behaviour. A consideration uses a _sensor_ for input data.
* *UtilityAIConsiderationGroup* Several considerations can be grouped to create more complex or high-level logic.
* *UtilityAISensor* The sensor node is used to update input data to the AI Agent's considerations.
* *UtilityAISensorGroup* Several sensors can be grouped for more high-level sensor input to the considerations.
* *UtilityAIAction* A behaviour, if selected, will run any actions attached to it.
* *UtilityAIActionGroup* Groups can help organize how a behaviour will run the actions attached to it.

There are also a number of specialized sensor nodes to accomodate 2D and 3D visibility queries, distance and angle calculations, etc. 

---- This section contains information about a feature under development `DEV` ----

The included Node Query System (NQS) can be used to "find the best node for the job". It is a set of nodes for scoring and filtering nodes or node groups. It works with anything that has been derived from the Node-class. While this feature is still in development, the intended uses within a game are for example:

 * Scoring and filtering cover points
 * Scoring and prioritizing targets
 * Scoring movement targets or tiles

And pretty much any other use case where you have a set of nodes and want to select the best or top N of the nodes based on some evaluation criteria.

---- End of section about a feature under development `DEV` ----


## How to use the nodes

Start by adding a UtilityAIAgent to your scene. Next you can add the Sensors as the childs of the AI agent node. And then add the Behaviours. It is expected that any sensors are before behaviours. 

Then add considerations to the Behaviours you have added and connect them to sensors by setting the input_sensor_nodepath property on the considerations. And finally, add the Actions to the behaviour. 

In your code update the sensor's `sensor_value` with a floating point value between 0.0 and 1.0. Then run the UtilityAIAgent's `evaluate_options()` method and `update_current_behaviour()` method to get an `action` to execute. You can then get the action by using the `get_current_action()` method.
Do what ever you need to do for the action selected and once done, mark it as finished using the `set_is_finished(true)` method. This will allow the current behaviour to step to the next action during the `update_current_behaviour()` call.

## Documentation

You can find the documentation of the latest release [here](https://github.com/JarkkoPar/Utility_AI_GDExtension/blob/main/documentation/Nodes_latest.md).


## Compiling from source

1. Clone the repository
2. Initialize and update submodules
```
git submodule init && git submodule update
```
3. Now you should be able to compile the project with scons
```
scons platform=<valid platform>
```

After compilation, copy the bin folder into `demo/addons/utility_ai/` folder. If all goes well, you should be able to launch the demo project in Godot and start using the addon.

