// From CS360 lecture notes

int get_block(int fd, int blk, char buf[ ])
{
	lseek(fd, (long)blk * BLKSIZE, 0);
	read(fd, buf, BLKSIZE);
}

int put_block(int fd, int blk, char buf[ ])
{
	lseek(fd, (long)blk * BLKSIZE, 0);
	write(fd, buf, BLKSIZE);
}

int tst_bit(char *buf, int bit)
{
	int i, j;
	i = bit / 8; j = bit % 8;
	if (buf[i] & (1 << j))
		return 1;
	return 0;
}

int set_bit(char *buf, int bit)
{
	int i, j;
	i = bit / 8; j = bit % 8;
	buf[i] |= (1 << j);
}

int clr_bit(char *buf, int bit)
{
	int i, j;
	i = bit / 8; j = bit % 8;
	buf[i] &= ~(1 << j);
}

MINODE *iget(int dev, int ino)
{

	int i, blk, disp;
	char buf[BLKSIZE];
	MINODE *mip;
	INODE *ip;

	for (i = 0; i < NMINODE; i++) {
		mip = &minode[i];
		if ((mip->dev == dev) && (mip->ino == ino) && (mip->refCount)) {
			mip->refCount++;
			return mip;
		}
	}

	for (i = 0; i < NMINODE; i++) {
		mip = &minode[i];
		if (mip->refCount == 0) {
			mip->refCount = 1;
			mip->ino = ino; 
			mip->dev = dev;			
			mip->dirty = mip->mounted = mip->mptr = 0;
			blk  = (ino - 1) / 8 + iblock;
			disp = (ino - 1) % 8;
			get_block(dev, blk, buf);
			ip = (INODE *)buf + disp;
			mip->INODE = *ip;
			return mip;
		}
	}
	return 0;
}

int iput(MINODE *mip)
{

	int blk, disp;
	char buf[BLKSIZE];
	INODE *ip;

	mip->refCount--;

	if (mip->refCount > 0) {
		return;
	}

	if (!mip->dirty) {       
		return;
	}

	blk  = (mip->ino - 1) / 8 + iblock;
	disp = (mip->ino - 1) % 8;

	get_block(mip->dev, blk, buf);
	ip = (INODE *)buf + disp;
	*ip = mip->INODE;
	put_block(mip->dev, blk, buf);
}

int search(MINODE *mip, char *name)
{
	char buf[BLKSIZE];
	char namebuf[256];

	int blk = mip->INODE.i_block[0];

	if (blk == 0) {
		return 0;
	}

	get_block(mip->dev, blk, buf);
	char *cp = buf;
	dp = (DIR *)buf;

	while (cp < &buf[BLKSIZE]) {

		strncpy(namebuf, dp->name, dp->name_len);
		namebuf[dp->name_len] = 0;

		if (strcmp(name, namebuf) == 0) {
			return dp->inode;
		}
		cp += dp->rec_len;
		dp = (DIR*) cp;
	}
	return 0;
}

int tokenize(char *pathname)
{
	n = 0;
	name[n] = strtok(pathname, "/");
	while (1) {
		if (name[n] == NULL) { 
			break;
		}
		n++;
		if (n >= SIZEOFPATH) { 
			break;
		}
		name[n] = strtok(NULL, "/");
	}
}

int getino(int *dev, char *pathname)
{
	int i, ino, blk, disp;
	char buf[BLKSIZE];
	INODE *ip;
	MINODE *mip;

	if (strcmp(pathname, "/") == 0)
		return 2;

	if (pathname[0] == '/')
		mip = iget(*dev, 2);
	else
	{
		mip = iget(running->cwd->dev, running->cwd->ino);
	}

	strcpy(buf, pathname);
	tokenize(buf); 

	for (i = 0; i < n; i++) {
		ino = search(mip, name[i]);

		if (ino == 0) {
			iput(mip);
			return 0;
		}
		iput(mip);
		mip = iget(*dev, ino);

	}
	iput(mip);
	return ino;
}

int decFreeInodes(int dev)
{
  char buf[BLKSIZE];

  // decrement the free inodes count in SUPER and GD
  get_block(dev, 1, buf);
  sp = (SUPER *)buf;
  sp->s_free_inodes_count--;
  put_block(dev, 1, buf);

  get_block(dev, 2, buf);
  gp = (GD *)buf;
  gp->bg_free_inodes_count--;
  put_block(dev, 2, buf);
}

