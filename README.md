# Utility_AI

A Utility AI implementation for the Godot Engine using gdextension. If you don't know what Utility AI is, Wikipedia defines it as follows:

*"...Utility AI, is a simple but effective way to model behaviours for non-player characters. Using numbers, formulas and scores to rate the relative benefit of possible actions, one can assign utilities to each action. A behaviour can then be selected based on which one scores the highest 'utility'...* - [Wikipedia - Utility system](https://en.wikipedia.org/wiki/Utility_system)

You can download the latest version from the releases. The release contains an example project that shows the usage of these nodes.


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

## How to use the nodes

Start by adding a UtilityAIAgent to your scene. Next you can add the Sensors as the childs of the AI agent node. And then add the Behaviours. It is expected that any sensors are before behaviours. 

Then add considerations to the Behaviours you have added and connect them to sensors by setting the input_sensor_nodepath property on the considerations. And finally, add the Actions to the behaviour. 

In your code update the sensor's `sensor_value` with a floating point value between 0.0 and 1.0. Then run the UtilityAIAgent's `evaluate_options` method and `update_current_behaviour` method to get an `action` to execute. You can then get the action by using the `get_current_action` method.
Do what ever you need to do for the action selected and once done, mark it as finished using the `set_is_finished(true)` method. This will allow the current behaviour to step to the next action during the `update_current_behaviour` call.

## Nodes in-depth 

This section describes the nodes, their properties and methods in detail. After each property and method you can find the version tag when the given property/method was introduced. Nodes, properties and methods that are being developed for a future release have the version tag `DEV`.

### UtilityAIAgent 

This is the main node that is used to manage the UtilityAI. A UtilityAIAgent node represents an AI entity that can reason based in `sensor` input and then choose `behaviours` to react to the sensor input.

#### Properties

|Type|Name|Description|Version|
|--|--|--|--|
|bool|is_active|This property can be used to include or exlude the node from processing.|v1.0|
|int|num_behaviours_to_select|Pick a behaviour out of top `num_behaviours_to_select` behaviours found after reasoning.|v1.0|
|float|thinking_delay_in_seconds|Delay time forced between calls to the method `evaluate_options`.|v1.0|

#### Methods 

|Return value|Name|Description|Version|
|--|--|--|--|
|void|evaluate_options(float delta)|Gathers input from sensors and evaluates all the available behaviours by calculating a score for each of them and then choosing a random behaviour from the top `num_behaviours_to_select` behaviours.|v1.0|
|void|update_current_behaviour()|Updates the currently selected behaviour and if the current `action` has been marked as finished, returns the next action.|v1.0|
|void|abort_current_behaviour()|Immediately stops the currently selected behaviour and action. Used for stopping behaviours that have `Can Be Interrupted` property as `false`.|v1.0|


### UtilityAISensor and UtilityAISensorGroup

These two node types should be added as child nodes of the `UtilityAIAgent` node. They are used to give input data to `consideration` nodes. A `sensor` is used by one or more `consideration` nodes. A `sensor group` is a node that can be used to aggregate input from several sensors (or sensor groups) for a higher-level input to the consideration nodes. 

Why use sensors in the first place? Consider the situation where you have several behaviours that use the "IsPlayerClose" consideration and maybe different variations, such as "IsPlayerAboutMidDistanceFromMe" or what ever. With the sensor nodes you can calculate the distance once and set it to a sensor, and then all the various considerations can make use of the distance in a relatively easy way and the distance only needs to be calculated once.

#### Properties

The `UtilityAISensor` has the following properties:

|Type|Name|Description|Version|
|--|--|--|--|
|bool|is_active|This property can be used to include or exlude the node from processing. Note that even a deactivated sensor can be used as valid input for the Considerations.|v1.0|
|float|sensor_value|A floating point value in the range of 0..1.|v1.0|

The `UtilityAISensorGroup` has the following properties:

|Type|Name|Description|Version|
|--|--|--|--|
|bool|is_active|This property can be used to include or exlude the node from processing. Note that even a deactivated sensor can be used as valid input for the Considerations.|v1.0|
|float|sensor_value|A floating point value in the range of 0..1.|v1.0|
|float|evaluation_method|A choice of how the sensors and sensor groups that are childs of the node are aggregated. Can be one of the following: Sum:0,Min:1,Max:2,Mean:3,Multiply:4,FirstNonZero:5,OneMinusScore:6.|v1.0|
|float|evaluation_method|A choice of how the sensors and sensor groups that are childs of the node are aggregated. Can be one of the following: Sum:0,Min:1,Max:2,Mean:3,Multiply:4,FirstNonZero:5.|`DEV`|
|bool|invert_sensor_value|This inverts the group sensor_value by calculating: sensor_value = 1.0 - sensor_value. It is applied after all the child nodes have been evaluated.|`DEV`| 


