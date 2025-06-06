# Fantasy-Arena-A-Modular-Battle-Game-C-
⚔️ Fantasy Console Battle Game
A console-based C++ game where legendary heroes like Warriors, Mages, and mythical characters face off in fantasy arenas like Fire, Ice, and Jungle. Featuring turn-based combat, unique special abilities, and animated colored output for immersive gameplay.

🎮 Game Features
💥 Multiple Characters: Warrior, Mage, and Legendary Character, each with unique abilities.

🌍 Arena Effects: Arenas provide buffs to attack, defense, or health.

🎯 Turn-Based Combat: Players alternate between attacking or using special powers.

🔥 Cooldown System: Prevents spamming of powerful moves.

📜 Battle Report Logger: Keeps track of every move and prints a battle summary.

🌈 Console Colors: Enhanced visuals using ANSI escape codes.

🛠️ Requirements
C++11 or higher

Terminal/console that supports ANSI escape sequences (e.g., Windows Terminal, Linux, macOS Terminal)

💡 On Windows, you might need to enable ANSI escape code support (or use an environment like Git Bash, WSL, or VS Code terminal).

📂 File Overview
File Name	Description
Source.cpp	Main source file with complete game logic

🚀 How to Run
🔧 Compile
g++ Source.cpp -o battle_game
▶️ Run
./battle_game
🧙‍♂️ Character Classes
Character	Description
Warrior	Balanced stats. Special: Strong melee smash.
Mage	Agile with magical attacks. Special: Turns invisible to dodge next attack.
Legendary	Strongest stats. Special: Heals themselves during battle.

🌋 Arena Types
Arena	Buff Applied
Fire	+10% Attack
Ice	+10% Defense
Jungle	+10% Health

(Current default arena is Fire)

🧠 Game Mechanics
Attack: Deals damage to opponent based on your attack stat minus their defense.

Special Ability: Powerful unique skill with a cooldown of 3 turns.

Buffs: Applied at the start of the game based on the selected arena.

Battle Logger: Logs and displays a turn-by-turn report at the end.

🎮 Sample Gameplay Flow
yaml
Copy
Edit
Choose your character:
  [1] Warrior
  [2] Mage
  [3] Legendary
Enter choice: 1

Choose opponent:
  [1] Warrior
  [2] Mage
  [3] Legendary
Enter choice: 2

Battle starts in Fire Arena!

Bob the Warrior's move!
Options:
  [1] Attack
  [2] Use Special
Choose: 2
Bob the Warrior does a big smash!
...
📦 Future Improvements
Multiplayer support

More arenas and abilities

Health bars / GUI version

📜 License
This project is provided for learning and educational purposes.
