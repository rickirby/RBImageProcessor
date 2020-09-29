BASEPATH=$(pwd)
DIRECTORY="$BASEPATH/Carthage/Build/iOS"

if [[ ! -d "$DIRECTORY" ]]
then
    echo "\033[0;33mCreating \033[0;32mCarthage/Build/iOS \033[0;33mdirectory..."
    mkdir $BASEPATH/Carthage
    mkdir $BASEPATH/Carthage/Build
    mkdir $DIRECTORY
fi

echo "\033[0;33mDownloading \033[0;32mOpenCV \033[0;33mframework..."
curl -L https://sourceforge.net/projects/opencvlibrary/files/3.4.6/opencv-3.4.6-ios-framework.zip/download --output $DIRECTORY/opencv2_framework.zip
unzip -q $DIRECTORY/opencv2_framework.zip -d $DIRECTORY
rm $DIRECTORY/opencv2_framework.zip
