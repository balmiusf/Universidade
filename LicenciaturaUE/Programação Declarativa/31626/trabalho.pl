%:-initialization(rpg).			% always start the interpreter
:-dynamic(record/1).			% tells if recorder is on or off
:-dynamic(track/1). 			% tracking list
:-dynamic(pos/1). 				% current pos
:-dynamic(inventory/1). 		% player's inventory
:-dynamic(hp/1). 				% hero's life
:-dynamic(attack_power/1). 	% hero's attack damage
:-dynamic(equiped_w/1).		% equiped weapon
:-dynamic(equiped_a/1).		% equiped accessory	
:-dynamic(hunger/1).			% hunger level
:-dynamic(thirst/1).			% thirst level
:-dynamic(loaded/1).			% is the map already loaded
:-dynamic(godmode/1).			% is god mode enabled
% there will be a shop at the start of the dungeon

% player's starting items
inventory('Torch').		 % can only use look command with torch
inventory('Herb').			 % healing
inventory('Vial of Water'). % thirst
inventory('Loaf of Bread'). % food

deadboss(0).			% deadboss set to no
loaded(0). 			% is file loaded? default -> no
godmode(0).				% player is not god when he first enters
hunger(30). 			% starting hunger level
thirst(30).			% starting thirst level
hp(150). 				% hero's health pool
attack_power(20). 		% hero's attack power

% find all adjacent to the current node and send it to a list
adjacentes(A,L) :- 
		F =.. [passagem,A,Y,X],
		findall([Y,X],F,L).	

% finds all the possible paths A to B, works with cycles
caminho(A,A,_,[A]).		
caminho(A,B,VISITED,[A,'->',X,'->'|K]):- passagem(A,C,X), \+(member(C,VISITED)),caminho(C,B,[C|VISITED],K).


% prints the list in format I1,I2,I3,I4,....IN
printlist([]):- !.		
printlist([X]):- write(X),nl,!.
printlist([X|H]):- write(X),write(', '),
					printlist(H).

% print list for look command
printlist_3([[X,T]]):- format('      ~w leads to room ~w',[T,X]),nl,!.
printlist_3([[X,T]|T2]):- 
		format('      ~w leads to room ~w',[T,X]),nl,
		printlist_3(T2).
					
% existing room items into a list
room_item_list(QUARTO,LIST):- 
		findall(Nome,item(QUARTO,Nome),LIST).

% items in inventory into a list
inv_item_list(LIST):-
		findall(Nome,inventory(Nome),LIST).

		
% inventory item list print		
printlist2([]):- write('Hero: Ups.. Actually its Empty'),nl,nl,!.			
printlist2([X]):- format('      ~w',[X]),nl,!.
printlist2([X|H]):- format('      ~w',[X]),write(', '),
					printlist(H).

% calls room item list to see the list of items then prints its content					
printItems(QUARTO):- 
		room_item_list(QUARTO,LIST),
		printlist2(LIST).

	% same has previous but to items in the inventory
printInvItems:- 
		inv_item_list(LIST),
		printlist2(LIST).


% tracking	related
% insert in tracking list
insert(X,[],[X]).
insert(X,[H|T],[X,H|T]).
 
% every time he moves to a room or engages in combat it changes the hunger and thirst levels
change_food_thirst_levels:-
		
		hunger(FOOD),
		thirst(THIRST),
		
		N_FOOD is FOOD - 2,
		N_THIRST is THIRST - 3,
		
		retract(hunger(_)),
		retract(thirst(_)),
		asserta(hunger(N_FOOD)),
		asserta(thirst(N_THIRST)).


% everytime a player steps into a room, there is a 10% chance that the room has
% a trap, if the players is unlucky and triggers the trap, he suffers HP loss
act_trap:-
	
	random(1,10,L),
	(L = 1 -> retract(hp(X)), Y #= X - 20, 
		(Y #=< 0 -> write(''); asserta(hp(Y)), nl,
		write('Hero: ARGHHH a trap! Better be careful next time!'),
		nl);
	nl,write('Hero: Uh.. No trap..'),nl).
		
% check to see if ITEM is in player's inventory
lights(ITEM):- inventory(ITEM).	

% add to tracking list the operation X in question
tracking(X):- 
	retract(record(Y)),!,
	(Y = 0 -> write('') ;
	retract(track(LIST)),
	insert(X,LIST,LIST_NEW),	
	asserta(track(LIST_NEW))),
	asserta(record(Y)).

