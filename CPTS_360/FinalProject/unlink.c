void my_unlink(char *filename) {

	MINODE *mip, *pmip;
	char dirName[128], baseName[128];

    int ino = getino(&fd, filename); 
	if (ino <= 0) {
		printf("my_unlink(): file name does not exist\n"); 
		return;
	}
	
    mip = iget(dev, ino); 
    if (S_ISDIR(mip->INODE.i_mode)) { 
        iput(mip);
        printf("my_unlink(): Can't unlink DIR type\n");
        return;
    }

    mip->INODE.i_links_count--; 

    if (mip->INODE.i_links_count > 0) { 
        mip->dirty = 1;
    } else { 
        for (int i = 0; i <= 12; i++) { 
            if (mip->INODE.i_block[i] == 0) { 
                break;
            }
            bdealloc(mip->dev, mip->INODE.i_block[i]); 
        }
        idealloc(dev, ino); 
    }

    iput(mip); 

	strcpy(baseName, basename(filename)); 
    strcpy(dirName, dirname(filename)); 

    int pino = getino(&fd,dirName); 
    pmip = iget(dev, pino);

    rm_child(pmip, baseName); 

	pmip->INODE.i_links_count--; 
	pmip->INODE.i_atime = time(0L); 
	pmip->INODE.i_mtime = time(0L); 

    pmip->dirty = 1; 
    iput(pmip); 
}
