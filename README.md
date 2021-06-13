# RBImageProcessor
Framework to translate Braille documents into readable text

### How to develop this framework:
This framework needs other dependency, OpenCV.

Dependency download script has been prepared. Run this on terminal:

```
./Scripts/DownloadDependency.sh
```

### How to use this framework on other project:
on Cartfile, add following lines:

```
github "rickirby/RBImageProcessor" == 0.2.1
```

Then execute "carthage update --platform iOS" on terminal

Please expect longer time while building this framework on first time. It needs to download OpenCV framework. Just open carthage build log to see the progress.

Follow [this tutorial](https://www.raywenderlich.com/7649117-carthage-tutorial-getting-started) for adding carthage-generated framework to the project


### Current version:
0.2.1