% print tracking list				
printTracking([X]):- 
		write(X),nl,!.
		
printTracking([X|H]):- 
		write(X),
		write(', '),
		printTracking(H).

% current positions
start(X):- 
		pos(X),!.

% call inicial to see what is the room he starts in		
start(X):- 
		inicial(X),
		asserta(pos(X)).
		
% get paths into a list and lenght of list from current position
getDir(Dir, Paths, Lenght):- 
		pos(Y), 
		findall(X,passagem(Y,X,Dir),Paths), 
		length(Paths,Lenght).

% if a direction leads to more than one room -> make the Hero choose one of them
chooseOne(Paths,Dir):- 
		pos(Y),
		write('Hero: This path leads to more than one room..'),nl,nl,
		write('Hero: Where should i go? '), 
		printlist2(Paths),							%print all available paths
		read(X), nl,
		(number(X),passagem(Y,X,Dir) -> move(X);				% if the path exists
		write('Hero: I cant do that.. ')),nl.

		
% check the status of the monster
% player always attacks first
% if monster's hp is below or equal to 0, remove it from the room
% if he has items attached to him, add it to the room item list
% if the monster if a mini boss (aka Guardian) it has special interaction with the hero, same applies to Samael.
check_m(POS,HP_M,_,_,_,NAME_M):- 
	HP_M =< 0, nl, % if the monster is dead
				
	(NAME_M = 'Guardian of the Golden Chamber' -> 
	format('~w: You may have defeated me but you will not get past Lord Samael..',[NAME_M]),nl,nl,
	write('Hero: Im not afraid of no monster. But ill take the challenge!'),nl,nl,
	write('Hero: Looks like he dropped something..'),nl,nl,retract(dropped(POS,NAME_KEY)),			
	asserta(item(POS,NAME_KEY)),retract(monster(POS,NAME_M,_,_)),!;							
	
	(NAME_M = 'Fallen Master Hero' -> write('Hero: Looks like he dropped something..'),nl,nl, % monster drops an item
	retract(dropped(POS,NAME_SWORD)),
	asserta(item(POS,NAME_SWORD)),
	retract(monster(POS,NAME_M,_,_)),!);																% add it to the room item list

	write('Hero: The monster is no more'),nl,nl,
	retract(monster(POS,NAME_M,_,_)),!).

	
% if the monster hp is superior to 0, then the monster can attack the hero. Updates the hero HP, and the monster HP aswell
% if the monster is the Guardian then its attack speech is different.
check_m(POS,HP_M,ATT_M,HP_P,_,NAME_M):- 
	HP_M > 0, %monster still alive
	(NAME_M = 'Guardian of the Golden Chamber' ->  format('~w: YOU SHALL NOT PASS!',[NAME_M]);
	
	format('~w: You will not reach the Golden Chamber!',[NAME_M])),nl,nl,
	format('[~w Attacks]',[NAME_M]),nl,nl,
	HP_NP is HP_P - ATT_M,							% change player's hp
	write('Hero: ARGHH! Try and stop me!'),nl,
	retract(monster(POS,NAME_M,_,_)),			
	asserta(monster(POS,NAME_M,HP_M,ATT_M)),
	retract(hp(_)), asserta(hp(HP_NP)).

% after defeating the mini boss, and the hero enters the final chamber
% Samael will interect with the player according to his [the hero] attack power
speak_samael:-
	attack_power(HERO_ATT), 
	write('Samael: Welcome to my chamber Hero'),nl,nl,
	(HERO_ATT > 998 -> write('Samael: I see you are wielding a powerful artifact..'),nl,
	write('Samael: This should be an interesting fight [he talks about your weapon]'),nl;
	
	write('Samael: You have overcome many obstacules to reach this chamber and to stand here before me'),nl,nl,
	write('Samael: But sometimes, the hero dies in the end'),nl,nl).

% fight with samael, same has the monster but with special interection in case it his defeated
% drops the power the stone that can be used to end the game
fight_samael(HP_M,ATT_M,_,_,NAME_M):-
	HP_M =< 0, nl,pos(X),
	write('[You have defeated Samael]'),nl,nl,
	write('Samael: Interesting... Perhaps you are worthy of it'),nl,nl,
	write('Samael: Here... Take it'),nl,nl,
	write('Hero: Looks like he dropped something'),nl,nl,
	retract(monster(X,NAME_M,_,ATT_M)),
	retract(dropped(X,NAME_I)),
	asserta(item(X,NAME_I)).

	
