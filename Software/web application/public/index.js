
const home = document.getElementById("myHeat");
const vehicles = document.getElementById("myVehicles");
const weather = document.getElementById("myWeather");
const enterBtn = document.getElementById('enterBtn');
const startBtn = document.getElementById('startBtn');
const loadval = document.getElementById("answer");
const database = firebase.database();
const rootRef = database.ref();
var Load = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var Cost = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var CO2 = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var SUM = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var gas = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var ele = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var E = [20166, 20400 ,20634 ,20868 ,21102 ,21336 ,21570 ,21803 ,22037 ,22271 ,22505 ,22739 ,22973 ,23207 ,23441 ,23675 ,23909 ,24143 ,24377, 24610,24844];
var C = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var EM = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];

var energy_total = 0;
var titles = ["1", "2","3","4","5","6","7","8","9","10", "11","12"]
var adopted = 0;
var sum = 0;
/*function ReadLoad(){
     
     var text; 
     text = "<div class= \"w3-content w3-justify w3-text-grey w3-padding-64\"> The Load Output array [";
     for(i = 0; i < 12 ; i++) {
        var num = i + 1;
        var n = num.toString();
         var starCountRef = firebase.database().ref('homes/Load-' + n);
          starCountRef.on('value', (snapshot) => {
            const data = snapshot.val();
            Load[i] = data;

            if(i == 11){
                text += Load[i];
            }else{
                text += Load[i] + ",";
            }
            
          });
      }
    text += "]</div>";
    loadval.innerHTML = text;
}*/

function price(load, type1, type2){
  var cum_cost = (0.2318 * load * type2) + (0.7146 * load * type1);

  return cum_cost;
}
function energy_cons(h1,h2){
   var energy = (Math.pow(12, 2)/400)+((Math.pow(12, 2)/800) * h1 )+((Math.pow(12, 2)/2400) * h2) ;

   return energy;
}

function homeValue(no_home) {
    var x = (no_home / 100) * 12;
    return Math.floor(x);
}

function vehiclesValue(no_vehicles) {
    var y = (no_vehicles / 100) * 17;
    return Math.floor(y);
}

function weatherValue(temp) {
    if (temp >= 0 && temp < 10) {

        return 5;

    } else if (temp >= 10 && temp < 20) {

        return 4;

    } else if (temp >= 20 && temp < 30) {

        return 3;

    } else if (temp >= 30 && temp < 40) {

        return 2;

    } else if (temp >= 40 && temp < 50) {

        return 1;

    } else {

        return 0;

    } 
}

function getRandomInt(max) {
  return Math.floor(Math.random() * Math.floor(max)) + 1;
}

startBtn.addEventListener('click', (e) => {
    e.preventDefault();
    rootRef.child("electric_homes").set(0);
    rootRef.child("electric_vehicles").set(0);
    rootRef.child("weather").set(0);
    rootRef.child("active").set(0);
    
    for(i = 0; i < 12 ; i++) {
        var num = i + 1;
        var n = num.toString();
         var starCountRef = firebase.database().ref('homes/Load-' + n);
          starCountRef.set(0);
      }

});

