// original game uses its own deterministic rng
// this is the decompiled version of it

static int weird_global = 1;

unsigned int random_unsigned_int()
{
	weird_global = weird_global * 214013 + 2531011;
	return weird_global >> 0x10 & 0x7fff;
}

int random_int()
{
	unsigned int uVar1;
	unsigned int uVar2;

	uVar1 = random_unsigned_int();
	uVar2 = random_unsigned_int();
	return uVar2 * ((-(unsigned int)((uVar1 & 1) != 0) & 2) - 1);
}

int random_int_in_range(int start, int end)
{
	int iVar1;
	int iVar2;

	do {
		do {
			iVar1 = random_int();
			iVar2 = iVar1 % (end - start);
		} while (iVar2 < start);
	} while (end < iVar2);

	return iVar2;
}
