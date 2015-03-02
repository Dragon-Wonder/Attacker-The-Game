# Attacker: The Game
A game I am working on as a way to teach myself c++ putting it here mainly to have a version in a central location, but also to get feedback and help if I get any.

This game is super simple, and as I said I am mostly just using it as a way to improve my understanding of c++. I will welcome any tips or ideas for improvements that someone might provide.

The game itself is boiled down to the most basic level of a game. There are five stats that you can set up however you wish (but there must be at least 1 skill point in each stat).

Strength (STR) - How much damage you do.

Constitution (CONS) - Your health.

Dexterity (DEX) - Effects your chance to dodge. (Will do more later).

Defence (DEF) - Effects how much damage you take.

Luck (LUK) - The random chance things will go your way with dodges, crits, and monsters that spawn.



You must go through 10 randomly generated dungeons fighting monsters along the way.

During each battle you may 'Attack' in which case you and the monster both trade blows. You can 'Heal' for 10% of you maxmium health and the monster does less damage or exit the game.

On each level you are trying to get the the down stairs which is represented by "<". While the player is a "+". Doors are "$" currently they don't do anything special, but that will likely change in a furture verison.

Like I said there is not a lot to the game as of right now but that is partly why I'm putting the game here so I can get feedback and ideas on how to improve the game.

##Goals

I have a few goals in mind about what I want to do with this but I am always looking for more ideas.

###Completed Goals

- [x] Implent more monsters that have different stats and increase the variaty a bit. -2/17/15

- [x] Implented more variety in monster with random modifiers. -2/19/15

- [x] Change level ups to be you can place any amount of points in any stat. -2/20/15

- [x] Implenment a dungeon scene as main objective. -2/24/15

- [x] Random chance to run into monsters. -2/24/15

- [x] Save System - 2/27/15

- [x] Change healing to be done between monster fights rather than during.

###Short-Term

- [ ] Something that allows the monster or player to move first and chance to stun.

- [ ] More actions during a battle (no ideas on what).

- [ ] Redo the monster leveling up system (a bit wonky right now).

  - Might need to also redo entirely the damage and health calculation depending on what I end up changing.

- [ ] Redo leveling system to work off of experience, rather than dungeons completed.
  - So if I do this, the player would need a way to go back to fight weaker monsters if they find that they moved to the next dungeon too quickly.


- [ ] Doors are more than just a thing you can walk through.

  - Can smash door down, find key or pick the lock.
  
  - Some doors are locked, but not always, random chance.

###Long-term

- [ ] Add Pictures 

  - This is a real long term goal and will take a bit of work.
  
  - Start with monsters, move onto health bars then finally do the player.

- [ ] A looting system(?) 

  - Unsure of this one but I think it would be a cool idea.
  
- [ ] MORE LEVELS

  - Of course if I am going to add all this stuff I will need to extend the game to make it worth while.

- [ ] Line of sight, which causes the dungeon to be loaded as you see it.

- [ ] Monster spawn in when the dungeon is made, and you have to defeat them all before the stairs will appear.

- [ ] Items / inventory system.

- [ ] Magic system (?)
  - A common element in many rougelike games it might be worth looking into.

- [ ] Introduce a story line into it, likely just going to be super basic.

- [ ] An element weakness / strength factor.
  -Bascically every monster and attack has an element (fire, water, energy, etc...) and some are more resistive to some attacks then others. 
  - Likely won't be impleneted until after magic if I decide to add it.
