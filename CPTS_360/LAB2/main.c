#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct NODE {

	char name[64];
	char type;
	struct NODE *childPtr, *siblingPtr, *parentPtr;

} NODE;

NODE *root, *cwd, *tempCwd;
FILE *fp;

char line[128];
char command[16], pathname[64];
char dirname[64], basename[64], relDirName[64], relBaseName[64];
char tempDir[128];

char *cmd[] = { "menu", "mkdir", "rmdir", "ls", "cd", "pwd", "creat", "rm", "reload", "save", "quit", 0 };

int findCmd(char *command);
void initialize();
void userInput();
void processUserInput(char *cmd, char *path);
void mkdir();
void mkdirAux(char *pathname, char type);
NODE *search(NODE *list, char *key);
int pwd();
int rpwd(NODE *p);
void cd();
NODE *cdAux(char *pathname, char *base);
void save();
void saveAux(NODE *list, FILE *fp);
void findRelativeBaseName(char *path);
int insertDir(NODE **list, NODE *p);
NODE *newNode(NODE *pCurr, char type);
void reload();
NODE *delete(NODE **list, char *key, char type);
void rmdir();
void rmdirAux(char *pathname, char type);
void ls();
void lsAux(char *pathname);
void menu();
void quit();
void rm();
void creat();

int main(int argc, char *argv []) 
{
	initialize();

	printf("Enter ? for help\n");

	while (1) 
    {
		printf("Command : ");

		userInput();

		void(*fptr[])() = { menu, mkdir, rmdir, ls, cd, pwd, creat, rm, reload, save, quit };

		int option = findCmd(command);

		if (option != -1) 
        {
			(*fptr[option])();

		} 
        else
        {
			printf("Invalid commmand\n");
		}
	}

	return 0;
}

void menu() {

	printf("\n==================== MENU ======================\n");
	printf("mkdir rmdir ls cd pwd creat rm reload save quit\n");
	printf("================================================\n");
}

void userInput() 
{
	memset(&line[0], 0, sizeof(line));
	memset(&command[0], 0, sizeof(command));
	memset(&pathname[0], 0, sizeof(pathname));

	fgets(line, 128, stdin);

	sscanf(line, "%s %s", command, pathname);

	if (strchr(pathname, '/'))
    {
		processUserInput(command, pathname);
	}

	else 
    {
		strcpy(basename, pathname);
		strcpy(dirname, "");
	}
}

void processUserInput(char *cmd, char *pathname) 
{
	char *temp = malloc(sizeof(char) * strlen(pathname) + 1);
	memset(&dirname[0], 0, sizeof(dirname));
	memset(&basename[0], 0, sizeof(basename));

	int index = 0;

	strcpy(temp, pathname);
	index = strrchr(temp, '/') - temp + 1;
	strncpy(dirname, temp, index);
	strcpy(basename, strrchr(temp, '/') + 1);

	free(temp);
}

void initialize() 
{
	char rootName[] = "/";

	root = (NODE *)malloc(sizeof(NODE));

	strcpy(root->name, rootName);
	root->type = 'D';
	root->siblingPtr = root;

	root->childPtr = 0;

	root->parentPtr = root;

	cwd = root;

	printf("Root initialized OK\n");
}

int findCmd(char *command)
{
	int i = 0;

	if (strcmp(command, "?") == 0) 
    {
		return 0;
	}

	while (cmd[i]) 
    {
		if (strcmp(command, cmd[i]) == 0)
        {
			return i;
        }

		i++;
	}
	return -1;
}

void mkdir() 
{
	if (strlen(pathname) > 0) 
    {
		mkdirAux(pathname, 'D');
	} 
    else 
    {
		printf("Invalid: Pathname not found\n");
	}

}

void mkdirAux(char *pathname, char type) 
{
	char temp[64];

	NODE *pCurr = 0, *pTemp = 0;

	strcpy(temp, pathname);

	char *token = 0;



	if (temp[0] == '/') 
    {
		pCurr = root->childPtr;

	} 
    else 
    {
		pCurr = cwd->childPtr;
	}



	if (strcmp(temp, "/") == 0) 
    {
		printf("Invalid: Cannot create another directory/file with root name\n");

	} 
    else if (root->childPtr == 0) 
    {
		root->childPtr = newNode(root, type);
	} 
    else if (strchr(temp, '/') == 0) 
    {
		pTemp = search(pCurr, basename);

		if (!pTemp || (pTemp->type != type && !search(pTemp->siblingPtr, basename))) 
        {
			insertDir(&(cwd)->childPtr, newNode(cwd, type));

		} 
        else 
        {
			if (type == 'D') 
            {
				printf("Invalid: Directory Name Already Exists\n");

			} 
            else 
            {
				printf("Invalid: File Name Already Exists\n");
			}
		}

	} 
    else 
    {
		findRelativeBaseName(pathname);

		token = strtok(temp, "/");

		while (token) 
        {
			pCurr = search(pCurr, token);

			if (strcmp(relBaseName, "") == 0) 
            {
				pTemp = search(pCurr, basename);

				if (!pTemp || (pTemp->type != type && !search(pTemp->siblingPtr, basename))) 
                {
					insertDir(&(root)->childPtr, newNode(root, type));
				} 
                else 
                {
					if (type = 'D') 
                    {
						printf("Invalid: Directory Name Already Exists\n");
					}
					else 
                    {
						printf("Invalid: File Name Already Exists\n");
					}
				}
				break;
			}

			if (pCurr == NULL) 
            {
				break;
			}
			if (strcmp(relBaseName, pCurr->name) == 0 && pCurr->type == 'D')
            {
				pTemp = search(pCurr, basename);

				if (!pTemp) 
                {
					insertDir(&(pCurr)->childPtr, newNode(pCurr, type));
				}

				else 
                {
					printf("Invalid: Directory Name Already Exists\n");
				}
				break;
			}

			if (pCurr->type == 'D') 
            {
				pCurr = pCurr->childPtr;

				token = strtok(NULL, "/");
			}

			else 
            {
				printf("Invalid: cannot insert a file into a file\n");

				break;
			}
		}
	}
}

