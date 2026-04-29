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

## Run Custom ASM

For quick local experiments, use the helper script:

```bash
./scripts/run-asm.sh path/to/program.s
```

Optional custom start PC:

```bash
./scripts/run-asm.sh path/to/program.s 0x80000000
```

The script assembles `.s` into a flat image, runs the emulator, and saves:
- `output/<program>.memsave.bin`
- `output/<program>.regsave.bin`

Note: add `.word 0` at the end of your program to stop execution.

Example:

```bash
./scripts/run-asm.sh examples/asm/example_sum_1_to_10.s
```

Cleanup output manually:

```bash
rm -rf output/
```

## Tests

```bash
ninja test
```

`ninja test` assembles all files from `tests/asm/`, builds flat binaries in
`build/tests/`, runs them through `build/debug/rv32i`, and checks register /
memory / PC values declared in `# EXPECT_*` directives.
