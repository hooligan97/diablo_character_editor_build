# Diablo Save Editor

This character editor will extract the hero from a save game and export it as json, it will also create a new save game from json.

Check out the [WASM demo](https://noctonic.github.io/diablo/)

Huge shout out to the folks at [DevilutionX](https://github.com/diasurgical/devilutionX) for all of their hard work. 


## Building


```
cmake -S . -B build
cmake --build build

# or just run make
```


output is `build/editor`.

### WebAssembly

```
emcmake cmake -S . -B build_wasm
cmake --build build_wasm --target d1_wasm
```

output is `d1_edit.js` and `d1_edit.wasm` 

## Usage

```
./editor savefile.sv [output.json] [--create] [--multi] [--spawn] [--hellfire]
```