% samael's turn to attack, same has check_m but with special interactions
fight_samael(HP_M,ATT_M,HP_P,_,NAME_M):-
	pos(X),
	HP_M > 0, write('Samael: Pathetic..'),nl,
	nl,format('[~w Attacks]',[NAME_M]),nl,nl,
	HP_NP is HP_P - ATT_M,
	write('Hero: ARGHH!!'),nl,nl,
	retract(monster(X,NAME_M,_,_)),!,
	asserta(monster(X,NAME_M,HP_M,ATT_M)),
	retract(hp(_)), asserta(hp(HP_NP)).
	

% check if there is a monster in the room
% if that monster is samael then he calls for him. [the hero]

istheremonster(ROOM):- 
	monster(ROOM,NAME_M,_,_),
	(NAME_M = 'Samael' -> write('Hero: He doesnt look like the others.. looks... different'),
	nl,nl,write('Samael: Come mortal'),nl,nl
	; nl,write('Hero: Im not alone in here..'),nl,nl,
	format('~w: Face me!',[NAME_M]),nl).

% end game talk
game_end:- write('Hero: No.. This cant be the end..'), nl,nl,
			write('[G A M E O V E R]'),nl,nl.
			
% ##############################################################################
% ##############################################################################	
% ##############################################################################
% ##############################################################################

% begin position
% begin at the last position
begin:- 
		asserta(track([])),
		asserta(record(0)),
		start(X), nl,
		format('Hero: Starting in room ~w, interesting..',[X]),nl.
		%asserta(pos(X)).

% interpretador com estado externo
% interpretador
% if its the first time playing the interpreter, it asks for a map, 
% if its not the first time playing the interpreter then it skips the check, since its already been loaded,

% stoping the interpreter: 
	% if input is stop, then stop the interpreter
	% if hero's hp less or equal to 0 then stop the interpreter
	% if the hero defeats the boss and gets the Power Stone then stop  the interpreter
	% if the hero's food level is less or equal to 0 then stop the interpreter
	% if the hero's thirst level is less or equal to 0, then stop the interpreter
	
% unless the interpreter is stopped the game is in a loop, always asking for user input

rpg:- 
		nl,(loaded(LOADED), LOADED = 0 -> write('Load Map: '),read(X), nl,nl,consult(X),
		retract(loaded(_)),asserta(loaded(1));
		write('')),
		
		% start game!
		
		begin, repeat,
		
		Y = 'Samael is Power Stone',
		hp(HP),nl,
		hunger(FOOD),
		thirst(THIRST),
		
		(inventory(Y)-> write('[You have acquired the Power Stone]'),nl,nl,					
		write('Hero: Such power, what is this?'),nl,nl,
		write('Samael: With such gift there is always a curse and you freed me from it'),nl,nl,
		write('Samael: And someone has to bear the curse, always. And now im free at least,'),
		nl,nl,
		write('Samael: And you will now bear the name of Samael until another Hero comes'),nl,nl,
		write('[G A M E O V E R]'),true; 	
		
		THIRST =< 0 -> 	write('Hero: I cant go without water...'),nl,nl,game_end,true; 
		FOOD =< 0 -> 	write('Hero: I cant go without food...'),nl,nl,game_end,true; 
		
		(HP =< 0) -> game_end,true; 
		
		% if all the checks fail, ask for input
		write('Hero: What should I do now? '),
		read(A),nl, (A = stop -> true; rpg(A),	fail)). 
	
% base set of commands
% go to position N 
% if it fails, send message and ask for another input
% can only go(N) to valid positions 
% N can only be a number, else fails
rpg(go(N)):- 
		pos(X), 
		(number(N),passagem(X,N,_) -> write('Hero: I hope i dont run into a trap.. '),nl,nl,
		move(N); 
		write('Hero: I cant go there...'),nl,nl),
		tracking(go(N)).
		
% look around the room for paths and items
% if he has torch he can see whats around him, that includes paths and items, else he cant
rpg(look):- 
		pos(X),
		adjacentes(X,L),
		(lights('Torch') ->
		write('Hero: These are my options.. '), nl,nl,
		printlist_3(L),nl,nl, 
		write('Hero: And these are all over the place.. '),nl,nl,
		printItems(X); 
		
		write('Hero: To dark in here... only if i had a torch with me...')),
		tracking(look).
 	
