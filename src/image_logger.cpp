#include "image_logger.h"
#include "lms/datamanager.h"
#include "lms/imaging/pnm.h"

bool ImageLogger::initialize() {
    config = getConfig();

    std::string imageChannel = config->get<std::string>("image_channel");
    directory = config->get<std::string>("directory");
    imageCounter = 0;

    if(directory.empty()) {
        logger.error("init") << "directory is empty";
        return false;
    }

    if(imageChannel.empty()) {
        logger.error("init") << "image_channel is empty";
        return false;
    }

    imagePtr = datamanager()->readChannel<lms::imaging::Image>(this, imageChannel);
    return true;
}

bool ImageLogger::deinitialize() {
    return true;
}

bool ImageLogger::cycle() {
    bool result = lms::imaging::savePGM(*imagePtr,
                                        directory + "/image_" + std::to_string(imageCounter) + ".pgm");

    if(! result) {
        logger.warn("cycle") << "Could not write image";
    }

    imageCounter++;
    return true;
}
