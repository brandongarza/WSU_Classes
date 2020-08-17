int make_dir() {
	char temp[128], parent[128], child[128];
	
	if (pathname[0] == '/') { // if absolute pathname, set as root dev
		dev = root->dev;
	} else {
		dev = running->cwd->dev; // if relative, set as cwd dev
	}

	// given /a/b/c or a/b/c
	strcpy(temp, pathname); // make copy of pathname, to prevent from changing it
	char *pParent = dirname(temp); // i.e. parent= "/a/b" OR "a/b" 
	strcpy(parent, pParent);
	
    strcpy(temp, pathname); // make copy of pathname, to prevent from changing it
	char *pChild = basename(temp); // i.e. child = "c"
	strcpy(child, pChild);

	int pino = getino(&dev, parent); // get inode of parent
	if (pino == 0) { // verify parent inode is valid
		return 0;
	}

	MINODE *pmip = iget(dev, pino); // get parent MINODE

	if (!S_ISDIR(pmip->INODE.i_mode)) { // check if not DIR type
		iput(pmip);
		return 0;
	}

	int cino = search(pmip, child); // get child ino

	if (cino != 0) { // check child does NOT exists in the parent directory
		iput(pmip);
		return 0;
	}

	if (strcmp(child, "/") == 0) { // if child is root, exit
	
		iput(pmip);
		return 0;
	}

	mymkdir(pmip, child); // step 4

	INODE *pip = &pmip->INODE; 
	pip->i_links_count++; // inc parent inodes's link count by 1
	pip->i_atime = time(0L); // touch its atime 

	pmip->dirty = 1; // mark it DIRTY
	iput(pmip); // step 6
}


int mymkdir(MINODE *pmip, char *name) {
	
	char buf[BLKSIZE];
	char *cp;

	int ino = ialloc(dev); // allocate an inode and a disk block for the new directory;
	int bno = balloc(dev);

	
	//load the inode into a minode[] (in order to write contents to the INODE in memory).
	
	MINODE *mip = iget(dev, ino); //new mip for DIR

	
	INODE *ip = &mip->INODE; // get INODE

	// Write contents to mip->INODE to make it as a DIR.
	// FROM KC WANG LECTURE NOTES
	ip->i_mode = 0x41ED;		// OR 040755: DIR type and permissions
	ip->i_uid  = running->uid;	// Owner uid
	ip->i_gid  = running->gid;	// Group Id
	ip->i_size = BLKSIZE;		// Size in bytes
	ip->i_links_count = 2;	    // Links count=2 because of . and ..
	ip->i_atime = ip->i_ctime = ip->i_mtime = time(0L);  // set to current time
	ip->i_blocks = 2;           // LINUX: Blocks count in 512-byte chunks
	ip->i_block[0] = bno;       // new DIR has one data block
	for (int i = 1; i < 15 ; i++) {
		ip->i_block[i] = 0; // set i_block[i] = 0
	}

	mip->dirty = 1; // mark minode dirty
	
	iput(mip); // write the new INODE out to disk

	get_block(dev, bno, buf);
	cp = buf;
	DIR *dp = (DIR *)buf;

	// create data block for new DIR containing . and .. entries
	dp->inode = ino;
	dp->rec_len = 12;
	dp->name_len = 1;
	dp->name[0] = '.';

	cp += dp->rec_len;      
	dp = (DIR*)cp;        

	dp->inode = pmip->ino;
	dp->rec_len = 1012;
	dp->name_len = 2;
	dp->name[0] = '.';
	dp->name[1] = '.';

	put_block(dev, bno, buf); // write buf[ ] to the disk block bno

	enter_name(pmip, ino, name); // enter name ENTRY into parent's directory
}

int enter_name(MINODE *pmip, int myino, char *myname) {
	char buf[BLKSIZE];
	char name[256];
	
	char *cp;
	DIR *dp;
	
	INODE *pip = &pmip->INODE;

	int i;
	for (i = 0; i < 12; i++) { // assume: only 12 direct blocks

		if (pip->i_block[i] == 0) { // check if valid direct block
			break;
		}

		get_block(pmip->dev, pip->i_block[i], buf); // get parent's data block into a buf[]; 

		dp = (DIR *)buf;
		cp = buf;

		while ((cp + dp->rec_len) < buf + BLKSIZE) { // // step to LAST entry in block: int blk = parent->INODE.i_block[i];
    
			strncpy(name, dp->name, dp->name_len);
			name[dp->name_len] = 0;

			cp += dp->rec_len;
			dp = (DIR *)cp;
		}
		strncpy(name, dp->name, dp->name_len);
		name[dp->name_len] = 0;
		

		// From KC WANG Lecture notes
		int need_length = 4 * ((8 + strlen(myname) + 3) / 4);

		int ideal_len = 4 * ((8 + strlen(name) + 3) / 4);

		int remain = dp->rec_len - ideal_len;

		if (remain >= need_length) { // enter the new entry as the LAST entry and trim the previous entry to its IDEAL_LENGTH; 

			dp->rec_len = ideal_len;

			cp += dp->rec_len;
			dp = (DIR *)cp;

			dp->inode = myino;
			dp->name_len = strlen(myname);
			strcpy(dp->name, myname);
			dp->rec_len = remain;
		
			put_block(dev, pip->i_block[i], buf); // write block back
			return 1;
		}
	}
	
	// Reach here means: NO space in existing data block(s)
	// Allocate a new data block; INC parent's isze by 1024;
    // Enter new entry as the first entry in the new data block with rec_len=BLKSIZE.
	int bno = balloc(dev);
	pip->i_block[i] = bno;
	pip->i_size += BLKSIZE;
	pmip->dirty = 1;

	get_block(dev, bno, buf);
	cp = buf;
	dp = (DIR*)buf;

	dp->inode = myino;	
	dp->name_len = strlen(myname);
	strcpy(dp->name, myname);
	dp->rec_len = BLKSIZE;

	put_block(dev, bno, buf); // write block back

	return 1;

}

