# Utility_AI
A Utility AI implementation for the Godot Engine using gdextension.

## Node listing

* *UtilityAIAgent* This is the main node that is used manage the UtilityAI. It represents an AI entity.
* *UtilityAIBehaviour* The various things the AI agent can do are called _behaviours_. Each Behaviour consists of _considerations_ and _actions_.
* *UtilityAIConsideration* The AI agent does it's reasoning on what behaviour to use by going through its considerations and producing a score for each behaviour. This node is used to represent a single thing the AI Agent should consider about a behaviour. A consideration uses a _sensor_ for input data.
* *UtilityAIConsiderationGroup* Several considerations can be grouped to create more complex or high-level logic.
* *UtilityAISensor* The sensor node is used to update input data to the AI Agent's considerations.
* *UtilityAISensorGroup* Several sensors can be grouped for more high-level sensor input to the considerations.
* *UtilityAIAction* A behaviour, if selected, will run any actions attached to it.
* *UtilityAIActionGroup* Groups can help organize how a behaviour will run the actions attached to it.

## How to use the nodes

Start by adding a UtilityAIAgent to your scene. Next you can add the Sensors as the childs of the AI agent node. And then add the Behaviours. It is expected that any sensors are before behaviours. 

Then add considerations to the Behaviours you have added. And finally the Actions. 

In your code update the sensor's `sensor_value` with a floating point value between 0.0 and 1.0. Then run the UtilityAIAgent's `evaluate_options` method and `update_current_behaviour` method to get an `action` to execute. You can then get the action by using the `get_current_action` method.
Do what ever you need to do for the action selected and once done, mark it as finished using the `set_is_finished(true)` method. This will allow the current behaviour to step to the next action during the `update_current_behaviour` call.

## Nodes in-depth 

### UtilityAIAgent 

This is the main node that is used to manage the UtilityAI. A UtilityAIAgent node represents an AI entity that can reason based in `sensor` input and then choose `behaviours` to react to the sensor input. The UtilityAIAgent has the following methods:

#### Properties

|Type|Name|Description|
|--|--|--|
|int|num_behaviours_to_select|Pick a behaviour out of top `num_behaviours_to_select` behaviours found after reasoning.|
|float|thinking_delay_in_seconds|Delay time forced between calls to the method `evaluate_options`.|
|--|--|--|

#### Methods 

|Return value|Name|Description|
|--|--|--|
|void|evaluate_options(float delta)|Gathers input from sensors and evaluates all the available behaviours by calculating a score for each of them and then choosing a random behaviour from the top `num_behaviours_to_select` behaviours.|
|void|update_current_behaviour()|Updates the currently selected behaviour and if the current `action` has been marked as finished, returns the next action.|
|--|--|--|

