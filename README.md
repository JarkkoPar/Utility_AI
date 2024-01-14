# Utility_AI

A Utility AI implementation for the Godot Engine using gdextension. If you don't know what Utility AI is, Wikipedia defines it as follows:

*"...Utility AI, is a simple but effective way to model behaviours for non-player characters. Using numbers, formulas and scores to rate the relative benefit of possible actions, one can assign utilities to each action. A behaviour can then be selected based on which one scores the highest 'utility'...* - [Wikipedia - Utility system](https://en.wikipedia.org/wiki/Utility_system)

You can download the latest version of the source code from the releases. The releases in this repository contain only the source code. To get the binaries and the example project, go to this repository: [Utility AI GDExtension](https://github.com/JarkkoPar/Utility_AI_GDExtension).

Please note that this is the **source code repository** and may contain in-development changes. While I aim to keep the main branch always in a compilable shape, it may sometimes contain incomplete features.

## Compatibility

Godot 4.1.2 or newer.

## Components

* *Utility based AI Agent Behaviours* 
* *Behaviour Tree with utility support*
* *State Tree with utility support*
* *Node Query System*


## How to use the nodes

You can find the tutorials [here](https://github.com/JarkkoPar/Utility_AI_GDExtension/tree/main/tutorial).

## Documentation

You can find the documentation [here](https://github.com/JarkkoPar/Utility_AI_GDExtension/blob/main/documentation/Nodes_latest.md).


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

After compilation, the binaries are created in to the `demo/addons/utility_ai/` folder. If all goes well, you should be able to launch the demo project in Godot and start using the addon.

