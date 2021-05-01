# SOFTWARE REPORT

This documents the web application and Arduino codes used in the Future Of Heat Project.

# Web Application

The web application is the user interface resonsible for the interaction between the user and the diorama.

## Front-End Development
The web application is a single-page wesite that consists of four sections:

* Home
* User Inputs
* Output graphs
* Trend charts

The [Chartist.js](https://gionkunz.github.io/chartist-js/) charting library built with SVG was used for the front-end chart generation because it provides responsive functions that enhance the user's experience.

###### Plugins
Some features for the charts aren't included in the main chartist.js file but we used plugins that were avaiable to add features like:

* Axis labels
    - This plugin allows the creation and placement of axis titles. The plugin will throw an error if it is applied to a chart that contains no axes, such as a Pie chart.

    In order to use it, you will need to include the excellent charting library Chartist.js in your page.

http://gionkunz.github.io/chartist-js/index.html
* Tooltips at data points
* Coloring above/below a threshold
Also, [W3Schools](https://www.w3schools.com/html/) is a web deveolper information website that is referenced on this app. The site provides a reference maunal covering many aspects of the web application HTML, CSS, JavaScript programming.

## Back-End Development

We used [Google's Firbase](https://firebase.google.com) to handle hosting and realtime database. The web applications stores the electric homes, electric vehicle and weather range
using the [Firebase Realtime Database](https://firebase.google.com/products/realtime-database). The Firebase database is structured as a JSON tree with four main parents:

*   electric_homes
*   electric_vehicles
*   homes
*   weather

Functions in index.js calculate the number of electric homes and electric vehicles using users percentage selection and the weather range using the outside temperature selection.

### Setup and configure Firebase
1.  Create an account at (https://firebase.google.com/)

2.  After setting up your new project, it will display all the initialization code you need to get started, for example :

        
        <script> // Your web app's Firebase configuration
           // For Firebase JS SDK v7.20.0 and later, measurementId is optional
           var firebaseConfig = {
               apiKey: "AIzaSyCtjVPCkMEUtS4fd6zuc91DjEeeXi2ncL0",
               authDomain: "test-future-of-heat.firebaseapp.com"
               databaseURL: "https://test-future-of-heat-default-rtdb.firebaseio.com",
               projectId: "test-future-of-heat",
               storageBucket: "test-future-of-heat.appspot.com",
               messagingSenderId: "1019447598625",
               appId: "1:1019447598625:web:c3299f5ea4e0d20dd34d60",
               measurementId: "G-9ZXX8F0T40"
           };

           // Initialize Firebase
           firebase.initializeApp(firebaseConfig);
           firebase.analytics();
        </script>


3.  Enable Firestore under console => Database
4.  Set database permissions to enable read/write access for all users

        {
          "rules": {
            ".read": true,
            ".write": true,
          },
        }

The /database.rules.json is a copy of the Firebase Realtime Database rules.

The web application uses plain javascript to wirte and read data from our dev-database.
Below is a snippet of the write and read code that are implemented in the index.js file when the 'Click to Start' and 'Enter' buttons are clicked:

When 'Click to Start' button is pressed all values in the database are reset to zero.

    const database = firebase.database();
    const rootRef = database.ref();
    startBtn.addEventListener('click', (e) => {
        e.preventDefault();
        rootRef.child("electric_homes").set(0);
        rootRef.child("electric_vehicles").set(0);
        rootRef.child("weather").set(0);
        
    
        for(i = 0; i < 12 ; i++) {
            var num = i + 1;
            var n = num.toString();
             var starCountRef = firebase.database().ref('homes/Load-' + n);
              starCountRef.set(0);
          }

    });

When 'Enter' button is pressed all values in the database are updated according to the users selection.

    enterBtn.addEventListener('click', (e) => {
        e.preventDefault();
        rootRef.child("electric_homes").set(homeValue(home.value));
        rootRef.child("electric_vehicles").set(vehiclesValue(vehicles.value));
        rootRef.child("weather").set(weatherValue(weather.value));
        rootRef.child("active").set(1);

    });

Essentially, the .ref() method gets you to the root of the database, and calling .child() creates a child key.

More information on how to initialize and work with Firbase for a web application can be found in [Firbase Documentation](https://firebase.google.com/docs/web/setup)

## Dependencies
