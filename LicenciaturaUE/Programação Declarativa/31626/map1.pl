:-dynamic(item/2). 			% item, room ,description 
:-dynamic(monster/4).	 	% monsters are scattered around the dungeon. room , name, hp, attack
:-dynamic(dropped/2). 		% dropped goodies


% quarto
% quarto(ID,NOME)
% floor 1 rooms

quarto(11,'#11').
quarto(12,'#12').
quarto(13,'#13').
quarto(14,'#14').
quarto(15,'#15').
quarto(16,'#16').
quarto(17,'#17').
quarto(18,'#18').

% floor 2 rooms
quarto(1,'#1').
quarto(2,'#2').
quarto(3,'#3').
quarto(4,'#4').
quarto(5,'Golden Chamber').
quarto(6,'#6').
quarto(7,'#7').
quarto(8,'#8').
quarto(9,'#9').
quarto(10,	'#10').

% floor 1 path

passagem(11,18,sw).
passagem(11,14,nw).
passagem(12,17,e).
passagem(12,18,se).
passagem(13,17,e).
passagem(13,16,nw).
passagem(14,11,n).
passagem(14,16,nw).
passagem(14,15,nw).
passagem(15,16,n).
passagem(15,1,down). % go to second floor
passagem(16,13,e).
passagem(16,15,se).
passagem(16,14,se).	
passagem(17,12,e).
passagem(17,13,w).
passagem(18,11,s).
passagem(18,12,ne).

% paths
% passagem(ID1,ID2,DIR)
passagem(1,4,w).
passagem(1,4,s).
passagem(1,15,up).
passagem(1,8,e).
passagem(1,6,se).
passagem(2,8,se).
passagem(2,3,ne).
passagem(2,3,w).
passagem(2,10,n).
passagem(2,5,n).
passagem(2,9,n).
passagem(3,9,ne).
passagem(3,9,w).
passagem(3,6,se).
passagem(3,2,sw).
passagem(3,2,s).
passagem(4,1,sw).
passagem(4,10,nw).
passagem(4,1,nw).
passagem(5,2,s).
passagem(6,3,w).
passagem(6,1,se).
passagem(6,8,se).
passagem(7,10,se).
passagem(8,1,ne).
passagem(8,2,w).
passagem(8,6,ne).
passagem(9,2,sw).
passagem(9,3,nw).
passagem(10,7,nw).
passagem(10,2,se).
passagem(10,4,n).

inicial(11).		% starting room
final_chamber(5). % final room

item(11,'Potion'). 
item(11,'Potion'). 
item(11,'Note').
item(8,'Good ol generic sword').
item(14,'Ancient Stone Sword').
item(17,'Ancient bracelet of Power'). % one of 3
item(16,'Necklace of Justice').
item(12,'Small Potion').
item(18,'Ancient Stone Sword').
item(16,'Herb').
item(1,'Potion').
item(1,'Potion').
item(7,'Potion').
item(16,'Pickle').
item(18,'Cheese').
item(4,'Small Potion').
item(3,'Good ol generic sword').
item(10,'Ancient Ring of Power').
item(7,'Big Potion').
item(1,'Pickle').
item(15,'Cheese').
item(9,'Cheese').
item(9,'Jug of Water').
item(1,'Jug of Water').
item(12,'Wine').
item(4,'Wine').
item(18,'Wine').
item(14,'Vial of Water').


monster(6,'Skeleton Warrior',300,40). % ROOM, NAME, HP, ATTACK
monster(3,'Skeleton Berserker',400,50). % ROOM, NAME, HP, ATTACK
monster(16,'Zombie',10,10).
monster(12,'Fallen Rookie Hero',30,15).
monster(4,'Fallen Hero',200,100).
monster(7,'Fallen Master Hero',300,150).
monster(14,'Skeleton Warrior',10,10).
monster(15,'Skeleton Beserker',50,30).
monster(1,'Fallen Rookie Hero',300,60).
monster(10,'Fallen Hero',50,50).
monster(8,'Fallen Veteran Hero',450,300).

% boss monsters
monster(2,'Guardian of the Golden Chamber',700,350). % guardian of the chamber
monster(5,'Samael',999,999). % final boss

% drops by monster
dropped(2,'Key to the Golden Chamber'). % dropped by chamber boss
dropped(5,'Samael is Power Stone').
dropped(7,'The Destroyers Wrath').

special('Key to the Golden Chamber').
special('Samael is Power Stone').
special('The Destroyers Wrath').
special('Necklace of Justice').
special('Ancient Ring of Power').
special('Ancient bracelet of Power').

% equip weapons
weapon('Ancient Stone Sword',30).
weapon('Good ol generic RPG sword',40).
weapon('Flaming whip of vengeance',200).
weapon('The Destroyers Wrath',600). % only weapon that can kill samael

% consumables
potions('Herb',15).
potions('Small Potion',30).
potions('Potion',50).
potions('Big Potion',60).

% food and water

food('Loaf of Bread',20).
food('Pickle',20).
food('Cheese',20).

thirst('Vial of Water',13).
thirst('Jug of Water',20).
thirst('Wine',10).
thirst('Canteen of water',30).

% accessories
accessories('Necklace of Justice',30,30).
accessories('Ancient Ring of Power',200,200).
accessories('Ancient bracelet of Power',200,200).
