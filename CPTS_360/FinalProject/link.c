void my_link(char *source, char *destination) {

	MINODE *pip, *sip;
	char tempDir[128], fileName[128];
	int pino, sino;

    if (strlen(source) == 0) { 
        printf("my_link(): source invalid\n");
        return -1;
    }

    if (strlen(destination) == 0) { 
        printf("my_link(): destination invalid\n");
        return -1;
    }

    char *cp = strrchr(destination, '/');  
    if (cp != 0) {
        strcpy(tempDir, destination); 
		char *pParent = dirname(tempDir); 
		pino = getino(&fd, pParent); 
 		strcpy(tempDir, destination);
		char *pChild = basename(tempDir);
		strcpy(fileName, pChild); 
    } else {
		pino = running->cwd->ino; 
        strcpy(fileName, destination); 
    }
	

    if (pino == 0) { 
        printf("my_link(): parent dir doesn't exist\n");
        return -1;
    }

	sino = getino(&fd, source);

    if (sino == 0) { 
        printf("my_link(): source file doesn't exist\n");
        return -1;
    }

    sip = iget(fd, sino); 

    if (S_ISDIR(sip->INODE.i_mode)) { 
        iput(sip);
        printf("my_link(): link to DIR is NOT allowed\n");
        return -1; 
    }

    pip = iget(fd, pino); 
 
	int tmp = search(&pip->INODE, fileName); 
    if (tmp != 0) { 
        iput(sip);
        iput(pip);
        printf("my_link(): file name already exist\n");
        return -1; 
    }

	enter_name(pip, sino, fileName);

	sip->dirty = 1; 
    sip->INODE.i_links_count++; 
    iput(sip); 

    pip->dirty = 1; 
    pip->refCount++; 
    iput(pip); 

}




