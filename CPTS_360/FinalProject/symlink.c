int my_symlink(char *currPath, char *newPath) {

    char oldName[60], newName[60]; 
	char parent[60], child[60];

    strcpy(oldName, currPath); 
    strcpy(newName, newPath); 

	strcpy(parent, dirname(newPath)); 
    strcpy(child, basename(newPath)); 

    int oldIno = getino(&fd, oldName); 

    if(oldIno < 0) { 
        puts("my_symlink(): Source file doesn't exist.");
        return;
    }

    int pino = getino(&dev, parent); 
    MINODE *pmip = iget(dev, pino); 

    int temp = search(pmip, child); 

    if(temp > 0) { 
        iput(pmip);
        puts("my_symlink(): destination file already exists");
        return;
    }

    int ino = ialloc(dev); 

    MINODE *mip = iget(dev, ino); 
    INODE *ip = &mip->INODE; 

	ip->i_size = strlen(oldName);
    ip->i_uid = running->uid;   
    ip->i_gid = running->pid;  
    ip->i_mode = 0x0a1ff;       //SLINK permission
    strcpy((char*)(ip->i_block), currPath);
    ip->i_links_count = 1;
 
    ip->i_atime = time(0L);
	ip->i_ctime = time(0L);
	ip->i_mtime = time(0L);
    ip->i_blocks = 0;

    enter_name(pmip, ino, child); 

    mip->dirty = 1; 
    iput(mip); 

    pmip->dirty = 1; 
    iput(pmip); 
}

