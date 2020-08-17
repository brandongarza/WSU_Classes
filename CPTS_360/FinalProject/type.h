/*	type.h for CS360 Project             */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ext2fs/ext2_fs.h>
#include <libgen.h>
#include <string.h>
#include <sys/stat.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// define shorter TYPES, save typing efforts
typedef struct ext2_group_desc  GD;
typedef struct ext2_super_block SUPER;
typedef struct ext2_inode       INODE;
typedef struct ext2_dir_entry_2 DIR;    // need this for new version of e2fs

SUPER *sp;
GD    *gp;
INODE *ip;
DIR   *dp;


#define BLKSIZE           1024
#define ISIZE              128
#define SIZEOFPATH 64
#define BBITMAP    3

#define BITS_PER_BLOCK    (8*BLOCK_SIZE)
#define INODES_PER_BLOCK  (BLOCK_SIZE/sizeof(INODE))

// Default dir and regulsr file modes
#define DIR_MODE          0040777 
#define FILE_MODE         0100644
#define SUPER_MAGIC       0xEF53
#define SUPER_USER        0

// Proc status
#define FREE              0
#define BUSY              1
#define READY             2

// Table sizes
#define NMINODE          64
#define NMOUNT            4
#define NPROC             2
#define NFD              16
#define NOFT             32

// In-memory inodes structure
typedef struct Minode{
  INODE INODE;
  int dev, ino;
  int refCount;
  int dirty;
  int mounted;
  struct mntable *mptr;
}MINODE;

// Open File Table
typedef struct Oft{
  int  mode;
  int  refCount;
  MINODE *mptr;
  int  offset;
}OFT;

// PROC structure
typedef struct Proc{
  int   uid;
  int   pid;
  int   gid;
  int   status;

  struct Minode *cwd;
  OFT   *fd[NFD];

  struct Proc *next;
  struct Proc *parent;
  struct Proc *child;
  struct Proc *sibling;
} PROC;

// Mount Table structure
typedef struct Mount{
        int    dev;   
        int    ninodes;
        int    nblocks;
        int    imap, bmap, iblk; 
        struct Minode *mounted_inode;
        char   name[256]; 
        char   mount_name[64];
} MOUNT;


// globals
MINODE minode[NMINODE];       
MINODE *root;                
PROC   proc[NPROC], *running; 
OFT    oft[NOFT];

int fd, dev;                              
int nblocks, ninodes, bmap, imap, iblock; 
int n, i, ino, bno;

char line[128], cmd[64], pathname[64], newFileName[64];
char buf[BLKSIZE];
char *name[SIZEOFPATH];
char *disk = "mydisk";

char *commands[] = { "quit", "mkdir", "creat", "rmdir", "link",
				"symlink", "unlink", "stat", "chmod", "touch", "open", "close", "ls", "cd", "pwd", 0 };