% combat
% player always attacks first
% player can ignore the monster if he so chooses but the monster will not disappear
% attacking consumes resources, that means it drains hunger and thirst
% if the monster is Samael then its a special fight (calls a different predicate)
% Note: some monsters drop items, valuable items
rpg(attack):- 
	write('[Hero attacks]'),nl,nl,hp(HP_P),attack_power(ATT_P),pos(Y), 
	godmode(GOD), 
		(GOD = 0 ->
	retract(thirst(THIRST)), retract(hunger(FOOD)), 
	
	N_THIRST  is THIRST - 5, N_FOOD is FOOD - 3,
	
	asserta(thirst(N_THIRST)), asserta(hunger(N_FOOD)); write('')),
	
	monster(Y,NAME_M,HP_M,ATT_M), 	
	HP_NM is HP_M - ATT_P, 
	
	% special boss
	(NAME_M = 'Samael' -> fight_samael(HP_NM,ATT_M,HP_P,ATT_P,NAME_M);
	check_m(Y,HP_NM,ATT_M,HP_P,ATT_P,NAME_M)),
	tracking(attack). 

% blocking will negate the damage of the monster, but the player will not be able to attack, obviously
% drains resources ( hunger and thirst)
rpg(block):- 
	godmode(GOD), 
		(GOD = 0 ->
		retract(thirst(THIRST)), retract(food(FOOD)), 
	
		N_THIRST  is THIRST - 5, N_FOOD is FOOD - 3,
	
		asserta(thirst(N_THIRST)), asserta(food(N_FOOD)); write('')),
	
		pos(Y),
		write('[Hero blocks]'),nl, monster(Y,NAME_M,_,_),
		(NAME_M = 'Samael' -> write('Samael: Blocking? Pathetic attempt to survive..');
		format('~w: Blocking will not save you forever intruder!',[NAME_M]),nl,nl,
		format('[~w attacks ]',[NAME_M]),nl,nl,
		write('Hero: Ahah! No effect! Nice try!')),
		tracking(block).

% item like swords and accessories will only be in effect once they are equiped
% cannot equip two of the same item. That means, only one weapon and one type of accessory (up to 3) 

rpg(equip(X)):- 
		% if there there is no weapon equipped, equip it and add its stats
		(atom(X),inventory(X),weapon(X,ATT_P), \+(equiped_w(Y)) -> retract(attack_power(ATT)),
		ATT_NW is ATT_P + ATT,
		asserta(attack_power(ATT_NW)),
		asserta(equiped_w(X)), write('[Weapon Equiped]'),nl,write('Hero: Better then fighting with my bare hands'),nl				; 
  		
		% if there is a weapon equipped remove it the current one,
		% that means remove its added stats and replace it with the new weapon's stats
		atom(X),inventory(X),weapon(X,ATT_P), equiped_w(Y) -> 			
		retract(equiped_w(Y)),
		weapon(Y,ATT_W),
		retract(attack_power(ATT)),
		ATT_NW is ATT - ATT_W,
		ATT_NW_2 is ATT_NW+ ATT_P,
		asserta(attack_power(ATT_NW_2)),
		asserta(equiped_w(X)), write('[Weapon Equiped]'),nl,write('Hero: I think i like this one better'),nl			; 
		
		atom(X),equiped_w(X) ->  write('Hero: Its already Equiped..'),nl,nl; % item already equipped
		
		% if the accessory is not equipped, add its stats
		atom(X), inventory(X), accessories(X,ATT_B,HP_B),\+(equiped_a(X)) -> retract(attack_power(ATT)), 
		retract(hp(HP)), N_ATT is ATT + ATT_B, N_HP is HP + HP_B,
		asserta(attack_power(N_ATT)), 
		asserta(hp(N_HP)),asserta(equiped_a(X)), write('Hero: Stylish'),nl				; 
		
		atom(X),equiped_a(X) -> write('Hero: Its already Equiped..'),nl,nl; % item already equipped
		
		write('Hero: I equip that'),nl,nl),
		
		tracking(equip(X)).
	
