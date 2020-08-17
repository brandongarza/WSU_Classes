int my_open(char* pathname) {

	if (strlen(pathname) == 0) { // check if file name was entered in cmd
		printf("my_open(): need to enter pathname\n"); 
		return -1;
	}

	if (strlen(newFileName) == 0) { // check if mode was entered in cmd
		printf("my_open(): need to enter mode => 0|1|2|3 for R|W|RW|APPEND\n"); //you may use mode 0|1|2|3 for R|W|RW|APPEND
		return -1;
	}
	
    
    int ino = getino(&dev, pathname); // get ino of entered file name
	
    if (ino==0 && O_CREAT) { // from KC WANG book CH 11.5.4
        creat_file();
        ino = getino(&dev, pathname);
    }

	MINODE *mip = iget(dev, ino); // load INODE into memory
	
	if (!S_ISREG(mip->INODE.i_mode)) { // check mip->INODE.i_mode to verify it's not a REGULAR file
		printf("my_open(): must be REGULAR file type\n");
		iput(mip);
		return -1;
	}

    for(int i = 0; i < 16; i++) { // itterate through the running process file descriptor array  
		if (running->fd[i] != 0) {
			if (running->fd[i]->mptr == mip) { // check if that file is already opened
				if (running->fd[i]->mode > 0) { // check whether the file is ALREADY opened with INCOMPATIBLE mode: W, RW, APPEND
					printf("my_open(): file already opened with incompatible mode\n"); // if already open, reject
					return -1;
				}
			}
		}
	}

    OFT* oftp;
	oftp = malloc(sizeof(OFT)); // allocate free OpenFileTable (OFT) 
	int temp = falloc(oftp); // add to file descriptor array in current running process

	if (temp == -1) {
		printf("my_open(): OFT not allocated\n");
		return -1;
	}
   
    // and fill in values of allocated OFT
	oftp->mode = newFileName[0] - 48; // convert entered mode from char to int ('1' to 1)
	oftp->refCount = 1; 
	oftp->mptr = mip; // point at file's minode[]

	switch(newFileName[0] - 48) {
		case 0: oftp->offset = 0; // R: offset = 0
				break;
		case 1: truncate(mip); // W: truncate file to 0 size
				break;
		case 2: oftp->offset = 0; // RW: do NOT truncate
				break;
		case 3: oftp->offset = mip->INODE.i_size; // APPEND mode
				break;
		default: printf("invalid mode\n");
				 return -1;
	}

    for(int i = 0; i < 16; i++) { // find SMALLEST i in running PROC's fd[] such that fd[i] is NULL
        if(running->fd[i] == 0) {
            fd = i;
            break;
        }
        running->fd[i] = oftp->offset; // let running->fd[i] point at the OFT entry
    }

	// update INODE's time fields
	mip->INODE.i_atime = time(0L);
	mip->INODE.i_mtime = time(0L);
	mip->INODE.i_ctime = time(0L);

	mip->dirty = 1; // mark as dirty
	iput(mip);
	memset(newFileName, 0, 64); // reset input array, global
	return temp;

}
