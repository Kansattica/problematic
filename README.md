# problematic
Prints randomly generated errors to the console. You can see it in action here: https://problematic.internetpro.me

Compile it like this: `g++ -std=c++17 -O3 problematic.cpp -o problematic`

It produces a LOT of output very fast (upwards of 110 MiB/s on my machine), so it's best to pipe the output through `head` or `pv -L`. I usually run it like so:

```
./problematic asdf | pv -q -L 300
```

If you pass at least one argument to `problematic`, it will use ANSI color codes to denote the different warning levels. It doesn't matter what that argument is.
