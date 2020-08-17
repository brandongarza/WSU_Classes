int my_close(int fd) {
    
    
    if((fd < 0) || (fd >= 16)) { // verify fd is within range
        printf("my_close(): invalid fd value\n");
		return -1;
    }

    
    if(running->fd[fd] == NULL) { // verify running->fd[fd] is pointing at a OFT entry
        printf("my_close(): running->fd[fd] is not pointing at a OFT entry\n");
		return -1;
    }

	
    OFT* oftp = running->fd[fd]; // point at the open file table for given file descriptor number 
	running->fd[fd] = 0; // set the pointer pointing at the open file table for the current running process and given file descriptor number to null, "closing" it
	oftp->refCount--; // decrement open file table ref count
	if (oftp->refCount > 0) { // if not last user of this OFT entry
		return 0;
	}

	MINODE * mip;
	mip = oftp->mptr; //if last user of this OFT entry ==> dispose of the Minode[]
	iput(mip);

	return 0;
}
