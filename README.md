#QOmdb
A simple Qt/QML wrapper for the The Open Movie Database ( [OMDb API](http://www.omdbapi.com) ). 

#List of properties
* id
* title
* year
* plot { Short, Full }
* type { Movie, Series, Episode }
* returnType { Json, Xml }
* includeTomatoRatings

#Requirement
Qt >= 5.3 and C++11

#Building
* Clone
* Run qmake && make

#Use
* Copy directory **imports** to your project location  
* To make the engine to search for this module, add the path where the **imports** directory is using *addImportPath*.  
For eg. If the directory **imports** is at location */home/ashish/QOmdbTest* then, 
```
QQuickView view;
view.engine()->addImportPath("/home/ashish/QOmdbTest/imports");
view.setSource(QUrl(QStringLiteral("qrc:/example.qml")));
```

#Examples
```
QOmdb {
        id: omdb
        title: "Back to the Future"
        plot: QOmdb.Short

        onFinished: {
            if(isJson) {
                var data = JSON.parse(doc)
                for (var key in data) {
                    console.log("Key: ", key, "Value: ", data[key])
                }
            }
        }
    }
```

#License

MIT

#Contact
Feel free to contact me for any questions at ashishd157 at gmail.com