void creat() 
{
	if (strlen(pathname) > 0) 
    {
		mkdirAux(pathname, 'F');
	} 
    else 
    {
		printf("Invalid: Pathname not found\n");
	}
}

void rmdir()
{
	if (strlen(pathname) > 0) 
    {
		rmdirAux(pathname, 'D');
	} 
    else 
    {
		printf("Invalid: Pathname not found\n");
	}
}

void rmdirAux(char *pathname, char type) 
{
	char temp[64];

	NODE *pCurr = 0;

	strcpy(temp, pathname);

	char *token = 0;

	if (temp[0] == '/') 
    {
		pCurr = root->childPtr;

	} 
    else 
    {
		pCurr = cwd->childPtr;
	}

	if (strcmp(temp, "/") == 0) 
    {
		printf("Invalid: Cannot delete root directory\n");

	} 
    else if (strchr(temp, '/') == 0) 
    {
		delete(&(cwd)->childPtr, basename, type);

	} 
    else 
    {
		findRelativeBaseName(pathname);

		token = strtok(temp, "/");

		while (token) 
        {
			pCurr = search(pCurr, token);

			if (strcmp(relBaseName, "") == 0) 
            {
				delete(&(root)->childPtr, basename, type);

				break;
			}

			if (pCurr == NULL) 
            {
				break;
			}

			if (strcmp(relBaseName, pCurr->name) == 0) 
            {
				delete(&(pCurr)->childPtr, basename, type);

				break;
			}

			pCurr = pCurr->childPtr;

			token = strtok(NULL, "/");
		}

		if (token == 0 && type == 'D') 
        {
			printf("Directory is not empty\n");

		} 
        else if (token == 0) 
        {
			printf("File not found\n");
		}
	}
}

void rm() 
{
	if (strlen(pathname) > 0) 
    {
		rmdirAux(pathname, 'F');
	} 
    else 
    {
		printf("Invalid: Pathname not found\n");
	}
}

NODE *delete(NODE **list, char *key, char type) 
{
	NODE *p, *q;

	p = search(*list, key);

	if (p == 0) 
    {
		printf("Pathname not found\n");

		return 0;
	}

	if (p->type != type) 
    {
		p = search(p->siblingPtr, key);
	}

	if (p == *list) 
    {
		if (p->childPtr == 0) 
        {
			*list = p->siblingPtr;

			free(p);
		} 
        else if (p->childPtr) 
        {
			printf("Directory is not empty\n");

			return 0;
		} 

	} 
    else 
    {
		q = *list;

		while (q->siblingPtr != p)
        {
			q = q->siblingPtr;
        }

		if (p->childPtr == 0) 
        {
			q->siblingPtr = p->siblingPtr;

			free(p);
		} 
        else if (p->childPtr) 
        {
			printf("Directory is not empty\n");

			return 0;
		} 
	}
	return p;
}

void findRelativeBaseName(char *path) 
{
	char temp[128] = { '\0' };

	char tempBase[128] = { '\0' };

	strcpy(temp, path);

	int index = 0;

	memset(&relBaseName[0], 0, sizeof(relBaseName));

	index = strrchr(temp, '/') - temp;

	strncpy(tempBase, temp, index);

	if (strcmp(tempBase,"") != 0) 
    {
		if (strchr(tempBase, '/')) 
        {
			index = strrchr(tempBase, '/') - tempBase;

			strcpy(relBaseName, &tempBase[index + 1]);
		} 
        else 
        {
			strcpy(relBaseName, tempBase);
		}

	} 
    else 
    {
		strcpy(relBaseName, "");
	}
}