int incFreeInodes(int dev)
{
  char buf[BLKSIZE];

  // decrement the free inodes count in SUPER and GD
  get_block(dev, 1, buf);
  sp = (SUPER *)buf;
  sp->s_free_inodes_count++;
  put_block(dev, 1, buf);

  get_block(dev, 2, buf);
  gp = (GD *)buf;
  gp->bg_free_inodes_count++;
  put_block(dev, 2, buf);
}

int ialloc(int dev)
{
  int  i;
  char buf[BLKSIZE];

  get_block(dev, imap, buf);

  for (i = 0; i < ninodes; i++) {
    if (tst_bit(buf, i) == 0) {
      set_bit(buf, i);
      decFreeInodes(dev);

      put_block(dev, imap, buf);

      return i + 1;
    }
  }
  return 0;
}

int balloc(int dev)
{
  int  i;
  char buf[BLKSIZE];

  get_block(dev, bmap, buf);

  for (i = 0; i < nblocks; i++) {
    if (tst_bit(buf, i) == 0) {
      set_bit(buf, i);
      decFreeInodes(dev);

      put_block(dev, bmap, buf);

      return i + 1;
    }
  }
  return 0;
}

int idealloc(int dev, int ino)
{
  int  i;
  char buf[BLKSIZE];

  get_block(dev, imap, buf);

  i = ino - 1;

  if (tst_bit(buf, i) == 1) {
    clr_bit(buf, i);
    incFreeInodes(dev);

    put_block(dev, imap, buf);

    return i + 1;
  }
  return 0;
}

int bdealloc(int dev, int bno)
{
  int  i;
  char buf[BLKSIZE];

  get_block(dev, bmap, buf);

  i = bno - 1;

  if (tst_bit(buf, i) == 1) {
      clr_bit(buf, i);
      incFreeInodes(dev);

      put_block(dev, bmap, buf);

      return i + 1;
  }
  return 0;
}

int falloc(OFT* oftp) {

	for(int i = 0; i < 16; i++) {
		if (running->fd[i] == NULL) {
			break;
		}
	}
	if (i==16) {
		return -1;
	}
	running->fd[i]=oftp;
	return i;
}

int findmyname(MINODE *parent, int myino, char *myname)
{

	int i;
	INODE *ip;
	char buf[BLKSIZE];
	char *cp;
	DIR *dp;

	if(myino == root->ino)
	{
		strcpy(myname, "/");
		return 0;
	}

	if(!parent)
	{
		printf("ERROR: no parent\n");
		return 1;
	}

	ip = &parent->INODE;

	if(!S_ISDIR(ip->i_mode))
	{
		printf("ERROR: not directory\n");
		return 1;
	}

	for(i = 0; i < 12; i++)
	{
		if(ip->i_block[i])
		{
			get_block(dev, ip->i_block[i], buf);
			dp = (DIR*)buf;
			cp = buf;

			while(cp < buf + BLKSIZE)
			{
				if(dp->inode == myino)
				{
					strncpy(myname, dp->name, dp->name_len);
					myname[dp->name_len] = 0;
					return 0;
				}
				else
				{
					cp += dp->rec_len;
					dp = (DIR*)cp;
				}
			}
		}
	}
	return 1;
}

int findino(MINODE *mip, int *myino, int *parentino)
{

	INODE *ip;
	char buf[1024];
	char *cp;
	DIR *dp;

	if(!mip)
	{
		printf("ERROR: ino does not exist!\n");
		return 1;
	}

	ip = &mip->INODE;

	if(!S_ISDIR(ip->i_mode))
	{
		printf("ERROR: ino not a directory\n");
		return 1;
	}

	get_block(dev, ip->i_block[0], buf);
	dp = (DIR*)buf;
	cp = buf;

	//.
	*myino = dp->inode;

	cp += dp->rec_len;
	dp = (DIR*)cp;

	//..
	*parentino = dp->inode;

	return dp->inode;
}

int findCmd(char *command) {
	int i = 0;
	
	if (strcmp(command, "?") == 0) {
		return 0;
	}

	while (commands[i]) {
		if (strcmp(command, commands[i]) == 0)
			return i;
		i++;
	}
	return -1;
}

