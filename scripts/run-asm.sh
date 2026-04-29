#!/usr/bin/env bash
set -euo pipefail

if [[ $# -lt 1 || $# -gt 2 ]]; then
  echo "Usage: $0 <program.s> [pc]"
  echo "  pc default: 0x80000000"
  exit 1
fi

src="$1"
pc="${2:-0x80000000}"

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
repo_root="$(cd "$script_dir/.." && pwd)"
emu="$repo_root/build/debug/rv32i"

if [[ ! -f "$src" ]]; then
  echo "error: source file not found: $src"
  exit 1
fi

if [[ ! -x "$emu" ]]; then
  echo "error: emulator not found at $emu"
  echo "run: ninja"
  exit 1
fi

tmpdir="$(mktemp -d)"
cleanup() {
  rm -rf "$tmpdir"
}
trap cleanup EXIT

src_abs="$(realpath "$src")"
base_name="$(basename "$src_abs" .s)"
out_dir="$repo_root/output"

mkdir -p "$out_dir"

riscv32-unknown-elf-as -march=rv32i "$src_abs" -o "$tmpdir/$base_name.o"
riscv32-unknown-elf-objcopy -O binary -j .text "$tmpdir/$base_name.o" "$tmpdir/image.bin"

(
  cd "$tmpdir"
  "$emu" image.bin "$pc"
)

cp "$tmpdir/memsave.bin" "$out_dir/$base_name.memsave.bin"
cp "$tmpdir/regsave.bin" "$out_dir/$base_name.regsave.bin"

echo "OK: ran $src_abs"
echo "saved: $out_dir/$base_name.memsave.bin"
echo "saved: $out_dir/$base_name.regsave.bin"
