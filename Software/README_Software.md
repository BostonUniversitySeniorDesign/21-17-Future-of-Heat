# SOFTWARE REPORT

This documents the web application and Arduino codes used in the Future Of Heat Project.

# Web Application

The web application is the user interface resonsible for the interaction between the user and the diorama.

### Front-End Development

* CSS - Style

## Installation

 We used [Google's Firbase](https://firebase.google.com) to handle hosting and realtime database. The web applications stores the electric homes, electric vehicle and weather range
using the [Firebase Realtime Database](https://firebase.google.com/products/realtime-database). The Firebase database is structured as a JSON tree with four main parents:

    * electric_homes
    * electric_vehicles
    * homes
    * weather


### Setup and configure Firebase
Create an account at https://firebase.google.com/

    * After setting up your new project, it will display all the initialization code you need to get started, for example :

        
        <script>// Your web app's Firebase configuration
        // For Firebase JS SDK v7.20.0 and later, measurementId is optional
        var firebaseConfig = {
            apiKey: "AIzaSyCtjVPCkMEUtS4fd6zuc91DjEeeXi2ncL0",
            authDomain: "test-future-of-heat.firebaseapp.com",
            databaseURL: "https://test-future-of-heat-default-rtdb.firebaseio.com",
            projectId: "test-future-of-heat",
            storageBucket: "test-future-of-heat.appspot.com",
            messagingSenderId: "1019447598625",
            appId: "1:1019447598625:web:c3299f5ea4e0d20dd34d60",
            measurementId: "G-9ZXX8F0T40"
        };
        // Initialize Firebase
        firebase.initializeApp(firebaseConfig);
        firebase.analytics();</script>

    * Enable Firestore under console => Database
    * Set database permissions to enable read/write access for all users

