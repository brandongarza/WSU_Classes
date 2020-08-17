int my_quit()
{
	int i;
	MINODE *mip;
	for (i = 0; i < NMINODE; i++)
	{
		mip = &minode[i];
		if (mip->refCount > 0)
			iput(mip);
	}
	exit(0);
}
