#import <Foundation/Foundation.h>

extern int gulu_file_exists(const char* path);
extern DIR* gulu_opendir(const char* target_path);
extern int gulu_read_file(const char *target_path, char *buffer, size_t bufsize);
extern int gulu_write_file(const char *target_path, const char *data, size_t len);
extern int gulu_unlink_file(const char *target_path);

%hook NSFileManager
- (BOOL)fileExistsAtPath:(NSString *)path
{
    const char *cpath = [path UTF8String];
    if([path hasPrefix:@"/private/var"] || [path hasPrefix:@"/var/mobile"])
    {
        return gulu_file_exists(cpath);
    }
    return %orig;
}
%end

%hook open
int open(const char *path, int flags, ...)
{
    if(strstr(path,"/private/var") || strstr(path,"/var/mobile")){
        // 这里转发给Gulu，后续补全
        return -1;
    }
    return %orig;
}
%end
