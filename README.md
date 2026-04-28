# RV32I

Small RV32I emulator in C.

Main binary: `build/debug/rv32i`.

It reads memory and register dumps from files, starts execution from the PC you
pass in, then writes the final state to `memsave.bin` and `regsave.bin`.

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
./build/debug/rv32i <mem.bin> <regs.bin> <pc>
```

```bash
./build/debug/rv32i mem.bin regs.bin 0x0
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
