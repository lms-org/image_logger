#include <image_logger.h>

extern "C" {
void* getInstance () {
    return new ImageLogger();
}
}
