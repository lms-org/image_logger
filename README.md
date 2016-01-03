# image_logger

Saves all images from a data channel into a directory on your local hard drive.

## Format
- If the image format is GREY then *.pgm files will be saved.
- If the image format is RGB then *.ppm files will be saved.
- All other image formats issue an error. Use image_converter to convert the image to either GREY or RGB.

## DataChannels
- **IMAGE** - Image to write into a file

## Config
- **filepattern** - Pattern to be used for file names. You can use all options of [printf](http://www.cplusplus.com/reference/cstdio/printf/) here. The images are enumerated in ascending order. Defaults to "%04i".

## Dependencies
- [imaging](https://github.com/syxolk/imaging)

## Recommended modules
- [image_converter](https://github.com/syxolk/image_converter) - to convert the image to another format before saving it
- [camera_importer](https://github.com/Phibedy/camera) - to get an image from a camera
