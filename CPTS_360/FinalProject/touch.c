void my_touch(char* file) {
    
	if (!strcmp(file, "")) { 
    	printf("my_touch(): No pathname entered\n");
   		return;
  	}

    int ino = getino(&dev, file); 

	if (ino != 0) { // if file already exists
    	MINODE *mip = iget(dev, ino); 
		INODE *ip = &mip->INODE; 

    	ip->i_atime = time(0L);
		ip->i_ctime = time(0L);
		ip->i_mtime = time(0L);
		mip->dirty = 1;
    	iput(mip);
	} else {
		creat_file(); 
	}

}

