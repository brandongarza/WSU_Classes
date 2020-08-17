int my_rmdir() {
	
	char buf[BLKSIZE], child[128], tempname[128];
	char *cp;
	DIR *dp;

	int ino = getino(&dev, pathname);

	MINODE *mip = iget(dev, ino); 

	if (running->uid != 0) {
		if (running->uid != mip->INODE.i_uid) { 
			iput(mip);
			return -1;
		}
	}

	if (!S_ISDIR(mip->INODE.i_mode) || mip->refCount != 1 || mip->INODE.i_links_count > 2) {
		iput(mip);
		return -1;
	}

	int bno = mip->INODE.i_block[0]; 

	get_block(dev, bno, buf);

	cp = buf;
	dp = (DIR *)buf;

	if (strcmp(dp->name, ".") != 0) { 
		iput(mip);
		return -1;
	}

	cp += dp->rec_len;
	dp = (DIR *)cp;

	int pino = dp->inode; 
	if (strcmp(dp->name, "..") != 0 || dp->rec_len != 1012) { 
		iput(mip);
		return -1;
	}

	put_block(dev, bno, buf);

	for (int i = 0; i < 12; i++) {
		if (mip->INODE.i_block[i] != 0) {
			bdealloc(mip->dev, mip->INODE.i_block[i]);
		} 
	}

	idealloc(mip->dev, mip->ino); 

	MINODE *pip = iget(mip->dev, pino); 

	iput(mip); 

	strcpy(tempname, pathname);
	char *temp = basename(tempname);
	strcpy(child, temp);

	rm_child(pip, child); 

	pip->INODE.i_links_count--; 
	pip->INODE.i_atime = time(0L); 
	pip->INODE.i_mtime = time(0L); 
	pip->dirty = 1; 
	iput(pip);
	return 1;
}

int rm_child(MINODE *parent, char *name) {

	char buf[BLKSIZE], temp[128];
	char *cp;
	int bno;
	int temp_rec_len;
	DIR *tempDp;

	for (int i = 0; i < 12; i++) { 

		bno = parent->INODE.i_block[i];
		
		if (bno == 0) {
			break;
		}

		get_block(parent->dev, bno, buf);

		cp = buf;
		dp = (DIR *) cp;
		
		strncpy(temp, dp->name, dp->name_len);
		temp[dp->name_len] = 0;
		
		// 1st case if first entry in data block
		if (strcmp(temp, name) == 0) { 
			for (int j = i; j < 12; j++) {
				parent->INODE.i_block[j] = parent->INODE.i_block[j + 1];
			}
			bdealloc(dev, i);
			parent->INODE.i_size -= BLKSIZE; 
			put_block(parent->dev, bno, buf); 
			return 1;
		}

		// 2nd case if in the middle of a block
		while (cp + dp->rec_len < buf + BLKSIZE) {

			strncpy(temp, dp->name, dp->name_len);
			temp[dp->name_len] = 0;

			if (strcmp(temp, name) == 0) { 
				temp_rec_len = dp->rec_len; 
				char *dest = cp; 
				char *src = cp + dp->rec_len; 

				int k = 0;
				while (cp + dp->rec_len < buf + BLKSIZE) { 
					k += dp->rec_len;
					cp += dp->rec_len;
					dp = (DIR*)cp;
				}

				k += dp->rec_len;
				dp->rec_len += temp_rec_len; 

				memmove(dest, src, k); 

				put_block(parent->dev, bno, buf); 
				return 1;

			}

			tempDp = dp;

			cp += dp->rec_len;
			dp = (DIR *)cp;
		}

		strncpy(temp, dp->name, dp->name_len);
		temp[dp->name_len] = 0;
	
		// 3rd case if last entry in dir
		if (strcmp(temp, name) == 0) {

			int prev_ren_len = dp->rec_len;
			cp = cp - tempDp->rec_len;

			dp = (DIR *)cp;
			dp->rec_len += prev_ren_len;

			put_block(parent->dev, bno, buf);
			return 1;
		}
	}
}
