// from KC WANG lecture notes
int init() {
    MINODE *mip;

    for (int i = 0; i < NMINODE; i++) // MINODE minode[64]; all with refCount=0
	{
        mip = &minode[i];
        mip->dev = mip->ino = 0;
        mip->refCount = 0;
        mip->mounted = 0;
        mip->mptr = 0;
    }

    for (int i = 0; i < NPROC; i++) // 2 PROCs, P0 with uid=0, P1 with uid=1, all PROC.cwd=0
    {
        running = &proc[i];
        running->uid = i;
        running->gid = i;
        running->pid = i + 1;
        running->cwd = 0;
        for (int j = 0; j < NFD; j++)
        {
            running->fd[j] = 0;
        }
    }

    root = 0; //set root=0
}

int mount_root() {

	dev = open(disk, O_RDWR);// open device for RW (get a file descriptor as dev for the opened device)
	fd = dev;
    if (dev < 0) {
        printf("mount_root(): could not open %s\n", disk);
        exit(1);
    }
    get_block(fd, 1, buf);
    sp = (SUPER *)buf;

    if (sp->s_magic != 0xEF53) { // read SUPER block to verify it's an EXT2 FS
        printf("mount_root(): not EXT2 FS type\n");
        exit(2);
    }

    ninodes = sp->s_inodes_count;
    nblocks = sp->s_blocks_count;
    get_block(fd, 2, buf);
    gp = (GD *)buf;
    bmap = gp->bg_block_bitmap;
    imap = gp->bg_inode_bitmap;
    iblock = gp->bg_inode_table;

    root = iget(dev, 2); /* get root inode */
	//proc[0].cwd = root; //set cwd of both p0 and p1 point at the root minode
	//proc[1].cwd = root;

    running = &proc[0]; // let running->p0
    running->cwd = iget(dev, 2); // set cwd as root
}
