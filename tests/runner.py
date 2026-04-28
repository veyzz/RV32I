#!/usr/bin/env python3
"""
Each .s test file declares its spec via comment directives:

    # INIT_REG   <idx>  <value>
    # INIT_MEM   <addr> <u32>
    # EXPECT_REG <idx>  <value>
    # EXPECT_MEM <addr> <u32>
    # EXPECT_PC  <value>

Values can be decimal, hex (0x...), or negative.
"""
import glob
import os
import re
import shutil
import struct
import subprocess
import sys
import tempfile

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
EMU = os.path.join(REPO_ROOT, 'build', 'debug', 'rv32i')
ASM_DIR = os.path.join(REPO_ROOT, 'tests', 'asm')
BIN_DIR = os.path.join(REPO_ROOT, 'build', 'tests')

# REG_PC is printed twice (before and after the run) — keep the last
PC_RE = re.compile(r'^REG_PC:.*\|\s*(-?\d+)\s*$', re.MULTILINE)

DIRECTIVES = {'INIT_REG', 'INIT_MEM', 'EXPECT_REG', 'EXPECT_MEM', 'EXPECT_PC'}


def parse_directives(asm_path):
    spec = {
        'INIT_REG': {}, 'INIT_MEM': {},
        'EXPECT_REG': {}, 'EXPECT_MEM': {},
        'EXPECT_PC': None,
    }
    with open(asm_path) as fp:
        for line in fp:
            parts = line.split()
            if len(parts) < 3 or parts[0] != '#' or parts[1] not in DIRECTIVES:
                continue
            tag = parts[1]
            try:
                if tag == 'EXPECT_PC':
                    spec[tag] = int(parts[2], 0)
                else:
                    spec[tag][int(parts[2], 0)] = int(parts[3], 0)
            except (IndexError, ValueError):
                print(f'warn: malformed directive in {asm_path}: {line.strip()}',
                      file=sys.stderr)
    return spec


def run_test(name):
    spec = parse_directives(os.path.join(ASM_DIR, f'{name}.s'))
    work = tempfile.mkdtemp(prefix=f'rv32i-{name}-')
    try:
        mem_bin = os.path.join(work, 'mem.bin')
        shutil.copyfile(os.path.join(BIN_DIR, f'{name}.bin'), mem_bin)

        if spec['INIT_MEM']:
            with open(mem_bin, 'r+b') as fp:
                for addr, val in spec['INIT_MEM'].items():
                    fp.seek(addr)
                    fp.write(struct.pack('<I', val & 0xFFFFFFFF))

        regs = bytearray(128)
        for r, v in spec['INIT_REG'].items():
            struct.pack_into('<I', regs, r * 4, v & 0xFFFFFFFF)
        with open(os.path.join(work, 'regs.bin'), 'wb') as fp:
            fp.write(regs)

        proc = subprocess.run(
            [EMU, 'mem.bin', 'regs.bin', '0x0'],
            cwd=work, capture_output=True, text=True,
        )

        failures = []

        if spec['EXPECT_REG']:
            with open(os.path.join(work, 'regsave.bin'), 'rb') as fp:
                saved = fp.read()
            for r, exp in spec['EXPECT_REG'].items():
                got = struct.unpack_from('<I', saved, r * 4)[0]
                exp_u = exp & 0xFFFFFFFF
                if got != exp_u:
                    failures.append(f'x{r}: expected=0x{exp_u:08x} got=0x{got:08x}')

        if spec['EXPECT_MEM']:
            with open(os.path.join(work, 'memsave.bin'), 'rb') as fp:
                saved = fp.read()
            for addr, exp in spec['EXPECT_MEM'].items():
                got = struct.unpack_from('<I', saved, addr)[0]
                exp_u = exp & 0xFFFFFFFF
                if got != exp_u:
                    failures.append(f'mem[0x{addr:x}]: expected=0x{exp_u:08x} got=0x{got:08x}')

        if spec['EXPECT_PC'] is not None:
            matches = PC_RE.findall(proc.stdout)
            if not matches:
                failures.append('PC not found in emulator output')
            elif int(matches[-1]) != spec['EXPECT_PC']:
                failures.append(f'PC: expected={spec["EXPECT_PC"]} got={matches[-1]}')

        if failures:
            print(f'FAIL  {name}')
            for msg in failures:
                print(f'      {msg}')
            return False
        print(f'PASS  {name}')
        return True
    finally:
        shutil.rmtree(work, ignore_errors=True)


def main():
    if not os.path.exists(EMU):
        sys.exit(f'emulator not found at {EMU} — run: ninja')

    asm_files = sorted(glob.glob(os.path.join(ASM_DIR, '*.s')))
    failed = 0
    skipped = 0
    for asm in asm_files:
        name = os.path.splitext(os.path.basename(asm))[0]
        if not os.path.exists(os.path.join(BIN_DIR, f'{name}.bin')):
            print(f'SKIP  {name} (no binary — run: ninja)')
            skipped += 1
            continue
        if not run_test(name):
            failed += 1

    print('---')
    print(f'passed: {len(asm_files) - failed - skipped}  failed: {failed}  skipped: {skipped}')
    sys.exit(1 if failed or skipped else 0)


if __name__ == '__main__':
    main()