% directions
% works with multiple paths in same direction
% calculates the paths from its current position
% and according to how many paths, it has an interection. 
% if there are more then one path in the same direction then make the player choose a path
% can be used without torch. 
rpg(n):- 
		pos(Y),
		getDir(n,Paths,Lenght), 
		(Lenght = 0 -> write('Hero: Theres a wall there.. '),nl ,nl;
		Lenght = 1 ->  passagem(Y,X,n),write('Hero: I hope i dont run into a trap...' ),nl,
		nl, move(X); 
		Lenght > 1 -> write('Hero: I hope i dont run into a trap...' ),nl,
		nl,chooseOne(Paths,n)),
		tracking(n).
								
rpg(s):- 
		pos(Y),
		getDir(s,Paths,Lenght), 
		(Lenght = 0 -> write('Hero: Theres a wall there.. '),nl,nl ;						
		Lenght = 1 ->  passagem(Y,X,s),write('Hero: I hope i dont run into a trap...' ),nl,
		nl, move(X); 
		Lenght > 1 ->write('Hero: I hope i dont run into a trap...' ),nl,
		chooseOne(Paths,s)),
		tracking(s).
								
rpg(e):- 	pos(Y),getDir(e,Paths,Lenght), 
		(Lenght = 0 -> write('Hero: Theres a wall there.. '),nl,nl ;
		Lenght = 1 ->  passagem(Y,X,e),write('Hero: I hope i dont run into a trap...' ),nl,
		nl, move(X); 
		Lenght > 1 -> write('Hero: I hope i dont run into a trap...' ),nl,
		chooseOne(Paths,e)),
		tracking(e).
								
rpg(w):- 	pos(Y),getDir(w,Paths,Lenght), 
		(Lenght = 0 -> write('Hero: Theres a wall there.. '),nl,nl ;
		Lenght = 1 ->  passagem(Y,X,w),write('Hero: I hope i dont run into a trap...' ),nl,
		nl, move(X); 
		Lenght > 1 -> write('Hero: I hope i dont run into a trap...' ),nl,
		nl,chooseOne(Paths,w)),
		tracking(w).
								
rpg(nw):- 	pos(Y),getDir(nw,Paths,Lenght), 
		(Lenght = 0 -> write('Hero: Theres a wall there.. '),nl,nl ;
		Lenght = 1 ->  passagem(Y,X,nw),write('Hero: I hope i dont run into a trap...' ),nl,
		nl, move(X); 
		Lenght > 1 -> write('Hero: I hope i dont run into a trap...' ),nl,
		nl,chooseOne(Paths,nw)),
		tracking(nw).
								
rpg(sw):-	pos(Y), getDir(sw,Paths,Lenght), 
		(Lenght = 1 ->  passagem(Y,X,sw),write('Hero: I hope i dont run into a trap...' ),nl,
		nl, move(X); 
		Lenght > 1 -> write('Hero: I hope i dont run into a trap...' ),nl,
		nl,chooseOne(Paths,sw); Lenght = 0 ->
		write('Hero: Theres a wall there.. '),nl,nl),
		tracking(sw).
								
rpg(ne):- 	pos(Y),getDir(ne,Paths,Lenght), 
		(Lenght = 1 ->  passagem(Y,X,ne),write('Hero: I hope i dont run into a trap...' ),nl,
		nl, move(X); 
		Lenght > 1 -> write('Hero: I hope i dont run into a trap...' ),nl,
		nl,chooseOne(Paths,ne);
		Lenght = 0 -> write('Hero: Theres a wall there.. '),nl,nl),
		tracking(ne).
								
rpg(se):- 	pos(Y),getDir(se,Paths,Lenght), 
		(Lenght = 0 -> write('Hero: Theres a wall there.. '),nl,nl ;
		Lenght = 1 ->  passagem(Y,X,se),write('Hero: I hope i dont run into a trap...' ),nl,
		nl, move(X); 
		Lenght > 1 -> write('Hero: I hope i dont run into a trap...' ),nl,
		nl,chooseOne(Paths,se)),
		tracking(se).
								
rpg(up):- 		pos(Y),getDir(up,Paths,Lenght), 
		(Lenght = 0 -> write('Hero: Theres a wall there.. '),nl,nl ;
		Lenght = 1 ->  passagem(Y,X,up),write('Hero: I hope i dont run into a trap...' ),nl,
		nl, move(X); 
		Lenght > 1 -> write('Hero: I hope i dont run into a trap...' ),nl,
		nl,chooseOne(Paths,up)),
		tracking(up).
								
