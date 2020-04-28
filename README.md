# problematic
Prints randomly generated errors to the console. You can see it in action here: https://gracebuilds.internetpro.me

Compile it like this: `g++ -std=c++17 -O3 problematic.cpp -o problems`

It produces a LOT of output very fast, so it's best to pipe the output through `head` or `pv -L`. I usually run it like so:

```
./problems asdf | pv q -L 300
```

If you pass at least one argument to `problems`, it will use ANSI color codes to denote the different warning levels. It doesn't matter what that argument is.
