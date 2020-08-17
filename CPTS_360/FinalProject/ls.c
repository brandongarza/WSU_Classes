int ls(char *pathname)  {

	int dev = 0;
	if (pathname[0] == '/') { 
		dev = root->dev;
	} else { 
		dev = running->cwd->dev; 
	}
	
	int ino = 0;
	if (pathname[0] == 0) { 
		ino = running->cwd->ino;
	} else {
		ino = getino(&dev, pathname); 
	}

	if (ino == 0) { 
		printf("ls(): %s invaid pathname\n", pathname); 
		return 0;
	}

	MINODE *mip = iget(dev, ino); 

	if (S_ISDIR(mip->INODE.i_mode)) {
		ls_dir(pathname, mip);
	} else {
		ls_file(ino, pathname);
	}
	iput(mip);

}

void ls_dir(char *pathname, MINODE *mip) {
	int block, ino;
	char *cp;	
	char buf[BLKSIZE], name[128];
	
	for (int i = 0; i < 12; i++) { 
		block = mip->INODE.i_block[i];  

		if (block == 0) { 
			return;
		}

		get_block(fd, block, buf); 

		cp = buf;
		DIR *dp = (DIR *)buf;

		while (cp < buf + BLKSIZE) {  

			strncpy(name, dp->name, dp->name_len);
			name[dp->name_len] = 0;

			ino = getino(&dev, name); 
			
			ls_file(ino, name); 

			cp += dp->rec_len;
			dp = (DIR*) cp;
		}
	}
}

int ls_file(int ino, char *pathname) {

	
	char *t1 = "xwrxwrxwr-------";
	char *t2 = "----------------";

	MINODE *mip = iget(dev, ino); 
	INODE *ip = &mip->INODE; 
	

	if (S_ISDIR(mip->INODE.i_mode)) { // if dir
		printf("%c", 'd');
	} else if (S_ISREG(ip->i_mode)) {   // if file
		printf("%c", '-');
	} else if (S_ISLNK(ip->i_mode)) {  // if link
		printf("%c", 'l');
	}
	
	for (int i = 8; i >= 0; i--) {  
		if (ip->i_mode & (1 << i)) { 
			printf("%c", t1[i]);
		} else {
			printf("%c", t2[i]);
		}
	}
	char time[128];
	strcpy(time, ctime(&mip->INODE.i_ctime)); // get time
	time[strlen(time) - 1] = '\0';

	printf(" %d %d %d %s %d %s\n", ip->i_links_count, ip->i_uid, ip->i_gid, time, ip->i_size, pathname);

	iput(mip); 
}