rpg(down):- 	pos(Y),getDir(down,Paths,Lenght), 
		(Lenght = 0 -> write('Hero: Theres a wall there.. '),nl,nl ;
		Lenght = 1 ->  passagem(Y,X,down),write('Hero: I hope i dont run into a trap...' ),nl,
		nl, move(X); 
		Lenght > 1 -> write('Hero: I hope i dont run into a trap...' ),nl,
		nl,chooseOne(Paths,down)),
		tracking(down).

		
% inventory related commands
% print inventory contents
rpg(inv):- nl,
		write('Hero: My backpack.. '),
		printInvItems, 	
		nl,
		tracking(inv).

		
% get an item from the room item list
% if exists in room, add it to inventory, else give error msg
% if its a special item, has special interection
rpg(get(X)):-
		pos(Y),							% get position
		
		(atom(X),item(Y,X) ->			% get item in room
		retract(item(Y,X)),	!,			% remove item from room
		asserta(inventory(X)),			% add item do inventory
		
		(X = 'Key to the Golden Chamber' -> write('Hero: I wonder where i can use this ..'),nl,nl; write('Hero: Got it!'),nl); % if its a special item
		
		write('Hero: I cant see that item..'),nl),	% error msg
		
		tracking(get(X)).				% record (if on)

		
% drops the item in the inventory
% reverse of get(X)
% if the item is equiped then drop it, and remove added stats
% if X is not an atom, then give error msg
rpg(drop(X)):- 
		pos(Y),
		(atom(X),inventory(X) -> 
		write('Hero: Dropping the item'),nl,nl, 
		retract(inventory(X)),!,
		asserta(item(Y,X)),
		(weapon(X,ATT_W), equiped_w(X) -> retract(attack_power(ATT)),NEW_ATT is ATT - ATT_W, asserta(attack_power(NEW_ATT));
		accessories(X,ATT_A,_),equiped_a(X) ->  retract(attack_power(ATT)),NEW_ATT is ATT - ATT_A, asserta(attack_power(NEW_ATT)); 
		write(''));
		write('Hero: I dont have that item..'),nl,nl),		
		tracking(drop(X)).

% if the item, command used for thirst and hunger, 
% if X is not an atom, give error msg
rpg(use(X)):- 
		(atom(X),inventory(X), food(X,REC) -> retract(hunger(FOOD)), N_X is FOOD + REC, asserta(hunger(N_X)), 
		write('Hero: Yummy!'),retract(inventory(X)),nl;
		inventory(X), thirst(X,REC),atom(X) -> retract(thirst(THIRST)), N_X is THIRST + REC, asserta(thirst(N_X)), 
		write('Hero: Refreshing!'),retract(inventory(X)),nl;
		write('Hero: I cant use that'),nl,nl), tracking(use(X)).
		
		