#### Methods 

None.


### UtilityAIBehaviour

This node type should be added as child node of the `UtilityAIAgent` node or the `UtilityAIBehaviourGroup`, preferably after any `sensor` and `sensor group` nodes. There can be several behaviour nodes as childs of the `UtilityAIAgent` or the `UtilityAIBehaviourGroup` node.

As you may have guessed from the name, the purpose of the behaviour nodes is to define what the `AI agent` will do based on different inputs given using the `sensor` nodes. To accomplish this each behaviour node must have one or more `consideration` or `consideration group` nodes as its childs, and also one or more `action` or `action group` nodes. 

The behaviour node will use the  `consideration` nodes that are its childs to determine a `score` for itself. Basically it just sums up the scores from the considerations. When the behaviour is chosen by the `AI agent` as the one to execute, the `action` nodes are stepped through.

The behaviour has also two "cooldown" properties: `cooldown_seconds` and `cooldown_turns`. These can be used to temporarily exclude some behaviours from subsequent `AI agent`'s `evaluate_options` calls once they have been chosen. The `cooldown_seconds` is meant to be used with real-time games and the `cooldown_turns` with turn based games but both can be used even at the same time. The difference in the cooldown countdown is that the `cooldown_seconds` counts down regardless of how many times the `AI agent`'s `evaluate_options` method is called, and the `cooldown_turns` counts down only when the `evaluate_options` method is called. 

#### Properties

The `UtilityAIBehaviour` has the following properties:

|Type|Name|Description|Version|
|--|--|--|--|
|bool|is_active|This property can be used to include or exlude the node from processing.|v1.0|
|bool|can_be_interrupted|A boolean value to determine if the behaviour can be interrupted or not. If a behaviour cannot be interrupted, the `evaluate_options` method of the `UtilityAIAgent` will not execute until the behaviour has completed all its actions.|v1.0|
|float|score|The score for the behaviour after the behaviour has evaluated its considerations.|v1.0|
|float|cooldown_seconds|If > 0.0, after the behaviour is chosen it will a score of 0.0 during the `evaluate_options` until the time has passed.|v1.0|
|int|cooldown_turns|If > 0, after the behaviour is chosen it will a score of 0 during the `evaluate_options` until the given number of calls to the evaluation function has been done.|v1.0|


#### Methods 

None.

### UtilityAIBehaviourGroup

The `UtilityAIBehaviourGroup` node type should be added as child node of the `UtilityAIAgent` node, preferably after any `sensor` and `sensor group` nodes. There can only be one level of child nodes, which means you cannot have nested Behaviour Group nodes.

The purpose of the behaviour group nodes is to allow logical grouping if behaviours and also to allow group-based activation and deactivation of Behaviour nodes.

The behaviour group node will use the  `consideration` nodes that are its childs to determine a `score` for itself. If this `score` is greater or equal to the set `activation score` or if there are no considerations added to the behaviour group, the child behaviours will be evaluated during the AI Agent's `evaluate_options` call. 


#### Properties

The `UtilityAIBehaviourGroup` has the following properties:

|Type|Name|Description|Version|
|--|--|--|--|
|bool|is_active|This property can be used to include or exlude the node from processing.|v1.0|
|float|score|The score for the behaviour group after the considerations that are its child nodes have been evaluated. If no consideration nodes have been added as the childs of the Behaviour Group, the score will be 0.0 but the child behaviours of the Behaviour Group will still be evaluated.|v1.0|
|float|activation_score|The score must be greater or equal to the activation score for the behaviour group to allow for evaluation of the behaviour nodes that are its children.|v1.0|


#### Methods 

None.


### UtilityAIConsideration and UtilityAIConsiderationGroup

These two node types should be added as child nodes of the `UtilityAIBehaviour` node. They are used when a `behaviour` is being scored by the `AI agent`. 

Each consideration node can contain an `activation curve` that can be defined in the node properties. If no curve has been set, the consideration nodes input value will be used as the consideration result as-is.

If a `sensor` or a `sensor group` is used as the input value for a consideration the input for the consideration will be the `sensor_value` property of the sensor node. Otherwise the value of the consideration's `activation_input_value` property will be used.

Consideration groups can be used to aggregate the input from several considerations or consideration groups to create more complex consideration logic. 

-- `DEV` The following section about a feature under development --

A custom evaluation method can be defined for the `UtilityAIConsideration` node by extending the node with a script and defining a method named `eval`: 

```gdscript
func eval() -> void:
    # Your code here. 
    score = 0.0
```

