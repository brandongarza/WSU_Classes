int pwd() {
		
	MINODE *mip = running->cwd; 
	
	if(mip == root) {
		printf("/\n");
		return;
	}
	
	rpwd(mip); 
	printf("\n");
    return 1;
}

void rpwd(MINODE *wd) {
	
	int ino, parent_ino;
	char name[128] = "";
	MINODE *mip = wd;

	if (wd == root) { // stop when at root
		return;
	}

	findino(mip, &ino, &parent_ino); // get ino of current directory and ino (pino) of its the parent directory 
	mip = iget(dev, parent_ino); 
	findmyname(mip, ino, name); 

	rpwd(mip); 
	printf("/%s", name); 
}
