# Logger
The ultimate logger for your C++ projects. https://github.com/kaartine/Logger

Logger library has factory class that creates singleton instaces of output target implementations (Console & file outputs).
Logger support C style logging
```SLOGE("My log %s starts here", "blue");```
and C++ style (streams)
```log(Logs::ERROR) << "My C++ log" << std::endl;```

Logger can be expanded to support new output targets. Factory -class will then create the new instances.

## Known issues
* Multihreading is not tested very well. Sometimes traces might get mixed if there is lots of traffic.

## Dependencies
Logger depends on GTest library (https://github.com/google/googletest)

## Compiling
For building you will to have cmake installed. Also https connection to github is needed (GTest is automatically cloned during the build)
```
mkdir build
cd build
cmake ..
cmake --build . --config Release
```
Visual studio solution can be then found under build -folder.

## Run tests
```
ctest -C Release
```

## Example app
Code includes example application that introduces the features of the Logger -class.
Example app is called example_app.exe. It is located at build/Release/example_app.exe

# Ideas for further developement
* Add more trace levels
* Add empty trace macros to remove tracing at compile time
* Add multithread tests for Windows
* File name for file outputter could from environment variables or maybe from Windows register. It could also have some default location.
* Add feature to ctest that runs tests with Valgrind