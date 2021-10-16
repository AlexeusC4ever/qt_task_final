Game "Points"
The main aim of this game is to surround enemy's points with your own points.

The game involves two players, each of them takes turns making moves. <br />
When it's someone's turn to move, he chooses a cell in which he wants to put a point. After his click, the program draws a point of a certain color on a game field.<br />
The color of a current player defines between moves by program itself or it defines by server before the game if it's online game.<br />
After drawing the point, the program runs an algorithm to find cycles player could create and if algorithm finds cycles and if there are
enemy points inside these cycles, the program will paint over the corresponding captured area. <br />
It will also count the points inside the surrounded area and make them non-clickable. <br />
If all cells is non-clickable the game ends and the winner is displayed.<br />
In settings user can change the size of game field. It will start a new game.<br />
Also user can save the current game progress and then continue the game at any time.<br />
The project includes online game. User can run a server (gameserver.exe) by himself and then connect to it right through the usual interface by button 'PLAY ONLINE'.<br />
Online game will start as soon as server cathces two connections.<br />
If one of the players quits the game, the server notifies the other player, then disconnects him and ends the game.<br />
