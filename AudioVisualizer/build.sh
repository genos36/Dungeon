PROJECT_FOLDER=.

$PROJECT_FOLDER/cmake/update_extra.sh

cmake $PROJECT_FOLDER -DCMAKE_BUILD_TYPE=Release

cmake --build $PROJECT_FOLDER