#ifndef _system_filesys_h
#define _system_filesys_h
/*
   Unix SMB/CIFS implementation.

   filesystem system include wrappers

   Copyright (C) Andrew Tridgell 2004

     ** NOTE! The following LGPL license applies to the replace
     ** library. This does NOT imply that all of Samba is released
     ** under the LGPL

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 3 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, see <http://www.gnu.org/licenses/>.

*/

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <sys/stat.h>

#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif

#ifdef HAVE_SYS_MOUNT_H
#include <sys/mount.h>
#endif

#ifdef HAVE_MNTENT_H
#include <mntent.h>
#endif

#ifdef HAVE_SYS_VFS_H
#include <sys/vfs.h>
#endif

#ifdef HAVE_SYS_ACL_H
#include <sys/acl.h>
#endif

#ifdef HAVE_ACL_LIBACL_H
#include <acl/libacl.h>
#endif

#ifdef HAVE_SYS_FS_S5PARAM_H
#include <sys/fs/s5param.h>
#endif

#if defined (HAVE_SYS_FILSYS_H) && !defined (_CRAY)
#include <sys/filsys.h>
#endif

#ifdef HAVE_SYS_STATFS_H
# include <sys/statfs.h>
#endif

#ifdef HAVE_DUSTAT_H
#include <sys/dustat.h>
#endif

#ifdef HAVE_SYS_STATVFS_H
#include <sys/statvfs.h>
#endif

#ifdef HAVE_SYS_FILIO_H
#include <sys/filio.h>
#endif

#ifdef HAVE_SYS_FILE_H
#include <sys/file.h>
#endif

#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#else
#ifdef HAVE_SYS_FCNTL_H
#include <sys/fcntl.h>
#endif
#endif

#ifdef HAVE_SYS_MODE_H
/* apparently AIX needs this for S_ISLNK */
#ifndef S_ISLNK
#include <sys/mode.h>
#endif
#endif

#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif

#ifdef HAVE_SYS_UIO_H
#include <sys/uio.h>
#endif

#if defined(HAVE_SYS_ATTRIBUTES_H)
#include <sys/attributes.h>
#elif defined(HAVE_ATTR_ATTRIBUTES_H)
#include <attr/attributes.h>
#endif

/* mutually exclusive (SuSE 8.2) */
#if defined(HAVE_ATTR_XATTR_H)
#include <attr/xattr.h>
#elif defined(HAVE_SYS_XATTR_H)
#include <sys/xattr.h>
#endif

#ifdef HAVE_SYS_EA_H
#include <sys/ea.h>
#endif

#ifdef HAVE_SYS_EXTATTR_H
#include <sys/extattr.h>
#endif

#ifdef HAVE_SYS_RESOURCE_H
#include <sys/resource.h>
#endif

#ifndef XATTR_CREATE
#define XATTR_CREATE  0x1       /* set value, fail if attr already exists */
#endif

#ifndef XATTR_REPLACE
#define XATTR_REPLACE 0x2       /* set value, fail if attr does not exist */
#endif

/* Some POSIX definitions for those without */

#ifndef S_IFDIR
#define S_IFDIR         0x4000
#endif
#ifndef S_ISDIR
#define S_ISDIR(mode)   ((mode & 0xF000) == S_IFDIR)
#endif
#ifndef S_IRWXU
#define S_IRWXU 00700           /* read, write, execute: owner */
#endif
#ifndef S_IRUSR
#define S_IRUSR 00400           /* read permission: owner */
#endif
#ifndef S_IWUSR
#define S_IWUSR 00200           /* write permission: owner */
#endif
#ifndef S_IXUSR
#define S_IXUSR 00100           /* execute permission: owner */
#endif
#ifndef S_IRWXG
#define S_IRWXG 00070           /* read, write, execute: group */
#endif
#ifndef S_IRGRP
#define S_IRGRP 00040           /* read permission: group */
#endif
#ifndef S_IWGRP
#define S_IWGRP 00020           /* write permission: group */
#endif
#ifndef S_IXGRP
#define S_IXGRP 00010           /* execute permission: group */
#endif
#ifndef S_IRWXO
#define S_IRWXO 00007           /* read, write, execute: other */
#endif
#ifndef S_IROTH
#define S_IROTH 00004           /* read permission: other */
#endif
#ifndef S_IWOTH
#define S_IWOTH 00002           /* write permission: other */
#endif
#ifndef S_IXOTH
#define S_IXOTH 00001           /* execute permission: other */
#endif

#ifndef O_ACCMODE
#define O_ACCMODE (O_RDONLY | O_WRONLY | O_RDWR)
#endif

#ifndef MAXPATHLEN
#define MAXPATHLEN 256
#endif

#ifndef SEEK_SET
#define SEEK_SET 0
#endif

#ifdef _WIN32
#define mkdir(d,m) _mkdir(d)
#endif

/*
   this allows us to use a uniform error handling for our xattr
   wrappers
*/
#ifndef ENOATTR
#define ENOATTR ENODATA
#endif


#if !defined(HAVE_XATTR_XATTR) || defined(XATTR_ADDITIONAL_OPTIONS)

ssize_t rep_getxattr (const char *path, const char *name, void *value, size_t size);
#define getxattr(path, name, value, size) rep_getxattr(path, name, value, size)
/* define is in "replace.h" */
ssize_t rep_fgetxattr (int filedes, const char *name, void *value, size_t size);
#define fgetxattr(filedes, name, value, size) rep_fgetxattr(filedes, name, value, size)
/* define is in "replace.h" */
ssize_t rep_listxattr (const char *path, char *list, size_t size);
#define listxattr(path, list, size) rep_listxattr(path, list, size)
/* define is in "replace.h" */
ssize_t rep_flistxattr (int filedes, char *list, size_t size);
#define flistxattr(filedes, value, size) rep_flistxattr(filedes, value, size)
/* define is in "replace.h" */
int rep_removexattr (const char *path, const char *name);
#define removexattr(path, name) rep_removexattr(path, name)
/* define is in "replace.h" */
int rep_fremovexattr (int filedes, const char *name);
#define fremovexattr(filedes, name) rep_fremovexattr(filedes, name)
/* define is in "replace.h" */
int rep_setxattr (const char *path, const char *name, const void *value, size_t size, int flags);
#define setxattr(path, name, value, size, flags) rep_setxattr(path, name, value, size, flags)
/* define is in "replace.h" */
int rep_fsetxattr (int filedes, const char *name, const void *value, size_t size, int flags);
#define fsetxattr(filedes, name, value, size, flags) rep_fsetxattr(filedes, name, value, size, flags)
/* define is in "replace.h" */

#endif /* !defined(HAVE_XATTR_XATTR) || defined(XATTR_ADDITIONAL_OPTIONS) */

#endif
