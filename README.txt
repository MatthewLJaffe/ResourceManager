This project is a Resource Managment game inspried by the Guildhall Portfolio assignment created by Matthew Jaffe
This project was finished January 28th 2023 

All relevant code files are included in the same directory in this directory. Dependencies are included
in the src directory, and required assets such as the ttf fonts and pngs are included in the assets directory.
All dependcies are locally included in this directory. 

To compile and run the program, open ResourceManager.sln in visual studio
Select x86 as the target platform
the program can then be run in visual studio 

How to Play:
Move around the map to pick up resources. More resources can be found at the ends of the map 
but more aliens will also spawn the further out you go. At the start of each wave a large group
of aliens spawn so having building a base that you can fall back to is recommended. 

Controls:
Move with A/D
Open the crafting menu with I
use keys 1-6 to select crafted resources and left mouse to use crafted resources

In the crafting menu:
Drag with left mouse to move around the crafting graph.
Resource nodes can also be individually dragged around to be displayed in the preffered configuration.
You can selected a node to see what resources are required to craft it in the Resource list.
The crafting menu can be zoomed in or out with the mouse wheel.

Resource Manager:
This project was inspired by the SMU Guildhall Resource Management portfolio assignment.
By default this program will read in the text file resources.txt which it uses to build the directed resource graph.
Support for different quantities of resources has been added so for example:
handgun bullets[2] ore[2]
Means that handgun depends on 2 bullets and 2 ore in order to be crafted.
if "start without" is written on the first line of the resource file then to start there will be 0 of all resources.
A resource will become visible in the GUI Resource Graph if one or both of the following conditions are met:
1 or more of all its requred resources exist in the resource graph or can be crafted.
1 or more of the resource exists in the resource graph

The following commands are supported via command line:
add "resource name" adds resource to the graph if it already exists increments the amount 1
multiple resources can be added using add "resource name"[amount]

del "resource name" removes resource from graph if there are multiple of the resource it decrements the amount by 1
multiple of a resource can be removed from the resource graph using del "resource name"[amount]

erase "resource name"
permanently removes resource from the graph. resources that depended on it before no longer do

link "from resource" "to resource"
creates a link where "from resource" now depends on "to resource"
multiple of a resource can be linked to "from resource" by using link "from resource" "to resource"[amount]

unlink "from resource" "to resource"
destroys the link from "from resource" to "to resource" so "from resource" no longer depends on "to resource"

q
quits the program

The modified resource graph is saved when quitting the application as "OutResources.txt"

To supply the game with a different resources file to build the graph based on add it as a command line argument
invocation would look like

./ResourceManager OtherResourceFile.txt 