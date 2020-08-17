void my_stat(char *file) {
    int ino = getino(&dev, file); // get ino of given file name
    MINODE *mip = iget(dev, ino); // load INDOE into memory 

	// print INODE information 
	printf("\ndev=%d\nino=%u\nuid=%d ", dev, ino, mip->INODE.i_uid); 
    printf("\ngid=%d\nmode= %x\nnlink=%lu\n", mip->INODE.i_gid, mip->INODE.i_mode, (unsigned long)mip->INODE.i_links_count);	
    printf("size=%d\ntime=%s\n", (int)mip->INODE.i_size, ctime(&mip->INODE.i_ctime));

    mip->dirty = 1; // mark as dirty
    iput(mip); // write INODE back to the disk
}
