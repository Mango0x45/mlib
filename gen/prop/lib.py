import functools
import os
import sys
from pathlib import Path
from typing import Generator

def chunks[T](xs: list[T], n: int) -> Generator[list[T], None, None]:
	for i in range(0, len(xs), n):
		yield xs[i:i + n]

def powers_of_2() -> Generator[int, None, None]:
	i = 0
	while True:
		yield 2 ** i
		i += 1

def columns(n: int) -> int:
	xs = list(set(functools.reduce(list.__add__, (
		[i, n // i] for i in range(1, int(n ** 0.5) + 1) if n % i == 0)
	)))
	for x in sorted(xs, reverse=True):
		y = 5
		y += x * 5
		y += x - 1
		if y <= 80:
			return x

	raise ValueError

def isize(x: int) -> int:
	if x < 256:
		return 1
	if x < 65535:
		return 2
	if x < 4294967295:
		return 3
	if x < 18446744073709551615:
		return 4
	raise ValueError

def typename(x: int) -> str:
	if x < 256:
		return "uint8_t"
	if x < 65535:
		return "uint16_t"
	if x < 4294967295:
		return "uint32_t"
	if x < 18446744073709551615:
		return "uint64_t"
	raise ValueError

def cwd_init() -> None:
	dir = Path(os.path.dirname(sys.argv[0]))
	os.chdir(dir / '..' / '..')
