# To-Do
## Completed
* get it working
* make a nicer class-based structure
* add stats and levelling
* add random generator
* improve combat: chance to miss
## Features
* !saving and loading characters!
* add equipment (weapons, armour)
* add items (health potions, )
* add magic (spells)
* add a shop in town (health potions, magic scrolls, equipment upgrades)
* add different kinds of creatures to encounter
* add extra locations to adventure to, with different sets of creatures
* crafting of armour/weapons in town
* add a bounty board/minor quests
## Tech
* rewrite commands system to use reified method calls like [this (GPG)](http://gameprogrammingpatterns.com/command.html) and [this (MSDN)](https://docs.microsoft.com/en-us/dotnet/api/microsoft.extensions.commandlineutils.commandlineapplication?view=aspnetcore-1.1) (this will make 'help' command easier as we could just find commands applied to current state instead of manual)
* also try to improve state transitions (e.g. when the state changes to town from wilderness, show the same line about "you've come back to town" or whenever you go to the menu, always show "this is the menu" or something)
* add a system to read monsters from file, for easy configurability by eager players
* add networking, maybe (need to think about how this would work)
