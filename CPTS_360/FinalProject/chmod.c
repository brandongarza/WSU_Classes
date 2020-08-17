void my_chmod(char *pathname) {
    char input[128], permission[128];
	memset(permission, 0, 128);
   
    int ino = getino(&dev, pathname);  
    MINODE* mip = iget(dev, ino); 

	sscanf(newFileName, "%s", permission); 

	int mode = permission[0] - 48 << 6;       
	mode |= permission[1] - 48 << 3;
	mode |= permission[2] - 48;

	mip->INODE.i_mode &= 0xFF000; 
	mip->INODE.i_mode |= mode; 

    mip->dirty = 1;  
    iput(mip);
}
