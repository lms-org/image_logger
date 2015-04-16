#include "image_logger.h"
#include "lms/datamanager.h"
#include "lms/imaging/pnm.h"

bool ImageLogger::initialize() {
    config = getConfig();

    std::string imageChannel = config->get<std::string>("image_channel");
    directory = config->get<std::string>("directory");
    format = config->get<std::string>("format");
    imageCounter = 0;

    if(directory.empty()) {
        logger.error("init") << "directory is empty";
        return false;
    }

    if(imageChannel.empty()) {
        logger.error("init") << "image_channel is empty";
        return false;
    }

    if(format.empty()) {
        logger.error("init") << "format was not specified";
        return false;
    } else if(format != "pgm" && format != "ppm") {
        logger.error("init") << "format must be either pgm or ppm";
        return false;
    }

    imagePtr = datamanager()->readChannel<lms::imaging::Image>(this, imageChannel);
    return true;
}

bool ImageLogger::deinitialize() {
    return true;
}

bool ImageLogger::cycle() {
    bool result;

    if(format == "pgm") {
        if(imagePtr->format() != lms::imaging::Format::GREY) {
            logger.error("cycle") << "Image is in format " << imagePtr->format()
                                  << " but expected " << lms::imaging::Format::GREY;
            return false;
        }

        result = lms::imaging::savePGM(*imagePtr,
            directory + "/image_" + std::to_string(imageCounter) + ".pgm");
    } else if(format == "ppm") {
        if(imagePtr->format() != lms::imaging::Format::RGB) {
            logger.error("cycle") << "Image is in format " << imagePtr->format()
                                  << " but expected " << lms::imaging::Format::RGB;
            return false;
        }

        result = lms::imaging::savePPM(*imagePtr,
            directory + "/image_" + std::to_string(imageCounter) + ".ppm");
    }

    if(! result) {
        logger.warn("cycle") << "Could not write image";
    }

    imageCounter++;
    return true;
}