In your custom `eval` method you should set the `score` property to a value between 0 and 1. You can sample the `activation_curve` using the method `sample_activation_curve(double input_value)`. Also, you can set the `has_vetoed` property by using your custom function. If `has_vetoed` property is true, it causes the Behaviour to receive a score of 0.0 and the behaviour immediately ends evaluating other considerations. Note that the `has_vetoed` property will not be reset back to false automatically, so if you set it to true in your custom evaluation method, you will also need to set it to false when you want the veto-state to end.

If you need to override the `_ready()` method for your custom consideration, you need to add the `initialize_consideration()` method call to your `_ready()` method:
```gdscript
func _ready():
    initialize_consideration()
    # Your code here. 
    
```

-- End of section about a feature under development --

#### Properties

The `UtilityAIConsideration` has the following properties:

|Type|Name|Description|Version|
|--|--|--|--|
|bool|is_active|This property can be used to include or exlude the node from processing.|v1.0|
|float|activation_input_value|A floating point value in the range of 0..1.|v1.0|
|NodePath|input_sensor_node_path|A nodepath to a sensor or a sensor group node that will set the `activation_input_value`.|v1.0|
|Curve|activation_curve|A godot curve property that defines how the `activation_input_value` will be translated to a `score`.|v1.0|
|float|score|The resulting score for the consideration after evaluation.|v1.0|
|bool|has_vetoed|If this is set to `true`, the consideration forces the score to be 0.0 and ends the evaluation immediately.|v1.0|

The `UtilityAIConsiderationGroup` has the following properties:

|Type|Name|Description|Version|
|--|--|--|--|
|float|evaluation_method|A choice of how the sensors and sensor groups that are childs of the node are aggregated. Can be one of the following: Sum:0,Min:1,Max:2,Mean:3,Multiply:4,FirstNonZero:5,OneMinusScore:6.|v1.0|
|float|evaluation_method|A choice of how the sensors and sensor groups that are childs of the node are aggregated. Can be one of the following: Sum:0,Min:1,Max:2,Mean:3,Multiply:4,FirstNonZero:5.|`DEV`|
|float|score|The resulting score for the consideration group after evaluation.|v1.0|
|bool|has_vetoed|If this is set to `true`, the consideration group forces the score to be 0.0 and ends the evaluation immediately. The consideration group can receive this value from any of the considerations that are its childs.|v1.0|
|bool|invert_score|This inverts the group score by calculating: score = 1.0 - score. It is applied after all the child nodes have been evaluated.|`DEV`| 


#### Methods 

The `UtilityAIConsideration` has the following methods:

|Type|Name|Description|Version|
|--|--|--|--|
|void|initialize_consideration()|If you override the _ready() method, you have to call initialize_consideration() in your _ready() method.|`DEV`|
|double|sample_activation_curve(double input_value)|Use the input_value to get the resulting Y-value for the `activation_curve`. If no valid curve is set, this method will return 0.0.|`DEV`|

### UtilityAIAction and UtilityAIActionGroup

These two node types should be added as child nodes of the `UtilityAIBehaviour` node. They are used when a `behaviour` is being executed by the `AI agent`. 

Action groups can be used create sequences of actions, or to pick one random action from several choices. This allows for more complex actions to be performed by a behaviour.

*NOTE!* When the `AI agent` has chosen a behaviour, the action step function is called to find the first action to execute. The action that is being executed must be set as finished for the `AI agent` step function to be able to go to the next action. The action logic itself can be implemented anywhere else.

#### Properties

The `UtilityAIAction` has the following properties:

|Type|Name|Description|Version|
|--|--|--|--|
|bool|is_active|This property can be used to include or exlude the node from processing.|v1.0|
|int|action_id|A user-definable numeric ID for the action. Provided as an alternative to using action node names for identifying which is the current action the `AI agent` is currently executing.|v1.0|
|bool|is_finished|Use this property only to let the `AI agent` know when the chosen action is finished. The stepper function will immediately set it back to false once it has moved on to the next action.|v1.0|

The `UtilityAIActionGroup` has the following properties:

|Type|Name|Description|Version|
|--|--|--|--|
|float|execution_rule|A choice of how the actions that are child nodes are executed: Sequence:0,PickOneAtRandom:1. The Sequence choice will execute the actions from top to bottom and the Pick One At Random does what it says it will.|v1.0|
|bool|is_finished|Set internally by the stepper, visible only for debugging purposes.|v1.0|

#### Methods 

None.


## Compiling from source

To compile this repository, first setup the GDExample project as described in the Godot documentation. Copy the contents of this repository into the src-folder. Finally, copy the SConstruct file from the src folder to the parent folder.
 
You should now be able to compile the project with the scons commands as noted in the Godot documentation for the GDExample project. 

After compilation, copy the libutilityai.gdextension file and the icons-folder with its contents to the Demo-project bin-folder. If all goes well, you should now be able to use the nodes in the Demo-project and the nodes should have their icons.

