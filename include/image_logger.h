#ifndef IMAGE_LOGGER_H
#define IMAGE_LOGGER_H

#include "lms/module.h"
#include "lms/imaging/image.h"

class ImageLogger : public lms::Module {
public:
    bool initialize() override;
    bool deinitialize() override;
    bool cycle() override;
private:
    lms::ReadDataChannel<lms::imaging::Image> imagePtr;

    std::string directory;

    /**
     * @brief Format string that is used together with snprintf
     * to produce the file names.
     */
    std::string filepattern;
};

#endif /* IMAGE_LOGGER_H */
