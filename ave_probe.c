#include <IOKit/IOKitLib.h>
#include <stdio.h>

int main(void) {
    io_service_t service = IOServiceGetMatchingService(kIOMasterPortDefault, IOServiceMatching("com.apple.avevideoencoder"));
    if (!service) {
        printf("找不到AVEVideoEncoder服务\n");
        return 1;
    }
    io_connect_t conn;
    kern_return_t kr = IOServiceOpen(service, mach_task_self(), 0, &conn);
    if (kr == KERN_SUCCESS) {
        printf("✅ AVE服务打开成功\n");
        IOServiceClose(conn);
    } else {
        printf("❌ 打开失败，返回码: %x\n", kr);
    }
    IOObjectRelease(service);
    return 0;
}
