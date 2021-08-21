
## How to Build
* Visit [Open weather](https://openweathermap.org/forecast16) and get a developer api key. 
* Download [QT Framework (Version 6.1.2)](https://www.qt.io/download) for your platform. Select the Open source installer. 
	* Select Qt version 6.1.2 during the installation process.  
> For linux OS, make sure your system is up to date by running 
> * sudo apt-get update
> * sudp apt-get install g++
Be sure to complete these two before running the installation process. 
* Clone the Repository to your local machine. 
* Open the Qt Creator, select file -> open project
	* navigate to the directory of this project.
	* navigate to `Headers/globals/Constants.h` and paste the obtained API key in the empty string assigned to the `const QString API_KEY`
	#### Running The Application
	##### Build Tool: qmake and make
	
* After building the project, you can run the app using the Qt Creator Run icon ▶️
* Or on your terminal you can run 
 > qmake QuickWeather.pro, then run
 > make
 > Run the generated QuickWeather executable. 
 
 ## Project Description
<img src="app_demo.gif" width="700" height="500" />

 QuickWeather is an application that displays some relevant weather information about place entered by the application user. 
 ### Requirements: 
 * Internet => The Application fetch the weather information from a remote server so internet is required for the application to work. 
 * Qt Framework => As described above, you will need to follow the setup above to run the application locally. 
 
 ### Architecture
 The Project is built using the [Model View Presenter(MVP)](https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93presenter) Architecture. 
 #### Project Files Description
 * **globals/** => Contains all global files like Constants and Util files.
	 * **apputil.h**  => Provides Calculation Utilities such as temperature converstion.
	 * **Constants.h** => Contains the _API_KEY_ global constant field and other constant fields like _SEARCHED_PLACE_TEXT_FILE_ for storing the file name of last searched place. 
	 * **Logger.h**=> An overloaded template `struct` that provides information Logging flexibilty, classified into `debug`, `warning` and `error`.
	 * **UrlBuilder.h**=> Helps to build the url path for getting the weather information for the entered place. 
	 
* **models/** => Contains all the App models used to represent different information as required. 
	* **City.h** => Represent the Searched Location information, such as City name, country and timezone. 
	* **WeatherObject.h** => This contains the weather information about the searched place such as Temperature and other weather contents like icon and description. 
	* **WeatherObjectResponse.h** => This is a composition of City object and WeatherObject. Aggrigating both to a single object. 
* **parser/** => Contains file for parsing the obtained QJsonObject to usable WeatherObjectResponse. 
	* **jsonobjectparser.h** => Every Model object has a mechanism for parsing it from QJsonObject, JsonObjectParser `struct` parses the obtained QJsonObject from the server to WeatherObjectResponse object. 
* **ui/** => The UI provides the mechanism for displaying the information to the user of QuickWeather app.
	[Remember the Architecture](https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93presenter) 
	* **WeatherSummaryView.h** => An abstraction that represents behavior of the UI. 
	*  **mainwindow.h, mainwindow.cpp** => This is implements WeatherSummaryView's pure virtual functions. It also knows about the view presenter, that is _WeatherSummaryPresenter_. 
	* **_NetworkReplyDeleteDelegate_** => This is a templated class used for cleaning the `QNetworkReplay*`. From [QFrameWork Documentation](https://doc.qt.io/qt-5/qnetworkreply.html), developers are responsible for cleaning up the `QNetworkReplay*`. 
	* **weathersummarypresenter.h, weathersummarypresenter.cpp** => Performs the UI logics such as
		* Saving last searched location
		* Provides logic for processing selected day so the information can be displayed as main. 
	* **mainwindow.ui**=> This is a form editor. Used for static design of the applicaiton user interface. 
* **_main.cpp_** => This is the entry point to the QT application. 

### Rubric Points
#### Loops, Functions I/O
In `WeatherResponse.h`, a for-loop is used to log every weather object to the console in the `toString()` function. 
The project is Architected using MVP Architecture. functions are organised withing classes. Check `WeatherSummaryPresenter`. 
The app takes input from the user (place) and displays the weather for the entered location. 
#### Object Oriented Programming
* The project uses Object Oriented Programming techniques. See `weathersummarypresenter.h` , `weathersummarypresenter.cpp ` `mainwindow.cpp`. 
* Classes use appropriate access specifiers for class members..
* Class constructors utilize member initialization lists, see `weathersummarypresenter.cpp`. 
* Classes abstract implementation details from their interfaces, see 	`mainwindow.h`.
* Classes encapsulate behavior. State is accessed via functions. See `weathersummarypresenter.h` and `weathersummarypresenter.cpp`. 
* Classes follow an appropriate inheritance hierarchy, see `WeatherSummaryView.h` and `mainwindow.h`.
* Overloaded functions allow the same function to operate on different parameters. See `Logger.h`. 
* Derived class functions override virtual base class functions. See `WeatherSummaryView.h`
* Templates generalize functions in the project, see `NetworkReplyDeleteDelegate.h`. 

#### Memory Management
* The project makes use of references in function declarations. See the models such as `City.h`.
* The project uses destructors appropriately. See `mainwindow.cpp` -> `MainWindow::~MainWindow()`. 
* The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. See `WeatherSummaryPresenter`. 
* The project follows the Rule of 5: For non Qt objects such as weathersummarypresenter.h rule of 5 is defined. Some rules set to default because the view object is a Qt object, manual copying is complicated and not needed. 
* The project uses move semantics to move data, instead of copying it, where possible, see `jsonobjectparser.h`.
* The project uses smart pointers instead of raw pointers, see `weathersummarypresenter.h`. 