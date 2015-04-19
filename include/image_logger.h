#ifndef IMAGE_LOGGER_H
#define IMAGE_LOGGER_H

#include "lms/module.h"
#include "lms/type/module_config.h"
#include "lms/imaging/image.h"

class ImageLogger : public lms::Module {
public:
    bool initialize() override;
    bool deinitialize() override;
    bool cycle() override;
private:
    const lms::type::ModuleConfig *config;

    const lms::imaging::Image *imagePtr;

    std::string directory;

    // valid formats: pgm, ppm
    std::string format;

    /**
     * @brief Format string that is used together with snprintf
     * to produce the file names.
     */
    std::string filepattern;

    int imageCounter;
};

#endif /* IMAGE_LOGGER_H */
