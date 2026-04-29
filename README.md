# RV32I

Small RV32I emulator in C.

Main binary: `build/debug/rv32i`.

It reads a flat memory image, starts execution from `0x80000000` (or an
optional PC argument), then writes the final state to `memsave.bin` and
`regsave.bin`.

## Requirements
- `gcc` — builds the emulator.
- `ninja`
- `python3`
- RISC-V binutils:
  - `riscv32-unknown-elf-as`
  - `riscv32-unknown-elf-objcopy`

## Build

```bash
ninja
```

This builds `build/debug/rv32i` (default target).

## Run

```bash
./build/debug/rv32i <image.bin> [pc]
```

```bash
./build/debug/rv32i image.bin
```

Outputs:
- `memsave.bin`
- `regsave.bin`

## Tests

```bash
ninja test
```

`ninja test` assembles all files from `tests/asm/`, builds flat binaries in
`build/tests/`, runs them through `build/debug/rv32i`, and checks register /
memory / PC values declared in `# EXPECT_*` directives.
