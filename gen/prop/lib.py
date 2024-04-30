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

def columns(n: int, m: int) -> int:
	xs = list(set(functools.reduce(list.__add__, (
		[i, n // i] for i in range(1, int(n ** 0.5) + 1) if n % i == 0)
	)))
	for x in sorted(xs, reverse=True):
		y = 5
		y += x * m
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

def report_size(before: int, after: int) -> None:
	def btokib(n: int) -> str:
		s = str(round(n / 1024, 2))
		if s.endswith('.0'):
			s = s[:-2]
		return s + ' KiB'

	prefix = sys.argv[0].split('/')[-1]
	change = round((after - before) / before * 100, 1)
	before = btokib(before)
	after  = btokib(after)
	print(f'%s\t%s%%\t%s → %s' % (prefix, change, before, after), file=sys.stderr)
