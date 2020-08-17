int my_chdir(char *pathname) {

	int dev = 0;
	if (pathname[0] == '/') { // if pathname is absolute 
		dev = root->dev;
	} else { 
		dev = running->cwd->dev; // if pathname is relative
	}

	int ino = 0;
	if (pathname[0] != '\0') { 
		ino = getino(&dev, pathname);
	} else {
		ino = running->cwd->ino; 
	}
	
	if (ino == 0) { 
		printf("my_chdir(): pathname is invalid\n");
		return 0;
	}

	MINODE *mip = iget(dev, ino);

	if (S_ISDIR(mip->INODE.i_mode)) { 
		iput(running->cwd); 
		running->cwd = mip; 
	} else {
		printf("cd(): not valid DIR type\n");
		iput(mip);
	}
}
