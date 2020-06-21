# LJDVELH
C++ Gamebook project (Using SDL2)

Le Jeu Dont Vous Etes Le Hero in French or Gamebook in English is unique and specific mission to be completed by browsing through the pages, with an always different ending. This project can be considered as a digital version of Gamebook. 

This project developped by Iliass El Lahibi, Emma Petit, Louis Garrido and Oguzhan Umut Ozgur in January 2020. Also, this project developped under the supervision of Université Claude Bernard Lyon 1.

# How to play ? 
New Game and Continue game allow you to play the game. On the left page you have the story text and the current action number, on the right page you have the possible choises and their number. You can choose one of the choises. You can roll a dice by clicking the dice which can be found on the bottom of the right page. You can go back to home screen (menu) by pressing 'M'. 
Game Path draws the path tree of all possible choises you can make and also it shows in green the blocks of your current path.
Current Path shows you the path you followed in your last save. 
Export HTML creates an HTML file of Gamebook's Web version.

# How to add new book ?
You can easily adapt any Gamebook (with a free-license) to the game. You have to reformulize the format. You can check the books used in the base project to understand how to implement new books.
Basic Structure: Total number of actions/texts
                 Number of the action, explination of the action(story)
                 Number of total choises for the current action
                 Number of the choise, (Optional) text/description of the choise 
                 ...
                 Number of the choise, (Optional) text/description of the choise 
                 
## Example:  
5                                                         //Number of total actions/texts

1,Here is the home                                        //First action

2                                                         //First action has 2 choises

2,take the stairs                                         //First choise

3,take the left door                                      //Second choise

2,You see a big meeting room after taking the stairs      //Second action

2                                                         //Second action has 2 choises

4,take the left door                                      //First choise

5,check the meeting room                                  //Second choise

3,it is a small basic bed-room                            //Third action

1                                                         //Third action has 1 choises

1,You go back                                             //First choise

4,There is a trap, you fall and die                       //forth action has 0 choises

0,                                                        //The end

5,You find the room you have been looking for             //fifth action has 0 choises

0                                                         //The end


# packages/libraries used 
## sdl2
## sdl2.nuget
## sdl2_image.nuget
## sdl2_mixer.nuget
## sdl2_ttf.nuget

# License
Musics, images and books used in the project are free copyright.
This project is a free license project. You can download, modify and redistribute while it is not for commercial use. Name of the base developpers must be mentioned. 

Contact for questions and further Information: oguzhan-umut.ozgur@etu.univ-lyon1.fr
