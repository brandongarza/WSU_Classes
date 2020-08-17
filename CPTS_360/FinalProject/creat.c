int creat_file() {

	char temp[128], parent[128], child[128];
	
	if (pathname[0] == '/') { 
		dev = root->dev; 
	} else { 				  
		dev = running->cwd->dev; 
	}

	strcpy(temp, pathname); 
	char *pParent = dirname(temp); 
	strcpy(parent, pParent);

	strcpy(temp, pathname); 
	char *pChild = basename(temp);
	strcpy(child, pChild);

	int pino = getino(&dev, parent); 
	if (pino == 0) { 
		return 0;
	}

	MINODE *pmip = iget(dev, pino); 

	if (!S_ISDIR(pmip->INODE.i_mode)) { 
		return 0;
	}

	int cino = search(pmip, child); 

	if (cino != 0) {
		return 0;
	}

	my_creat(pmip, child);
	
	// dont increase parent's link count	

	INODE *pip = &pmip->INODE; 
	pip->i_atime = time(0L); 
	pip->i_ctime = time(0L); 
	pip->i_mtime = time(0L); 

	pmip->dirty = 1; 
	
	iput(pmip);
}

int my_creat(MINODE *pmip, char *myname) {
	
	char buf[BLKSIZE];
	char name[128];
	
	char *cp;
	DIR *dp;

	int ino = ialloc(dev); 
	MINODE *mip = iget(dev, ino); 
	INODE *ip = &mip->INODE;

	ip->i_mode = 0x81A4;		//0x81A4 OR 0100644
	ip->i_uid  = running->uid;	
	ip->i_gid  = running->gid;	
	ip->i_size = 0;		
	ip->i_links_count = 1;	    
	ip->i_atime = ip->i_ctime = ip->i_mtime = time(0L);  
	ip->i_blocks = 0;  
	ip->i_block[0] = 0;     
	for (int i = 1; i < 15 ; i++) { 
		ip->i_block[i] = 0;
	}

	mip->dirty = 1;              
	iput(mip); 

	enter_name(pmip, ino, myname);

}
