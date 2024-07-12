## Do-It-Yourself simple hash-table

Inspired by university assignment mentioned in this [video](https://www.youtube.com/watch?v=kQsHF7C-FUY).
Although I ignored some key guidelines to organize the project given in the video, I've implemented hashtable interface with **template functions** and **rvalue-references** because I wanted to practise it.

[diy_hashtable/](https://github.com/AlekseyLapunov/Practise_cpp/tree/main/DIY_HashTable/diy_hashtable) is the catalog of "static header-only" library which contains hash-table implementation.

[Client/](https://github.com/AlekseyLapunov/Practise_cpp/tree/main/DIY_HashTable/Client) is the catalog of client that simply runs some code to interact with DIY hash-table.

There are two **template functions** that are used in the prototype of DIY hash-table class:
1. Hash-Function. **Input**: rvalue key. **Output**: size_t index.
2. Key-Validator-Function. **Input**: rvalue key. **Output**: bool isValid.