% if the item is of type potion, recover hp
% if the item is not an atom, give error msg
rpg(heal(X)):- 
		(atom(X),inventory(X),potions(X,HP_RECOVERY) -> retract(inventory(X)),!,
		retract(hp(N)), M #= N + HP_RECOVERY, asserta(hp(M)),write('Hero: Where would i be without you..'),nl; write('Hero: I cant use that'),nl),
		tracking(heal(X)).


% check the player stats, HP, ATT, FOOD,THIRST
rpg(stats):- 
	hp(X), format('   [Health Points: ~w]',[X]),nl,
	attack_power(ATT), format('   [Attack Power: ~w]',[ATT]),nl,
	hunger(FOOD), format('   [Hunger: ~w]',[FOOD]),nl,
	thirst(THIRST), format('   [Thirst: ~w]',[THIRST]),nl,
	tracking(stats).

	
% record
% if recorder already on send message to user
rpg(record):-
		retract(record(X)),!,
		(X = 0 -> asserta(record(1)),nl,
		write('Hero: Let me grab my quil and paper...'),nl;nl,
		write('Hero: I am already writing down...'),nl,
		asserta(record(1))).


% turns off the recorder
% if recorder already off send message to user
rpg(forget):-
		retract(record(X)),!,
		(X = 1 -> asserta(record(0)),nl,
		write('Hero: Storing my quil and paper in the backpack...'),nl;nl,
		write('Hero: My writing material is already in the backpack...'),nl,
		asserta(record(0))).


% list every step so far
rpg(track):- 
	retract(track(LIST)),!,
	(LIST = [] -> nl,write('Hero: I havent done anything yet..'),nl ;nl, 
	write('Hero: Heres what I have done so far..'),nl,
	printTracking(LIST)),
	asserta(track(LIST)),!.


% wizard mode
% jumps to N, 
rpg(jump(N)):- 
		(\+(number(N)) -> write('[Thats not a valid room]'),nl,nl;
		write('Hero: Woaaaah im teleporting!'),nl,nl,
		(final_chamber(N),monster(N,_,_,_) ->  retract(pos(_)),
		write('Hero: The Golden Chamber ham.. Looks golden.. '),nl,nl,write('Hero: Wait.. Who is that?'),nl,nl,
		istheremonster(N),speak_samael,asserta(pos(N));
		
		final_chamber(N),\+(monster(N,_,_,_)) -> retract(pos(_)),write('Hero: The Golden Chamber ham.. Looks golden.. '),nl,nl,
		asserta(pos(N));
 		move(N))),
		tracking(jump(N)).

% NOTE: if you want to add item remember to use 'X' instead of just X
% makes and item appear at the current location
rpg(warp(X)):- 
		(atom(X)->
		pos(QUARTO),
		asserta(item(QUARTO,X)),write('[Item warp at location]'),nl; write('[Not a valid item]'),nl),
		tracking(warp(X)).
		
%  NOTE: if you want to destroy an item remember to use 'X' instead of X
% destroy an item that belongs to the room item list
rpg(destroy(X)):-
		(atom(X) ->
		pos(Y), (item(Y,X) ->
		retract(item(Y,X)),!,write('[Item destroyed at location]'),nl; write('Not a valid item]'),nl); write('[Not a valid item]'),nl),
		tracking(destroy(X)).


% cheat codes
% path from X room to final room
rpg(path(X)):- tracking(path(X)),nl,write('[All avaible paths]'),final_chamber(Y), caminho(X,Y,[X],LIST), nl,printlist(LIST),nl.  

% path current position to final room
rpg(path):- tracking(path), nl,write('[All avaible paths]'), pos(X), final_chamber(Y),  caminho(X,Y,[X],LIST),nl,printlist(LIST),nl.  

% path from X to Y.
rpg(path(X,Y)):- tracking(path(X,Y)), nl, write('[All avaible paths]'),  caminho(X,Y,[X],LIST),nl,printlist(LIST),nl.  

% god mode, self explanitory (spell check)
rpg(gm):- (godmode(X), X = 0 -> write('[God Mode Actived]'),nl,retract(attack_power(ATT)), GM_ATT is ATT + 9999, 
			asserta(attack_power(GM_ATT)),retract(godmode(_)),asserta(godmode(1));
			write('[God Mode already Activated]'),nl),tracking(gm).

% disables god mode
rpg(nogm):- (godmode(X), X = 1 -> nl, write('[God Mode Deactived]'),nl,retract(attack_power(GM_ATT)), 
			NO_GM_ATT is GM_ATT - 9999, asserta(attack_power(NO_GM_ATT)),retract(godmode(_)),asserta(godmode(0));
			write('[God Mode already Deactivated]'),nl),tracking(nogm).

% update new position
% update hunger + thirst levels unless he is in godmode
% checks if player has a key if he wants to enter the final chamber
% if he has key in inventory and the room NAME is the golden chamber then -> special interections with samael, 
move(NX):- 
		retract(pos(X)),!, 
		quarto(NX,NAME),
		(godmode(GOD), GOD = 0 -> change_food_thirst_levels; write('')),
		
		(KEY = 'Key to the Golden Chamber', inventory(KEY) , NAME = 'Golden Chamber' -> write('[You use the key]'),nl,nl,write('Hero: The Golden Chamber ham.. Looks golden.. '),nl,nl,write('Hero: Wait.. Who is that?'),nl,nl,
		istheremonster(NX),speak_samael,asserta(pos(NX))
		; NAME \=  'Golden Chamber' -> format('Hero: Room ~w , interesting...',[NAME]),nl,act_trap,asserta(pos(NX)),istheremonster(NX);
		
		NAME = 'Golden Chamber' -> write('Hero: I cant do that. There must be a key around here somewhere...'),nl,nl,asserta(pos(X))). 	 	