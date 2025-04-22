#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>

#ifdef _WIN32
    #include <direct.h>
    #define GETCWD _getcwd
    #define PATH_MAX 260
#else
    #include <unistd.h>
    #include <limits.h>
    #include <sys/statvfs.h>
    #define GETCWD getcwd
#endif

// 获取文件系统信息的函数
void get_filesystem_info(const char* path) {
#ifdef _WIN32
    printf("在Windows系统上，我们无法使用标准C获取文件系统详细信息。\n");
    printf("如需此功能，请查看Windows特定版本的程序。\n");
#else
    struct statvfs fsinfo;
    if (statvfs(path, &fsinfo) == -1) {
        perror("获取文件系统信息失败");
        return;
    }
    
    printf("文件系统信息:\n");
    printf("- 块大小: %lu 字节\n", fsinfo.f_bsize);
    printf("- 最大文件名长度: %lu\n", fsinfo.f_namemax);
    printf("- 总块数: %lu\n", fsinfo.f_blocks);
    printf("- 空闲块数: %lu\n", fsinfo.f_bfree);
#endif
}

// 获取可移植的文件系统类型名称
const char* get_filesystem_type() {
#ifdef _WIN32
    return "Windows FS (可能是NTFS或FAT32)";
#elif defined(__APPLE__)
    return "macOS FS (可能是APFS或HFS+)";
#else
    return "Unix/Linux FS (可能是ext4、XFS等)";
#endif
}

int main() {
    // 文件路径
    const char* filename = "./C语言地址乃至文件存储寻址.md";
    
    // 获取当前目录
    char current_dir[PATH_MAX];
    if (GETCWD(current_dir, sizeof(current_dir)) == NULL) {
        perror("获取当前目录失败");
        return 1;
    }
    printf("当前目录: %s\n\n", current_dir);
    
    // 尝试打开文件
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("打开文件失败");
        return 1;
    }
    
    // 获取文件完整路径
    char full_path[PATH_MAX];
#ifdef _WIN32
    if (_fullpath(full_path, filename, PATH_MAX) == NULL) {
        perror("获取完整路径失败");
        fclose(file);
        return 1;
    }
#else
    char* result = realpath(filename, full_path);
    if (result == NULL) {
        perror("获取完整路径失败");
        fclose(file);
        return 1;
    }
#endif
    
    // 使用stat获取文件信息
    struct stat file_stat;
    if (stat(filename, &file_stat) != 0) {
        perror("获取文件状态失败");
        fclose(file);
        return 1;
    }
    
    // 打印文件信息
    printf("文件名: %s\n", filename);
    printf("完整路径: %s\n", full_path);
    printf("文件大小: %lld 字节\n", (long long)file_stat.st_size);
    
    // 获取文件的inode号（类似于文件ID）
    printf("inode号: %llu\n", (unsigned long long)file_stat.st_ino);
    
    // 打印文件的最后修改时间
    char time_str[100];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&file_stat.st_mtime));
    printf("最后修改时间: %s\n", time_str);
    
    // 文件权限
    printf("文件权限: %o\n", file_stat.st_mode & 0777);
    
    // 获取文件系统类型和信息
    const char* fs_type = get_filesystem_type();
    printf("\n文件系统类型: %s\n", fs_type);
    
    // 获取文件系统信息
    get_filesystem_info(full_path);
    
    // 比较文档描述的索引节点结构
    printf("\n与文档中描述的索引方式比较:\n");
    printf("文档描述了Unix风格的inode结构:\n");
    printf("- 直接块 (前6个块)\n");
    printf("- 一级间接块 (块号6-1029)\n");
    printf("- 二级间接块 (块号1030-1049605)\n\n");
    
    printf("不同操作系统的文件系统采用不同的索引方式:\n");
    
#ifdef _WIN32
    printf("- Windows系统常用NTFS或FAT文件系统:\n");
    printf("  * NTFS使用主文件表(MFT)记录而非inode\n");
    printf("  * 小文件直接存储在MFT记录中\n");
    printf("  * 大文件使用基于区段的分配和运行列表\n");
#elif defined(__APPLE__)
    printf("- macOS系统使用APFS或HFS+文件系统:\n");
    printf("  * 它们使用B-tree或B+tree索引结构\n");
    printf("  * 不使用文档中描述的间接块方式\n");
#else
    printf("- Linux/Unix系统使用ext4等文件系统:\n");
    printf("  * ext4确实使用类似的inode结构\n");
    printf("  * 但现代ext4使用更高效的extent方式而非间接块\n");
    printf("  * 只在特殊情况下才会回退到间接块方式\n");
#endif
    
    printf("\n总结: 文档中描述的是传统Unix文件系统(如早期ext2)的索引方式,\n");
    printf("      现代文件系统通常采用更高效的方法来管理大文件\n");
    
    fclose(file);
    return 0;
}