enterBtn.addEventListener('click', (e) => {
    e.preventDefault();
    rootRef.child("electric_homes").set(homeValue(home.value));
    rootRef.child("electric_vehicles").set(vehiclesValue(vehicles.value));
    rootRef.child("weather").set(weatherValue(weather.value));
    rootRef.child("active").set(1);
    adopted = homeValue(home.value);
    var ind1 = [null, null, null, null,null, null, null, null, null, null, null, null];
    var ind2 = [null, null, null, null,null, null, null, null, null, null];
    var ind3 = [null, null, null, null,null, null, null, null, null, null];
    var index = home.value/5;
    ind1[index] = E[index];
     
    for(i = 0; i < 11 ; i++) {
        var num = i + 1;
        var n = num.toString();
         var starCountRef = firebase.database().ref('homes/Load-' + n);
         Load[i] = getRandomInt(3.5);
         starCountRef.set(Load[i]);
    }

        var starCountRef = firebase.database().ref('homes/Load-12');
         Load[i] = 6;
         starCountRef.set(Load[i]);
   
  
     for(i = 0; i < 11 ; i++) {
        var num = i + 1;
        var n = num.toString();
         var starCountRef = firebase.database().ref('homes/Load-' + n);
          starCountRef.on('value', (snapshot) => {
            const data = snapshot.val() * 10000;
            Load[i] = data;
            
            if(i < adopted){
              Cost[i] = price(data, 1, 0);
              CO2[i] = data * 0.91;
            } else{
              
              Cost[i] = price(data, 0, 1);
              CO2[i] = data * 1.21;

            }

            if (i < 11 && i > 0) {
              sum = sum + Cost[i];
              SUM[i] = sum;
            }
            
          });
      }

      var starCountRef = firebase.database().ref('homes/Load-12');
      starCountRef.on('value', (snapshot) => {
        const data = snapshot.val();
        Load[11] = data;

        if(i < adopted){
          Cost[i] = data * 0.2295;
          CO2[i] = data * 0.91;
        } else{
          
          Cost[i] = data * 0.5670;
          CO2[i] = data * 1.21;

        }

      });
    
   
    var chart = new Chartist.Bar('.campaign', {
        labels: ['1', '2', '3', '4', '5', '6','7', '8', '9', '10', '11', 'Hotel'],
          series: [CO2]
        }, {
          plugins: [
            Chartist.plugins.tooltip(),
            Chartist.plugins.ctAxisTitle({
              axisX: {
                axisTitle: 'House Unit',
                axisClass: 'ct-axis-title',
                offset: {
                  x: 0,
                  y: 30

                },
                textAnchor: 'middle'
              },
              axisY: {
                axisTitle: 'Emissions (in metric tons)',
                axisClass: 'ct-axis-title',
                offset: {
                  x: 0,
                  y: -15
                },
                textAnchor: 'middle',
                flipTitle: false
              }
            })
          ],
          seriesBarDistance: 10,
          fullWidth: true,
          width: 480,
          chartPadding: {
            right: 10,
            bottom: 10
          }
        },[
          ['screen and (max-width: 640px)', {
            seriesBarDistance: 5,
            axisX: {
              labelInterpolationFnc: function (value) {
                return value[0];
              }
            }
          }]
        ]);

    //var chart = [chart];

    var chart2 = new Chartist.Bar('.campaign1', {
      labels: ['1', '2', '3', '4', '5', '6','7', '8', '9', '10', '11', 'Hotel'],
        series: [Cost]
      }, {
        plugins: [
          Chartist.plugins.tooltip(),
          Chartist.plugins.ctAxisTitle({
            axisX: {
              axisTitle: 'House Unit',
              axisClass: 'ct-axis-title',
              offset: {
                x: 0,
                y: 30

              },
              textAnchor: 'middle'
            },
            axisY: {
              
              axisTitle: 'Cost ($)',
              axisClass: 'ct-axis-title',
              offset: {
                x: 0,
                y: -15
              },
              textAnchor: 'middle',
              flipTitle: false
            }
          })
      ],
        seriesBarDistance: 10,
        width: 480,
        chartPadding: {
          right: 10,
          bottom: 10,
          left: 25
        },
        axisY: {
          onlyInteger: true,
          scaleMinSpace: 20,
          labelInterpolationFnc: function(value) {

              return '$' + (value / 1) ;
          }
      }
      },[
        ['screen and (max-width: 640px)', {
          seriesBarDistance: 5,
          axisX: {
            labelInterpolationFnc: function (value) {
              return value[0];
            }
          }
        }]
      ]);

      chart2.on('draw', function(ctx) {
        
        if(ctx.type === 'bar') {
              ctx.element.attr({
              style: 'stroke:  ForestGreen'
          });
        }
      });
    //var chart1 = [chart1];

    var chart3 = new Chartist.Bar('.campaign2', {
      labels: ['1', '2', '3', '4', '5', '6','7', '8', '9', '10', '11', 'Hotel'],
        series: [Load]
      }, {
        plugins: [
          Chartist.plugins.tooltip(),
          Chartist.plugins.ctAxisTitle({
            axisX: {
              axisTitle: 'House Unit',
              axisClass: 'ct-axis-title',
              offset: {
                x: 0,
                y: 30

              },
              textAnchor: 'middle'
            },
            axisY: {
              axisTitle: 'Power (Mwh)',
              axisClass: 'ct-axis-title',
              offset: {
                x: 0,
                y: -15
              },
              textAnchor: 'middle',
              flipTitle: false
            }
          })
        ],
        seriesBarDistance: 10,
        width: 480,
        chartPadding: {
          right: 10,
          bottom: 10,
          left: 25
        }
      },[
        ['screen and (max-width: 640px)', {
          seriesBarDistance: 5,
          axisX: {
            labelInterpolationFnc: function (value) {
              return value[0];
            }
          },
          axisY: {
            labelInterpolationFnc: function(value) {

                return (value / 1) + 'KW';
            }
        }
        }]
    ]);
    chart3.on('draw', function(ctx) {
        
      if(ctx.type === 'bar') {
            ctx.element.attr({
            style: 'stroke:  Crimson'
        });
      }
    });
    



    for(j = 0 ; j < 11; j++){
        if(j < 6){
          
          C[j] = price((energy_cons(1,1) * j),1,0) + price((energy_cons(0,1) * (9-j)),0,1) + price((energy_cons(0,0) * 6),0,1);
          EM[j] = (0.81* energy_cons(1,1) * j) + (1.51* energy_cons(0,0) * (9-j)) + (1.51 * energy_cons(0,0) * 6);
        }else{
          
          C[j] = price((energy_cons(1,1) * j),1,0) + price((energy_cons(0,1) * (9-j)),0,1) + price((energy_cons(1,1) * 6),1,0) ;
          EM[j] = (0.81 * energy_cons(1,1) * j) + (1.51* energy_cons(0,0) * (9-j)) + (0.81 * energy_cons(0,0) * 6);
        }
    }
    var new_ind = (home.value-5)/5;
    if(home.value % 5 == 5){
      ind2[new_ind] = C[new_ind];
      ind3[new_ind] = EM[new_ind];
    }else{
      ind2[new_ind] = C[new_ind];
      ind3[new_ind] = EM[new_ind];
    }
    var chart4 = new Chartist.Line('.line1', {
        
        series: [E,ind1],
        labels: [0,5,10,15, 20, 25,30, 35, 40,45, 50, 55,60,65,70,75, 80,85, 90, 95,100]
      }, {
          low: 0,
          showArea: true,
          width: 800,
          color:'#581845',
          plugins: [
            Chartist.plugins.tooltip(),
            Chartist.plugins.ctThreshold({
              threshold: 23000
            }),
            Chartist.plugins.ctAxisTitle({
              axisX: {
                axisTitle: 'Adoption Rate',
                axisClass: 'ct-axis-title',
                offset: {
                  x: 0,
                  y: 40

                },
                textAnchor: 'middle'
              },
              axisY: {
                axisTitle: 'Peak Winter Demand (MW)',
                axisClass: 'ct-axis-title',
                offset: {
                  x: 0,
                  y: -10
                },
                textAnchor: 'middle',
                flipTitle: false,
                
              }
            })
          ],
          axisY: {
            onlyInteger: true,
            scaleMinSpace: 20,
            labelInterpolationFnc: function(value) {
                return  (value / 1);
            }
          },
          axisX: {
            labelInterpolationFnc: function(value, index) {
              return index % 2 === 0 ? value : null;
            }
          },
          chartPadding: {
            left: 30,
            right: 30,
            top: 0,
            bottom: 30
          }
    });

    chart4.on('draw', function(ctx) {
      
      if(ctx.type === 'point') {
          ctx.element.attr({
            style: 'stroke:  OrangeRed'
        });
        
      }else if(ctx.type === 'line') {
            ctx.element.attr({
            style: 'stroke:  OrangeRed'
        });
      }

      
    });

  
    var chart5 = new Chartist.Line('.line2', {
      labels: ['0%', '10%', '20%', '30%', '40%', '50%', '60%','70%', '80%', '90%', '100%'],
      series: [C,ind2]
    }, {
        low: 0,
        showArea: true,
        width: 480,
        color:'#581845',
        plugins: [
          Chartist.plugins.tooltip(),
          Chartist.plugins.ctAxisTitle({
            axisX: {
              axisTitle: 'Adoption Rate',
              axisClass: 'ct-axis-title',
              offset: {
                x: 0,
                y: 29

              },
              textAnchor: 'middle',
              
            },
            axisY: {
              axisTitle: 'Cost ($)',
              axisClass: 'ct-axis-title',
              offset: {
                x: 0,
                y: -15
              },
              textAnchor: 'middle',
              flipTitle: false
            }
          })
        ],
        chartPadding: {
          right: 10,
          bottom: 10,
          left: 25
      }
    });

    chart5.on('draw', function(ctx) {
        
      if(ctx.type === 'point') {
            ctx.element.attr({
            style: 'stroke:  OrangeRed'
        });
      }else if(ctx.type === 'line') {
            ctx.element.attr({
            style: 'stroke:  OrangeRed'
        });
      }
    });

    var chart6 = new Chartist.Line('.line3', {
      labels: ['0%', '10%', '20%', '30%', '40%', '50%', '60%','70%', '80%', '90%', '100%'],
      series: [EM, ind3]
    }, {
        low: 0,
        showArea: true,
        width: 480,
        color:'#581845',
        plugins: [
            Chartist.plugins.tooltip(),
            Chartist.plugins.ctAxisTitle({
              axisX: {
                axisTitle: 'Adoption Rate',
                axisClass: 'ct-axis-title',
                offset: {
                  x: 0,
                  y: 29
                },
                textAnchor: 'middle'
              },
              axisY: {
                axisTitle: 'Emissions (in metric tons)',
                axisClass: 'ct-axis-title',
                offset: {
                  x: 0,
                  y: -15
                },
                textAnchor: 'middle',
                flipTitle: false
              },
              chartPadding: {
                right: 10,
                bottom: 10,
                left: 25
            }
            })
        ],
        axisY: {
            onlyInteger: true,
            scaleMinSpace: 20,
            labelInterpolationFnc: function(value) {
                return (value / 1) ;
            }
        }
    });

    chart6.on('draw', function(ctx) {
        
      if(ctx.type === 'point') {
            ctx.element.attr({
            style: 'stroke:  OrangeRed'
        });
      }else if(ctx.type === 'line') {
            ctx.element.attr({
            style: 'stroke:  OrangeRed'
        });
      }
    });
});