NODE *newNode(NODE *pCurr, char type) 
{
	NODE *newNode;

	newNode = (NODE *)malloc(sizeof(NODE));

	strcpy(newNode->name, basename);

	newNode->childPtr = 0;

	newNode->siblingPtr = 0;

	newNode->parentPtr = pCurr;

	newNode->type = type;

	return newNode;
}

NODE *search(NODE *list, char *key) 
{
	NODE *p = list;

	while (p != NULL) 
    {
		if (strcmp(p->name, key) == 0) 
        {
			return p;

		} else 
        {
			p = p->siblingPtr;
		}
	}
	return 0;
}

int insertDir(NODE **list, NODE *p) 
{
	NODE *q = *list;

	if (q == 0) 
    {
		*list = p;
	} 
    else 
    {               
		while (q->siblingPtr)   

			q = q->siblingPtr;

		q->siblingPtr = p;     
	}
	p->siblingPtr = 0;       
}

void cd() 
{
	cdAux(pathname, basename);
}

NODE *cdAux(char *dir, char *base) 
{
	NODE *temp = 0;

	char *token = 0;

	if (dir[0] == '/') 
    {
		if (strcmp(dir, "/") == 0) 
        {
			cwd = root;

			return root;
		}

		token = strtok(++dir, "/");

		temp = root->childPtr;

		while (token || temp) 
        {
			temp = search(temp, token);			

			if (temp == NULL) 
            {
				return 0;
			} 

			if (strcmp(temp->name, base) == 0 && temp->type == 'D') 
            {
				cwd = temp;

				return temp;

			} 
            else if (strcmp(temp->name, base) == 0 && temp->type == 'F') 
            {
				temp = temp->siblingPtr;

			} 
            else 
            {
				token = strtok(NULL, "/");

				temp = temp->childPtr;
			}
		}

	} else if (strlen(dir) > 0 && dir[0] != '/') 
    {
		token = strtok(dir, "/");

		temp = cwd->childPtr;

		while (token || temp) 
        {
			temp = search(temp, token);

			if (temp == NULL) 
            {
				return 0;
			}

			if (strcmp(temp->name, base) == 0 && temp->type == 'D') 
            {
				cwd = temp;

				return temp;

			} 
            else if (strcmp(temp->name, base) == 0 && temp->type == 'F') 
            {
				temp = temp->siblingPtr;

			} 
            else 
            {
				token = strtok(NULL, "/");

				temp = temp->childPtr;
			}
		}

	} else 
    {
		cwd = root;
	}

	return temp;

}

int pwd() 
{
	memset(&tempDir[0], 0, sizeof(tempDir));

	rpwd(cwd);

	if (cwd == root) 
    {
		printf("%s\n", "/");

	} 
    else 
    {
		printf("%s\n", tempDir);
	}
}

int rpwd(NODE *p) 
{
	if (p == root) 
    {
		return 0;

	}
    else
    {
		rpwd(p->parentPtr);

		strcat(tempDir, "/");

		strcat(tempDir, p->name);
	}
}

void save() 
{
	FILE *fp = fopen("savefile.txt", "w+");

	fprintf(fp, "%c %s\n", root->type, root->name);

	saveAux(root->childPtr, fp);

	fclose(fp);
}

void saveAux(NODE *list, FILE *fp) 
{
	NODE *pCurr = list;

	if (!pCurr) 
    {
		return;
	}

	fprintf(fp, "%c ", pCurr->type);

	currDir(pCurr, fp);

	saveAux(pCurr->childPtr, fp);

	saveAux(pCurr->siblingPtr, fp);
}

int currDir(NODE *temp, FILE *fp) 
{
	memset(&tempDir[0], 0, sizeof(tempDir));

	rpwd(temp);

	if (temp == root) 
    {
		fprintf(fp, "%s\n", "/");
	}

	else 
    {
		fprintf(fp, "%s\n", tempDir);
	}
}

void ls() 
{
	lsAux(pathname);
}

void lsAux(char *pathname) 
{
	NODE *pCurr = 0, *pTemp = 0;

	/*

	if (pathname[0] == '/') {

		pCurr = root->childPtr;

	} else {

		pCurr = cwd->childPtr;

	}*/

	pTemp = cwd;

	if (strlen(basename) > 0) 
    {
		pCurr = cdAux(pathname, basename);
	}

	if (pCurr || cwd) 
    {
		pCurr = cwd->childPtr;

		while (pCurr) 
        {
			printf("%c %s\n", pCurr->type, pCurr->name);

			pCurr = pCurr->siblingPtr;
		}

		cwd = pTemp;

	} 
    else 
    {
		printf("Invalid: pathname not found\n");
	}
}

void reload() 
{
	char type[128], path[128];

	FILE *fp = fopen("savefile.txt", "r");

	while (fscanf(fp, "%s %s", type, path) != EOF) 
    {
		if (strcmp(path, "/") != 0) 
        {
			processUserInput("", path);

			mkdirAux(path, type[0]);
		}
	}
	fclose(fp);
}

void quit() 
{
    save();
	exit(0);
}