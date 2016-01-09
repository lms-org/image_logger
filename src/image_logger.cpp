#include "image_logger.h"
#include "lms/imaging/pnm.h"

bool ImageLogger::initialize() {
    if(! isEnableSave()) {
        logger.error() << "Command line option --enable-save was not specified";
        return false;
    }

    directory = saveLogDir("images");
    filepattern = config().get<std::string>("filepattern", "%04i");

    if(filepattern.empty()) {
        logger.error("init") << "Filepattern was not specified";
        return false;
    }

    logger.debug("init") << "Log images to " << directory;

    imagePtr = readChannel<lms::imaging::Image>("IMAGE");
    return true;
}

bool ImageLogger::deinitialize() {
    return true;
}

bool ImageLogger::cycle() {
    using lms::imaging::Format;

    bool result = false;

    char name[50];
    std::snprintf(name, sizeof(name), filepattern.c_str(), cycleCounter());
    std::string fullPath = directory + name;

    switch(imagePtr->format()) {
    case Format::GREY:
        result = lms::imaging::savePGM(*imagePtr, fullPath + ".pgm");
        break;
    case Format::RGB:
        result = lms::imaging::savePPM(*imagePtr, fullPath + ".ppm");
        break;
    default:
        logger.error("cycle")
            << "Image format is neither GREY nor RGB, but "
            << imagePtr->format();
        return false;
    }

    if(! result) {
        logger.warn("cycle") << "Could not write image";
        return false;
    } else {
        logger.debug("cycle") << "Wrote image: " << fullPath;
    }

    return true;
}
